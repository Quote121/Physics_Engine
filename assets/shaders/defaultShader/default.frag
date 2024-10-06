#version 460 core

out vec4 FragColor;

uniform vec3 colour = vec3(1, 1, 0);

void main()
{
    FragColor = vec4(colour, 1.0);
}
