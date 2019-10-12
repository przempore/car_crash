#include "collision_detection.hpp"

#include <cmath>
#include <iostream>

namespace {

// https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almostEqual(T x, T y, int ulp) {
  // the machine epsilon has to be scaled to the magnitude of the values used
  // and multiplied by the desired precision in ULPs (units in the last place)
  return std::abs(x - y) <= std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp
      // unless the result is subnormal
      || std::abs(x - y) < std::numeric_limits<T>::min();
}

double getRadianAngle(double degrees) {
  return degrees / 180 * M_PI;
}

bool lessOrEqual(const double value1, const double value2) {
  return almostEqual(value1, value2, 2) || value1 <= value2;
}

struct Point {
  double x, y;

  inline Point operator-(const Point &other) {
    return {this->x - other.x, this->y - other.y};
  }

  inline Point operator+(const Point &other) {
    return {this->x + other.x, this->y + other.y};
  }

  friend std::ostream &operator<<(std::ostream &os, const Point &p);
  friend bool operator<(const Point &lhs, const Point &rhs);
};

constexpr std::uint32_t VERTEX_A_IDX = 0;
constexpr std::uint32_t VERTEX_B_IDX = 1;
constexpr std::uint32_t VERTEX_C_IDX = 2;
constexpr std::uint32_t VERTEX_D_IDX = 3;
constexpr std::uint32_t RECTANGLE_APEXES_COUNT = 4;
using RectangleApexes = std::array<Point, RECTANGLE_APEXES_COUNT>;

// https://math.stackexchange.com/a/2518716
RectangleApexes getRectangleVertices(const sf::RectangleShape &shape) {
  auto angle = getRadianAngle(shape.getRotation());
//    std::cout << "angle: " << angle << std::endl;
  auto w = shape.getSize().x / 2;
  auto b = shape.getSize().y / 2;
  Point u{w * std::cos(angle), w * std::sin(angle)};
  Point v{-b * std::sin(angle), b * std::cos(angle)};

  Point Zc{shape.getPosition().x, shape.getPosition().y};

  return {
      Zc - u + v,
      Zc + u + v,
      Zc + u - v,
      Zc - u - v,
  };
}

// https://stackoverflow.com/a/37865332
bool pointInRectangle(Point m, RectangleApexes r) {
  auto vector = [](Point p1, Point p2) -> Point {
    return {p2.x - p1.x, p2.y - p1.y};
  };

  auto dot = [](Point u, Point v) {
    return u.x * v.x + u.y * v.y;
  };
  Point AB = vector(r[VERTEX_A_IDX], r[VERTEX_B_IDX]);
  Point AM = vector(r[VERTEX_A_IDX], m);
  Point BC = vector(r[VERTEX_B_IDX], r[VERTEX_C_IDX]);
  Point BM = vector(r[VERTEX_B_IDX], m);

  double dotABAM = dot(AB, AM);
  double dotABAB = dot(AB, AB);
  double dotBCBM = dot(BC, BM);
  double dotBCBC = dot(BC, BC);
  return lessOrEqual(0, dotABAM) &&
      lessOrEqual(dotABAM, dotABAB) &&
      lessOrEqual(0, dotBCBM) &&
      lessOrEqual(dotBCBM, dotBCBC);
}

}

std::ostream &operator<<(std::ostream &os, const Point &p) {
  os << "(" << p.x << "," << p.y << ")";
  return os;
}

inline bool operator<(const Point &lhs, const Point &rhs) {
  return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}

// https://www.gamedev.net/articles/programming/general-and-gameplay-programming/2d-rotated-rectangle-collision-r2604
bool checkVehiclesDrivingBesides(sf::RectangleShape &shape, sf::RectangleShape &shape1) {
  auto tv_apexes = getRectangleVertices(shape);
  auto ego_apexes = getRectangleVertices(shape1);

  for (size_t apex_idx = VERTEX_A_IDX; apex_idx < RECTANGLE_APEXES_COUNT; apex_idx++) {
    if (pointInRectangle(tv_apexes[apex_idx], ego_apexes)) return true;
    if (pointInRectangle(ego_apexes[apex_idx], tv_apexes)) return true;
  }

  return false;
}

bool isCollided(sf::RectangleShape &shape, sf::RectangleShape &shape1) {
  const double distance =
      std::hypot(shape.getPosition().x - shape1.getPosition().x, shape.getPosition().y - shape1.getPosition().y);
  const auto traffic_vehicle_diagonal =
      std::sqrt(std::pow(shape.getSize().x, 2.0) + std::pow(shape.getSize().y, 2.0));
  const auto ego_vehicle_diagonal =
      std::sqrt(std::pow(shape1.getSize().x, 2.0) + std::pow(shape1.getSize().y, 2.0));
  const auto sum_of_half_diagonals = traffic_vehicle_diagonal / 2 + ego_vehicle_diagonal / 2;

  if (distance <= sum_of_half_diagonals) {
    return checkVehiclesDrivingBesides(shape, shape1);
  }

  return false;
}
