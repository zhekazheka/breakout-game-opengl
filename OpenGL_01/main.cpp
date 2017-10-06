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
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
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
//
//GLuint VAO, VBO, EBO;
//
//void setTriangleState()
//{
//    GLfloat vertices[] = {
//        // Positions         // Colors
//        0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Bottom Right
//        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Bottom Left
//        0.0f,  -0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // Top
//    };
//
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(VAO);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    
//    // Position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//    // Color attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//    
//    glBindVertexArray(0);
//}
//
//void setRectangleState()
//{
//    GLfloat vertices[] = {
//        // Positions          // Colors           // Texture Coords
//        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // Top Right
//        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   4.0f, 0.0f,   // Bottom Right
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left
//    };
//
//    GLuint indices[] = {  // Note that we start from 0!
//        0, 1, 3,   // First Triangle
//        1, 2, 3,    // Second Triangle
//    };
//    
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//    
//    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
//    glBindVertexArray(VAO);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//    
//    // Position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//    
//    // Color attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//    
//    // Texture attribute
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(2);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
//    
//    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
//}
//
//void setCubeState()
//{
//    GLfloat vertices[] =
//    {
//        // vertext position   text coord  colour
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f
//    };
//    
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    
//    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
//    glBindVertexArray(VAO);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    
//    // Position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//    
//    // Texture attribute
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//    
//    // Colour attribute
//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(2);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
//    
//    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
//}
//
//void setSimpleColorCubeState()
//{
//    GLfloat vertices[] =
//    {
//        // vertext position   colour
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//        
//        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
//        
//        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//        
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//        
//        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
//        
//        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f
//    };
//    
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    
//    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
//    glBindVertexArray(VAO);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    
//    // Position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//    
//    // Colour attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
//    
//    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
//}
//
//
//void testMatrix()
//{
//    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
//    glm::mat4 trans;
//    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
//    vec = trans * vec;
//    std::cout << "Translation result is: " << vec.x << vec.y << vec.z << std::endl;
//}
//
//int main(int argc, const char * argv[])
//{
//    char * dir = getcwd(NULL, 0); // Platform-dependent, see reference link below
//    printf("Current dir: %s", dir);
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
//    ShaderLoader simpleShader("../../../OpenGL_01/Shaders/SimpleColour.ver",
//                              "../../../OpenGL_01/Shaders/SimpleColour.frag");
//    
//    
////    setTriangleState();
////    setRectangleState();
////    setCubeState();
//    setSimpleColorCubeState();
//    
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    
//    GLint nrAttributes;
//    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
//    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
//    
//    
//    int width, height;
//    unsigned char* image = SOIL_load_image("../../../OpenGL_01/Resources/Textures/container.jpg",
//                                           &width, &height, 0, SOIL_LOAD_RGB);
//    
//    GLuint texture1, texture2;
//    glGenTextures(1, &texture1);
//    glGenTextures(1, &texture2);
//    
//    // ====================
//    // Texture 1
//    // ====================
//    glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
//    // Set our texture parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // Set texture filtering
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    
//    SOIL_free_image_data(image);
//    glBindTexture(GL_TEXTURE_2D, 0);
//    
//    
//    image = SOIL_load_image("../../../OpenGL_01/Resources/Textures/wall.jpg",
//                            &width, &height, 0, SOIL_LOAD_RGB);
//    
//    // ====================
//    // Texture 2
//    // ====================
//    glBindTexture(GL_TEXTURE_2D, texture2);
//    // Set our texture parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//    // Set texture filtering
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    
//    SOIL_free_image_data(image);
//    glBindTexture(GL_TEXTURE_2D, 0);
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
//    glEnable(GL_DEPTH_TEST);
//    
//    GLfloat positionOffsetX = 0;
//    
//    // game loop
//    while(!glfwWindowShouldClose(window))
//    {
//        GLfloat currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//        
//        glfwPollEvents();
//        
//        doMovement();
//        
//        glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        
//        GLfloat timeValue = glfwGetTime();
//        positionOffsetX += (sin(timeValue + 0.5f)) / 2;
//        
//        GLfloat radius = 5.0f;
//        GLfloat camX = sin(glfwGetTime()) * radius;
//        GLfloat camZ = cos(glfwGetTime()) * radius;
//        
//        glm::mat4 view;
//        view = view = camera.GetViewMatrix();
//        
////        glm::mat4 view;
////        // Note that we're translating the scene in the reverse direction of where we want to move
////        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
////        view = glm::rotate(view, glm::radians(xAxis), glm::vec3(0.0f, 1.0f, 0.0f));
////        view = glm::rotate(view, glm::radians(yAxis), glm::vec3(1.0f, 0.0f, 0.0f));
//        
//        glm::mat4 projection;
//        projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / screenHeight, 0.1f, 100.0f);
//        
//        GLint modelLoc = glGetUniformLocation(simpleShader.Program, "model");
//        
//        GLint viewLoc = glGetUniformLocation(simpleShader.Program, "view");
//        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//        
//        GLint projectionLoc = glGetUniformLocation(simpleShader.Program, "projection");
//        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//        
//        // Bind Texture
////        glActiveTexture(GL_TEXTURE0);
////        glBindTexture(GL_TEXTURE_2D, texture1);
////        glUniform1i(glGetUniformLocation(simpleShader.Program, "ourTexture1"), 0);
////        glActiveTexture(GL_TEXTURE1);
////        glBindTexture(GL_TEXTURE_2D, texture2);
////        glUniform1i(glGetUniformLocation(simpleShader.Program, "ourTexture2"), 1);
//        
//        // Activate shader
//        simpleShader.Use();
//        
//        // Draw container
//        glBindVertexArray(VAO);
//        
//        for(GLuint i = 0; i < 10; ++i)
//        {
//            glm::mat4 model;
//            model = glm::translate(model, cubePositions[i]);
//            GLfloat angle = 20.0f * i;
//            double randAxis = ((double)std::rand() / (RAND_MAX)) + 1;
//            model = glm::rotate(model, (GLfloat)timeValue * glm::radians(angle), glm::vec3(randAxis, randAxis, randAxis));
//            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//            
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
////        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
////        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//        
//        glfwSwapBuffers(window);
//    }
//    
//    // Properly de-allocate all resources once they've outlived their purpose
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    
//    glfwTerminate();
//    
//    return 0;
//}
