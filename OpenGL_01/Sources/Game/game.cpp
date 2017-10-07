//
//  Game.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 10/6/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "game.h"

#include "shader-loader.h"
#include "texture-loader.h"

Game::Game(GLuint width, GLuint height)
: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
    
}

Game::~Game()
{
    delete spriteRenderer;
}

void Game::Init(ShaderLoader* shaderLoader, TextureLoader* textureLoader)
{
    this->shaderLoader = shaderLoader;
    this->textureLoader = textureLoader;
    
    Shader spriteShader = shaderLoader->LoadShader("OpenGL_01/Shaders/SpriteRendering/sprite.vert", "OpenGL_01/Shaders/SpriteRendering/sprite.frag", nullptr, "sprite");
    
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    spriteShader.Use();
    spriteShader.SetInteger("image", 0);
    spriteShader.SetMatrix4("projection", projection);
    
    // Load textures
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/awesomeface.png", GL_TRUE, "face");
    
    // Set render-specific controls
    spriteRenderer = new SpriteRenderer(spriteShader);
}

void Game::Update(GLfloat dt)
{
    
}


void Game::ProcessInput(GLfloat dt)
{
    
}

void Game::Render()
{
    Texture2D texture = textureLoader->GetTexture("face");
    spriteRenderer->DrawSprite(texture, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
