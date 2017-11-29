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
#include "particle-generator.h"
#include "post-processor.h"
#include "power-up.h"
#include "text-renderer.h"
#include "safe_event.h"

class Player;
class BallObject;
class PowerUpsController;
class PowerUpsFactory;
class CollisionDetector;

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
    void Init(ShaderLoader* shaderLoader, TextureLoader* textureLoader, GameState initialState);
    
    // GameLoop
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
    
private:
    void Start();
    void ResetLevel();
    void ResetPlayer();
    void SetupGameEvents();
    void LoadLevels();
    
    std::vector<std::unique_ptr<GameLevel>> levels;
    int levelIndex;
    
    ShaderLoader* shaderLoader;
    TextureLoader* textureLoader;
    
    
    std::unique_ptr<SpriteRenderer> spriteRenderer;
    std::unique_ptr<TextRenderer> textRenderer;
    
    std::unique_ptr<Player> player;
    std::unique_ptr<BallObject> ball;
    std::unique_ptr<ParticleGenerator> particleGenerator;
    std::unique_ptr<PostProcessor> postProcessor;
    
    std::unique_ptr<PowerUpsController> powerUpsController;
    std::unique_ptr<PowerUpsFactory> powerUpsFactory;
    
    std::unique_ptr<CollisionDetector> collisionDetector;
};

#endif /* Game_h */
