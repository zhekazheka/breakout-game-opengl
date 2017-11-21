//
//  pass-through-power-up.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/21/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "pass-through-power-up.h"
#include "ball-object.h"
#include "player.h"

PassThroughPowerUp::PassThroughPowerUp(EPowerUpType type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture)
: PowerUp(type, color, duration, position, texture)
{
    
}

void PassThroughPowerUp::Activate()
{
    PowerUp::Activate();
    
    ballObject->PassThrough = GL_TRUE;
    ballObject->Color = glm::vec3(1.0f, 0.5f, 0.5f);
}

void PassThroughPowerUp::Deactivate()
{
    PowerUp::Deactivate();
    
    ballObject->PassThrough = GL_FALSE;
    ballObject->Color = glm::vec3(1.0f);
}
