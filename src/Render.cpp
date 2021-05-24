#include <iostream>
#include "Render.h"
#include <GL/Glew.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};

void glClearError()
{
    while(glGetError() != GL_NO_ERROR );
}


bool glCheckError(const char* func, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "openGL meet error:"<<error<<"in function:"<<func<<"; and file :"<<file<<";line::"<<line<<std::endl;
        return false;
    }
    return true;
}

void Render::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Render::Draw(VertexArray& va, IndexBuffer& ib, Shader& shader, bool aDraw)
{
    va.Bind();
    ib.Bind();
    shader.Bind();
    if(aDraw)
        glDrawArrays(GL_TRIANGLES, 0, 36);
    else
        glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Render::Draw(VertexArray& va, Shader& shader)
{
    va.Bind();
    shader.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
