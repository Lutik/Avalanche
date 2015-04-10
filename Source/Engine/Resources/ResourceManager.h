#pragma once

#include "ResourceDescriptions.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"

template<class ResourceDesc, class Resource> using ResourceContainer
	= std::map<std::string, std::pair<ResourceDesc, std::unique_ptr<Resource>>>;

class ResourceManager
{
	ResourceContainer<TextureDesc, Texture2D> _textures;
	ResourceContainer<MeshDesc, Mesh> _meshes;
	ResourceContainer<ShaderDesc, ShaderProgram> _shaders;
	ResourceContainer<MaterialDesc, Material> _materials;
public:
	void LoadDescriptions(const std::string &fileName);

	void LoadResources();
	void UnloadResources();

	Texture2D* GetTexture(const std::string &name) const;
	Mesh* GetMesh(const std::string &name) const;
	ShaderProgram* GetShader(const std::string &name) const;
	Material* GetMaterial(const std::string &name) const;
};

namespace Av
{
	extern ResourceManager resourceManager;
}