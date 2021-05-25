#include "Render.h"
#include <GL/Glew.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


void Render::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Render::ClearDepth()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::ClearColor(float v1, float v2, float v3, float v4)
{
    glClearColor(v1,v2,v3,v4);
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
