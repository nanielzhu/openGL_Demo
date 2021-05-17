#include <iostream>
#include "render.h"
#include <GL/Glew.h>

void glClearError()
{
    while(glGetError() != GL_NO_ERROR );
};

bool glCheckError(const char* func, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "openGL meet error:"<<error<<"in function:"<<func<<"; and file :"<<file<<";line::"<<line<<std::endl;
        return false;
    }
    return true;
};
