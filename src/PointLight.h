#include "glm/glm.hpp"

class PointLight {
public:
    PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

    glm::vec3 position() const;
    glm::vec3 ambient() const;
    glm::vec3 diffuse() const;
    glm::vec3 specular() const;

    float Kc() const;
    float Kl() const;
    float Kq() const;

private:
    glm::vec3 m_position;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    float m_constant = 1.0;
    float m_linear = 0.14;
    float m_quadratic = 0.07;
};
