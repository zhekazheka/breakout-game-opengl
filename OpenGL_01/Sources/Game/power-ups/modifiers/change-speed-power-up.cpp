//
//  change-speed-power-up.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/19/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "change-speed-power-up.h"
#include "ball-object.h"

ChangeSpeedPowerUp::ChangeSpeedPowerUp(EPowerUpType type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture)
: PowerUp(type, color, duration, position, texture)
{
    
}

void ChangeSpeedPowerUp::Activate()
{
    PowerUp::Activate();
    ballObject->Velocity *= 1.2;
}

void ChangeSpeedPowerUp::Deactivate()
{
    PowerUp::Deactivate();
    ballObject->Velocity /= 1.2f;
}
