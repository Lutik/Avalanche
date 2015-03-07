#version 330 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;

uniform mat4 modelview;
uniform mat4 projection;

out vec2 uv;
out vec3 normal;

void main(void)
{
	mat3 normalMat = transpose(inverse(mat3(modelview)));
	normal = normalize(normalMat * in_normal);
	uv = in_uv;
	gl_Position = projection * modelview * vec4(in_pos, 1);
}