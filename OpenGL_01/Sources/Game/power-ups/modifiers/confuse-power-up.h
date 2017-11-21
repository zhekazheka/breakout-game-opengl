//
//  confuse-power-up.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/21/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef confuse_power_up_h
#define confuse_power_up_h

#include "power-up.h"

class PostProcessor;

class ConfusePowerUp : public PowerUp
{
public:
    ConfusePowerUp(PostProcessor* postProcessor, EPowerUpType type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture);
    
    void Activate();
    void Deactivate();
    
private:
    PostProcessor* postProcessor;
};

#endif /* confuse_power_up_h */
