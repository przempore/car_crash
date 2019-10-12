#ifndef CAR_CRASH_SRC_COLLISION_DETECTION_HPP_
#define CAR_CRASH_SRC_COLLISION_DETECTION_HPP_

#include <SFML/Graphics.hpp>

struct Point {
  double x, y;

  inline Point operator-(const Point& other) {
    return {this->x - other.x, this->y - other.y};
  }

  inline Point operator+(const Point& other) {
    return {this->x + other.x, this->y + other.y};
  }

  friend std::ostream& operator<<(std::ostream& os, const Point& p);
  friend bool operator<(const Point& lhs, const Point& rhs);
};

/*
    d----c
    |    |
    |    |
    a----b
 */
struct RectangleApexes {
  Point a, b, c, d;

  bool operator<(const RectangleApexes& other) {
    return std::tie(this->a, this->b, this->c, this->d) <
        std::tie(other.a, other.b, other.c, other.d);
  }
};

bool isCollided(sf::RectangleShape &shape, sf::RectangleShape &shape1);


void print(sf::RectangleShape &shape, sf::RectangleShape &shape1);
void print();

#endif //CAR_CRASH_SRC_COLLISION_DETECTION_HPP_
