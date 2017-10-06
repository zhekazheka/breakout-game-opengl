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
//
//#include <unistd.h>
//
//#include "shader-loader.h"
//#include "camera.h"
//
//GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
//GLfloat lastFrame = 0.0f;  	// Time of last frame
//
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//Camera camera(glm::vec3(3.0f, 2.0f, 5.0f));
//
//bool keys[1024];
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//    // When a user presses the escape key, we set the WindowShouldClose property to true,
//    // closing the application
//    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//    {
//        glfwSetWindowShouldClose(window, GL_TRUE);
//    }
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
//GLfloat lastX = 400, lastY = 300;
//bool isFirstMouseInput = true;
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    if(isFirstMouseInput)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        isFirstMouseInput = false;
//    }
//    
//    GLfloat xoffset = xpos - lastX;
//    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
//    
//    lastX = xpos;
//    lastY = ypos;
//    
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(yoffset);
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
//int main(int argc, const char * argv[])
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
//    glfwSetKeyCallback(window, key_callback);
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
//    
//    // build and compile our shader zprogram
//    // ------------------------------------
//    ShaderLoader lightingShader("../../../OpenGL_01/Shaders/BaseMaterial.ver",
//                              "../../../OpenGL_01/Shaders/BaseMaterial.frag");
//    ShaderLoader lampShader("../../../OpenGL_01/Shaders/SimpleLightSource.ver",
//                              "../../../OpenGL_01/Shaders/SimpleLightSource.frag");
//    
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices[] = {
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//        
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//        
//        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//        
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//        
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//    };
//    // first, configure the cube's VAO (and VBO)
//    unsigned int VBO, cubeVAO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &VBO);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    
//    glBindVertexArray(cubeVAO);
//    
//    // position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    
//    // normal attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//    
//    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
//    unsigned int lightVAO;
//    glGenVertexArrays(1, &lightVAO);
//    glBindVertexArray(lightVAO);
//    
//    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    
//    
//    glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
//    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
//    
//    // testing variable to move light in circle
//    float anglePhi = 0.0f;
//    float rotationSpeed = 0.23f;
//    float circleRadius = 2.0f;
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
//        // move light in circle for fun
//        // ----------------------------
//        lightPos.x = circleRadius * sin(anglePhi);
//        lightPos.y = circleRadius * cos(anglePhi);
//        anglePhi += rotationSpeed * deltaTime;
//        if(anglePhi >= 360.0f)
//        {
//            anglePhi = 0.0f;
//        }
//        
//        // changing light color over time
//        // ------------------------------
//        lightColor.x = sin(currentFrame * 2.0f);
//        lightColor.y = sin(currentFrame * 0.7f);
//        lightColor.z = sin(currentFrame * 1.3f);
//        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
//        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
//        
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        
//        // be sure to activate shader when setting uniforms/drawing objects
//        lightingShader.use();
//        
//        // passing to the uniforms
//        lightingShader.setVec3("lightPos",  lightPos);
//        
//        lightingShader.setVec3("light.ambient",  ambientColor);
//        lightingShader.setVec3("light.diffuse",  diffuseColor); // darken the light a bit to fit the scene
//        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//
//        lightingShader.setVec3("material.ambient",  objectColor);
//        lightingShader.setVec3("material.diffuse",  1.0f, 0.5f, 0.31f);
//        lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
//        lightingShader.setFloat("material.shininess", 32.0f);
//        
//        
//        // view/projection transformations
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        lightingShader.setMat4("projection", projection);
//        lightingShader.setMat4("view", view);
//        
//        // world transformation
//        glm::mat4 model;
//        lightingShader.setMat4("model", model);
//        
//        // render the cube
//        glBindVertexArray(cubeVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        
//        
//        // also draw the lamp object
//        lampShader.use();
//        lampShader.setMat4("projection", projection);
//        lampShader.setMat4("view", view);
//        model = glm::mat4();
//        model = glm::translate(model, lightPos);
//        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
//        lampShader.setMat4("model", model);
//        
//        glBindVertexArray(lightVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
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
//    glDeleteVertexArrays(1, &lightVAO);
//    glDeleteBuffers(1, &VBO);
//    
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
