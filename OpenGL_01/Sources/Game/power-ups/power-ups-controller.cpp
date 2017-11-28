//
//  power-ups-controller.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/19/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "power-ups-controller.h"
#include "power-ups-factory.h"
#include "player.h"
#include "ball-object.h"
#include "game-events.h"
#include "event-dispatcher.h"
#include "brick.h"

PowerUpsController::PowerUpsController(PowerUpsFactory* powerUpsFactory, Player* player, BallObject* ball, SpriteRenderer* spriteRenderer)
{
    this->powerUpsFactory = powerUpsFactory;
    this->player = player;
    this->ball = ball;
    this->spriteRenderer = spriteRenderer;
    
    EventDispatcher::GetInstance().Dispatcher.listen
    (std::function<void(const BrickDestroyedEvent& ev)>([this](const BrickDestroyedEvent& ev)
                                                        {
                                                            SpawnPowerUps(ev.GetBrick()->Position);
                                                        })
     );
}

GLboolean ShouldSpawn(GLuint chance)
{
    GLuint random = rand() % 100 + 1;
    return random <= chance;
}

void PowerUpsController::SpawnPowerUps(glm::vec2 &position)
{
    std::unique_ptr<PowerUp> powerUp;
    if (ShouldSpawn(42))
    {
        int min = EPowerUpType::Speed;
        int max = EPowerUpType::PadSizeIncrease;
        EPowerUpType type = static_cast<EPowerUpType>((rand() % (max - min + 1)) + min);
        powerUp = powerUpsFactory->SpawnPowerUp(type, position);
    }

    if (ShouldSpawn(15)) // Negative powerups should spawn more often
    {
        int min = EPowerUpType::Confuse;
        int max = EPowerUpType::Chaose;
        EPowerUpType type = static_cast<EPowerUpType>((rand() % (max - min + 1)) + min);
        powerUp = powerUpsFactory->SpawnPowerUp(type, position);
    }
    
    if(powerUp != nullptr)
    {
        powerUp.get()->SetEntities(player, ball);
        this->powerUps.push_back(std::move(powerUp));
    }
}

void PowerUpsController::ActivatePowerUp(PowerUp &powerUp)
{
    if(!IsOtherPowerUpActive(powerUp.Type))
    {
        powerUp.Activate();
    }
}

bool PowerUpsController::IsOtherPowerUpActive(EPowerUpType type)
{
    for (std::vector<std::unique_ptr<PowerUp>>::iterator it = powerUps.begin(); it != powerUps.end(); ++it)
    {
        PowerUp* powerUp = it->get();
        if (powerUp->Activated)
        {
            if (powerUp->Type == type)
            {
                return GL_TRUE;
            }
        }
    }
    return GL_FALSE;
}

// [zheka] TODO remove it after collision refactoring. It is here to prevent linker error with game.cpp
bool PowerUpsController::CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
    // Collision x-axis?
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
    two.Position.x + two.Size.x >= one.Position.x;
    // Collision y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
    two.Position.y + two.Size.y >= one.Position.y;
    // Collision only if on both axes
    return collisionX && collisionY;
}

void PowerUpsController::Update(float dt, float levelHeight)
{
    for (std::vector<std::unique_ptr<PowerUp>>::iterator it = powerUps.begin(); it != powerUps.end(); ++it)
    {
        PowerUp* powerUp = it->get();
        powerUp->Position += powerUp->Velocity * dt;
        if (powerUp->Activated)
        {
            powerUp->Duration -= dt;

            if (powerUp->Duration <= 0.0f)
            {
                powerUp->Deactivate();
            }
        }
        
        if (!powerUp->Destroyed)
        {
            if (powerUp->Position.y >= levelHeight)
            {
                powerUp->Destroyed = GL_TRUE;
            }
            
            if (CheckCollision(*player, *powerUp))
            {	// Collided with player, now activate powerup
                ActivatePowerUp(*powerUp);
                powerUp->Destroyed = GL_TRUE;
            }
        }
    }
    this->powerUps.erase(std::remove_if(this->powerUps.begin(), this->powerUps.end(),
                                        [](std::unique_ptr<PowerUp> const& powerUp) { return powerUp.get()->Destroyed && !powerUp.get()->Activated; }
                                        ), this->powerUps.end());
}

void PowerUpsController::Render()
{
    for (std::vector<std::unique_ptr<PowerUp>>::iterator it = powerUps.begin(); it != powerUps.end(); ++it)
    {
        PowerUp* powerUp = it->get();
        if (!powerUp->Destroyed)
        {
            powerUp->Draw(*spriteRenderer);
        }
    }
}
