//
//  player.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/19/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "player.h"

Player::Player(glm::vec2 startPosition, glm::vec2 size, Texture2D texture, int initialLives)
: GameObject(startPosition, size, texture)
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

