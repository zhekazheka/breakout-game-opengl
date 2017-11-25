//
//  icollidable.h
//  OpenGL_01
//
//  Created by zhekazheka on 11/23/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef icollidable_h
#define icollidable_h

#include "collision-types.h"

class GameObject;

class ICollidable
{
public:
    // defines if object is dynamic for collision and therefore should be process on each frame
    virtual bool IsDynamic() const = 0;
    
    // defines if object solid and cannot be pass through
    virtual bool IsSolid() const = 0;
    
    // defines an object collision type
    virtual ECollisionType GetCollisionType() const = 0;
    
    // calls on collision detected
    virtual void HandleCollision(const ICollidable* other, Collision& collision) = 0;
};

#endif /* icollidable_h */
