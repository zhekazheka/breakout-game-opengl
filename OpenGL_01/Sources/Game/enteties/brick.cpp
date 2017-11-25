//
//  brick.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/23/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "brick.h"

#include <iostream>

Brick::Brick(CollisionDetector* collisionDetector, bool isSolid)
: Collidable(collisionDetector, isSolid)
{ }

Brick::Brick(CollisionDetector* collisionDetector, bool isSolid, glm::vec2 startPosition, glm::vec2 size, Texture2D texture, glm::vec3 color)
: Collidable(collisionDetector, isSolid, startPosition, size, texture, color)
{ }

bool Brick::IsDynamic() const
{
    return false;
}

ECollisionType Brick::GetCollisionType() const
{
    return ECollisionType::BRICK;
}

void Brick::HandleCollision(const ICollidable* other, Collision& collision)
{
//    std::cout << "[Brick::HandleCollision] with " << other.Sprite.ID;
    
    Destroyed = !IsSolid();
}
