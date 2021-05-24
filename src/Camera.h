#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include <GLFW/glfw3.h>



// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };
    // constructor with vectors
    Camera(glm::vec3 position, glm::vec3 up, float yaw = YAW, float pitch = PITCH);
    Camera(glm::vec3 position);
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() const;
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Movement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float& xoffset, float& yoffset, GLboolean constrainPitch = true);
    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void setZoom(float yoffset);
    void ProcessKeyControl(GLFWwindow *window);
    const glm::vec3& getPosition() const { return mPosition;};
    const glm::vec3& getFront() const { return mFront;};
    const glm::vec3& getUp() const { return mUp;};
    inline float getZoom() const { return mZoom;};

private:
    // camera Attributes
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;
    // euler Angles
    float mYaw;
    float mPitch;
    // camera options
    float mMovementSpeed;
    float mMouseSensitivity;
    float mZoom;
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
    void updateCameraMove();
};

#endif