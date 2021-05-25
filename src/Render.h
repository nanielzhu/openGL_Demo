#pragma once
#include "glm/glm.hpp"

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 760;

class VertexArray;
class IndexBuffer;
class Shader;

class Render
{
public:
    void Clear();
    void ClearDepth();
    void ClearColor(float, float, float, float);
    void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader, bool aDraw);
    void Draw(VertexArray& va, Shader& shader);
    Render() = default;
    ~Render() = default;
};

