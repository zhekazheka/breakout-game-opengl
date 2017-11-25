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
//#include "simple-collision-detector.h"
#include "player.h"
#include "ball-object.h"
#include "power-ups-controller.h"
#include "power-ups-factory.h"
#include "collision-detector.h"

Game::Game(GLuint width, GLuint height)
: State(GAME_MENU), Keys(), Width(width), Height(height)
{
    
}

Game::~Game()
{
    delete spriteRenderer;
    delete player;
    delete ball;
    delete particleGenerator;
    delete postProcessor;
    delete textRenderer;
    delete powerUpsController;
    delete powerUpsFactory;
    delete collisionDetector;
}

void Game::Init(ShaderLoader* shaderLoader, TextureLoader* textureLoader)
{
    this->shaderLoader = shaderLoader;
    this->textureLoader = textureLoader;
    
    this->collisionDetector = new CollisionDetector();
    
    Shader spriteShader = shaderLoader->LoadShader("OpenGL_01/Shaders/SpriteRendering/sprite.vert",
                                                   "OpenGL_01/Shaders/SpriteRendering/sprite.frag", nullptr, "sprite");
    
    Shader particleShader = shaderLoader->LoadShader("OpenGL_01/Shaders/Particles/simpleParticle.vert",
                                                     "OpenGL_01/Shaders/Particles/simpleParticle.frag", nullptr, "particles");
    
    Shader postProcessorShader = shaderLoader->LoadShader("OpenGL_01/Shaders/PostprocessEffects/basicPostEffects.vert",
                                                    "OpenGL_01/Shaders/PostprocessEffects/basicPostEffects.frag", nullptr, "post-process");
    
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    spriteShader.Use();
    spriteShader.SetInteger("image", 0);
    spriteShader.SetMatrix4("projection", projection);
    
    particleShader.Use().SetInteger("sprite", 0);
    particleShader.SetMatrix4("projection", projection);
    
    // Set render-specific controls
    spriteRenderer = new SpriteRenderer(spriteShader);
    
    // Load textures
    Texture2D ballTexture = textureLoader->LoadTexture("OpenGL_01/Resources/Textures/awesomeface.png", GL_TRUE, "face");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/LevelAssets/background.jpg", GL_FALSE, "background");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/LevelAssets/block.png", GL_FALSE, "block");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/LevelAssets/block_solid.png", GL_FALSE, "block_solid");
    Texture2D paddleTexture = textureLoader->LoadTexture("OpenGL_01/Resources/Textures/LevelAssets/paddle.png", true, "paddle");
    Texture2D particleTexture = textureLoader->LoadTexture("OpenGL_01/Resources/Textures/particle.png", GL_TRUE, "particle");
    
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/PowerUps/powerup_speed.png", GL_TRUE, "powerUpSpeed");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/PowerUps/powerup_sticky.png", GL_TRUE, "powerUpSticky");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/PowerUps/powerup_passthrough.png", GL_TRUE, "powerUpPass");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/PowerUps/powerup_increase.png", GL_TRUE, "powerUpSize");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/PowerUps/powerup_confuse.png", GL_TRUE, "powerUpConfuse");
    textureLoader->LoadTexture("OpenGL_01/Resources/Textures/PowerUps/powerup_chaos.png", GL_TRUE, "powerUpChaos");
    
    
    // Load levels
    for(int i = 0; i < 4; ++i)
    {
        GameLevel level(textureLoader, collisionDetector);
        
        std::stringstream ss;
        ss << "OpenGL_01/Resources/Levels/" << i << ".lvl";
        const std::string& tmp = ss.str();
        const char* filePath = tmp.c_str();
        level.Load(filePath, this->Width, this->Height * 0.5);
        
        this->levels.push_back(level);
    }
    
    // current level
    this->levelIndex = 0;
    
    glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2,
                                    this->Height - PLAYER_SIZE.y);
    player = new Player(collisionDetector, playerPos, PLAYER_SIZE, paddleTexture, 3);
    
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    ball = new BallObject(collisionDetector, ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ballTexture);
    
    particleGenerator = new ParticleGenerator(particleShader, particleTexture, 500);
    
    postProcessor = new PostProcessor(postProcessorShader, this->Width, this->Height);
    
    textRenderer = new TextRenderer(this->Width, this->Height, shaderLoader);
    textRenderer->Load("OpenGL_01/Resources/Fonts/arial.ttf", 24);
    
    powerUpsFactory = new PowerUpsFactory(textureLoader, postProcessor);
    powerUpsController = new PowerUpsController(powerUpsFactory, player, ball, spriteRenderer);
}

void Game::Update(GLfloat dt)
{
    ball->Move(dt, this->Width);
    
//    DoCollisions();
    collisionDetector->Update(dt);
    
    particleGenerator->Update(dt, *ball, 2, glm::vec2(ball->Radius / 2));
    
    if (ball->Position.y >= this->Height) // Did ball reach bottom edge?
    {
        LiveComponent* liveComponent = player->GetLiveComponent();
        liveComponent->ReduceLives(1);
        if(!liveComponent->IsAlive())
        {
            this->ResetLevel();
            this->State = GAME_MENU;
        }
        this->ResetPlayer();
    }
    
    powerUpsController->Update(dt, Height);
    
    postProcessor->Update(dt);
    
    if (this->State == GAME_ACTIVE && this->levels[this->levelIndex].IsCompleted())
    {
        this->ResetLevel();
        this->ResetPlayer();
        postProcessor->Chaos = GL_TRUE;
        this->State = GAME_WIN;
    }
}


