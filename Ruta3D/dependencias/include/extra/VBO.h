#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

using namespace glm;

struct Vertex{
    vec3 position;
    vec3 normal;
    vec3 color;
    vec2 texUV;
};


class VBO{
    public:
        GLuint ID;
        VBO(std::vector<Vertex>& vertices);

        void Bind();
        void Unbind();
        void Delete();
};

#endif