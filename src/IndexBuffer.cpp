#include "IndexBuffer.h"
#include <GL/Glew.h>

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
{
    glGenBuffers(1,&mRenderID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRenderID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,count * sizeof(unsigned int),data, GL_STATIC_DRAW);
};

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1,&mRenderID);
};

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRenderID);
};

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
};


