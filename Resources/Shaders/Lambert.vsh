#version 330 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 light_position;

out vec2 uv;
out vec3 normal;
out vec3 light_vec;

void main(void)
{
	// calculate camera-space vectors
	mat3 model_it = transpose(inverse(mat3(model)));
	normal = normalize(mat3(view) * model_it * in_normal);
	vec4 light_pos = view * vec4(light_position, 1);
	vec4 vert_pos = view * model * vec4(in_pos, 1);
	light_vec = light_pos.xyz - vert_pos.xyz;

	uv = in_uv;
	gl_Position = projection * view * model * vec4(in_pos, 1);
}