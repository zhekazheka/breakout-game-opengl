//
//  game-level.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 10/7/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef game_level_h
#define game_level_h

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "game-object.h"
#include "sprite-renderer.h"
#include "texture-loader.h"


/// GameLevel holds all Tiles as part of a Breakout level and
/// hosts functionality to Load/render levels from the harddisk.
class GameLevel
{
public:
    // Level state
    std::vector<GameObject> Bricks;
    
    // Constructors
    GameLevel() { }
    GameLevel(TextureLoader* textureLoader);
    
    // Loads level from file
    void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    
    // Render level
    void Draw(SpriteRenderer &renderer);
    
    // Check if the level is completed (all non-solid tiles are destroyed)
    GLboolean IsCompleted();
private:
    // Initialize level from tile data
    void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
    
    TextureLoader* textureLoader;
};

#endif /* game_level_h */
