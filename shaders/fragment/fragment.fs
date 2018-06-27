
#version 330 core
out vec4 FragColor;

in vec3 ourPos;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(2.0*TexCoord.x, 2.0*TexCoord.y)), mixValue);
};
