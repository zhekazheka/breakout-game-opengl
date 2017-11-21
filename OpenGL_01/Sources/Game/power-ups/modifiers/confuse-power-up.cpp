//
//  confuse-power-up.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/21/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "confuse-power-up.h"
#include "post-processor.h"

ConfusePowerUp::ConfusePowerUp(PostProcessor* postProcessor, EPowerUpType type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture)
: PowerUp(type, color, duration, position, texture)
{
    this->postProcessor = postProcessor;
}

void ConfusePowerUp::Activate()
{
    PowerUp::Activate();
    
    if (!postProcessor->Chaos)
    {
        postProcessor->Confuse = GL_TRUE; // Only activate if chaos wasn't already active
    }
}

void ConfusePowerUp::Deactivate()
{
    PowerUp::Deactivate();
    
    postProcessor->Confuse = GL_FALSE;
}
