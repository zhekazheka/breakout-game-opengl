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

enum EDirection
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum ECollisionType
{
    BALL,
    PLAYER,
    BRICK
};

typedef std::tuple<bool, EDirection, glm::vec2> Collision;

#endif /* collision_types_h */
