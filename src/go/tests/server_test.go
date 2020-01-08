package server_tests

import (
	pb "../golang_server/car_crash"
	utils "../golang_server/utilities"
	"fmt"
	//"google.golang.org/grpc"
	//"log"
	//"net"
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

func TestCopyToGrpc(t *testing.T) {
	rectangeToTranslate := utils.Rectangle{
		Id: 42,
		Position: utils.Point{
			X: 123,
			Y: 321,
		},
		Angle: 42.1,
		Dimension: utils.Point{
			X: 432,
			Y: 987,
		},
		Color: utils.RectangleColor_Red,
		Origin: utils.Point{
			X: 765,
			Y: 567,
		},
	}
	got := utils.CopyToGrpc(&rectangeToTranslate)

	expected := &pb.Rectangle{
		Id: 42,
		Position: &pb.Point{
			X: 123,
			Y: 321,
		},
		Angle: 42.1,
		Dimension: &pb.Point{
			X: 432,
			Y: 987,
		}, Color: pb.Rectangle_Red,
		Origin: &pb.Point{
			X: 765,
			Y: 567,
		},
	}
	fmt.Printf("got: %+v\n", got)
	fmt.Printf("expected: %+v\n", expected)
	if got.Id != expected.Id ||
		got.Position.X != expected.Position.X ||
		got.Position.Y != expected.Position.Y ||
		got.Angle != expected.Angle ||
		got.Dimension.X != expected.Dimension.X ||
		got.Dimension.Y != expected.Dimension.Y ||
		got.Color != expected.Color ||
		got.Origin.X != expected.Origin.X ||
		got.Origin.Y != expected.Origin.Y {
		t.Errorf("got '%+v' want '%+v'", got, expected)
	}
}

func TestCopyFromGrpc(t *testing.T) {
	rectangeToTranslate := pb.Rectangle{
		Id: 42,
		Position: &pb.Point{
			X: 123,
			Y: 321,
		},
		Angle: 42.1,
		Dimension: &pb.Point{
			X: 432,
			Y: 987,
		},
		Color: pb.Rectangle_Yellow,
		Origin: &pb.Point{
			X: 765,
			Y: 567,
		},
	}
	got := utils.CopyFromGrpc(&rectangeToTranslate)

	expected := utils.Rectangle{
		Id: 42,
		Position: utils.Point{
			X: 123,
			Y: 321,
		},
		Angle: 42.1,
		Dimension: utils.Point{
			X: 432,
			Y: 987,
		}, Color: utils.RectangleColor_Yellow,
		Origin: utils.Point{
			X: 765,
			Y: 567,
		},
	}
	fmt.Printf("got: %+v\n", got)
	fmt.Printf("expected: %+v\n", expected)
	if got != expected {
		t.Errorf("got '%+v' want '%+v'", got, expected)
	}
}

//func TestServer(t *testing.T) {
//lis, err := net.Listen("tcp", port)
//if err != nil {
//log.Fatalf("failed to listen: %v", err)
//}
//s := grpc.NewServer()
//carCrashServer := new(utils.Server)
//carCrashServer.Vehicles = make(map[uint32]utils.Rectangle)
//pb.RegisterCarCrashServer(s, carCrashServer)
//fmt.Printf("Serving at tcp%s", port)
//if err := s.Serve(lis); err != nil {
//log.Fatalf("failed to serve: %v", err)
//}
//}
