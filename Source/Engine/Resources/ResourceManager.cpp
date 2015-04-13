#include "stdafx.h"

#include "ResourceManager.h"

#include "Utils.h"

#include "ModelLoaders.h"

namespace Av {
	ResourceManager resourceManager;
}

template<class ResourceDesc, class Resource>
void LoadResourceDescriptions(const Json::Value &json,
	const std::string &resType,
	const std::string &basePath,
	ResourceContainer<ResourceDesc, Resource> &descriptions)
{
	Json::Value descArray = json.get(resType, Json::Value());
	for(const Json::Value &value : descArray)
	{
		std::string name = value.get("name", "").asString();
		if( !name.empty() )
		{
			ResourceDesc desc(value, basePath);
			auto result = descriptions.emplace(name, std::make_pair(desc, std::shared_ptr<Resource>()));
			if( !result.second ) {
				// Log error - resource with this name already exists
			} else if( !result.first->second.first.IsValid() ) {
				// Log error - resource is invalid
			}
		}
		else
		{
			// Log error - resource name not specified
		}
	}
}

void ResourceManager::LoadDescriptions(const std::string &fileName)
{
	Json::Value root;
	Json::Reader reader;

	bool parseOK = reader.parse(File::ReadFile(fileName), root, false);
	if( parseOK )
	{
		const Json::Value emptyArray;

		const std::string basePath = File::FolderFromPath(fileName);

		LoadResourceDescriptions<TextureDesc, Texture2D>(root, "Textures", basePath, _textures);
		LoadResourceDescriptions<MeshDesc, Mesh>(root, "Meshes", basePath, _meshes);
		LoadResourceDescriptions<ShaderDesc, ShaderProgram>(root, "Shaders", basePath, _shaders);
		LoadResourceDescriptions<MaterialDesc, Material>(root, "Materials", basePath, _materials);
	}
}

void ResourceManager::LoadResources()
{
	// Textures
	for(auto &elem : _textures)
	{
		TextureDesc &desc = elem.second.first;
		std::shared_ptr<Texture2D> &ptr = elem.second.second;
		Image2D img = loadTexture(desc.path);
		if( !img.Empty() )
		{
			ptr = std::make_shared<Texture2D>();
			ptr->SetImage(img);
		}
		else
		{
			// log error
		}
	}

	// Meshes
	for(auto &elem : _meshes)
	{
		MeshDesc &desc = elem.second.first;
		Mesh::Ptr &ptr = elem.second.second;
		ptr = LoadMeshOBJ(desc.path);
		if( !ptr ) {
			// log error
		}
	}

	// Shaders
	for(auto &elem : _shaders)
	{
		ShaderDesc &desc = elem.second.first;
		std::shared_ptr<ShaderProgram> &ptr = elem.second.second;
		ptr = std::make_shared<ShaderProgram>();
		ptr->Link(desc.vs_path, desc.fs_path);
		// todo: check for errors during shader linking
	}

	// Materials
	for(auto &elem : _materials)
	{
		MaterialDesc &desc = elem.second.first;
		std::shared_ptr<Material> &ptr = elem.second.second;
		ptr = std::make_shared<Material>(desc);
	}
}

template<class ResContainer>
void UnloadResourceContainer(ResContainer& cont)
{
	for(auto &elem : cont) {
		elem.second.second.reset();
	}
}

void ResourceManager::UnloadResources()
{
	UnloadResourceContainer(_materials);
	UnloadResourceContainer(_meshes);
	UnloadResourceContainer(_shaders);
	UnloadResourceContainer(_textures);
}


template<class ResourceDesc, class Resource>
Resource *GetResourceRawPtr(const std::string &name, const ResourceContainer<ResourceDesc, Resource> &container)
{
	auto itr = container.find(name);
	return (itr != container.end()) ? itr->second.second.get() : nullptr;
}

template<class ResourceDesc, class Resource>
std::shared_ptr<Resource> GetResource(const std::string &name, const ResourceContainer<ResourceDesc, Resource> &container)
{
	auto itr = container.find(name);
	return (itr != container.end()) ? itr->second.second : std::shared_ptr<Resource>();
}

Texture2D* ResourceManager::GetTexture(const std::string &name) const
{
	return GetResourceRawPtr<TextureDesc, Texture2D>(name, _textures);
}

Mesh::Ptr ResourceManager::GetMesh(const std::string &name) const
{
	return GetResource<MeshDesc, Mesh>(name, _meshes);
}

ShaderProgram* ResourceManager::GetShader(const std::string &name) const
{
	return GetResourceRawPtr<ShaderDesc, ShaderProgram>(name, _shaders);
}

Material* ResourceManager::GetMaterial(const std::string &name) const
{
	return GetResourceRawPtr<MaterialDesc, Material>(name, _materials);
}