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
//unsigned int loadCubemap(std::vector<std::string> faces);
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
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//    
//    // build and compile shaders
//    // -------------------------
//    Shader shaderSkybox("OpenGL_01/Shaders/Cubemap.vert",
//                  "OpenGL_01/Shaders/Cubemap.frag");
//    
//    Shader shaderRed("OpenGL_01/Shaders/SimpleUBO.vert",
//                  "OpenGL_01/Shaders/SimpleUBO.frag");
//    Shader shaderGreen("OpenGL_01/Shaders/SimpleUBO.vert",
//                     "OpenGL_01/Shaders/SimpleUBO.frag");
//    Shader shaderBlue("OpenGL_01/Shaders/SimpleUBO.vert",
//                     "OpenGL_01/Shaders/SimpleUBO.frag");
//    Shader shaderDark("OpenGL_01/Shaders/SimpleUBO.vert",
//                     "OpenGL_01/Shaders/SimpleUBO.frag");
//    
//    float cubeVertices[] = {
//        // positions
//        -0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f,  0.5f, -0.5f,
//        0.5f,  0.5f, -0.5f,
//        -0.5f,  0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//        
//        -0.5f, -0.5f,  0.5f,
//        0.5f, -0.5f,  0.5f,
//        0.5f,  0.5f,  0.5f,
//        0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f,
//        -0.5f, -0.5f,  0.5f,
//        
//        -0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//        -0.5f, -0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f,
//        
//        0.5f,  0.5f,  0.5f,
//        0.5f,  0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f,  0.5f,
//        0.5f,  0.5f,  0.5f,
//        
//        -0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f,  0.5f,
//        0.5f, -0.5f,  0.5f,
//        -0.5f, -0.5f,  0.5f,
//        -0.5f, -0.5f, -0.5f,
//        
//        -0.5f,  0.5f, -0.5f,
//        0.5f,  0.5f, -0.5f,
//        0.5f,  0.5f,  0.5f,
//        0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f, -0.5f,
//    };
//        
//    float skyboxVertices[] = {
//        // positions
//        -1.0f,  1.0f, -1.0f,
//        -1.0f, -1.0f, -1.0f,
//        1.0f, -1.0f, -1.0f,
//        1.0f, -1.0f, -1.0f,
//        1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        
//        -1.0f, -1.0f,  1.0f,
//        -1.0f, -1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f,  1.0f,
//        -1.0f, -1.0f,  1.0f,
//        
//        1.0f, -1.0f, -1.0f,
//        1.0f, -1.0f,  1.0f,
//        1.0f,  1.0f,  1.0f,
//        1.0f,  1.0f,  1.0f,
//        1.0f,  1.0f, -1.0f,
//        1.0f, -1.0f, -1.0f,
//        
//        -1.0f, -1.0f,  1.0f,
//        -1.0f,  1.0f,  1.0f,
//        1.0f,  1.0f,  1.0f,
//        1.0f,  1.0f,  1.0f,
//        1.0f, -1.0f,  1.0f,
//        -1.0f, -1.0f,  1.0f,
//        
//        -1.0f,  1.0f, -1.0f,
//        1.0f,  1.0f, -1.0f,
//        1.0f,  1.0f,  1.0f,
//        1.0f,  1.0f,  1.0f,
//        -1.0f,  1.0f,  1.0f,
//        -1.0f,  1.0f, -1.0f,
//        
//        -1.0f, -1.0f, -1.0f,
//        -1.0f, -1.0f,  1.0f,
//        1.0f, -1.0f, -1.0f,
//        1.0f, -1.0f, -1.0f,
//        -1.0f, -1.0f,  1.0f,
//        1.0f, -1.0f,  1.0f
//    };
//    
//    // cube VAO
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//    // skybox VAO
//    unsigned int skyboxVAO, skyboxVBO;
//    glGenVertexArrays(1, &skyboxVAO);
//    glGenBuffers(1, &skyboxVBO);
//    glBindVertexArray(skyboxVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    
//    // configure a uniform buffer object
//    // ---------------------------------
//    // first. We get the relevant block indices
//    unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(shaderRed.ID, "Matrices");
//    unsigned int uniformBlockIndexGreen = glGetUniformBlockIndex(shaderGreen.ID, "Matrices");
//    unsigned int uniformBlockIndexBlue = glGetUniformBlockIndex(shaderBlue.ID, "Matrices");
//    unsigned int uniformBlockIndexYellow = glGetUniformBlockIndex(shaderDark.ID, "Matrices");
//    // then we link each shader's uniform block to this uniform binding point
//    glUniformBlockBinding(shaderRed.ID, uniformBlockIndexRed, 0);
//    glUniformBlockBinding(shaderGreen.ID, uniformBlockIndexGreen, 0);
//    glUniformBlockBinding(shaderBlue.ID, uniformBlockIndexBlue, 0);
//    glUniformBlockBinding(shaderDark.ID, uniformBlockIndexYellow, 0);
//    // Now actually create the buffer
//    unsigned int uboMatrices;
//    glGenBuffers(1, &uboMatrices);
//    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
//    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
//    glBindBuffer(GL_UNIFORM_BUFFER, 0);
//    // define the range of the buffer that links to a uniform binding point
//    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
//    
//    // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
//    glm::mat4 projection = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
//    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
//    glBindBuffer(GL_UNIFORM_BUFFER, 0);
//    
//    // load textures
//    // -------------
//    unsigned int cubeTexture = loadTexture("OpenGL_01/Resources/Textures/container2.png");
//    
//    std::vector<std::string> faces =
//    {
//        "OpenGL_01/Resources/Textures/Cubemaps/Skyboxes/skies/right.jpg",
//        "OpenGL_01/Resources/Textures/Cubemaps/Skyboxes/skies/left.jpg",
//        "OpenGL_01/Resources/Textures/Cubemaps/Skyboxes/skies/top.jpg",
//        "OpenGL_01/Resources/Textures/Cubemaps/Skyboxes/skies/bottom.jpg",
//        "OpenGL_01/Resources/Textures/Cubemaps/Skyboxes/skies/back.jpg",
//        "OpenGL_01/Resources/Textures/Cubemaps/Skyboxes/skies/front.jpg"
//    };
//    unsigned int cubemapTexture = loadCubemap(faces);
//    
//    // shader configuration
//    // --------------------
//    shaderSkybox.use();
//    shaderSkybox.setInt("skybox", 0);
//    
//    Model ourModel("OpenGL_01/Resources/Models/nanosuit/nanosuit.obj");
//    
//    // draw as wireframe
////    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        
//        // set the view and projection matrix in the uniform block - we only have to do this once per loop iteration.
//        glm::mat4 view = camera.GetViewMatrix();
//        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
//        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
//        glBindBuffer(GL_UNIFORM_BUFFER, 0);
//        
//        // draw scene as normal
//        // draw 4 cubes
//        // RED
//        glBindVertexArray(cubeVAO);
//        shaderRed.use();
//        glm::mat4 model;
//        model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f)); // move top-left
//        shaderRed.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        // GREEN
//        shaderGreen.use();
//        model = glm::mat4();
//        model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f)); // move top-right
//        shaderGreen.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        // DARK
//        shaderDark.use();
//        model = glm::mat4();
//        model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f)); // move bottom-left
//        shaderDark.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        // BLUE
//        shaderBlue.use();
//        model = glm::mat4();
//        model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f)); // move bottom-right
//        shaderBlue.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        
//        // draw dude
//        shaderRed.use();
//        model = glm::mat4();
//        model = glm::translate(model, glm::vec3(3.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
//        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
//        shaderRed.setMat4("model", model);
//        ourModel.Draw(shaderRed);
//        
//        // draw skybox as last
//        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
//        shaderSkybox.use();
//        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
////        view = camera.GetViewMatrix();
//        shaderSkybox.setMat4("view", view);
//        shaderSkybox.setMat4("projection", projection);
//        // skybox cube
//        glBindVertexArray(skyboxVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//        glDepthFunc(GL_LESS); // set depth function back to default
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
//    glDeleteBuffers(1, &cubeVBO);
//    glDeleteVertexArrays(1, &skyboxVAO);
//    glDeleteBuffers(1, &skyboxVBO);
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
