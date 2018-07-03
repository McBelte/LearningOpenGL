

#include "glm/glm.hpp"

class DirectionalLight {
public:    
    DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
    glm::vec3 direction() const;
    glm::vec3 ambient() const;
    glm::vec3 diffuse() const;
    glm::vec3 specular() const;
    float shininess() const;

private:
    glm::vec3 m_direction;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
};