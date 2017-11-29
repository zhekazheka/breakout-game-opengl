//
//  pad-size-increase-power-up.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/21/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "pad-size-increase-power-up.h"
#include "ball-object.h"
#include "player.h"

PadSizeIncreasePowerUp::PadSizeIncreasePowerUp(EPowerUpType type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture)
: PowerUp(type, color, duration, position, texture)
{
    
}

void PadSizeIncreasePowerUp::Activate()
{
    PowerUp::Activate();
    
    player->Size.x += 50;
    player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
    
    ballObject->EnableSticky(true);
}

void PadSizeIncreasePowerUp::Deactivate()
{
    PowerUp::Deactivate();
 
    player->Size.x = std::max(PLAYER_SIZE.x, player->Size.x - 50);
    player->Color = glm::vec3(1.0f);
    
    ballObject->EnableSticky(false);
}
