#include "rectangle.hpp"

namespace CC {

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "x: " << p.x << ", y: " << p.y;
  return os;
}

std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
  os << "id: " << r.id << ", position: {" << r.position << "}, "
     << r.angle << ", dimension: {" << r.dimension << "}, color: "
     << rectangle_color_dict.at(r.color)
     << ", origin: {" << origin << '}';
  return os;
}

::carcrash::Rectangle_Color translateToGrpcColor(Rectangle::Color color) {
  switch (color) {
    case Rectangle::Color::Black: return ::carcrash::Rectangle_Color::Rectangle_Color_Black;
    case Rectangle::Color::White: return ::carcrash::Rectangle_Color::Rectangle_Color_White;
    case Rectangle::Color::Red: return ::carcrash::Rectangle_Color::Rectangle_Color_Red;
    case Rectangle::Color::Green: return ::carcrash::Rectangle_Color::Rectangle_Color_Green;
    case Rectangle::Color::Blue: return ::carcrash::Rectangle_Color::Rectangle_Color_Blue;
    case Rectangle::Color::Yellow: return ::carcrash::Rectangle_Color::Rectangle_Color_Yellow;
    case Rectangle::Color::Magenta: return ::carcrash::Rectangle_Color::Rectangle_Color_Magenta;
    case Rectangle::Color::Cyan: return ::carcrash::Rectangle_Color::Rectangle_Color_Cyan;
    case Rectangle::Color::Transparent: return ::carcrash::Rectangle_Color::Rectangle_Color_Transparent;
  }

  return ::carcrash::Rectangle_Color::Rectangle_Color_Black;
}

Rectangle::Color translateToCCColor(::carcrash::Rectangle_Color color) {
  switch (color) {
    case ::carcrash::Rectangle_Color::Rectangle_Color_Black: return Rectangle::Color::Black;
    case ::carcrash::Rectangle_Color::Rectangle_Color_White: return Rectangle::Color::White;
    case ::carcrash::Rectangle_Color::Rectangle_Color_Red: return Rectangle::Color::Red;
    case ::carcrash::Rectangle_Color::Rectangle_Color_Green: return Rectangle::Color::Green;
    case ::carcrash::Rectangle_Color::Rectangle_Color_Blue: return Rectangle::Color::Blue;
    case ::carcrash::Rectangle_Color::Rectangle_Color_Yellow: return Rectangle::Color::Yellow;
    case ::carcrash::Rectangle_Color::Rectangle_Color_Magenta: return Rectangle::Color::Magenta;
    case ::carcrash::Rectangle_Color::Rectangle_Color_Cyan: return Rectangle::Color::Cyan;
    case ::carcrash::Rectangle_Color::Rectangle_Color_Transparent: return Rectangle::Color::Transparent;
  }

  return Rectangle::Color::Black;
}

::carcrash::Point createGrpcPoint(const Point& p) {
  ::carcrash::Point point;
  if (point.IsInitialized()) {
    point.set_x(p.x);
    point.set_y(p.y);
  }

  return point;
}

::carcrash::Rectangle copyToGrpc(const Rectangle& from) {
  ::carcrash::Rectangle to;

  to.set_id(from.id);
  to.set_angle(from.angle);
  to.set_color(translateToGrpcColor(from.color));
  auto position = createGrpcPoint(from.position);
  auto& mut_pos = *to.mutable_position();
  mut_pos = position;
  auto dimension = createGrpcPoint(from.dimension);
  auto& mut_dim = *to.mutable_dimension();
  mut_dim = dimension;

  return to;
}

Rectangle copyFromGrpc(const ::carcrash::Rectangle& from) {
  return {
      from.id(),
      {from.position().x(), from.position().y()},
      from.angle(),
      {from.dimension().x(), from.dimension().y()},
      translateToCCColor(from.color()),
      {from.origin().x(), from.origin().y()},
  };
}

}

