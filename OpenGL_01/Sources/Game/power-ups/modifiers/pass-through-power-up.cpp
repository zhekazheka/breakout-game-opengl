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
    
    ballObject->EnablePassThrough(true);
}

void PassThroughPowerUp::Deactivate()
{
    PowerUp::Deactivate();
    
    ballObject->EnablePassThrough(false);
}
