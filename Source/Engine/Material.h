#pragma once

#include "Shader.h"
#include "Texture.h"
#include "ResourceDescriptions.h"

class Material
{
	ShaderProgram *_shader = nullptr;
	std::vector<std::pair<GLint, Texture2D*>> _textures;
public:
	Material(const MaterialDesc& desc);

	void Bind();

	ShaderProgram *GetShader() { return _shader; }
};