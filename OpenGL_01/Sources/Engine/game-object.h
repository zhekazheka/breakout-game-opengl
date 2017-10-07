//
//  game-object.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 10/7/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef game_object_h
#define game_object_h

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite-renderer.h"


// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    // Object state
    glm::vec2   Position, Size, Velocity;
    glm::vec3   Color;
    GLfloat     Rotation;
    GLboolean   IsSolid;
    GLboolean   Destroyed;
    
    // Render state
    Texture2D   Sprite;
    
    // Constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    
    // Draw sprite
    virtual void Draw(SpriteRenderer &renderer);
};

#endif /* game_object_h */
