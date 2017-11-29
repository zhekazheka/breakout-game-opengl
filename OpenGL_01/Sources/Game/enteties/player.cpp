//
//  player.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/19/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "player.h"

#include <iostream>

Player::Player(bool isSolid, glm::vec2 startPosition, Texture2D texture, int initialLives)
: Collidable(isSolid, startPosition, PLAYER_SIZE, texture), liveComponent( new LiveComponent(initialLives, initialLives))
{}

Player::~Player()
{}

LiveComponent* Player::GetLiveComponent() const
{
    return liveComponent.get();
}

bool Player::IsDynamic() const
{
    return true;
}

ECollisionType Player::GetCollisionType() const
{
    return ECollisionType::PLAYER;
}

void Player::HandleCollision(const ICollidable* other, Collision& collision)
{}
