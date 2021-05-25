#pragma once
#include "glm/glm.hpp"




class Mvp
{
private:
    glm::mat4 mMvp;
public:
    Mvp() { mMvp = glm::mat4(1.0f); };
    const glm::mat4& ToViewwithMovingCam();
    const glm::mat4& ToViewwithcontrol(glm::vec3 aPos, glm::vec3 aFront, glm::vec3 aUp);
    const glm::mat4& ToViewReverse();
    const glm::mat4& ToProj();
    const glm::mat4& ToProjwithcontrol(float angle);
    const glm::mat4& ToModelwithloc( const glm::vec3 pos[],unsigned int i);
    const glm::mat4& ToModelwithrotate();
    const glm::mat4& ToModelwithScale(glm::vec3&, float scale);
};