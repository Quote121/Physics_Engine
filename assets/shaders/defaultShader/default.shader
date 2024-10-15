#type fragment
#version 460 core

out vec4 FragColor;

uniform vec3 colour = vec3(1, 1, 0);

void main()
{
    FragColor = vec4(colour, 1.0);
}


// =============
//    Vertex
// =============
#type vertex
#version 460 core

layout (location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos, 1.0);
}
