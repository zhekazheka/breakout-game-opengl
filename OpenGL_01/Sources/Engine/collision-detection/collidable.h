//
//  collidable.h
//  OpenGL_01
//
//  Created by zhekazheka on 11/23/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef collidable_h
#define collidable_h

#include "icollidable.h"
#include "game-object.h"
#include "collision-detector.h"

#include <iostream>

class Collidable : public GameObject, public ICollidable
{
public:
    Collidable(CollisionDetector* collisionDetector, bool isSolid)
    {
        collisionDetector->RegisterCollider(this);
        this->isSolid = isSolid;
    }
    
    Collidable(CollisionDetector* collisionDetector, bool isSolid, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f))
    : GameObject(pos, size, sprite, color, velocity)
    {
        collisionDetector->RegisterCollider(this);
        this->isSolid = isSolid;
    }
    
    virtual bool IsSolid() const
    {
        return isSolid;
    }
    
protected:
    bool isSolid;
};

#endif /* collidable_h */
