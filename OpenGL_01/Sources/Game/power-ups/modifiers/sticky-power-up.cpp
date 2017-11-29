//
//  sticky-power-up.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/21/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "sticky-power-up.h"
#include "ball-object.h"
#include "player.h"

StickyPowerUp::StickyPowerUp(EPowerUpType type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture)
: PowerUp(type, color, duration, position, texture)
{
    
}

void StickyPowerUp::Activate()
{
    PowerUp::Activate();
    
    ballObject->EnableSticky(true);
    player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
}

void StickyPowerUp::Deactivate()
{
    PowerUp::Deactivate();
    
    ballObject->EnableSticky(false);
    player->Color = glm::vec3(1.0f);
}
