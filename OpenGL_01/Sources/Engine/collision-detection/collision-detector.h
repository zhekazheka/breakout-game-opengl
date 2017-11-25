//
//  collision-detector.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/23/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef collision_detector_h
#define collision_detector_h

#include <vector>

#include "collision-types.h"

class Collidable;

class CollisionDetector
{
public:
    void RegisterCollider(Collidable* collidable);
    void DeregisterCollider(Collidable* collidable);
    void Update(float dt);
    
private:
    bool HandleBallCollision(Collidable* left, Collidable* right);
    void DispatchCollisions(Collidable* left, Collidable* right, Collision& collision);
    
    std::vector<Collidable*> colliders;
};

#endif /* collision_detector_h */
