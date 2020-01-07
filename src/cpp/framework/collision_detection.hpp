#ifndef CAR_CRASH_SRC_COLLISION_DETECTION_HPP_
#define CAR_CRASH_SRC_COLLISION_DETECTION_HPP_

#include <SFML/Graphics.hpp>

namespace CC {

bool isCollided(sf::RectangleShape& shape, sf::RectangleShape& shape1);

}

#endif  // CAR_CRASH_SRC_COLLISION_DETECTION_HPP_
