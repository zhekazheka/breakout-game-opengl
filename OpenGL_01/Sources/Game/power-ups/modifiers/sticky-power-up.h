//
//  sticky-power-up.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/21/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef sticky_power_up_h
#define sticky_power_up_h

#include "power-up.h"

class StickyPowerUp : public PowerUp
{
public:
    StickyPowerUp(EPowerUpType type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture);
    
    void Activate();
    void Deactivate();
};

#endif /* sticky_power_up_h */
