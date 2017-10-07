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
    
    // Load textures
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/awesomeface.png", GL_TRUE, "face");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/LevelAssets/background.jpg", GL_FALSE, "background");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/LevelAssets/block.png", GL_FALSE, "block");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/LevelAssets/block_solid.png", GL_FALSE, "block_solid");
    Texture2D paddleTexture = textureLoader->LoadTexture("OpenGL_01/Resources/Textures/LevelAssets/paddle.png", true, "paddle");
    
    // Load levels
    GameLevel one(textureLoader);
    one.Load("OpenGL_01/Resources/Levels/one.lvl", this->Width, this->Height * 0.5);
    
    GameLevel two(textureLoader);
    two.Load("OpenGL_01/Resources/Levels/two.lvl", this->Width, this->Height * 0.5);
    
    GameLevel three(textureLoader);
    three.Load("OpenGL_01/Resources/Levels/three.lvl", this->Width, this->Height * 0.5);
    
    GameLevel four(textureLoader);
    four.Load("OpenGL_01/Resources/Levels/four.lvl", this->Width, this->Height * 0.5);
    
    this->levels.push_back(one);
    this->levels.push_back(two);
    this->levels.push_back(three);
    this->levels.push_back(four);
    this->level = 0;
    
    glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2,
                                    this->Height - PLAYER_SIZE.y);
    player = new GameObject(playerPos, PLAYER_SIZE, paddleTexture);
}

void Game::Update(GLfloat dt)
{
    
}


void Game::ProcessInput(GLfloat dt)
{
    if (this->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (this->Keys[GLFW_KEY_A] || this->Keys[GLFW_KEY_LEFT])
        {
            if (player->Position.x >= 0)
            {
                player->Position.x -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_D] || this->Keys[GLFW_KEY_RIGHT])
        {
            if (player->Position.x <= this->Width - player->Size.x)
            {
                player->Position.x += velocity;
            }
        }
    }
}

void Game::Render()
{
    if(this->State == GAME_ACTIVE)
    {
        // Draw background
        Texture2D backgroundTexture = textureLoader->GetTexture("background");
        spriteRenderer->DrawSprite(backgroundTexture,
                             glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
                             );
        // Draw level
        this->levels[this->level].Draw(*spriteRenderer);
        
        //Draw player
        this->player->Draw(*spriteRenderer);
    }
}
