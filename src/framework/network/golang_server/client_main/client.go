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
	id, err := c.GetNewId(ctx, &empty.Empty{})
	if err != nil {
		log.Fatalf("could not greet: %v", err)
	}
	fmt.Printf("id: %d\n", id)
}
