#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include <limits>

namespace CC {

struct Point {
  uint32_t x = std::numeric_limits<uint32_t>::infinity();
  uint32_t y = std::numeric_limits<uint32_t>::infinity();
};

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
};

}


#endif // RECTANGLE_HPP_