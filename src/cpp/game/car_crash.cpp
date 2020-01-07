#define _USE_MATH_DEFINES
#include "car_crash.hpp"

#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <details/color.hpp>
#include <iostream>
#include <memory>

#include "collision_detection.hpp"

namespace {

constexpr float getAngle(float degrees) {
  return degrees * static_cast<float>(M_PI) / 180.f;
}

CC::Rectangle::Color toGrpcColor(Game::Wrappers::Color color) {
  switch (color.getUnderlying().toInteger()) {
    case 255:
      return CC::Rectangle::Color::Black;
    case 4294967295:
      return CC::Rectangle::Color::White;
    case 4278190335:
      return CC::Rectangle::Color::Red;
    case 16711935:
      return CC::Rectangle::Color::Green;
    case 65535:
      return CC::Rectangle::Color::Blue;
    case 4294902015:
      return CC::Rectangle::Color::Yellow;
    case 4278255615:
      return CC::Rectangle::Color::Magenta;
    case 16777215:
      return CC::Rectangle::Color::Cyan;
    case 0:
      return CC::Rectangle::Color::Transparent;
  }

  return CC::Rectangle::Color::Cyan;
}

sf::Color toSfColor(CC::Rectangle::Color color) {
  switch (color) {
    case CC::Rectangle::Color::Black:
      return sf::Color::Black;
    case CC::Rectangle::Color::White:
      return sf::Color::White;
    case CC::Rectangle::Color::Red:
      return sf::Color::Red;
    case CC::Rectangle::Color::Green:
      return sf::Color::Green;
    case CC::Rectangle::Color::Blue:
      return sf::Color::Blue;
    case CC::Rectangle::Color::Yellow:
      return sf::Color::Yellow;
    case CC::Rectangle::Color::Magenta:
      return sf::Color::Magenta;
    case CC::Rectangle::Color::Cyan:
      return sf::Color::Cyan;
    case CC::Rectangle::Color::Transparent:
      return sf::Color::Transparent;
  }

  return sf::Color::Magenta;
}

CC::Rectangle toCcRectangle(uint32_t id,
                            const Game::Wrappers::RectangleShape& r) {
  return {id,
          {r.getPosition().first, r.getPosition().second},
          r.getRotation(),
          {r.getSize().first, r.getSize().second},
          toGrpcColor(r.getFillColor()),
          {r.getOrigin().first, r.getOrigin().second}};
}

sf::RectangleShape toSfRectangle(CC::Rectangle r) {
  sf::RectangleShape ret(sf::Vector2f(r.dimension.x, r.dimension.y));
  ret.setFillColor(toSfColor(r.color));
  ret.setPosition(sf::Vector2f(r.position.x, r.position.y));
  ret.setRotation(r.angle);
  ret.setOrigin(sf::Vector2f(r.origin.x, r.origin.y));
  return ret;
}

const std::array COLORS = {
    //    sf::Color::Black,
    sf::Color::White,
    //    sf::Color::Red,
    sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta,
    sf::Color::Cyan,
    //    sf::Color::Transparent,

};

}  // namespace

