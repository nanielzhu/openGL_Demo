#pragma once

#include <vector>
#include <gl/Glew.h>
#include <type_traits>

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
    void Push(Identity<T>,unsigned int count)
    {
        if(std::is_floating_point_v<T>)
        {
            mElements.push_back({GL_FLOAT, count,GL_FALSE});
            mStride += VertexBufferElement::getSize(GL_FLOAT) * count;
        }
        if(std::is_integral_v<T>)
        {
            mElements.push_back({GL_UNSIGNED_INT, count,GL_FALSE});
            mStride += VertexBufferElement::getSize(GL_UNSIGNED_INT) * count;
        }
 
    }

    void Push(Identity<unsigned char>, unsigned int count)
    {
        mElements.push_back({GL_UNSIGNED_BYTE, count,GL_FALSE});
        mStride += VertexBufferElement::getSize(GL_UNSIGNED_BYTE) * count;
    }

    inline const unsigned int getMstride() const { return mStride;};
    inline const std::vector<VertexBufferElement> getElements() const {return mElements;}
};




