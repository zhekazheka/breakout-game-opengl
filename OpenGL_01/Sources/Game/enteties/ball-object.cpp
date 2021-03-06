//
//  ball-object.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 10/9/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "ball-object.h"

#include <iostream>

#include "brick.h"
#include "player.h"

BallObject::BallObject(bool isSolid)
: Collidable(isSolid), radius(12.5f), isStuck(true), isSticky(GL_FALSE), isPassingThrough(GL_FALSE)
{ }

BallObject::BallObject(bool isSolid, glm::vec2 pos, Texture2D sprite)
:  Collidable(isSolid, pos, glm::vec2(BALL_RADIUS * 2, BALL_RADIUS * 2), sprite, glm::vec3(1.0f), INITIAL_BALL_VELOCITY), radius(BALL_RADIUS),
   isStuck(true), isSticky(GL_FALSE), isPassingThrough(GL_FALSE)
{ }

glm::vec2 BallObject::Move(GLfloat dt, GLuint window_width)
{
    // If not stuck to player board
    if (!this->isStuck)
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
    this->isStuck = true;
    this->isSticky = false;
    this->isPassingThrough = false;
}

bool BallObject::IsDynamic() const
{
    return true;
}

ECollisionType BallObject::GetCollisionType() const
{
    return ECollisionType::BALL;
}

void BallObject::HandleCollision(const ICollidable* other, Collision& collision)
{    
    EDirection dir = std::get<1>(collision);
    glm::vec2 diff_vector = std::get<2>(collision);
    
    if(other->GetCollisionType() == ECollisionType::BRICK)
    {
        if (!(isPassingThrough && !other->IsSolid()))
        {
            if (dir == LEFT || dir == RIGHT) // Horizontal collision
            {
                Velocity.x = -Velocity.x; // Reverse horizontal velocity
                // Relocate
                GLfloat penetration = radius - std::abs(diff_vector.x);
                Position.x += dir == LEFT ? penetration : -penetration;
            }
            else // Vertical collision
            {
                Velocity.y = -Velocity.y; // Reverse vertical velocity
                // Relocate
                GLfloat penetration = radius - std::abs(diff_vector.y);
                Position.y += dir == DOWN ? penetration : -penetration;
            }
        }
    }
    else if(other->GetCollisionType() == ECollisionType::PLAYER)
    {
        if (!isStuck)
        {
            const Player* player = dynamic_cast<const Player*>(other);
            
            // Check where it hit the board, and change velocity based on where it hit the board
            GLfloat centerBoard = player->Position.x + player->Size.x / 2;
            GLfloat distance = (Position.x + radius) - centerBoard;
            GLfloat percentage = distance / (player->Size.x / 2);
            // Then move accordingly
            GLfloat strength = 2.0f;
            glm::vec2 oldVelocity = Velocity;
            Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
            Velocity.y = -1 * std::abs(Velocity.y);
            Velocity = glm::normalize(Velocity) * glm::length(oldVelocity);
            
            isStuck = isSticky;
        }
    }
}

void BallObject::EnablePassThrough(bool enable)
{
    isPassingThrough = enable;
    Color = isPassingThrough ? glm::vec3(1.0f, 0.5f, 0.5f) : glm::vec3(1.0f);
}

void BallObject::EnableSticky(bool enable)
{
    isSticky = enable;
}

float BallObject::GetRadius() const
{
    return radius;
}

bool BallObject::GetStuck() const
{
    return isStuck;
}

void BallObject::SetStuck(bool isStuck)
{
    this->isStuck = isStuck;
}
