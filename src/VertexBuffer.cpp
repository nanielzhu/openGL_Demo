#include "VertexBuffer.h"
#include <GL/Glew.h>

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    glGenBuffers(1,&mRenderID);
    glBindBuffer(GL_ARRAY_BUFFER, mRenderID);
    glBufferData(GL_ARRAY_BUFFER,size,data, GL_STATIC_DRAW);
};

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1,&mRenderID);
};

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, mRenderID);
};

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
};


