//
//  power-ups-factory.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/19/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef power_ups_factory_h
#define power_ups_factory_h

#include "power-up.h"

class TextureLoader;
class PostProcessor;

class PowerUpsFactory
{
public:
    PowerUpsFactory(TextureLoader* textureLoader, PostProcessor* postProcessor);
    
    std::unique_ptr<PowerUp> SpawnPowerUp(EPowerUpType type, glm::vec2 position);
    
private:
    GLboolean ShouldSpawn(GLuint chance);
    
    TextureLoader* textureLoader;
    PostProcessor* postProcessor;
};

#endif /* power_ups_factory_h */
