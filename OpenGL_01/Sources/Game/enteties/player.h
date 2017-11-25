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

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);

class Player : public Collidable
{
public:
    Player(CollisionDetector* collisionDetector, glm::vec2 startPosition, glm::vec2 size, Texture2D texture, int initialLives);
    ~Player();
    
    LiveComponent* GetLiveComponent() const;
    
    bool IsDynamic();
    void HandleCollision(const GameObject &other, Collision& collision);
    
private:
    LiveComponent* liveComponent;
};

#endif /* player_h */
