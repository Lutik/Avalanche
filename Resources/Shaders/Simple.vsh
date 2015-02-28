#version 330 core

layout(location = 0) in vec3 in_pos;

uniform mat4 mvp;

void main(void)
{
	gl_Position = vec4(in_pos, 1) * mvp;
}