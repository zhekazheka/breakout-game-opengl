//
//  power-ups-controller.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/19/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef power_ups_controller_h
#define power_ups_controller_h

#include <vector>
#include "glm.hpp"
#include "power-up.h"

class PowerUpsFactory;
class Player;
class BallObject;
class SpriteRenderer;

class PowerUpsController
{
public:
    PowerUpsController(PowerUpsFactory* powerUpsFactory, Player* player, BallObject* ball, SpriteRenderer* spriteRenderer);
    
    void SpawnPowerUps(glm::vec2 &position);
    void ActivatePowerUp(PowerUp &powerUp);
    void Update(float dt, float levelHeight);
    void Render();
    
private:
    bool IsOtherPowerUpActive(EPowerUpType type);
    bool CheckCollision(GameObject &one, GameObject &two);
    
    PowerUpsFactory* powerUpsFactory;
    std::vector<std::unique_ptr<PowerUp>> powerUps;
    
    Player* player;
    BallObject* ball;
    SpriteRenderer* spriteRenderer;
};

#endif /* power_ups_controller_h */
