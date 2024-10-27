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

uniform mat4 view;
uniform mat4 projection;

// out vec3 FragPos;

void main()
{
    // FragPos = vec3(model * vec4(aPos, 1.0));
	gl_Position = projection * view * vec4(aPos, 1.0);
}