namespace CC {

CarCrash::CarCrash(const std::string& ip)
    : rectangle_({120, 50}),
      rectangle_id_(std::numeric_limits<uint32_t>::infinity()),
      close_window_{false},
      moving_speed_{2.5f},
      moving_direction_{0},
      client_{ip} {
  rectangle_.setPosition({201, 221});
  rectangle_.setOrigin(
      {rectangle_.getSize().first / 4,  // TODO: x / 4 caused collision error
       rectangle_.getSize().second / 2});
}

void CarCrash::onStartup() {
  // 1. get all vehicles from server
  std::cout << __FILE__ << ':' << __LINE__ << " | " << __FUNCTION__
            << " | getVehicles\n";
  auto vehicles_from_server = client_.getVehicles();
  std::cout << __FILE__ << ':' << __LINE__ << " | " << __FUNCTION__
            << " | end getVehicles\n";

  // 2. find place on a game map where 'this' clients vehicle can be put

  // 3. register your vehicle
  std::cout << __FILE__ << ':' << __LINE__ << " | " << __FUNCTION__
            << " | getId\n";
  rectangle_id_ = client_.getId();
  std::cout << __FILE__ << ':' << __LINE__ << " | " << __FUNCTION__
            << " rectangle_id_: " << rectangle_id_ << '\n';
  std::cout << __FILE__ << ':' << __LINE__ << " | " << __FUNCTION__
            << " | end getId\n";
  rectangle_.setFillColor(COLORS[rectangle_id_ % COLORS.size()]);
  if (std::isinf(rectangle_id_)) {
    std::cout << "Rectangle id not set\n";
    return;
  }
  client_.registerVehicle(toCcRectangle(rectangle_id_, rectangle_));
}

void CarCrash::onShutdown() { client_.unregisterVehicle(rectangle_id_); }

void CarCrash::onUpdate() {
  move();

  // todo: check collisions between other rectangles from server
  //  if (isCollided(rectangle_, rectangles_[0])) {
  //    rectangle_.setFillColor(sf::Color::Red);
  //  } else {
  //    rectangle_.setFillColor(sf::Color::Blue);
  //  }

  client_.updateVehicle(rectangle_id_,
                        toCcRectangle(rectangle_id_, rectangle_));
}

void CarCrash::onDraw(Game::Wrappers::RenderWindow& target) {
  if (close_window_) {
    target.close();
  }

  std::cout << __FILE__ << ':' << __LINE__ << " | " << __FUNCTION__
            << " | getVehicles\n";
  auto vehicles_from_server = client_.getVehicles();
  std::cout << __FILE__ << ':' << __LINE__ << " | " << __FUNCTION__
            << " | end getVehicles\n";
  for (const auto& v : vehicles_from_server) {
    target.draw(toSfRectangle(v));
  }
}

void CarCrash::onInput(const Game::Input::Keyboard keyboard) {
  if (keyboard.state == Game::Input::KeyState::Down) {
    switch (keyboard.code) {
      case Game::Input::Key::Left: {
        rectangle_.setPosition({rectangle_.getPosition().first - moving_speed_,
                                rectangle_.getPosition().second});
      } break;
      case Game::Input::Key::Up: {
        rectangle_.setPosition(
            {rectangle_.getPosition().first,
             rectangle_.getPosition().second - moving_speed_});
      } break;
      case Game::Input::Key::Right: {
        rectangle_.setPosition({rectangle_.getPosition().first + moving_speed_,
                                rectangle_.getPosition().second});
      } break;
      case Game::Input::Key::Down: {
        rectangle_.setPosition(
            {rectangle_.getPosition().first,
             rectangle_.getPosition().second + moving_speed_});
      } break;
      case Game::Input::Key::Escape:
        close_window_ = true;
        break;
      case Game::Input::Key::R:
        appendMoveDirection(MoveDirections::right);
        break;
      case Game::Input::Key::E:
        appendMoveDirection(MoveDirections::left);
        break;
      case Game::Input::Key::W: {
        std::cout << "shape position: " << rectangle_.getPosition().first
                  << ", " << rectangle_.getPosition().second << '\n';
      } break;
      case Game::Input::Key::A:
        appendMoveDirection(MoveDirections::forward);
        break;
      case Game::Input::Key::Q:
        appendMoveDirection(MoveDirections::backwards);
        break;
      default:
        break;
    }
  } else {
    switch (keyboard.code) {
      case Game::Input::Key::A:
        removeMoveDirection(MoveDirections::forward);
        break;
      case Game::Input::Key::R:
        removeMoveDirection(MoveDirections::right);
        break;
      case Game::Input::Key::E:
        removeMoveDirection(MoveDirections::left);
        break;
      case Game::Input::Key::Q:
        removeMoveDirection(MoveDirections::backwards);
        break;
      default:
        break;
    }
  }
}

void CarCrash::move() {
  if (checkMoveDirection(MoveDirections::forward)) {
    float x = rectangle_.getPosition().first +
              moving_speed_ * std::cos(getAngle(rectangle_.getRotation()));
    float y = rectangle_.getPosition().second +
              moving_speed_ * std::sin(getAngle(rectangle_.getRotation()));
    rectangle_.setPosition({x, y});
    if (checkMoveDirection(MoveDirections::left)) {
      rectangle_.rotate(-2);
    }
    if (checkMoveDirection(MoveDirections::right)) {
      rectangle_.rotate(2);
    }
  }

  if (checkMoveDirection(MoveDirections::backwards)) {
    float x = rectangle_.getPosition().first -
              moving_speed_ * std::cos(getAngle(rectangle_.getRotation()));
    float y = rectangle_.getPosition().second -
              moving_speed_ * std::sin(getAngle(rectangle_.getRotation()));
    rectangle_.setPosition({x, y});
    if (checkMoveDirection(MoveDirections::left)) {
      rectangle_.rotate(2);
    }
    if (checkMoveDirection(MoveDirections::right)) {
      rectangle_.rotate(-2);
    }
  }
}

void CarCrash::appendMoveDirection(CarCrash::MoveDirections dir) {
  moving_direction_ |= static_cast<uint32_t>(dir);
}

void CarCrash::removeMoveDirection(CarCrash::MoveDirections dir) {
  moving_direction_ &= ~static_cast<uint32_t>(dir);
}
bool CarCrash::checkMoveDirection(MoveDirections dir) {
  return moving_direction_ & static_cast<uint32_t>(dir);
}

}  // namespace CC

namespace Game {

Game::IGameApplicationPtr createGameApplication(const std::string& ip) {
  return std::make_shared<CC::CarCrash>(ip);
}

}  // namespace Game
