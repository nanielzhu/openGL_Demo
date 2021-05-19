#include "Texture.h"
#include <GL/glew.h>
#include "stb/stb_image.h"
#include <iostream>

Texture::Texture(const std::string filePath)
        :mRenderID(0),mFilePath(filePath), mLocalBuffer(nullptr),mHeight(0),mWidth(0),mBPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    mLocalBuffer = stbi_load(mFilePath.c_str(), &mWidth, &mHeight, &mBPP, 0);
    glGenTextures(1,&mRenderID);
    glBindTexture(GL_TEXTURE_2D, mRenderID);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (mLocalBuffer)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mLocalBuffer);
        //glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,0);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(mLocalBuffer);
}

Texture::~Texture()
{
    glDeleteTextures(1, &mRenderID);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D,mRenderID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}


