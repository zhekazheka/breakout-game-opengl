//
//  live-component.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 11/19/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef live_component_h
#define live_component_h

class LiveComponent
{
public:
    LiveComponent(int initialLives, int maxLives);
    
    const int GetLives() const;
    void AddLives(int healing);
    void ReduceLives(int damage);
    void Reset();
    
    bool IsAlive() const;
    
private:
    int lives;
    int maxLives;
};

#endif /* live_component_h */
