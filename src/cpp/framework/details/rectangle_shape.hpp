#ifndef CAR_CRASH_SRC_DETAILS_RECTANGLE_SHAPE
#define CAR_CRASH_SRC_DETAILS_RECTANGLE_SHAPE

#include <SFML/Graphics/RectangleShape.hpp>
#include <string>
#include <utility>

#include "color.hpp"

namespace Game::Wrappers {

class RectangleShape {
 public:
  using Size = std::pair<float, float>;

 public:
  RectangleShape(Size size);
  ~RectangleShape() = default;
  RectangleShape() = delete;
  RectangleShape(RectangleShape const&) = delete;
  RectangleShape(RectangleShape&&) = delete;
  RectangleShape& operator=(RectangleShape const&) = delete;
  RectangleShape& operator=(RectangleShape&&) = delete;
  void setPosition(Size size);
  Size getPosition();
  void setOrigin(Size size);
  Size getSize() const;
  void setFillColor(Color color);
  float getRotation();
  void rotate(uint32_t r);

 private:
  sf::RectangleShape shape_;
};

}  // namespace Game::Wrappers

#endif  // CAR_CRASH_SRC_DETAILS_RECTANGLE_SHAPE
