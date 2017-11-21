//
//  chaos-power-up.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/21/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef chaos_power_up_h
#define chaos_power_up_h

#include "power-up.h"

class PostProcessor;

class ChaosPowerUp : public PowerUp
{
public:
    ChaosPowerUp(PostProcessor* postProcessor, EPowerUpType type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture);
    
    void Activate();
    void Deactivate();
    
private:
    PostProcessor* postProcessor;
};

#endif /* chaos_power_up_h */
