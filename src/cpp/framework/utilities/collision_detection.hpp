#ifndef CAR_CRASH_SRC_COLLISION_DETECTION_HPP_
#define CAR_CRASH_SRC_COLLISION_DETECTION_HPP_

#include "../graphics/rectangle_shape.hpp"

namespace CC {

bool isCollided(Game::Wrappers::RectangleShape& shape,
                Game::Wrappers::RectangleShape& shape1);

}

#endif  // CAR_CRASH_SRC_COLLISION_DETECTION_HPP_
