////
////  main.cpp
////  OpenGL_01
////
////  Created by Yevgeniy Tolstikov on 16/04/2017.
////  Copyright © 2017 HandMade. All rights reserved.
////
//
//#define GLEW_STATIC
//#include <GL/glew.h>
//
//#include <iostream>
//#include <GLFW/glfw3.h>
//
//#include <SOIL.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <math.h>
//#include <map>
//
//#include <unistd.h>
//#include <time.h>
//
//#include "shader-loader.h"
//#include "camera.h"
//#include "model.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window, int key, int scancode, int action, int mode);
//void doMovement();
//
//bool keys[1024];
//
//glm::vec3 lightPos(1.2f, 1.0f, 1.0f);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int main()
//{
//    // glfw initialization
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    // window creation
//    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
//    if (window == nullptr)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // register callbacks
//    glfwSetKeyCallback(window, processInput);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // glew initialization
//    glewExperimental = GL_TRUE;
//    if (glewInit() != GLEW_OK)
//    {
//        std::cout << "Failed to initialize GLEW" << std::endl;
//        return -1;
//    }
//
//    // set viewport
//    int screenWidth, screenHeight;
//    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
//    glViewport(0, 0, screenWidth, screenHeight);
//
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_CULL_FACE);
////    glCullFace(GL_FRONT);
////    glFrontFace(GL_CW);
//    
//    // build and compile shaders
//    // -------------------------
//    Shader shader("OpenGL_01/Shaders/Simple.vert",
//                  "OpenGL_01/Shaders/Simple.frag");
//    
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    /*
//     Remember: to specify vertices in a counter-clockwise winding order you need to visualize the triangle
//     as if you're in front of the triangle and from that point of view, is where you set their order.
//     
//     To define the order of a triangle on the right side of the cube for example, you'd imagine yourself looking
//     straight at the right side of the cube, and then visualize the triangle and make sure their order is specified
//     in a counter-clockwise order. This takes some practice, but try visualizing this yourself and see that this
//     is correct.
//     */
//    
//    float cubeVertices[] = {
//        // Back face
//        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
//        // Front face
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//        // Left face
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//        // Right face
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//        // Bottom face
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//        // Top face
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
//    };
//    float planeVertices[] = {
//        // positions          // texture Coords
//        5.0f, -0.5f, -5.0f,  2.0f, 2.0f,
//        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//        
//        
//        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//        5.0f, -0.5f,  5.0f,  2.0f, 0.0f
//        
//    };
//    float transparentVertices[] = {
//        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
//        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
//        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//        
//        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
//    };
//    // cube VAO
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    // plane VAO
//    unsigned int planeVAO, planeVBO;
//    glGenVertexArrays(1, &planeVAO);
//    glGenBuffers(1, &planeVBO);
//    glBindVertexArray(planeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    // transparent VAO
//    unsigned int transparentVAO, transparentVBO;
//    glGenVertexArrays(1, &transparentVAO);
//    glGenBuffers(1, &transparentVBO);
//    glBindVertexArray(transparentVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glBindVertexArray(0);
//    
//    // load textures
//    // -------------
//    unsigned int cubeTexture = loadTexture("OpenGL_01/Resources/Textures/container2.png");
//    unsigned int floorTexture = loadTexture("OpenGL_01/Resources/Textures/container2_specular.png");
//    unsigned int transparentTexture = loadTexture("OpenGL_01/Resources/Textures/blending_transparent_window.png", GL_CLAMP_TO_EDGE);
//    
//    // transparent vegetation locations
//    // --------------------------------
//    std::vector<glm::vec3> vegetation
//    {
//        glm::vec3(-1.5f, 0.0f, -0.48f),
//        glm::vec3( 1.5f, 0.0f, 0.51f),
//        glm::vec3( 0.0f, 0.0f, 0.7f),
//        glm::vec3(-0.3f, 0.0f, -2.3f),
//        glm::vec3 (0.5f, 0.0f, -0.6f)
//    };
//    
//    // shader configuration
//    // --------------------
//    shader.use();
//    shader.setInt("texture_diffuse1", 0);
//    
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        // --------------------
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//        
//        // input
//        // -----
//        doMovement();
//        
//        // sort the transparent windows before rendering
//        // ---------------------------------------------
//        std::map<float, glm::vec3> sorted;
//        for (unsigned int i = 0; i < vegetation.size(); ++i)
//        {
//            float distance = glm::length(camera.Position - vegetation[i]);
//            sorted[distance] = vegetation[i];
//        }
//        
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        
//        // draw objects
//        shader.use();
//        glm::mat4 projection = glm::perspective(camera.Zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        glm::mat4 model;
//        shader.setMat4("projection", projection);
//        shader.setMat4("view", view);
//        // cubes
//        glEnable(GL_CULL_FACE);
//        glBindVertexArray(cubeVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, cubeTexture);
//        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//        shader.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        model = glm::mat4();
//        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//        shader.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        // floor
//        glDisable(GL_CULL_FACE);
//        glBindVertexArray(planeVAO);
//        glBindTexture(GL_TEXTURE_2D, floorTexture);
//        model = glm::mat4();
//        shader.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        // vegetation
//        glBindVertexArray(transparentVAO);
//        glBindTexture(GL_TEXTURE_2D, transparentTexture);
//        for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
//        {
//            model = glm::mat4();
//            model = glm::translate(model, it->second);
//            shader.setMat4("model", model);
//            glDrawArrays(GL_TRIANGLES, 0, 6);
//        }
//        
//        
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteVertexArrays(1, &planeVAO);
//    glDeleteBuffers(1, &cubeVBO);
//    glDeleteBuffers(1, &planeVBO);
//    
//    
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//void doMovement()
//{
//    // Camera controls
//    if(keys[GLFW_KEY_W])
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if(keys[GLFW_KEY_S])
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if(keys[GLFW_KEY_A])
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if(keys[GLFW_KEY_D])
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//    
//    if (key < 0 && key >= 1024)
//    {
//        return;
//    }
//
//    if(action == GLFW_PRESS)
//    {
//        keys[key] = true;
//    }
//    else if(action == GLFW_RELEASE)
//    {
//        keys[key] = false;
//    }
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//    
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//    
//    lastX = xpos;
//    lastY = ypos;
//    
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(yoffset);
//}
