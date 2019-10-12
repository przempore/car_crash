#include "collision_detection.hpp"

#include <cmath>
#include <iostream>


// sfml representation of XY
//

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
  return degrees/180 * M_PI;
}

double getDegreeFromRadian(double radian) {
  return 180/M_PI;
}

bool lessOrEqual(const double value1, const double value2) {
  return almostEqual(value1, value2, 2) || value1 <= value2;
}

bool moreThan(const double value1, const double value2) {
  return !lessOrEqual(value1, value2) || value1 > value2;
}

void printApexes(const RectangleApexes& apexes, const Point& size, const Point& position) {
  std::cout << apexes.d << " ---------------------- " << apexes.c << ")\n";
  for (size_t i = 0; i < 3; i++) { std::cout << "\t|\t\t\t\t\t\t\t\t\t|\n"; }
  std::cout << size.y << "\t|\t\t\t";
  std::cout << position << "\t\t\t\t|\n";
  for (size_t i = 0; i < 3; i++) { std::cout << "\t|\t\t\t\t\t\t\t\t\t|\n"; }
  std::cout << apexes.a << " -------- " << size.x << " -------- " << apexes.b << ")\n";
}

// https://math.stackexchange.com/a/2518716
RectangleApexes getRectangleVertices(const sf::RectangleShape &shape) {
  auto angle = getRadianAngle(shape.getRotation());
//    std::cout << "angle: " << angle << std::endl;
  auto w = shape.getSize().x / 2;
  auto b = shape.getSize().y / 2;
  Point u {w * std::cos(angle), w * std::sin(angle)};
  Point v {-b * std::sin(angle), b * std::cos(angle)};

  Point Zc{shape.getPosition().x, shape.getPosition().y};
  return {
      {Zc + u + v},
      {Zc - u + v},
      {Zc - u - v},
      {Zc + u - v},
  };
}


Point getProjection(Point apexes, Point axis) {
  Point proj_axis{};
  auto up = apexes.x * axis.x + apexes.y * axis.y;
  auto down = std::pow(axis.x, 2.0) + std::pow(axis.y, 2.0);
  proj_axis.x = up / down;
  proj_axis.y = proj_axis.x;

  proj_axis.x *= axis.x;
  proj_axis.y *= axis.y;

  return proj_axis;
}

constexpr uint32_t POINT_COUNT_ON_AXIS{4};

auto getMinFromAxis(const std::array<Point, POINT_COUNT_ON_AXIS>& axis) {
  double min = std::numeric_limits<double>::max();
  for (const auto& p : axis) {
    if (min > p.x) min = p.x;
    if (min > p.y) min = p.y;
  }
  return min;
};

auto getMaxFromAxis(const std::array<Point, POINT_COUNT_ON_AXIS>& axis) {
  double max = std::numeric_limits<double>::min();
  for (const auto& p : axis) {
    if (max < p.x) max = p.x;
    if (max < p.y) max = p.y;
  }
  return max;
};

auto checkPointsOnAxis(const std::array<Point, POINT_COUNT_ON_AXIS>& points_A_on_axis,
                       const std::array<Point, POINT_COUNT_ON_AXIS>& points_B_on_axis) {
  auto min_A_axis = getMinFromAxis(points_A_on_axis);
  auto min_B_axis = getMinFromAxis(points_B_on_axis);

  auto max_A_axis = getMaxFromAxis(points_A_on_axis);
  auto max_B_axis = getMaxFromAxis(points_B_on_axis);

  // If the minimum scalar value of B is less than or equal to the maximum scalar value of A
  // and the maximum scalar value of B is greater than or equal to the minimum scalar value of A
  // then our objects overlap when projected onto this axis.
  return min_B_axis <= max_A_axis && max_B_axis >= min_A_axis;
};

bool projectAndCheck(const Point& axis, const RectangleApexes& A, const RectangleApexes& B) {
  std::array<Point, POINT_COUNT_ON_AXIS> points_A_on_axis = {
      getProjection(A.d, axis),
      getProjection(A.c, axis),
      getProjection(A.b, axis),
      getProjection(A.a, axis),
  };
  std::array<Point, POINT_COUNT_ON_AXIS> points_B_on_axis = {
      getProjection(B.b, axis),
      getProjection(B.c, axis),
      getProjection(B.d, axis),
      getProjection(B.a, axis),

  };

  return checkPointsOnAxis(points_A_on_axis, points_B_on_axis);
}

