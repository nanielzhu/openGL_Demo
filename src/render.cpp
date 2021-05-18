#include <iostream>
#include "Render.h"
#include <GL/Glew.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

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

void Render::Draw(VertexArray& va, IndexBuffer& ib, Shader& shader)
{
    va.Bind();
    ib.Bind();
    shader.Bind();
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}
