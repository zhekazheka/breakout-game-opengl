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
#include "game-object.h"

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class BallObject : public GameObject
{
public:
    // Ball state
    GLfloat Radius;
    GLboolean Stuck;
    
    // Constructor(s)
    BallObject();
    BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
    
    // Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    glm::vec2 Move(GLfloat dt, GLuint window_width);
    // Resets the ball to original state with given position and velocity
    void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif /* ball_object_h */
