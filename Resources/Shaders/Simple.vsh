#version 150 core

in vec2 in_pos;
in vec2 in_uv;

out vec2 uv;

void main(void)
{
	uv = in_uv;
	gl_Position = vec4(in_pos.x, in_pos.y, 0.0, 1.0);
}