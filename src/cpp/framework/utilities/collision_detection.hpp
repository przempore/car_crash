#ifndef CAR_CRASH_SRC_COLLISION_DETECTION_HPP_
#define CAR_CRASH_SRC_COLLISION_DETECTION_HPP_

#include "../graphics/rectangle_shape.hpp"

namespace CC {

    bool isCollided(const Game::Wrappers::RectangleShape &shape,
                    const Game::Wrappers::RectangleShape &shape1);

}

#endif  // CAR_CRASH_SRC_COLLISION_DETECTION_HPP_
