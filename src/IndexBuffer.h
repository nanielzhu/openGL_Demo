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
    void bind() const;
    void unbind() const;
    inline const unsigned int getCount() const { return mCount;}
};