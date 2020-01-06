//go:generate protoc -I ../../../proto/ ../../../proto/car_crash.proto --go_out=plugins=grpc:../car_crash

// Package main implements a server for Greeter service.
package main

import (
	"context"
	"fmt"
	"github.com/golang/protobuf/ptypes/empty"
	"google.golang.org/grpc"
	"log"
	"net"

	pb "../car_crash"
	utils "../utilities"
)

const (
	port = ":50051"
)

type server struct {
	pb.UnimplementedCarCrashServer
	vehicles map[uint32]utils.Rectangle
}

func (s *server) GetNewId(ctx context.Context, req *empty.Empty) (*pb.Id, error) {
	fmt.Printf("\n\tGetNewId\n")
	return &pb.Id{Id: uint32(len(s.vehicles))}, nil
}

func (s *server) GetVehicles(ctx context.Context, req *empty.Empty) (*pb.Vehicles, error) {
	outVehicles := new(pb.Vehicles)
	for _, r := range s.vehicles {
		outVehicles.Rectangles = append(outVehicles.Rectangles, utils.CopyToGrpc(&r))
	}

	fmt.Printf("\n\tGetVehicles\n")
	return outVehicles, nil
}

func (s *server) UpdateVehicle(ctx context.Context, req *pb.VehicleWithId) (*empty.Empty, error) {
	fmt.Printf("\n\tUpdateVehicle\n")
	out := new(empty.Empty)
	return out, nil
}

func (s *server) RegisterVehicle(ctx context.Context, req *pb.VehicleWithId) (*pb.Id, error) {
	rectangle := req.Rectangle
	newId := len(s.vehicles)
	s.vehicles[uint32(newId)] = utils.CopyFromGrpc(rectangle)
	fmt.Printf("RegisterVehicle | len(s.vehicles): %d\n", len(s.vehicles))
	return &pb.Id{Id: uint32(len(s.vehicles))}, nil
}

func (s *server) UnregisterVehicle(ctx context.Context, req *pb.Id) (*pb.Id, error) {
	delete(s.vehicles, req.Id)
	fmt.Printf("UnregisterVehicle | len(s.vehicles): %d\n", len(s.vehicles))
	return &pb.Id{Id: uint32(len(s.vehicles))}, nil
}

func main() {
	lis, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	s := grpc.NewServer()
	carCrashServer := new(server)
	carCrashServer.vehicles = make(map[uint32]utils.Rectangle)
	pb.RegisterCarCrashServer(s, carCrashServer)
	fmt.Printf("Serving at tcp%s", port)
	if err := s.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %v", err)
	}
}
