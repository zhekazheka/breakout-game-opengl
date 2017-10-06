#version 330 core
out vec4 FragColor;

in vec3 shadingColor;

uniform vec3 objectColor;
uniform vec3 viewPos;

void main()
{
    vec3 resultColor = shadingColor * objectColor;
    FragColor = vec4(resultColor, 1.0);
}
