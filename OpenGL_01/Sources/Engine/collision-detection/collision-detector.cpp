//
//  collision-detector.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/23/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "collision-detector.h"
#include "simple-collision-detector.h"

void CollisionDetector::RegisterCollider(Collidable* collidable)
{
    if(std::find(colliders.begin(), colliders.end(), collidable) == colliders.end())
    {
        colliders.push_back(collidable);
    }
}

void CollisionDetector::Update(float dt)
{
    unsigned long collidersCount = colliders.size();
    for(int i = 0; i < collidersCount; ++i)
    {
        Collidable* leftCollider = colliders[i];
        if(!leftCollider->IsDynamic() || leftCollider->Destroyed)
        {
            continue;
        }
        
        for(int j = 0; j < collidersCount; ++j)
        {
            Collidable* rightCollider = colliders[j];
            
            if(leftCollider == rightCollider || rightCollider->Destroyed)
            {
                continue;
            }
            
            if(HandleBallCollision(leftCollider, rightCollider))
            {
                continue;
            }
            
            if(CheckCollision(*leftCollider, *rightCollider))
            {
                Collision collision = std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
                DispatchCollisions(leftCollider, rightCollider, collision);
            }
        }
    }
}

bool CollisionDetector::HandleBallCollision(Collidable *left, Collidable *right)
{
    Collision collision = std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
    BallObject* ballObject = dynamic_cast<BallObject*>(left);
    if(ballObject != nullptr)
    {
        collision = CheckCollision(*ballObject, *right);
    }
    
    ballObject = dynamic_cast<BallObject*>(right);
    if(ballObject != nullptr)
    {
        collision = CheckCollision(*ballObject, *left);
    }
    
    if(std::get<0>(collision))
    {
        DispatchCollisions(left, right, collision);
    }
    
   return false;
}

void CollisionDetector::DispatchCollisions(Collidable *left, Collidable *right, Collision& collision)
{
    left->HandleCollision(*right, collision);
    right->HandleCollision(*left, collision);
}
