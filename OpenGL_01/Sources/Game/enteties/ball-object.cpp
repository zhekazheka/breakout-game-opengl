//
//  ball-object.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 10/9/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "ball-object.h"

#include <iostream>

BallObject::BallObject(CollisionDetector* collisionDetector)
: Collidable(collisionDetector), Radius(12.5f), Stuck(true), Sticky(GL_FALSE), PassThrough(GL_FALSE)
{ }

BallObject::BallObject(CollisionDetector* collisionDetector, glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite)
:  Collidable(collisionDetector, pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), Radius(radius),
   Stuck(true), Sticky(GL_FALSE), PassThrough(GL_FALSE)
{ }

glm::vec2 BallObject::Move(GLfloat dt, GLuint window_width)
{
    // If not stuck to player board
    if (!this->Stuck)
    {
        // Move the ball
        this->Position += this->Velocity * dt;
        
        // Then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (this->Position.x <= 0.0f)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = 0.0f;
        }
        else if (this->Position.x + this->Size.x >= window_width)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = window_width - this->Size.x;
        }
        if (this->Position.y <= 0.0f)
        {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }
    }
    return this->Position;
}

// Resets the ball to initial Stuck Position (if ball is outside window bounds)
void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
    this->Sticky = false;
    this->PassThrough = false;
}

bool BallObject::IsDynamic()
{
    return true;
}

void BallObject::HandleCollision(const GameObject &other, Collision& collision)
{
    std::cout << "[BallObject::HandleCollision] with " << other.Sprite.ID;
}
