#version 400 core

uniform sampler2D tex;

in vec2 uv;

out vec4 fragColor;

void main(void)
{
	fragColor = texture2D(tex, uv);
}