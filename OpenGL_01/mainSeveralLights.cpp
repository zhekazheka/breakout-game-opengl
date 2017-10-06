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
//
//GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
//GLfloat lastFrame = 0.0f;  	// Time of last frame
//
//Camera camera(glm::vec3(3.0f, 2.0f, 5.0f));
//
//bool keys[1024];
//
//unsigned int loadTexture(char const * path);
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
//float randFloat()
//{
//    return (float)rand() / (float)RAND_MAX;
//}
//
//int main(int argc, const char * argv[])
//{
//    // randomize
//    srand(time(NULL));
//    
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
//    ShaderLoader lightingShader("../../../OpenGL_01/Shaders/SeveralLights.vert",
//                              "../../../OpenGL_01/Shaders/SeveralLights.frag");
//    ShaderLoader lampShader("../../../OpenGL_01/Shaders/SimpleLightSource.vert",
//                              "../../../OpenGL_01/Shaders/SimpleLightSource.frag");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices[] = {
//        // positions          // normals           // texture coords
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//    };
//    
//    glm::vec3 cubePositions[] = {
//        glm::vec3( 0.0f,  0.0f,  0.0f),
//        glm::vec3( 2.0f,  5.0f, -15.0f),
//        glm::vec3(-1.5f, -2.2f, -2.5f),
//        glm::vec3(-3.8f, -2.0f, -12.3f),
//        glm::vec3( 2.4f, -0.4f, -3.5f),
//        glm::vec3(-1.7f,  3.0f, -7.5f),
//        glm::vec3( 1.3f, -2.0f, -2.5f),
//        glm::vec3( 1.5f,  2.0f, -2.5f),
//        glm::vec3( 1.5f,  0.2f, -1.5f),
//        glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//    
//    glm::vec3 pointLightPositions[] = {
//        glm::vec3( 0.7f,  0.2f,  2.0f),
//        glm::vec3( 2.3f, -3.3f, -4.0f),
//        glm::vec3(-4.0f,  2.0f, -12.0f),
//        glm::vec3( 0.0f,  0.0f, -3.0f)
//    };
//    
//    glm::vec3 randColors[] = {
//        glm::vec3( randFloat(),  0.0f,  randFloat()),
//        glm::vec3( randFloat(),  randFloat(),  0.0f),
//        glm::vec3( 0.0f,  randFloat(),  randFloat()),
//        glm::vec3( randFloat(),  randFloat(),  0.0f),
//    };
//
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
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // normal attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//
//    // texture coordinates
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(2);
//
//    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
//    unsigned int lightVAO;
//    glGenVertexArrays(1, &lightVAO);
//    glBindVertexArray(lightVAO);
//
//    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//
//    glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
//    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
//    
//    int ligtSourcesCount = sizeof(pointLightPositions)/sizeof(pointLightPositions[0]);
//
//    // load textures
//    // -----------------------------------------------------------------------------
//    unsigned int diffuseMap = loadTexture("../../../OpenGL_01/Resources/Textures/container2.png");
//    unsigned int emissionMap = loadTexture("../../../OpenGL_01/Resources/Textures/matrix.jpg");
//    unsigned int specularMap = loadTexture("../../../OpenGL_01/Resources/Textures/container2_specular.png");
//
//    // shader configuration
//    // --------------------
//    lightingShader.use();
//    lightingShader.setInt("material.diffuse", 0);
//    lightingShader.setInt("material.specular", 1);
//    lightingShader.setInt("material.emission", 2);
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
//        // changing light color over time
//        // ------------------------------
////        lightColor.x = sin(currentFrame * 2.0f);
////        lightColor.y = sin(currentFrame * 0.7f);
////        lightColor.z = sin(currentFrame * 1.3f);
//        glm::vec3 diffuseColor = lightColor * glm::vec3(0.9f);
//        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
//
//        // render
//        // ------
////        glClearColor(randColors[0].r, randColors[1].g, randColors[2].b, 1.0f);
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // be sure to activate shader when setting uniforms/drawing objects
//        lightingShader.use();
//
//        // passing to the uniforms
//        // common
//        lightingShader.setVec3("viewPos",  camera.Position);
//        
//        // direction light
//        lightingShader.setVec3("dirLight.direction",  glm::vec3(-0.8f, -1.0f, -0.0f));
//        lightingShader.setVec3("dirLight.ambient",  ambientColor);
//        lightingShader.setVec3("dirLight.diffuse",  diffuseColor * glm::vec3(0.3f));
//        lightingShader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
//        
//        // point lights
//        for(unsigned int i = 0; i < ligtSourcesCount; ++i)
//        {
//            std::string number = std::to_string(i);
//            
//            lightingShader.setVec3("pointLights[" + number + "].position", pointLightPositions[i]);
//            lightingShader.setFloat("pointLights[" + number + "].constant", 1.0f);
//            lightingShader.setFloat("pointLights[" + number +"].linear", 0.022);
//            lightingShader.setFloat("pointLights[" + number +"].quadratic", 0.0019);
//            lightingShader.setVec3("pointLights[" + number +"].ambient",  randColors[i] * glm::vec3(0.2f));
//            lightingShader.setVec3("pointLights[" + number +"].diffuse",  randColors[i]);
//            lightingShader.setVec3("pointLights[" + number +"].specular", 1.0f, 1.0f, 1.0f);
//        }
//        
//        // spot light
//        lightingShader.setVec3("spotLight.position",  camera.Position);
//        lightingShader.setVec3("spotLight.direction", camera.Front);
//        lightingShader.setFloat("spotLight.cutOff",   glm::cos(glm::radians(5.5f)));
//        lightingShader.setFloat("spotLight.outerCutOff",   glm::cos(glm::radians(12.5f)));
//        lightingShader.setVec3("spotLight.ambient",  ambientColor);
//        lightingShader.setVec3("spotLight.diffuse",  glm::vec3(1.0f, 1.0f, 0.5f));
//        lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
//        lightingShader.setFloat("spotLight.constant",  1.0f);
//        lightingShader.setFloat("spotLight.linear",  0.045f);
//        lightingShader.setFloat("spotLight.quadratic",  0.0075f);
//        
//        // material
//        lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
//        lightingShader.setFloat("material.shininess", 64.0f);
//
//
//        // view/projection transformations
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        lightingShader.setMat4("projection", projection);
//        lightingShader.setMat4("view", view);
//
//        // bind diffuse map
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, diffuseMap);
//
//        // bind specular map
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, specularMap);
//
//        // bind emission map
//        glActiveTexture(GL_TEXTURE2);
//        glBindTexture(GL_TEXTURE_2D, emissionMap);
//
//        // render the cubes
//        glBindVertexArray(cubeVAO);
//        
//        for(unsigned int i = 0; i < 10; ++i)
//        {
//            glm::mat4 model;
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            lightingShader.setMat4("model", model);
//            
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//        // world transformation
//        glm::mat4 model;
//        lightingShader.setMat4("model", model);
//        
//        // also draw the lamp object
//        lampShader.use();
//        lampShader.setMat4("projection", projection);
//        lampShader.setMat4("view", view);
//        
//        glBindVertexArray(lightVAO);
//        for(unsigned int i = 0; i < ligtSourcesCount; ++i)
//        {
//            model = glm::mat4();
//            model = glm::translate(model, pointLightPositions[i]);
//            model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
//            lampShader.setMat4("model", model);
//            
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
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
//
//// utility function for loading a 2D texture from file
//// ---------------------------------------------------
//unsigned int loadTexture(char const * path)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    unsigned char *data = SOIL_load_image(path, &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format;
//        if (nrComponents == 1)
//        format = GL_RED;
//        else if (nrComponents == 3)
//        format = GL_RGB;
//        else if (nrComponents == 4)
//        format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        SOIL_free_image_data(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        SOIL_free_image_data(data);
//    }
//
//    return textureID;
//}
