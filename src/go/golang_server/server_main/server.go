//go:generate protoc -I ../../../proto/ ../../../proto/car_crash.proto --go_out=plugins=grpc:../car_crash

// Package main implements a server for Greeter service.
package main

import (
	"fmt"
	"google.golang.org/grpc"
	"log"
	"net"

	pb "../car_crash"
	utils "../utilities"
)

const (
	port = ":50051"
)

func main() {
	lis, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	s := grpc.NewServer()
	carCrashServer := new(utils.Server)
	carCrashServer.Vehicles = make(map[uint32]utils.Rectangle)
	pb.RegisterCarCrashServer(s, carCrashServer)
	fmt.Printf("Serving at tcp%s", port)
	if err := s.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %v", err)
	}
}
