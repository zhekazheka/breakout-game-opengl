//
//  power-up.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 10/15/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef power_up_h
#define power_up_h

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "game-object.h"


// The size of a PowerUp block
const glm::vec2 SIZE(60, 20);
// Velocity a PowerUp block has when spawned
const glm::vec2 VELOCITY(0.0f, 150.0f);


// PowerUp inherits its state and rendering functions from
// GameObject but also holds extra information to state its
// active duration and whether it is activated or not.
// The type of PowerUp is stored as a string.
class PowerUp : public GameObject
{
public:
    // PowerUp State
    std::string Type;
    GLfloat     Duration;
    GLboolean   Activated;
    // Constructor
    PowerUp(std::string type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture)
    : GameObject(position, SIZE, texture, color, VELOCITY), Type(type), Duration(duration), Activated() { }
};

#endif /* power_up_h */
