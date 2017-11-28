//
//  game-events.h
//  OpenGL_01
//
//  Created by zhekazheka on 11/28/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef game_events_h
#define game_events_h

#include "safe_event.h"

class Brick;

struct BrickDestroyedEvent
{
    Brick* GetBrick() const
    {
        return brick;
    }
    
    void SetBrick(Brick* brick)
    {
        this->brick = brick;
    }
    
private:
    Brick* brick;
};

#endif /* game_events_h */
