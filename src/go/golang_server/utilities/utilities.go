package utilities

import (
	pb "../car_crash"
)

type RectangleColor uint32

const (
	RectangleColor_Black       RectangleColor = 0
	RectangleColor_White       RectangleColor = 1
	RectangleColor_Red         RectangleColor = 2
	RectangleColor_Green       RectangleColor = 3
	RectangleColor_Blue        RectangleColor = 4
	RectangleColor_Yellow      RectangleColor = 5
	RectangleColor_Magenta     RectangleColor = 6
	RectangleColor_Cyan        RectangleColor = 7
	RectangleColor_Transparent RectangleColor = 8
)

type Point struct {
	X float32
	Y float32
}

type Rectangle struct {
	Id        uint32
	Position  Point
	Angle     float32
	Dimension Point
	Color     RectangleColor
	Origin    Point
}

func translateToCCColor(color pb.Rectangle_Color) RectangleColor {
	switch color {
	case pb.Rectangle_Black:
		return RectangleColor_Black
	case pb.Rectangle_White:
		return RectangleColor_White
	case pb.Rectangle_Red:
		return RectangleColor_Red
	case pb.Rectangle_Green:
		return RectangleColor_Green
	case pb.Rectangle_Blue:
		return RectangleColor_Blue
	case pb.Rectangle_Yellow:
		return RectangleColor_Yellow
	case pb.Rectangle_Magenta:
		return RectangleColor_Magenta
	case pb.Rectangle_Cyan:
		return RectangleColor_Cyan
	case pb.Rectangle_Transparent:
		return RectangleColor_Transparent
	}
	return RectangleColor_Transparent
}

func tranlateToGRPCColor(color RectangleColor) pb.Rectangle_Color {
	switch color {
	case RectangleColor_Black:
		return pb.Rectangle_Black
	case RectangleColor_White:
		return pb.Rectangle_White
	case RectangleColor_Red:
		return pb.Rectangle_Red
	case RectangleColor_Green:
		return pb.Rectangle_Green
	case RectangleColor_Blue:
		return pb.Rectangle_Blue
	case RectangleColor_Yellow:
		return pb.Rectangle_Yellow
	case RectangleColor_Magenta:
		return pb.Rectangle_Magenta
	case RectangleColor_Cyan:
		return pb.Rectangle_Cyan
	case RectangleColor_Transparent:
		return pb.Rectangle_Transparent
	}
	return pb.Rectangle_Transparent
}

func CopyToGrpc(r *Rectangle) *pb.Rectangle {
	var toReturn pb.Rectangle

	toReturn.Id = r.Id
	position := pb.Point{
		X: r.Position.X,
		Y: r.Position.Y,
	}
	toReturn.Position = &position
	toReturn.Angle = r.Angle
	dimension := pb.Point{
		X: r.Dimension.X,
		Y: r.Dimension.Y,
	}
	toReturn.Dimension = &dimension
	toReturn.Color = tranlateToGRPCColor(r.Color)
	origin := pb.Point{
		X: r.Origin.X,
		Y: r.Origin.Y,
	}
	toReturn.Origin = &origin

	return &toReturn
}

func CopyFromGrpc(req *pb.Rectangle) Rectangle {
	var toReturn Rectangle
	toReturn.Id = req.Id
	toReturn.Position.X = req.Position.X
	toReturn.Position.Y = req.Position.Y
	toReturn.Angle = req.Angle
	toReturn.Dimension.X = req.Dimension.X
	toReturn.Dimension.Y = req.Dimension.Y
	toReturn.Color = translateToCCColor(req.Color)
	toReturn.Origin.X = req.Origin.X
	toReturn.Origin.Y = req.Origin.Y

	return toReturn
}
