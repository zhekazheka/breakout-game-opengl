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
//    glDepthFunc(GL_LESS);
//    
//    glEnable(GL_STENCIL_TEST);
//    
//    // This tells OpenGL that whenever the stencil value of a fragment is equal (GL_EQUAL)
//    // to the reference value 1 the fragment passes the test and is drawn, otherwise discarded.
//    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//    
//    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//    
////    glStencilMask(0xFF); // each bit is written to the stencil buffer as is
////    glStencilMask(0x00); // each bit ends up as 0 in the stencil buffer (disabling writes)
//    
//    // build and compile shaders
//    // -------------------------
//    Shader ourShader("OpenGL_01/Shaders/ModelLoading.vert",
//                            "OpenGL_01/Shaders/ModelLoading.frag");
//    
//    Shader shaderSingleColor("OpenGL_01/Shaders/SimpleSingleColor.vert",
//                     "OpenGL_01/Shaders/SimpleSingleColor.frag");
//    
//    Shader lampShader("OpenGL_01/Shaders/SimpleLightSource.vert",
//                     "OpenGL_01/Shaders/SimpleLightSource.frag");
//    
////    ShaderLoader ourShader("../../../OpenGL_01/Shaders/SimpleLightSource.vert",
////                     "../../../OpenGL_01/Shaders/SimpleLightSource.frag");
//    
//    // load models
//    // -----------
//    Model ourModel("OpenGL_01/Resources/Models/nanosuit/nanosuit.obj");
//    Model lampModel("OpenGL_01/Resources/Models/MysteryCup/MysteryCup.obj");
//    
//    
//    // draw in wireframe
////    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    
//    // testing variable to move light in circle
//    float anglePhi = 0.0f;
//    float rotationSpeed = 1.5f;
//    float circleRadius = 2.0f;
//    
//    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
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
//        // render
//        // ------
//        glClearColor(0.3f, 0.05f, 0.05f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//        
//        // draw the lamp object
//        
//        // We set its mask to 0x00 to not write to the stencil buffer.
//        glStencilMask(0x00);
//        
//        lampShader.use();
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        lampShader.setMat4("projection", projection);
//        lampShader.setMat4("view", view);
//        glm::mat4 model;
//        model = glm::mat4();
//        model = glm::translate(model, lightPos);
//        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
//        lampShader.setMat4("model", model);
//        lampModel.Draw(lampShader);
//        
//        // 1st. render pass, draw objects as normal, writing to the stencil buffer
//        // --------------------------------------------------------------------
//        glStencilFunc(GL_ALWAYS, 1, 0xFF);
//        glStencilMask(0xFF);
//        
//        // don't forget to enable shader before setting uniforms
//        ourShader.use();
//        
//        ourShader.setVec3("viewPos",  camera.Position);
//        ourShader.setVec3("pointLight.position", lightPos);
//        
//        glm::vec3 diffuseColor = lightColor * glm::vec3(0.9f);
//        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
//        
//        ourShader.setVec3("pointLight.ambient",  ambientColor);
//        ourShader.setVec3("pointLight.diffuse",  diffuseColor);
//        ourShader.setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
//        ourShader.setFloat("pointLight.constant",  1.0f);
//        ourShader.setFloat("pointLight.linear",  0.045f);
//        ourShader.setFloat("pointLight.quadratic",  0.0075f);
//        
//        lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
//        diffuseColor = lightColor * glm::vec3(0.9f);
//        ambientColor = diffuseColor * glm::vec3(0.2f);
//        
//        ourShader.setVec3("dirLight.direction", glm::vec3(0.8f, -1.0f, -0.0f));
//        ourShader.setVec3("dirLight.ambient",  ambientColor);
//        ourShader.setVec3("dirLight.diffuse",  diffuseColor);
//        ourShader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
//        
//        ourShader.setFloat("material.shininess", 64.0f);
//        
//        // view/projection transformations
//        ourShader.setMat4("projection", projection);
//        ourShader.setMat4("view", view);
//        
//        // render the loaded model
//        model = glm::mat4();
//        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
//        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
//        ourShader.setMat4("model", model);
//        ourModel.Draw(ourShader);
//        
//        model = glm::mat4();
//        model = glm::translate(model, glm::vec3(1.0f, -1.75f, -2.0f));
//        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
//        ourShader.setMat4("model", model);
//        ourModel.Draw(ourShader);
//        
//        // 2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
//        // Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn, thus only drawing
//        // the objects' size differences, making it look like borders.
//        // -----------------------------------------------------------------------------------------------------------------------------
//        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//        glStencilMask(0x00);
//        glDisable(GL_DEPTH_TEST);
//        shaderSingleColor.use();
//        float scale = 1.05f;
//        
//        shaderSingleColor.setMat4("projection", projection);
//        shaderSingleColor.setMat4("view", view);
//        
//        // render the loaded model
//        model = glm::mat4();
//        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
//        model = glm::scale(model, glm::vec3(0.2f * scale, 0.2f, 0.2f * scale));
//        shaderSingleColor.setMat4("model", model);
//        ourModel.Draw(shaderSingleColor);
//        
//        model = glm::mat4();
//        model = glm::translate(model, glm::vec3(1.0f, -1.75f, -2.0f));
//        model = glm::scale(model, glm::vec3(0.2f * scale, 0.2f, 0.2f * scale));
//        shaderSingleColor.setMat4("model", model);
//        ourModel.Draw(shaderSingleColor);
//        
//        glStencilMask(0xFF);
//        glEnable(GL_DEPTH_TEST);
//        
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
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
