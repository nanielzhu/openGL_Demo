#pragma once

class IndexBuffer
{
private:
    unsigned int mRenderID;
    unsigned int mCount;
public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    IndexBuffer()= delete;
    ~IndexBuffer();
    void Bind() const;
    void Unbind() const;
    inline  unsigned int getCount() const { return mCount;}
};