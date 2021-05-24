#include "Render.h"
#include <string>

class Texture
{
private:
    unsigned int mRenderID;
    std::string mFilePath;
    unsigned int mRgba;
    unsigned char* mLocalBuffer;
    int mWidth, mHeight, mBPP;

public:
    Texture(const std::string filePath, unsigned int rgba);
    ~Texture();
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    inline  int getmHeight() const { return mHeight;};
    inline  int getmWidth() const { return mWidth;};
};