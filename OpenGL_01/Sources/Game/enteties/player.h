//
//  player.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/19/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef player_h
#define player_h

#include "live-component.h"
#include "collidable.h"

// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(500.0f);

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);

class Player : public Collidable
{
public:
    Player(bool isSolid, glm::vec2 startPosition, glm::vec2 size, Texture2D texture, int initialLives);
    ~Player();
    
    LiveComponent* GetLiveComponent() const;
    
    bool IsDynamic() const;
    ECollisionType GetCollisionType() const;
    void HandleCollision(const ICollidable* other, Collision& collision);
    
private:
    LiveComponent* liveComponent;
};

#endif /* player_h */
