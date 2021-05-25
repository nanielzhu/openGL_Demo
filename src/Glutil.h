#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"


extern float mFov;
extern float xOffset;
extern float yOffset;

void glClearError();
bool glCheckError(const char* func, const char* file, int line);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window,double xpos, double ypos);