#pragma once

class VertexBuffer
{
private:
    unsigned int  mRenderID;
public:
    VertexBuffer(const void *data, unsigned int size);
    VertexBuffer()= delete;
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;
};