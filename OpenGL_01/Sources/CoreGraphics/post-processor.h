//
//  post-processor.hpp
//  OpenGL_01
//
//  Created by zhekazheka on 10/15/17.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef post_processor_h
#define post_processor_h

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite-renderer.h"
#include "shader.h"

// PostProcessor hosts all PostProcessing effects for the Breakout
// Game. It renders the game on a textured quad after which one can
// enable specific effects by enabling either the Confuse, Chaos or
// Shake boolean.
// It is required to call BeginRender() before rendering the game
// and EndRender() after rendering the game for the class to work.
class PostProcessor
{
public:
    // State
    Shader PostProcessingShader;
    Texture2D Texture;
    GLuint Width, Height;
    
    // Options
    GLboolean Confuse, Chaos, Shake;
    
    // Constructor
    PostProcessor(Shader shader, GLuint width, GLuint height);
    
    // Prepares the postprocessor's framebuffer operations before rendering the game
    void BeginRender();
    
    // Should be called after rendering the game, so it stores all the rendered data into a texture object
    void EndRender();
    
    // Renders the PostProcessor texture quad (as a screen-encompassing large sprite)
    void Render(GLfloat time);
    
    void Update(GLfloat deltaTime);
    
    void SetShakeTime(GLfloat shakeTime);
private:
    // Render state
    GLuint MSFBO, FBO; // MSFBO = Multisampled FBO. FBO is regular, used for blitting MS color-buffer to texture
    GLuint RBO; // RBO is used for multisampled color buffer
    GLuint VAO;
    
    GLfloat _shakeTime;
    
    // Initialize quad for rendering postprocessing texture
    void initRenderData();
    
    void updateShakeState();
};

#endif /* post_processor_h */
