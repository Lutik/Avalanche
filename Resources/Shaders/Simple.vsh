#version 330 core

layout(location = 0) in vec2 in_pos;
layout(location = 1) in vec2 in_uv;

uniform mat4 mvp;

out vec2 uv;

void main(void)
{
	uv = in_uv;
	gl_Position = vec4(in_pos.x, in_pos.y, 0, 1) * mvp;
}