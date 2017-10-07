//
//  main.cpp
//  OpenGL_01
//
//  Created by Yevgeniy Tolstikov on 16/04/2017.
//  Copyright © 2017 HandMade. All rights reserved.
//

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <GLFW/glfw3.h>

#include "game.h"
#include "shader-loader.h"
#include "texture-loader.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, const char * argv[])
{
    // glfw initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // window creation
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // glew initialization
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    // register callbacks
    glfwSetKeyCallback(window, key_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
    
    // OpenGL configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Create resources management tools
    ShaderLoader shaderLoader;
    TextureLoader textureLoader;
    
    // Initialize game
    Breakout.Init(&shaderLoader, &textureLoader);
    
    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    
    // Start Game within Menu State
    Breakout.State = GAME_ACTIVE;
    
    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        
        //deltaTime = 0.001f;
        // Manage user input
        Breakout.ProcessInput(deltaTime);
        
        // Update Game state
        Breakout.Update(deltaTime);
        
        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();
        
        glfwSwapBuffers(window);
    }
    
    // Delete all resources as loaded using the resource manager
    shaderLoader.Clear();
    textureLoader.Clear();
    
    glfwTerminate();
    
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            Breakout.Keys[key] = GL_TRUE;
        }
        else if (action == GLFW_RELEASE)
        {
            Breakout.Keys[key] = GL_FALSE;
        }
    }
}

