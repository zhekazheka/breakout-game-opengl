//
//  data.h
//  OpenGL_01
//
//  Created by Yevgeniy Tolstikov on 31/08/2017.
//  Copyright © 2017 HandMade. All rights reserved.
//

#ifndef data_h
#define data_h

#include <glm/glm.hpp>

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    aiString path;
};

#endif /* data_h */