void Game::ProcessInput(GLfloat dt)
{
    if (this->State == GAME_MENU)
    {
        if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
        {
            this->State = GAME_ACTIVE;
            this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
        }
        if (this->Keys[GLFW_KEY_W] && !this->KeysProcessed[GLFW_KEY_W])
        {
            this->levelIndex = (this->levelIndex + 1) % 4;
            this->KeysProcessed[GLFW_KEY_W] = GL_TRUE;
        }
        if (this->Keys[GLFW_KEY_S] && !this->KeysProcessed[GLFW_KEY_S])
        {
            this->levelIndex = levelIndex > 0 ? --levelIndex : 3;
            this->KeysProcessed[GLFW_KEY_S] = GL_TRUE;
        }
    }
    
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
    
    if (this->State == GAME_WIN)
    {
        if (this->Keys[GLFW_KEY_ENTER])
        {
            this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
            postProcessor->Chaos = GL_FALSE;
            this->State = GAME_MENU;
        }
    }
}

void Game::Render()
{
    if(this->State == GAME_ACTIVE || this->State == GAME_MENU || this->State == GAME_WIN)
    {
        postProcessor->BeginRender();
        
        // Draw background
        Texture2D backgroundTexture = textureLoader->GetTexture("background");
        spriteRenderer->DrawSprite(backgroundTexture,
                             glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
                             );
        // Draw level
        this->levels[this->levelIndex].Draw(*spriteRenderer);
        
        //Draw player
        this->player->Draw(*spriteRenderer);
        
        // Draw particles
        particleGenerator->Draw();
        
        // Draw ball
        ball->Draw(*spriteRenderer);
        
        powerUpsController->Render();
        
        postProcessor->EndRender();
        
        postProcessor->Render(glfwGetTime());
        
        std::stringstream ss;
        ss << player->GetLiveComponent()->GetLives();
        textRenderer->RenderText("Lives: " + ss.str(), 5.0f, 5.0f, 1.0f);
    }
    
    if (this->State == GAME_MENU)
    {
        textRenderer->RenderText("Press ENTER to start", 250.0f, this->Height / 2, 1.0f);
        textRenderer->RenderText("Press W or S to select level", 245.0f, this->Height / 2 + 20.0f, 0.75f);
    }
    
    if (this->State == GAME_WIN)
    {
        textRenderer->RenderText(
                         "You WON!!!", 320.0, Height / 2 - 20.0, 1.0, glm::vec3(0.0, 1.0, 0.0)
                         );
        textRenderer->RenderText(
                         "Press ENTER to retry or ESC to quit", 130.0, Height / 2, 1.0, glm::vec3(1.0, 1.0, 0.0)
                         );
    }
}

void Game::DoCollisions()
{
//    for (GameObject &box : this->levels[this->levelIndex].Bricks)
//    {
//        if (box.Destroyed)
//        {
//            continue;
//        }
//        
//        Collision collision = CheckCollision(*ball, box);
//        if (!std::get<0>(collision)) // If collision is true
//        {
//            continue;
//        }
//        
//        // Destroy block if not solid
//        box.Destroyed = !box.IsSolid;
//        
//        if(box.Destroyed)
//        {
//            postProcessor->SetShakeTime(0.05f);
//            powerUpsController->SpawnPowerUps(box.Position);
//        }
//        
//        // Collision resolution
//        Direction dir = std::get<1>(collision);
//        glm::vec2 diff_vector = std::get<2>(collision);
//        
//        if (!(ball->PassThrough && !box.IsSolid))
//        {
//            if (dir == LEFT || dir == RIGHT) // Horizontal collision
//            {
//                ball->Velocity.x = -ball->Velocity.x; // Reverse horizontal velocity
//                // Relocate
//                GLfloat penetration = ball->Radius - std::abs(diff_vector.x);
//                ball->Position.x += dir == LEFT ? penetration : -penetration;
//            }
//            else // Vertical collision
//            {
//                ball->Velocity.y = -ball->Velocity.y; // Reverse vertical velocity
//                // Relocate
//                GLfloat penetration = ball->Radius - std::abs(diff_vector.y);
//                ball->Position.y += dir == DOWN ? penetration : -penetration;
//            }
//        }
//    }
//    
//    Collision result = CheckCollision(*ball, *player);
//    if (!ball->Stuck && std::get<0>(result))
//    {
//        // Check where it hit the board, and change velocity based on where it hit the board
//        GLfloat centerBoard = player->Position.x + player->Size.x / 2;
//        GLfloat distance = (ball->Position.x + ball->Radius) - centerBoard;
//        GLfloat percentage = distance / (player->Size.x / 2);
//        // Then move accordingly
//        GLfloat strength = 2.0f;
//        glm::vec2 oldVelocity = ball->Velocity;
//        ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
//        ball->Velocity.y = -1 * abs(ball->Velocity.y);
//        ball->Velocity = glm::normalize(ball->Velocity) * glm::length(oldVelocity);
//        
//        ball->Stuck = ball->Sticky;
//    }
}

void Game::ResetLevel()
{
    std::stringstream ss;
    ss << "OpenGL_01/Resources/Levels/" << this->levelIndex << ".lvl";
    const std::string& tmp = ss.str();
    const char* filePath = tmp.c_str();
    this->levels[this->levelIndex].Load(filePath, this->Width, this->Height * 0.5f);
    player->GetLiveComponent()->Reset();
}

void Game::ResetPlayer()
{
    // Reset player/ball stats
    player->Size = PLAYER_SIZE;
    player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    ball->Reset(player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
}
