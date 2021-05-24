#pragma once

#include <vector>
#include <gl/Glew.h>

struct VertexBufferElement 
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    static unsigned int getSize(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT:              return 4;
            case GL_UNSIGNED_INT:       return 4;
            case GL_UNSIGNED_BYTE:      return 1;

        }
        return 0;
    }
};

template<typename T>
struct Identity { typedef T type;};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> mElements;
    unsigned int mStride;
public:
    VertexBufferLayout():mStride(0) {};
    ~VertexBufferLayout() = default;
    
    template<typename T>
    void Push(unsigned int count)
    {
        push(Identity<T>(), count);
 
    }

    void push(Identity<unsigned char>, unsigned int count)
    {
        mElements.push_back({GL_UNSIGNED_BYTE, count,GL_FALSE});
        mStride += VertexBufferElement::getSize(GL_UNSIGNED_BYTE) * count;
    }

    void push(Identity<float>, unsigned int count)
    {
        mElements.push_back({GL_FLOAT, count,GL_FALSE});
        mStride += VertexBufferElement::getSize(GL_FLOAT) * count;
    }

    void push(Identity<unsigned int>, unsigned int count)
    {
        mElements.push_back({GL_UNSIGNED_INT, count,GL_FALSE});
        mStride += VertexBufferElement::getSize(GL_UNSIGNED_INT) * count;
    }


    inline unsigned int getMstride() const { return mStride;};
    inline const  std::vector<VertexBufferElement>& getElements() const {return mElements;}
};




