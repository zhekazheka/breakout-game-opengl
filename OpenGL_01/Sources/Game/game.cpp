//
//  Game.cpp
//  OpenGL_01
//
//  Created by zhekazheka on 10/6/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#include "game.h"

#include <sstream>

#include "shader-loader.h"
#include "texture-loader.h"
#include "simple-collision-detector.h"

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
    Texture2D ballTexture = textureLoader->LoadTexture("OpenGL_01/Resources/Textures/awesomeface.png", GL_TRUE, "face");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/LevelAssets/background.jpg", GL_FALSE, "background");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/LevelAssets/block.png", GL_FALSE, "block");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/LevelAssets/block_solid.png", GL_FALSE, "block_solid");
    Texture2D paddleTexture = textureLoader->LoadTexture("OpenGL_01/Resources/Textures/LevelAssets/paddle.png", true, "paddle");
    
    // Load levels
    for(int i = 0; i < 4; ++i)
    {
        GameLevel level(textureLoader);
        
        std::stringstream ss;
        ss << "OpenGL_01/Resources/Levels/" << i << ".lvl";
        const std::string& tmp = ss.str();
        const char* filePath = tmp.c_str();
        level.Load(filePath, this->Width, this->Height * 0.5);
        
        this->levels.push_back(level);
    }
    
    // current level
    this->level = 0;
    
    glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2,
                                    this->Height - PLAYER_SIZE.y);
    player = new GameObject(playerPos, PLAYER_SIZE, paddleTexture);
    
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ballTexture);
}

void Game::Update(GLfloat dt)
{
    ball->Move(dt, this->Width);
    
    DoCollisions();
    
    if (ball->Position.y >= this->Height) // Did ball reach bottom edge?
    {
        this->ResetLevel();
        this->ResetPlayer();
    }
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
                if(ball->Stuck)
                {
                    ball->Position.x -= velocity;
                }
            }
        }
        if (this->Keys[GLFW_KEY_D] || this->Keys[GLFW_KEY_RIGHT])
        {
            if (player->Position.x <= this->Width - player->Size.x)
            {
                player->Position.x += velocity;
                if(ball->Stuck)
                {
                    ball->Position.x += velocity;
                }
            }
        }
        if(this->Keys[GLFW_KEY_SPACE])
        {
            ball->Stuck = false;
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
        
        ball->Draw(*spriteRenderer);
    }
}

void Game::DoCollisions()
{
    for (GameObject &box : this->levels[this->level].Bricks)
    {
        if (box.Destroyed)
        {
            continue;
        }
        
        Collision collision = CheckCollision(*ball, box);
        if (!std::get<0>(collision)) // If collision is true
        {
            continue;
        }
        
        // Destroy block if not solid
        box.Destroyed = !box.IsSolid;
        
        // Collision resolution
        Direction dir = std::get<1>(collision);
        glm::vec2 diff_vector = std::get<2>(collision);
        
        if (dir == LEFT || dir == RIGHT) // Horizontal collision
        {
            ball->Velocity.x = -ball->Velocity.x; // Reverse horizontal velocity
            // Relocate
            GLfloat penetration = ball->Radius - std::abs(diff_vector.x);
            ball->Position.x += dir == LEFT ? penetration : -penetration;
        }
        else // Vertical collision
        {
            ball->Velocity.y = -ball->Velocity.y; // Reverse vertical velocity
            // Relocate
            GLfloat penetration = ball->Radius - std::abs(diff_vector.y);
            ball->Position.y += dir == DOWN ? penetration : -penetration;
        }
    }
    
    Collision result = CheckCollision(*ball, *player);
    if (!ball->Stuck && std::get<0>(result))
    {
        // Check where it hit the board, and change velocity based on where it hit the board
        GLfloat centerBoard = player->Position.x + player->Size.x / 2;
        GLfloat distance = (ball->Position.x + ball->Radius) - centerBoard;
        GLfloat percentage = distance / (player->Size.x / 2);
        // Then move accordingly
        GLfloat strength = 2.0f;
        glm::vec2 oldVelocity = ball->Velocity;
        ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        ball->Velocity.y = -1 * abs(ball->Velocity.y);
        ball->Velocity = glm::normalize(ball->Velocity) * glm::length(oldVelocity);
    }
}

void Game::ResetLevel()
{
    std::stringstream ss;
    ss << "OpenGL_01/Resources/Levels/" << this->level << ".lvl";
    const std::string& tmp = ss.str();
    const char* filePath = tmp.c_str();
    this->levels[this->level].Load(filePath, this->Width, this->Height * 0.5f);
}

void Game::ResetPlayer()
{
    // Reset player/ball stats
    player->Size = PLAYER_SIZE;
    player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    ball->Reset(player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
}
