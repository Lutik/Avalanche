#version 330 core

uniform sampler2D diffuse_tex;
uniform vec3 light_color;
uniform vec3 light_attenuation;

in vec3 light_vec;
in vec2 uv;
in vec3 normal;

out vec4 fragColor;

float LightAttenuation(vec3 light)
{
	float dist = length(light);
	return 1.0 / (light_attenuation.x + light_attenuation.y * dist + light_attenuation.z * dist * dist);
}

vec3 LambertLighting(vec3 diffuseColor, vec3 lightColor, vec3 normal, vec3 light)
{
	float cosTheta = max(dot(normal, light), 0.0);
	return diffuseColor * lightColor * cosTheta;
}

void main(void)
{
	vec4 color = texture2D(diffuse_tex, uv);
	vec3 ambientColor = color.xyz * 0.05;
	vec3 diffuseColor = LambertLighting(color.xyz, light_color, normalize(normal), normalize(light_vec));
	diffuseColor.xyz *= LightAttenuation(light_vec);
	fragColor = vec4(ambientColor.xyz + diffuseColor.xyz, color.a);
}