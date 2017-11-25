//
//  ball-object.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 10/9/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef ball_object_h
#define ball_object_h

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite-renderer.h"
#include "collidable.h"

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const GLfloat BALL_RADIUS = 12.5f;

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class BallObject : public Collidable
{
public:
    // Ball state
    GLfloat Radius;
    GLboolean Stuck;
    GLboolean Sticky, PassThrough;
    
    // Constructor(s)
    BallObject(CollisionDetector* collisionDetector, bool isSolid);
    BallObject(CollisionDetector* collisionDetector, bool isSolid, glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
    
    // Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    glm::vec2 Move(GLfloat dt, GLuint window_width);
    // Resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
    
    bool IsDynamic() const;
    ECollisionType GetCollisionType() const;
    void HandleCollision(const ICollidable* other, Collision& collision);
};

#endif /* ball_object_h */
