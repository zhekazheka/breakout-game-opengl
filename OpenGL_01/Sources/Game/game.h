//
//  Game.h
//  OpenGL_01
//
//  Created by zhekazheka on 10/6/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader-loader.h"
#include "texture-loader.h"
#include "sprite-renderer.h"
#include "game-level.h"
#include "ball-object.h"
#include "particle-generator.h"
#include "post-processor.h"
#include "power-up.h"
#include "text-renderer.h"

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(500.0f);

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const GLfloat BALL_RADIUS = 12.5f;

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // Game state
    GameState State;
    GLboolean Keys[1024];
    GLboolean KeysProcessed[1024];
    GLuint Width, Height;
    
    std::vector<PowerUp> PowerUps;
    
    // Constructor/Destructor
    Game(GLuint width, GLuint height);
    ~Game();
    
    // Initialize game state (load all shaders/textures/levels)
    void Init(ShaderLoader* shaderLoader, TextureLoader* textureLoader);
    
    // GameLoop
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
    
    // [zheka] TODO move it to factory
    void SpawnPowerUps(GameObject& block);
    
    // [zheka] TODO maybe move it to some sort of PowerUpController
    void UpdatePowerUps(GLfloat dt);
    void ActivatePowerUp(PowerUp &powerUp);
    
private:
    std::vector<GameLevel> levels;
    GLuint level;
    
    ShaderLoader* shaderLoader;
    TextureLoader* textureLoader;
    SpriteRenderer* spriteRenderer;
    TextRenderer* textRenderer;
    
    GameObject* player;
    BallObject* ball;
    ParticleGenerator* particleGenerator;
    PostProcessor* postProcessor;
    
    int lives;
    
    void DoCollisions();
    void ResetLevel();
    void ResetPlayer();
};

#endif /* Game_h */
