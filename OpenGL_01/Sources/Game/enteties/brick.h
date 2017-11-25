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
    Brick(CollisionDetector* collisionDetector);
    Brick(CollisionDetector* collisionDetector, glm::vec2 startPosition, glm::vec2 size, Texture2D texture, glm::vec3 color, bool isSolid);
    
    bool IsDynamic();
    void HandleCollision(const GameObject &other, Collision& collision);
};

#endif /* brick_h */
