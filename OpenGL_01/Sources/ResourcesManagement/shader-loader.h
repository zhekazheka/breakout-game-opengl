//
//  shader-loader.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 10/6/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef shader_loader_h
#define shader_loader_h

#include <map>
#include <string>

#include <GL/glew.h>

#include "shader.h"

class ShaderLoader
{
public:
    ShaderLoader() { }
    
    // Resource storage
    std::map<std::string, Shader> Shaders;
    
    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
    
    // Retrieves a stored sader
    Shader GetShader(std::string name);
;
    // Properly de-allocates all loaded shaders
    void Clear();
private:
    // Loads and generates a shader from file
    Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
};

#endif /* shader_loader_h */
