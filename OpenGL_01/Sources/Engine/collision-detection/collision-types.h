//
//  collision-types.h
//  OpenGL_01
//
//  Created by zhekazheka on 11/25/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef collision_types_h
#define collision_types_h

#include <glm/glm.hpp>
#include <tuple>

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

#endif /* collision_types_h */
