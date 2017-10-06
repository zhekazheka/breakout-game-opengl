//
//  texture-loader.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 10/6/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef texture_loader_h
#define texture_loader_h

#include <map>
#include <string>

#include <GL/glew.h>

#include "texture.h"

class TextureLoader
{
public:
    TextureLoader() { }
    
    // Resource storage
    std::map<std::string, Texture2D> Textures;
    
    // Loads (and generates) a texture from file
    Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
    
    // Retrieves a stored texture
    Texture2D GetTexture(std::string name);
    
    // Properly de-allocates all loaded resources
    void Clear();
private:
    // Loads a single texture from file
    Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#endif /* texture_loader_h */
