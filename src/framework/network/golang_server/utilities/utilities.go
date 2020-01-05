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
	x float32
	y float32
}

type Rectangle struct {
	id         uint32
	position   Point
	angle      float32
	dimension  Point
	color      RectangleColor
	origin     Point
	is_colided bool
}

func tranlateToCCColor(color pb.Rectangle_Color) RectangleColor {
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

func CopyFromGrpc(req *pb.Rectangle) Rectangle {
	var toReturn Rectangle
	toReturn.id = req.Id
	toReturn.position.x = req.Position.X
	toReturn.position.y = req.Position.Y
	toReturn.angle = req.Angle
	toReturn.dimension.x = req.Dimension.X
	toReturn.dimension.y = req.Dimension.Y
	toReturn.color = tranlateToCCColor(req.Color)
	toReturn.origin.x = req.Origin.X
	toReturn.origin.y = req.Origin.Y

	return toReturn
}
