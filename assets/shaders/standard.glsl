#shader vertex
#version 430 core

layout (location = 0) in vec3 aPosition;

void main()
{
	gl_Position = vec4(aPosition, 1.0);
}

#shader fragment
#version 430 core

uniform vec3 uColor;

out vec4 fragmemtColor;

void main()
{
	fragmemtColor = vec4(uColor, 1.0);
}