//
//  player.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/19/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "player.h"

#include <iostream>

Player::Player(CollisionDetector* collisionDetector, glm::vec2 startPosition, glm::vec2 size, Texture2D texture, int initialLives)
: Collidable(collisionDetector, startPosition, size, texture)
{
    liveComponent = new LiveComponent(initialLives, initialLives);
}

Player::~Player()
{
    delete liveComponent;
}

LiveComponent* Player::GetLiveComponent() const
{
    return liveComponent;
}

bool Player::IsDynamic()
{
    return true;
}

void Player::HandleCollision(const GameObject &other, Collision& collision)
{
    std::cout << "[Player::HandleCollision] with " << other.Sprite.ID;
}

