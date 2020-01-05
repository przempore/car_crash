//go:generate protoc -I ../proto/ ../proto/car_crash.proto --go_out=plugins=grpc:car_crash

// Package main implements a server for Greeter service.
package main

import (
	"context"
	"fmt"
	"github.com/golang/protobuf/ptypes/empty"
	"google.golang.org/grpc"
	//codes "google.golang.org/grpc/codes"
	//status "google.golang.org/grpc/status"
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
	vehicles []utils.Rectangle
}

func (s *server) GetNewId(ctx context.Context, req *empty.Empty) (*pb.Id, error) {
	fmt.Printf("\n\tGetNewId\n")
	return &pb.Id{Id: uint32(len(s.vehicles))}, nil
}

func (s *server) GetVehicles(ctx context.Context, req *empty.Empty) (*pb.Vehicles, error) {
	fmt.Printf("\n\tGetVehicles\n")
	out := new(pb.Vehicles)
	return out, nil
}

func (s *server) UpdateVehicle(ctx context.Context, req *pb.VehicleWithId) (*empty.Empty, error) {
	fmt.Printf("\n\tUpdateVehicle\n")
	out := new(empty.Empty)
	return out, nil
}

func (s *server) RegisterVehicle(ctx context.Context, req *pb.VehicleWithId) (*pb.Id, error) {
	rectangle := req.Rectangle
	s.vehicles = append(s.vehicles, utils.CopyFromGrpc(rectangle))
	fmt.Printf("vehicles size: %d", len(s.vehicles))
	fmt.Printf("\n\tRegisterVehicle\n")
	return &pb.Id{Id: uint32(len(s.vehicles))}, nil
}

func (s *server) UnregisterVehicle(ctx context.Context, req *pb.Id) (*pb.Id, error) {
	fmt.Printf("\n\tUnregisterVehicle\n")
	return &pb.Id{Id: uint32(len(s.vehicles))}, nil
}

func main() {
	lis, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	s := grpc.NewServer()
	pb.RegisterCarCrashServer(s, &server{})
	fmt.Printf("Serving at tcp%s", port)
	if err := s.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %v", err)
	}
}