// https://stackoverflow.com/a/37865332
bool pointInRectangle(Point m, RectangleApexes r) {

  /*
   a-----b
   |     |
   |     |
   |     |
   |     |
   c-----d
   */

  auto vector = [] (Point p1, Point p2) -> Point {
    return { p2.x - p1.x, p2.y - p1.y };
  };

  auto dot = [] (Point u, Point v) {
    return u.x * v.x + u.y * v.y;
  };
  Point AB = vector(r.c, r.d);
  Point AM = vector(r.c, m);
  Point BC = vector(r.d, r.a);
  Point BM = vector(r.d, m);


  double dotABAM = dot(AB, AM);
  double dotABAB = dot(AB, AB);
  double dotBCBM = dot(BC, BM);
  double dotBCBC = dot(BC, BC);
  return lessOrEqual(0, dotABAM) &&
      lessOrEqual(dotABAM, dotABAB) &&
      lessOrEqual(0, dotBCBM) &&
      lessOrEqual(dotBCBM, dotBCBC);
}

// https://stackoverflow.com/a/2752754
bool pointInRectangle_2(Point m, RectangleApexes r) {

  /*
  d       c
   C-----D
   |     |
   |     |
   |     |
   |     |
   B-----A
  a       b

   */

  auto bax = r.b.x - r.a.x;
  auto bay = r.b.y - r.a.y;
  auto dax = r.d.x - r.a.x;
  auto day = r.d.y - r.a.y;

  if ((m.x - r.a.x) * bax + (m.y - r.a.y) * bay < 0.0) return false;
  if ((m.x - r.b.x) * bax + (m.y - r.b.y) * bay > 0.0) return false;
  if ((m.x - r.a.x) * dax + (m.y - r.a.y) * day < 0.0) return false;
  if ((m.x - r.d.x) * dax + (m.y - r.d.y) * day > 0.0) return false;

  return true;
}

// https://stackoverflow.com/a/42396910
Point vect2d(Point p1, Point p2) {
  return {p2.x - p1.x, -1 * (p2.y - p1.y)};
}

bool pointInRectangle_3(Point m, RectangleApexes r) {
  Point A = r.a;
  Point B = r.b;
  Point C = r.c;
  Point D = r.d;

  Point AB = vect2d(A, B);  float C1 = -1 * (AB.y*A.x + AB.x*A.y); float  D1 = AB.y * m.x + AB.x * m.y + C1;
  Point AD = vect2d(A, D);  float C2 = -1 * (AD.y*A.x + AD.x*A.y); float D2 = AD.y * m.x + AD.x * m.y + C2;
  Point BC = vect2d(B, C);  float C3 = -1 * (BC.y*B.x + BC.x*B.y); float D3 = BC.y * m.x + BC.x * m.y + C3;
  Point CD = vect2d(C, D);  float C4 = -1 * (CD.y*C.x + CD.x*C.y); float D4 = CD.y * m.x + CD.x * m.y + C4;
  return 0 >= D1 && 0 >= D4 && 0 <= D2 && 0 >= D3;
}

bool was_printed = false;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "(" << p.x << "," << p.y << ")";
  return os;
}

inline bool operator<(const Point& lhs, const Point& rhs) {
  return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}


// https://www.gamedev.net/articles/programming/general-and-gameplay-programming/2d-rotated-rectangle-collision-r2604
bool checkVehiclesDrivingBesides(sf::RectangleShape &shape, sf::RectangleShape &shape1) {
  auto tv_apexes = getRectangleVertices(shape);
  auto ego_apexes = getRectangleVertices(shape1);
  RectangleApexes A = tv_apexes < ego_apexes ? tv_apexes : ego_apexes;
  RectangleApexes B = tv_apexes < ego_apexes ? ego_apexes : tv_apexes;

  if (pointInRectangle(A.a, B)) return true;
  if (pointInRectangle(A.b, B)) return true;
  if (pointInRectangle(A.c, B)) return true;
  if (pointInRectangle(A.d, B)) return true;

  if (pointInRectangle(B.a, A)) return true;
  if (pointInRectangle(B.b, A)) return true;
  if (pointInRectangle(B.c, A)) return true;
  if (pointInRectangle(B.d, A)) return true;

  return false;

  Point axis0{A.b.x - B.a.x, A.b.y - B.a.y};
  Point axis1{A.b.x - B.c.x, A.b.y - B.c.y};
  Point axis2{B.a.x - B.d.x, B.a.y - B.d.y};
  Point axis3{B.a.x - B.b.x, B.a.y - B.b.y};

  // check axis0
  bool is_colliding = projectAndCheck(axis0, A, B);
  if (!is_colliding) return false;
  // check axis1
  is_colliding = projectAndCheck(axis1, A, B);
  if (!is_colliding) return false;
  // check axis2
  is_colliding = projectAndCheck(axis2, A, B);
  if (!is_colliding) return false;
  // check axis3
  is_colliding = projectAndCheck(axis3, A, B);
  if (!is_colliding) return false;

  return true;
}

