//
//  change-speed-power-up.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/19/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef change_speed_power_up_h
#define change_speed_power_up_h

#include "power-up.h"

class ChangeSpeedPowerUp : public PowerUp
{
public:
    ChangeSpeedPowerUp(EPowerUpType type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture);
    
    void Activate();
    void Deactivate();
};

#endif /* change_speed_power_up_h */
