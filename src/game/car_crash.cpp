#define _USE_MATH_DEFINES
#include "car_crash.hpp"

#include <memory>
#include <iostream>
#include <cmath>

#include <SFML/Graphics/Color.hpp>
#include "collision_detection.hpp"

namespace {

constexpr float getAngle(float degrees) {
  return degrees * static_cast<float>(M_PI) / 180.f;
}

CC::Rectangle::Color toGrpcColor(sf::Color color) {
  // todo: check if nubmers are correct
  switch (color.toInteger()) {
    case 255: return CC::Rectangle::Color::Black;
    case 4294967295: return CC::Rectangle::Color::White;
    case 4278190335: return CC::Rectangle::Color::Red;
    case 16711935: return CC::Rectangle::Color::Green;
    case 65535: return CC::Rectangle::Color::Blue;
    case 4294902015: return CC::Rectangle::Color::Yellow;
    case 4278255615: return CC::Rectangle::Color::Magenta;
    case 16777215: return CC::Rectangle::Color::Cyan;
    case 0: return CC::Rectangle::Color::Transparent;
  }

  return CC::Rectangle::Color::Cyan;
}

sf::Color toSfColor(CC::Rectangle::Color color) {
    switch (color) {
      case CC::Rectangle::Color::Black: return sf::Color::Black;
      case CC::Rectangle::Color::White: return sf::Color::White;
      case CC::Rectangle::Color::Red: return sf::Color::Red;
      case CC::Rectangle::Color::Green: return sf::Color::Green;
      case CC::Rectangle::Color::Blue: return sf::Color::Blue;
      case CC::Rectangle::Color::Yellow: return sf::Color::Yellow;
      case CC::Rectangle::Color::Magenta: return sf::Color::Magenta;
      case CC::Rectangle::Color::Cyan: return sf::Color::Cyan;
      case CC::Rectangle::Color::Transparent: return sf::Color::Transparent;
    }

    return sf::Color::Magenta;
}

CC::Rectangle toCcRectangle(uint32_t id, const sf::RectangleShape& r) {
  return {id, {r.getPosition().x, r.getPosition().y}, r.getRotation(), {r.getSize().x, r.getSize().y},
          toGrpcColor(r.getFillColor())};
}

sf::RectangleShape toSfRectangle(CC::Rectangle r) {
  sf::RectangleShape ret(sf::Vector2f(r.dimension.x, r.dimension.y));
  ret.setFillColor(toSfColor(r.color));
  ret.setPosition(sf::Vector2f(r.position.x, r.position.y));
  ret.setRotation(r.angle);
  return ret;
}

}

