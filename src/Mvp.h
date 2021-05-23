#pragma once
#include "glm/glm.hpp"




class Mvp
{
private:
    glm::mat4 mMvp;
public:
    Mvp() { mMvp = glm::mat4(1.0f); };
    void setViewwithMovingCam();
    void setViewwithcontrol( glm::vec3 aPos, glm::vec3 aFront, glm::vec3 aUp);
    void setViewReverse();
    void setProj();
    void setProjwithcontrol(float angle);
    void setModelwithloc( unsigned int i);
    void setModelwithrotate();
    const glm::mat4 getMvp() const { return mMvp ;};
};