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
    // define if object is dynamic for collision and therefore should be process on each frame
    virtual bool IsDynamic() = 0;
    
    // calls on collision detected
    virtual void HandleCollision(const GameObject &other, Collision& collision) = 0;
};

#endif /* icollidable_h */
