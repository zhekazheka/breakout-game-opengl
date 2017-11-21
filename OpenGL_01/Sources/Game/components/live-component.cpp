//
//  live-component.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/19/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "live-component.h"

#include <iostream>

LiveComponent::LiveComponent(int initialLives, int maxLives)
{
    this->lives = initialLives;
    this->maxLives = maxLives;
}

const int LiveComponent::GetLives() const
{
    return lives;
}

void LiveComponent::AddLives(int healing)
{
    lives += std::min(lives + healing, maxLives);
}

void LiveComponent::ReduceLives(int damage)
{
    lives = std::max(lives - damage, 0);
}

void LiveComponent::Reset()
{
    lives = maxLives;
}

bool LiveComponent::IsAlive() const
{
    return lives > 0;
}
