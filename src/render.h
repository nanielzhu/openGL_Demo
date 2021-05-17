#pragma once

#define ASSERT(func) if(!(func)) __debugbreak();
#define glCall(func) glClearError();\
                    func;\
                    ASSERT(glCheckError(#func, __FILE__,__LINE__))

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void glClearError();
bool glCheckError(const char* func, const char* file, int line);