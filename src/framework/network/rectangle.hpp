#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include <limits>
#include <unordered_map>
#include <string>

#include "car_crash.grpc.pb.h"

namespace CC {

struct Point {
  float x = std::numeric_limits<float>::infinity();
  float y = std::numeric_limits<float>::infinity();
};

std::ostream& operator<<(std::ostream& os, const Point& p);

struct Rectangle {
  enum class Color {
    Black,
    White,
    Red,
    Green,
    Blue,
    Yellow,
    Magenta,
    Cyan,
    Transparent,
  };

  uint32_t id = std::numeric_limits<uint32_t>::infinity();
  Point position;
  float angle = std::numeric_limits<float>::infinity();
  Point dimension;
  Color color = Color::Black;
  Point origin;
};

static const std::unordered_map<Rectangle::Color, std::string> rectangle_color_dict {
    {Rectangle::Color::Black, "Color::Black"},
    {Rectangle::Color::White, "Color::White"},
    {Rectangle::Color::Red, "Color::Red"},
    {Rectangle::Color::Green, "Color::Green"},
    {Rectangle::Color::Blue, "Color::Blue"},
    {Rectangle::Color::Yellow, "Color::Yellow"},
    {Rectangle::Color::Magenta, "Color::Magenta"},
    {Rectangle::Color::Cyan, "Color::Cyan"},
    {Rectangle::Color::Transparent, "Color::Transparent"},
};

std::ostream& operator<<(std::ostream& os, const Rectangle& r);

::carcrash::Rectangle_Color translateToGrpcColor(Rectangle::Color color);
Rectangle::Color translateToCCColor(::carcrash::Rectangle_Color color);
::carcrash::Point createGrpcPoint(const Point& p);
::carcrash::Rectangle copyToGrpc(const Rectangle& from);
Rectangle copyFromGrpc(const ::carcrash::Rectangle& from);

}  // namespace CC

#endif // RECTANGLE_HPP_

