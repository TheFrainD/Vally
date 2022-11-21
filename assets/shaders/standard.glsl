#shader vertex
#version 430 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;

out vec2 vUV;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
	vUV = aUV;
	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}

#shader fragment
#version 430 core

out vec4 fragmemtColor;

in vec2 vUV;

uniform sampler2D uImage;

void main()
{
	fragmemtColor = texture(uImage, vUV);
}