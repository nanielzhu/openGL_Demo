#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"
extern float xOffset;
extern float yOffset;
extern float fov;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void setViewwithCamera(glm::mat4& view);
void setViewwithcontrol(glm::mat4& view, glm::vec3 aPos, glm::vec3 aFront, glm::vec3 aUp);
void setViewReverse(glm::mat4& view);
void setProj(glm::mat4& proj);
void setProjwithcontrol(glm::mat4& proj,float angle);
void setModelwithloc(glm::mat4& model, unsigned int i);
void setModelwithrotate(glm::mat4& model);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window,double xpos, double ypos);