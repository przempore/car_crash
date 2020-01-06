package main

import (
	"context"
	"fmt"
	"github.com/golang/protobuf/ptypes/empty"
	"log"
	"time"

	pb "../car_crash"
	"google.golang.org/grpc"
)

const (
	address = "localhost:50051"
)

func main() {
	// Set up a connection to the server.
	conn, err := grpc.Dial(address, grpc.WithInsecure(), grpc.WithBlock())
	if err != nil {
		log.Fatalf("did not connect: %v", err)
	}
	defer conn.Close()
	c := pb.NewCarCrashClient(conn)

	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()
	id, err_1 := c.GetNewId(ctx, &empty.Empty{})
	if err_1 != nil {
		log.Fatalf("could not greet: %v", err_1)
	}
	fmt.Printf("id: %d\n", id)

	vehicles, err_3 := c.GetVehicles(ctx, &empty.Empty{})
	if err_3 != nil {
		log.Fatalf("could not greet: %v", err_3)
	}
	fmt.Printf("vehicles: %x\n", vehicles)

	_, err_4 := c.UpdateVehicle(ctx, &pb.VehicleWithId{})
	if err_4 != nil {
		log.Fatalf("could not greet: %v", err_4)
	}
	//fmt.Printf("id: %d\n", id)

	id_2, err_5 := c.RegisterVehicle(ctx, &pb.VehicleWithId{})
	if err_5 != nil {
		log.Fatalf("could not greet: %v", err_5)
	}
	fmt.Printf("id: %d\n", id_2)

	id_3, err_2 := c.UnregisterVehicle(ctx, &pb.Id{})
	if err_2 != nil {
		log.Fatalf("could not greet: %v", err_2)
	}
	fmt.Printf("id: %d\n", id_3)
}
