package utilities

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
