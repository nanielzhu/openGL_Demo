#pragma once
#include "glm/glm.hpp"
#define ASSERT(func) if(!(func)) __debugbreak();
#define glCall(func) glClearError();\
                    func;\
                    ASSERT(glCheckError(#func, __FILE__,__LINE__))

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

extern glm::vec3 cubePositions[];

void glClearError();
bool glCheckError(const char* func, const char* file, int line);
class VertexArray;
class IndexBuffer;
class Shader;


class Render
{
public:
    void Clear();
    void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader, bool aDraw);
    Render() = default;
    ~Render() = default;
};

