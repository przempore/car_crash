#include "rectangle_shape.hpp"

namespace Game::Wrappers {

    RectangleShape::RectangleShape(Size size)
            : shape_(sf::Vector2f(size.first, size.second)) {}

    void RectangleShape::setPosition(Size size) {
        shape_.setPosition({size.first, size.second});
    }

    RectangleShape::Size RectangleShape::getPosition() const {
        auto pos = shape_.getPosition();
        return {pos.x, pos.y};
    }

    void RectangleShape::setOrigin(Size size) {
        shape_.setOrigin({size.first, size.second});
    }

    RectangleShape::Size RectangleShape::getOrigin() const {
        auto origin = shape_.getOrigin();
        return {origin.x, origin.y};
    }

    RectangleShape::Size RectangleShape::getSize() const {
        auto size = shape_.getSize();
        return {size.x, size.y};
    }

    void RectangleShape::setFillColor(Color color) {
        shape_.setFillColor(color.getUnderlying());
    }

    Color RectangleShape::getFillColor() const {
        auto color = shape_.getFillColor();
        return Color(color);
    }

    float RectangleShape::getRotation() const { return shape_.getRotation(); }

    void RectangleShape::rotate(float r) { shape_.rotate(r); }

} // namespace Game::Wrappers
