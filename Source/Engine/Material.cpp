#include "stdafx.h"

#include "Material.h"
#include "ResourceManager.h"

Material::Material(const MaterialDesc &desc)
{
	_shader = Av::resourceManager.GetShader(desc.shader);

	for(const auto &texPair : desc.textures)
	{
		GLint loc = _shader->GetUniformLocation(texPair.first);
		if(loc >=  0) {
			Texture2D *tex= Av::resourceManager.GetTexture(texPair.second);
			_textures.emplace_back(loc, tex);
		}
	}
}

void Material::Bind()
{
	_shader->Bind();
	int sampler = 0;
	for(const auto &locTex : _textures) {
		locTex.second->Bind(sampler);
		_shader->SetUniform(locTex.first, sampler);
		++sampler;
	}
}