bool isCollided(sf::RectangleShape &shape, sf::RectangleShape &shape1) {
  const double distance = std::hypot(shape.getPosition().x - shape1.getPosition().x, shape.getPosition().y - shape1.getPosition().y);
  const auto traffic_vehicle_diagonal =
      std::sqrt(std::pow(shape.getSize().x, 2.0) + std::pow(shape.getSize().y, 2.0));
  const auto ego_vehicle_diagonal =
      std::sqrt(std::pow(shape1.getSize().x, 2.0) + std::pow(shape1.getSize().y, 2.0));
  const auto sum_of_half_diagonals = traffic_vehicle_diagonal / 2 + ego_vehicle_diagonal / 2;

//    return distance <= sum_of_half_diagonals;
  if (distance <= sum_of_half_diagonals) {
    return checkVehiclesDrivingBesides(shape, shape1);
  }

  was_printed = false;
  return false;
}

void print(sf::RectangleShape &shape, sf::RectangleShape &shape1) {
  Point ego_point{shape.getPosition().x, shape.getPosition().y};
  Point traffic_point{shape1.getPosition().x, shape1.getPosition().y};

  Point point_less = ego_point < traffic_point ? ego_point : traffic_point;
  Point point_more = ego_point < traffic_point ? traffic_point : ego_point;
  auto shape_apexes = getRectangleVertices(shape);
  auto shape1_apexes = getRectangleVertices(shape1);
  RectangleApexes A = shape_apexes;
  RectangleApexes B = shape1_apexes;

  auto is_equal = [] (double i1, double i2) {
    return fabs(fabs(i1) - fabs(i2)) <= 1.0;
  };

  std::cout << "\n\n\t--------- START ---------\t\n\n";
  size_t A_num = 0;
  size_t B_num = 0;
  for (uint32_t y = 0; y < 300; y++) {
    std::string line = "";
    for (uint32_t x = 100; x < 400; x++) {
      if (
          (is_equal(x, A.a.x) && is_equal(y, A.a.y)) ||
              (is_equal(x, A.b.x) && is_equal(y, A.b.y)) ||
              (is_equal(x, A.c.x) && is_equal(y, A.c.y)) ||
              (is_equal(x, A.d.x) && is_equal(y, A.d.y))
          ) {
//                line = "A(" + std::to_string(x) + "," + std::to_string(y) + ")";
        line = "A";
      } else if (
          (is_equal(x, B.a.x) && is_equal(y, B.a.y)) ||
              (is_equal(x, B.b.x) && is_equal(y, B.b.y)) ||
              (is_equal(x, B.c.x) && is_equal(y, B.c.y)) ||
              (is_equal(x, B.d.x) && is_equal(y, B.d.y))
          ) {
//                line = "B(" + std::to_string(x) + "," + std::to_string(y) + ")";
        line = "B";
      } else if (pointInRectangle({x, y}, A) && pointInRectangle({x, y}, B)) {
        line = "!";
      } else if (pointInRectangle({x, y}, A)) {
        A_num++;
        line = "*";
      } else if (pointInRectangle({x, y}, B)) {
        B_num++;
        line = "&";
      } else {
        line = "-";
      }
      std::cout << line;
    }
    std::cout << '\n';
  }

  std::cout << "\n\n\t--------- END ---------\t\n\n";
}

void print() {
  RectangleApexes r = {
      {50, 0},
      {0, 20},
      {10, 50},
      {60, 30},
  };
  for (size_t y = 0 ; y < 50 ; y++) {
    std::string line = "";
    for (size_t x = 0 ; x < 65 ; x++) {
      Point m{x, y};

      if (pointInRectangle_2(m, r)) {
        line = "*";
      } else {
        line = "-";
      }
      std::cout << line;
    }
    std::cout << '\n';
  }
}
