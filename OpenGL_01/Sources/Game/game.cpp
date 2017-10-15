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
    delete player;
    delete ball;
    delete particleGenerator;
    delete postProcessor;
}

void Game::Init(ShaderLoader* shaderLoader, TextureLoader* textureLoader)
{
    this->shaderLoader = shaderLoader;
    this->textureLoader = textureLoader;
    
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
    
    particleGenerator = new ParticleGenerator(particleShader, particleTexture, 500);
    
    postProcessor = new PostProcessor(postProcessorShader, this->Width, this->Height);
}

void Game::Update(GLfloat dt)
{
    ball->Move(dt, this->Width);
    
    DoCollisions();
    
    particleGenerator->Update(dt, *ball, 2, glm::vec2(ball->Radius / 2));
    
    if (ball->Position.y >= this->Height) // Did ball reach bottom edge?
    {
        this->ResetLevel();
        this->ResetPlayer();
    }
    
    UpdatePowerUps(dt);
    
    postProcessor->Update(dt);
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
        postProcessor->BeginRender();
        
        // Draw background
        Texture2D backgroundTexture = textureLoader->GetTexture("background");
        spriteRenderer->DrawSprite(backgroundTexture,
                             glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
                             );
        // Draw level
        this->levels[this->level].Draw(*spriteRenderer);
        
        //Draw player
        this->player->Draw(*spriteRenderer);
        
        // Draw particles
        particleGenerator->Draw();
        
        // Draw ball
        ball->Draw(*spriteRenderer);
        
        for (PowerUp &powerUp : this->PowerUps)
        {
            if (!powerUp.Destroyed)
            {
                powerUp.Draw(*spriteRenderer);
            }
        }
        
        postProcessor->EndRender();
        
        postProcessor->Render(glfwGetTime());
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
        
        if(box.Destroyed)
        {
            postProcessor->SetShakeTime(0.05f);
            SpawnPowerUps(box);
        }
        
        // Collision resolution
        Direction dir = std::get<1>(collision);
        glm::vec2 diff_vector = std::get<2>(collision);
        
        if (!(ball->PassThrough && !box.IsSolid))
        {
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
        
        ball->Stuck = ball->Sticky;
    }
    
    for (PowerUp &powerUp : this->PowerUps)
    {
        if (!powerUp.Destroyed)
        {
            if (powerUp.Position.y >= this->Height)
            {
                powerUp.Destroyed = GL_TRUE;
            }
            
            if (CheckCollision(*player, powerUp))
            {	// Collided with player, now activate powerup
                ActivatePowerUp(powerUp);
                powerUp.Destroyed = GL_TRUE;
                powerUp.Activated = GL_TRUE;
            }
        }
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

GLboolean ShouldSpawn(GLuint chance)
{
    GLuint random = rand() % chance;
    return random == 0;
}

void Game::SpawnPowerUps(GameObject &block)
{
    if (ShouldSpawn(75)) // 1 in 75 chance
    {
        this->PowerUps.push_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, textureLoader->GetTexture("powerUpSpeed")));
    }

    if (ShouldSpawn(75))
    {
        this->PowerUps.push_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position, textureLoader->GetTexture("powerUpSticky")));
    }

    if (ShouldSpawn(75))
    {
        this->PowerUps.push_back(PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, textureLoader->GetTexture("powerUpPass")));
    }
                     
    if (ShouldSpawn(75))
    {
        this->PowerUps.push_back(PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4), 0.0f, block.Position, textureLoader->GetTexture("powerUpSize")));
    }
                     
    if (ShouldSpawn(15)) // Negative powerups should spawn more often
    {
        this->PowerUps.push_back(PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, textureLoader->GetTexture("powerUpConfuse")));
    }
    
    if (ShouldSpawn(15))
    {
        this->PowerUps.push_back(PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.Position, textureLoader->GetTexture("powerUpChaos")));
    }
}

void Game::ActivatePowerUp(PowerUp &powerUp)
{
    // Initiate a powerup based type of powerup
    if (powerUp.Type == "speed")
    {
        ball->Velocity *= 1.2;
    }
    else if (powerUp.Type == "sticky")
    {
        ball->Sticky = GL_TRUE;
        player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
    }
    else if (powerUp.Type == "pass-through")
    {
        ball->PassThrough = GL_TRUE;
        ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
    }
    else if (powerUp.Type == "pad-size-increase")
    {
        player->Size.x += 50;
    }
    else if (powerUp.Type == "confuse")
    {
        if (!postProcessor->Chaos)
        {
            postProcessor->Confuse = GL_TRUE; // Only activate if chaos wasn't already active
        }
    }
    else if (powerUp.Type == "chaos")
    {
        if (!postProcessor->Confuse)
        {
            postProcessor->Chaos = GL_TRUE;
        }
    }
}

GLboolean IsOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type)
{
    for (const PowerUp &powerUp : powerUps)
    {
        if (powerUp.Activated)
            if (powerUp.Type == type)
                return GL_TRUE;
    }
    return GL_FALSE;
}

void Game::UpdatePowerUps(GLfloat dt)
{
    for (PowerUp &powerUp : this->PowerUps)
    {
        powerUp.Position += powerUp.Velocity * dt;
        if (powerUp.Activated)
        {
            powerUp.Duration -= dt;
            
            if (powerUp.Duration <= 0.0f)
            {
                // Remove powerup from list (will later be removed)
                powerUp.Activated = GL_FALSE;
                // Deactivate effects
                if (powerUp.Type == "sticky")
                {
                    if (!IsOtherPowerUpActive(this->PowerUps, "sticky"))
                    {	// Only reset if no other PowerUp of type sticky is active
                        ball->Sticky = GL_FALSE;
                        player->Color = glm::vec3(1.0f);
                    }
                }
                else if (powerUp.Type == "pass-through")
                {
                    if (!IsOtherPowerUpActive(this->PowerUps, "pass-through"))
                    {	// Only reset if no other PowerUp of type pass-through is active
                        ball->PassThrough = GL_FALSE;
                        ball->Color = glm::vec3(1.0f);
                    }
                }
                else if (powerUp.Type == "confuse")
                {
                    if (!IsOtherPowerUpActive(this->PowerUps, "confuse"))
                    {	// Only reset if no other PowerUp of type confuse is active
                        postProcessor->Confuse = GL_FALSE;
                    }
                }
                else if (powerUp.Type == "chaos")
                {
                    if (!IsOtherPowerUpActive(this->PowerUps, "chaos"))
                    {	// Only reset if no other PowerUp of type chaos is active
                        postProcessor->Chaos = GL_FALSE;
                    }
                }
            }
        }
    }
    this->PowerUps.erase(std::remove_if(this->PowerUps.begin(), this->PowerUps.end(),
                                        [](const PowerUp &powerUp) { return powerUp.Destroyed && !powerUp.Activated; }
                                        ), this->PowerUps.end());
}
