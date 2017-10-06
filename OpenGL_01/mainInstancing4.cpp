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
//    Shader planetShader("OpenGL_01/Shaders/Simple.vert",
//                  "OpenGL_01/Shaders/Simple.frag");
//    
//    Shader rockShader("OpenGL_01/Shaders/Instancing4.vert",
//                      "OpenGL_01/Shaders/Instancing4.frag");
//    
////    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    
//    unsigned int amount = 3000;
//    glm::mat4 *modelMatrices;
//    modelMatrices = new glm::mat4[amount];
//    srand(glfwGetTime()); // initialize random seed
//    float radius = 1.0;
//    float offset = 2.5f;
//    float displacementY = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//    for(unsigned int i = 0; i < amount; i++)
//    {
//        glm::mat4 model;
//        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
//        float angle = (float)i / (float)amount * 360.0f;
//        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//        float x = sin(angle) * radius + displacement;
//        float y = displacementY * 0.4f; // keep height of field smaller compared to width of x and z
//        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//        float z = cos(angle) * radius + displacement;
//        model = glm::translate(model, glm::vec3(x, y, z));
//        
//        // 2. scale: Scale between 0.05 and 0.25f
//        float scale = (rand() % 20) / 100.0f + 0.05;
//        model = glm::scale(model, glm::vec3(scale));
//        
//        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
//        float rotAngle = (rand() % 360);
//        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
//        
//        // 4. now add to list of matrices
//        modelMatrices[i] = model;
//    }
//    
//    Model planetModel("OpenGL_01/Resources/Models/planet/planet.obj");
//    Model rockModel("OpenGL_01/Resources/Models/rock/rock.obj");
//    
//    // vertex Buffer Object
//    unsigned int buffer;
//    glGenBuffers(1, &buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, buffer);
//    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
//    
//    for(unsigned int i = 0; i < rockModel.meshes.size(); i++)
//    {
//        unsigned int VAO = rockModel.meshes[i].VAO;
//        glBindVertexArray(VAO);
//        // vertex Attributes
//        GLsizei vec4Size = sizeof(glm::vec4);
//        
//        // we need to set 4 vec4 for mat4. In the shader location will be reserved for 4 vectors. 
//        glEnableVertexAttribArray(3);
//        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
//        glEnableVertexAttribArray(4);
//        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
//        glEnableVertexAttribArray(5);
//        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
//        glEnableVertexAttribArray(6);
//        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));
//        
//        glVertexAttribDivisor(3, 1);
//        glVertexAttribDivisor(4, 1);
//        glVertexAttribDivisor(5, 1);
//        glVertexAttribDivisor(6, 1);
//        
//        glBindVertexArray(0);
//    }
//    
//    float angle = 0.0f;
//    float rotationSpeed = 1.0f;
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
//        float x = radius * sin(angle);
//        float y = displacementY;
//        float z = radius * cos(angle);
//        angle += rotationSpeed * deltaTime;
//        if(angle >= 360.0f)
//        {
//            angle = 0.0f;
//        }
//        
//        std::cout << "pos: " << x << " " << z << std::endl;
//        
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        
//        planetShader.use();
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        planetShader.setMat4("projection", projection);
//        planetShader.setMat4("view", view);
//        
//        glm::mat4 model;
//        model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
//        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
//        planetShader.setMat4("model", model);
//        planetModel.Draw(planetShader);
//        
//        // draw meteorites
//        rockShader.use();
//        rockShader.setMat4("projection", projection);
//        rockShader.setMat4("view", view);
//        rockShader.setInt("texture_diffuse1", 0);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, rockModel.textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
//        
//        for (unsigned int i = 0; i < rockModel.meshes.size(); i++)
//        {
//            glBindVertexArray(rockModel.meshes[i].VAO);
//            
//            for(int j = 0; j < amount; ++j)
//            {
////                glm::mat4 model(1);
////                model = glm::translate(model, glm::vec3(x, y, z));
////                modelMatrices[j] += model;
//                modelMatrices[j] = glm::translate(modelMatrices[j], glm::vec3(x, y, z));
//            }
//            
////            modelMatrices[i] = glm::translate(modelMatrices[i], glm::vec3(x, y, z));
//            glBufferSubData(GL_ARRAY_BUFFER, 0, amount * sizeof(glm::mat4), &modelMatrices[0]);
//            
//            glDrawElementsInstanced(GL_TRIANGLES, rockModel.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
//            glBindVertexArray(0);
//        }
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
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
