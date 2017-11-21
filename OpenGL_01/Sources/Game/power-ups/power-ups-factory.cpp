//
//  power-ups-factory.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/19/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "power-ups-factory.h"

#include <iostream>

#include "texture-loader.h"
#include "post-processor.h"
#include "change-speed-power-up.h"
#include "sticky-power-up.h"
#include "pass-through-power-up.h"
#include "pad-size-increase-power-up.h"
#include "confuse-power-up.h"
#include "chaos-power-up.h"

PowerUpsFactory::PowerUpsFactory(TextureLoader* textureLoader, PostProcessor* postProcessor)
{
    this->textureLoader = textureLoader;
    this->postProcessor = postProcessor;
}

std::unique_ptr<PowerUp> PowerUpsFactory::SpawnPowerUp(EPowerUpType type, glm::vec2 position)
{
    switch(type)
    {
        case EPowerUpType::Speed:
            return std::unique_ptr<PowerUp>(new ChangeSpeedPowerUp(type, glm::vec3(0.5f, 0.5f, 1.0f), 5.0f, position, textureLoader->GetTexture("powerUpSpeed")));
            
        case EPowerUpType::Sticky:
            return std::unique_ptr<PowerUp>(new StickyPowerUp(type, glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, position, textureLoader->GetTexture("powerUpSticky")));
            
        case EPowerUpType::PassThrough:
            return std::unique_ptr<PowerUp>(new PassThroughPowerUp(type, glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, position, textureLoader->GetTexture("powerUpPass")));
        
        case EPowerUpType::PadSizeIncrease:
            return std::unique_ptr<PowerUp>(new PadSizeIncreasePowerUp(type, glm::vec3(1.0f, 0.6f, 0.4), 5.0f, position, textureLoader->GetTexture("powerUpSize")));
            
        case EPowerUpType::Confuse:
            return std::unique_ptr<PowerUp>(new ConfusePowerUp(postProcessor, type, glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, position, textureLoader->GetTexture("powerUpConfuse")));
            
        case EPowerUpType::Chaose:
            return std::unique_ptr<PowerUp>(new ChaosPowerUp(postProcessor, type, glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, position, textureLoader->GetTexture("powerUpChaos")));
    }
    
    std::cout << "No PowerUp for type: " << type << std::endl;
    return nullptr;
}
