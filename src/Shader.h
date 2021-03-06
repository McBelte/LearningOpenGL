#pragma once

#include <glad/glad.h>

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "DirectionalLight.h"
#include "PointLight.h"

class Shader {
public:
    unsigned int ID;

    Shader(const GLchar* vertexPath, const GLchar*  fragmentPath);

    void use();

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const glm::vec3& vector) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setMat4(const std::string& name, const glm::mat4& matrix) const;

    void setDirectionalLight(const DirectionalLight& light) const;
    void setPointLight(const std::vector<PointLight>& pointLights) const;

};