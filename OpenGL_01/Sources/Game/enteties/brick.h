//
//  brick.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/23/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef brick_h
#define brick_h

#include "collidable.h"

class Brick : public Collidable
{
public:
    Brick(CollisionDetector* collisionDetector, bool isSolid);
    Brick(CollisionDetector* collisionDetector, bool isSolid, glm::vec2 startPosition, glm::vec2 size, Texture2D texture, glm::vec3 color);
    
    bool IsDynamic() const;
    ECollisionType GetCollisionType() const;
    void HandleCollision(const ICollidable* other, Collision& collision);
    
};

#endif /* brick_h */
