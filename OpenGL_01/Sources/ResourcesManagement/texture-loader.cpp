//
//  texture-loader.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 10/6/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "texture-loader.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL.h>

Texture2D TextureLoader::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D TextureLoader::GetTexture(std::string name)
{
    return Textures[name];
}

void TextureLoader::Clear()
{
    // (Properly) delete all textures
    for (auto iter : Textures)
    {
        glDeleteTextures(1, &iter.second.ID);
    }
}

Texture2D TextureLoader::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
    // Create Texture object
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // Load image
    int width, height;
    unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    
    // Now generate texture
    texture.Generate(width, height, image);
    
    // And finally free image data
    SOIL_free_image_data(image);
    return texture;
}
