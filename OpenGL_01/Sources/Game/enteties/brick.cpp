//
//  brick.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/23/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "brick.h"

#include <iostream>

Brick::Brick(CollisionDetector* collisionDetector)
: Collidable(collisionDetector)
{ }

Brick::Brick(CollisionDetector* collisionDetector, glm::vec2 startPosition, glm::vec2 size, Texture2D texture, glm::vec3 color, bool isSolid)
: Collidable(collisionDetector, startPosition, size, texture, color)
{
    IsSolid = isSolid;
}

bool Brick::IsDynamic()
{
    return false;
}

void Brick::HandleCollision(const GameObject &other, Collision& collision)
{
    std::cout << "[Brick::HandleCollision] with " << other.Sprite.ID;
    
    Destroyed = !IsSolid;
}
