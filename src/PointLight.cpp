#include "PointLight.h"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
    : m_position(position)
    , m_ambient(ambient)
    , m_diffuse(diffuse)
    , m_specular(specular)
{
}

glm::vec3 PointLight::position() const {
    return m_position;
}

glm::vec3 PointLight::ambient() const {
    return m_ambient;
}

glm::vec3 PointLight::diffuse() const {
    return m_diffuse;
}

glm::vec3 PointLight::specular() const {
    return m_specular;
}

float PointLight::Kc() const {
    return m_constant;
}

float PointLight::Kl() const {
    return m_linear;
}

float PointLight::Kq() const {
    return m_quadratic;
}