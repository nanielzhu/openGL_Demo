#include "VertexArray.h"
#include <GL/Glew.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1,&mRenderID);
};

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1,&mRenderID);
};

void VertexArray::Bind() const
{
    glBindVertexArray(mRenderID);
};
    
void VertexArray::Unbind() const
{
    glBindVertexArray(0);
};

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for(unsigned int i =0; i< elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getMstride(), (const void*) offset);
        offset += element.count * VertexBufferElement::getSize(element.type);
    }
};
