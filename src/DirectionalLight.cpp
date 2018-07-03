#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
    : m_direction(direction)
    , m_ambient(ambient)
    , m_diffuse(diffuse)
    , m_specular(specular)
{}

glm::vec3 DirectionalLight::direction() const {
    return m_direction;
}

glm::vec3 DirectionalLight::ambient() const {
    return m_ambient;
}

glm::vec3 DirectionalLight::diffuse() const {
    return m_diffuse;
}

glm::vec3 DirectionalLight::specular() const {
    return m_specular;
}


