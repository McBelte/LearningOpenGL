#version 330 core

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
    float shininess;
};


struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform vec3 viewPos;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir);

out vec4 FragColor;


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform Material material;

void main() {

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = calcDirLight(dirLight, norm, viewDir);
    // for(int i = 0; i < NR_POINT_LIGHTS; i++) {
    //     result += calcPointLight(pointLights[i], norm, viewDir);
    // }

    FragColor = vec4(result, 1.0);
}


vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, light.direction), 0.0);

    vec3 reflectDir = reflect(-light.direction, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = vec3(0.0f, 0.0f, 0.0f);
    ambient += light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
    ambient += light.ambient * vec3(texture(material.texture_diffuse2, TexCoords));
    ambient += light.ambient * vec3(texture(material.texture_diffuse3, TexCoords));

    
    vec3 diffuse = vec3(0.0f, 0.0f, 0.0f);
    diffuse += light.diffuse * vec3(texture(material.texture_diffuse1, TexCoords)) * diff;
    diffuse += light.diffuse * vec3(texture(material.texture_diffuse2, TexCoords)) * diff;
    diffuse += light.diffuse * vec3(texture(material.texture_diffuse3, TexCoords)) * diff;

    vec3 specular = vec3(0.0f, 0.0f, 0.0f);
    specular +=  light.specular * vec3(texture(material.texture_specular1, TexCoords)) * spec;  
    specular +=  light.specular * vec3(texture(material.texture_specular2, TexCoords)) * spec;      

    return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - FragPos);
    
    float diff = max(dot(lightDir, normal), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, normal), 0.0), material.shininess);

    float distance = length(light.position - FragPos);
    float attunation = 1.0 / (light.constant + light.linear*distance + light.linear * pow(distance, 2.0));

    vec3 ambient;
    ambient += light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
    ambient += light.ambient * vec3(texture(material.texture_diffuse2, TexCoords));
    ambient += light.ambient * vec3(texture(material.texture_diffuse3, TexCoords));

    vec3 diffuse;
    diffuse += light.diffuse * vec3(texture(material.texture_diffuse1, TexCoords)) * diff;
    diffuse += light.diffuse * vec3(texture(material.texture_diffuse2, TexCoords)) * diff;
    diffuse += light.diffuse * vec3(texture(material.texture_diffuse3, TexCoords)) * diff;

    vec3 specular;
    specular +=  light.specular * vec3(texture(material.texture_specular1, TexCoords)) * spec;  
    specular +=  light.specular * vec3(texture(material.texture_specular2, TexCoords)) * spec;      

    ambient *= attunation;
    diffuse *= attunation;
    specular *= attunation;

    return (ambient + diffuse + specular);  
}