#version 330 core
out vec4 FragColor;

in vec3 MainColor;

void main()
{
    FragColor = vec4(MainColor, 1.0f);
}
