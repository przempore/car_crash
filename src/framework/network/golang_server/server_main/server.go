//go:generate protoc -I ../proto/ ../proto/car_crash.proto --go_out=plugins=grpc:car_crash

// Package main implements a server for Greeter service.
package main

import (
	"context"
	"fmt"
	"github.com/golang/protobuf/ptypes/empty"
	"google.golang.org/grpc"
	codes "google.golang.org/grpc/codes"
	status "google.golang.org/grpc/status"
	"log"
	"net"

	pb "../car_crash"
)

const (
	port = ":50051"
)

const (
	Black       = 0
	White       = 1
	Red         = 2
	Green       = 3
	Blue        = 4
	Yellow      = 5
	Magenta     = 6
	Cyan        = 7
	Transparent = 8
)

type Point struct {
	x float32
	y float32
}

type Rectangles struct {
	id uint32
}

type Vehicles struct {
	vehicles []uint32
}

type server struct {
	pb.UnimplementedCarCrashServer
	vehicles []Vehicles
}

func (s *server) GetNewId(ctx context.Context, req *empty.Empty) (*pb.Id, error) {
	fmt.Printf("\n\tGetNewId\n")
	return &pb.Id{Id: uint32(len(s.vehicles))}, nil
	//return nil, status.Errorf(codes.Unimplemented, "method GetNewId not implemented")
}

func (s *server) GetVehicles(ctx context.Context, req *empty.Empty) (*pb.Vehicles, error) {
	fmt.Printf("\n\tGetVehicles\n")
	return nil, status.Errorf(codes.Unimplemented, "method GetVehicles not implemented")
}

func (s *server) UpdateVehicle(ctx context.Context, req *pb.VehicleWithId) (*empty.Empty, error) {
	fmt.Printf("\n\tUpdateVehicle\n")
	return nil, status.Errorf(codes.Unimplemented, "method UpdateVehicle not implemented")
}

func (s *server) RegisterVehicle(ctx context.Context, req *pb.VehicleWithId) (*pb.Id, error) {
	fmt.Printf("\n\tRegisterVehicle\n")
	return nil, status.Errorf(codes.Unimplemented, "method RegisterVehicle not implemented")
}

func (s *server) UnregisterVehicle(ctx context.Context, req *pb.Id) (*pb.Id, error) {
	fmt.Printf("\n\tUnregisterVehicle\n")
	return nil, status.Errorf(codes.Unimplemented, "method UnregisterVehicle not implemented")
}

//func (s *server) GetNewId(ctx context.Context, req *empty.Empty) (*pb.Id, error) {
//fmt.Printf("\n\tGetNewId\n")
//return &pb.Id{Id: uint32(len(s.vehicles))}, nil
//return &pb.Id{Id: 32}, nil
//}

//func (s *server) GetVehicles(ctx context.Context, req *empty.Empty) (*Vehicles, error) {
//fmt.Printf("GetVehicles\n")
//return &pb.Vehicles{}
//return nil, status.Errorf(codes.Unimplemented, "method GetVehicles not implemented")
//}

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
