#version 330 core

uniform sampler2D diffuse_tex;
uniform vec3 light_dir;

in vec2 uv;
in vec3 normal;

out vec4 fragColor;

void main(void)
{
	float brightness = dot(normalize(normal), -light_dir);
	brightness =clamp(0, 1, brightness);
	vec4 color = texture2D(diffuse_tex, uv);
	color.xyz = color.xyz * brightness;
	fragColor = color;
}