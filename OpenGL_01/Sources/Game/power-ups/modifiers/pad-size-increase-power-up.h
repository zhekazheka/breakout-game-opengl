//
//  pad-size-increase-power-up.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/21/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef pad_size_increase_power_up_h
#define pad_size_increase_power_up_h

#include "power-up.h"

class PadSizeIncreasePowerUp : public PowerUp
{
public:
    PadSizeIncreasePowerUp(EPowerUpType type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture);
    
    void Activate();
    void Deactivate();
};

#endif /* pad_size_increase_power_up_h */
