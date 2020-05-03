package utilities

import (
	"context"

	"github.com/golang/protobuf/ptypes/empty"

	pb "../car_crash"
)

type Server struct {
	pb.UnimplementedCarCrashServer
	Vehicles map[uint32]Rectangle
}

func (s *Server) GetNewId(ctx context.Context, req *empty.Empty) (*pb.Id, error) {
	// fmt.Printf("\n\tGetNewId\n")
	return &pb.Id{Id: uint32(len(s.Vehicles))}, nil
}

func (s *Server) GetVehicles(ctx context.Context, req *empty.Empty) (*pb.Vehicles, error) {
	outVehicles := new(pb.Vehicles)
	for _, r := range s.Vehicles {
		outVehicles.Rectangles = append(outVehicles.Rectangles, CopyToGrpc(&r))
	}

	// fmt.Printf("\n\tGetVehicles\n")
	return outVehicles, nil
}

func (s *Server) UpdateVehicle(ctx context.Context, req *pb.VehicleWithId) (*empty.Empty, error) {
	// fmt.Printf("\n\tUpdateVehicle\n")

	s.Vehicles[req.Id.Id] = CopyFromGrpc(req.Rectangle)

	out := new(empty.Empty)
	return out, nil
}

func (s *Server) RegisterVehicle(ctx context.Context, req *pb.VehicleWithId) (*pb.Id, error) {
	rectangle := req.Rectangle
	newId := len(s.Vehicles)
	s.Vehicles[uint32(newId)] = CopyFromGrpc(rectangle)
	// fmt.Printf("RegisterVehicle | len(s.Vehicles): %d\n", len(s.Vehicles))
	return &pb.Id{Id: uint32(len(s.Vehicles))}, nil
}

func (s *Server) UnregisterVehicle(ctx context.Context, req *pb.Id) (*pb.Id, error) {
	delete(s.Vehicles, req.Id)
	// fmt.Printf("UnregisterVehicle | len(s.Vehicles): %d\n", len(s.Vehicles))
	return &pb.Id{Id: uint32(len(s.Vehicles))}, nil
}
