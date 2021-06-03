#include <string>

class Texture
{
private:
    unsigned int mRenderID;
    std::string mFilePath;
    unsigned char* mLocalBuffer;
    int mWidth, mHeight, mBPP;

public:
    Texture(const std::string filePath);
    ~Texture();
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    inline  int getmHeight() const { return mHeight;};
    inline  int getmWidth() const { return mWidth;};
};