namespace CC {

CarCrash::CarCrash() : rectangle_(sf::Vector2f(120, 50)),
                       rectangle_id_(std::numeric_limits<uint32_t>::infinity()),
//                       rectangles_{},
                       move_forward_{false},
                       move_backward_{false},
                       move_left_{false},
                       move_right_{false},
                       close_window_{false},
                       moving_speed_{2.5f} {
  // todo: client needs only its own rectangle, rest will get from server
////  rectangles_.emplace_back(sf::Vector2f(120, 50));
//  rectangles_.emplace_back(sf::Vector2f(120, 50));
  rectangle_.setFillColor(sf::Color::Blue);
//  rectangles_[0].setFillColor(sf::Color::Green);
  rectangle_.setPosition({201, 221});
//  rectangles_[0].setPosition({250, 100});
  rectangle_.setOrigin({rectangle_.getSize().x / 4,  // TODO: x / 4 caused collision error
                            rectangle_.getSize().y / 2});
//  rectangles_[0].setOrigin({rectangles_[0].getSize().x / 2, rectangles_[0].getSize().y / 2});
//  rectangles_[0].setRotation(-45);
}

CarCrash::~CarCrash() {
  // todo: move this to onShutdown
  std::cout << __FILE__ << ':' << __LINE__ << " | " << __FUNCTION__ << " | rectangle_id_ : " << rectangle_id_ << '\n';
  client_.unregisterVehicle(rectangle_id_);
}

void CarCrash::onStartup() {

  // 1. get all vehicles from server
  auto vehicles_from_server = client_.getVehicles();

  // 2. find place on a game map where 'this' clients vehicle can be put

  // 3. register your vehicle
  rectangle_id_ = client_.getId();
  std::cout << __FILE__ << ':' << __LINE__ << " | " << __FUNCTION__ <<  " rectangle_id_: " << rectangle_id_ << '\n';
  if (std::isinf(rectangle_id_)) {
    std::cout << "Rectangle id not set\n";
    return;
  }
  client_.registerVehicle(toCcRectangle(rectangle_id_, rectangle_));
}

void CarCrash::onShutdown() {}

void CarCrash::onUpdate() {
  if (move_forward_) {
    float x = rectangle_.getPosition().x + moving_speed_ * std::cos(getAngle(rectangle_.getRotation()));
    float y = rectangle_.getPosition().y + moving_speed_ * std::sin(getAngle(rectangle_.getRotation()));
    rectangle_.setPosition({x, y});
    if (move_left_) {
      rectangle_.rotate(-2);
    }
    if (move_right_) {
      rectangle_.rotate(2);
    }
  }

  if (move_backward_) {
    float x = rectangle_.getPosition().x - moving_speed_ * std::cos(getAngle(rectangle_.getRotation()));
    float y = rectangle_.getPosition().y - moving_speed_ * std::sin(getAngle(rectangle_.getRotation()));
    rectangle_.setPosition({x, y});
    if (move_left_) {
      rectangle_.rotate(2);
    }
    if (move_right_) {
      rectangle_.rotate(-2);
    }
  }

// todo: check collicions between other rectangles from server
//  if (isCollided(rectangle_, rectangles_[0])) {
//    rectangle_.setFillColor(sf::Color::Red);
//  } else {
//    rectangle_.setFillColor(sf::Color::Blue);
//  }

  // todo: update your vehicle in server
  std::cout << __FILE__ << ':' << __LINE__ << " | " << __FUNCTION__ <<  " rectangle_id_: " << rectangle_id_ << '\n';
  client_.updateVehicle(rectangle_id_, toCcRectangle(rectangle_id_, rectangle_));

}

void CarCrash::onDraw(Game::Wrappers::Graphics &target) {
  if (close_window_) {
    target.close();
  }

  // todo: get vehicles from server and draw them
  auto vehicles_from_server = client_.getVehicles();
  for (const auto& v : vehicles_from_server) {
    target.draw(toSfRectangle(v));
  }
}

void CarCrash::onInput(const Game::Input::Keyboard keyboard) {
  if (keyboard.state == Game::Input::KeyState::Down) {
    switch (keyboard.code) {
      case Game::Input::Key::Left: {
        rectangle_.setPosition({rectangle_.getPosition().x - moving_speed_, rectangle_.getPosition().y});
      }
        break;
      case Game::Input::Key::Up: {
        rectangle_.setPosition({rectangle_.getPosition().x, rectangle_.getPosition().y - moving_speed_});
      }
        break;
      case Game::Input::Key::Right: {
        rectangle_.setPosition({rectangle_.getPosition().x + moving_speed_, rectangle_.getPosition().y});
      }
        break;
      case Game::Input::Key::Down: {
        rectangle_.setPosition({rectangle_.getPosition().x, rectangle_.getPosition().y + moving_speed_});
      }
        break;
      case Game::Input::Key::Escape:close_window_ = true;
        break;
      case Game::Input::Key::R:move_right_ = true;
        break;
      case Game::Input::Key::E:move_left_ = true;
        break;
      case Game::Input::Key::W: {
        std::cout << "shape position: " << rectangle_.getPosition().x << ", " << rectangle_.getPosition().y
                  << '\n';
      }
        break;
      case Game::Input::Key::A:move_forward_ = true;
        break;
      case Game::Input::Key::Q:move_backward_ = true;
        break;
      default:break;
    }
  } else {

    switch (keyboard.code) {
      case Game::Input::Key::A:move_forward_ = false;
        break;
      case Game::Input::Key::R:move_right_ = false;
        break;
      case Game::Input::Key::E:move_left_ = false;
        break;
      case Game::Input::Key::Q:move_backward_ = false;
        break;
      default:break;
    }
  }
}

}

namespace Game {

Game::IGameApplicationPtr createGameApplication() {
  return std::make_shared<CC::CarCrash>();
}

}
