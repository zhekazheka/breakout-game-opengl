//
//  chaos-power-up.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/21/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "chaos-power-up.h"
#include "post-processor.h"

ChaosPowerUp::ChaosPowerUp(PostProcessor* postProcessor, EPowerUpType type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture)
: PowerUp(type, color, duration, position, texture)
{
    this->postProcessor = postProcessor;
}

void ChaosPowerUp::Activate()
{
    PowerUp::Activate();
    
    if (!postProcessor->Confuse)
    {
        postProcessor->Chaos = GL_TRUE;
    }
}

void ChaosPowerUp::Deactivate()
{
    PowerUp::Deactivate();
    
    postProcessor->Chaos = GL_FALSE;
}
