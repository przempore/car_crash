package server_tests

import (
	pb "../golang_server/car_crash"
	utils "../golang_server/utilities"
	"fmt"
	"google.golang.org/grpc"
	"log"
	"net"
	//"os"
	"testing"
)

const (
	port = ":50051"
)

func TestTest(t *testing.T) {
	if 1 != 1 {
		t.Errorf("got '%d' want '%d'", 1, 1)
	}
}

func TestServer(t *testing.T) {
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

//func testMain(m *testing.M) {
//log.Println("Do stuff BEFORE the tests!")
//exitVal := m.Run()
//log.Println("Do stuff AFTER the tests!")

//os.Exit(exitVal)
//}
