#include "stdafx.h"

#include "ResourceManager.h"
#include "Utils.h"

namespace Av {
	ResourceManager resourceManager;
}


TextureDesc::TextureDesc(const Json::Value &value, const std::string &basePath)
{
	path = basePath + value.get("path", "").asString();
}

bool TextureDesc::IsValid() const
{
	return File::Exists(path);
}



template<class ResourceDesc, class ResourcePtr>
void LoadResourceDescriptions(const Json::Value &json,
	const std::string &resType,
	const std::string &basePath,
	std::map<std::string, std::pair<ResourceDesc, ResourcePtr>> &descriptions)
{
	Json::Value descArray = json.get(resType, Json::Value());
	for(const Json::Value &value : descArray)
	{
		std::string name = value.get("name", "").asString();
		if( !name.empty() )
		{
			ResourceDesc desc(value, basePath);
			auto result = descriptions.emplace(name, std::make_pair(desc, ResourcePtr()));
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

		LoadResourceDescriptions<TextureDesc, TexturePtr>(root, "Textures", basePath, _textures);
	}
}

void ResourceManager::LoadResources()
{
	for(auto &elem : _textures)
	{
		TextureDesc &desc = elem.second.first;
		TexturePtr &ptr = elem.second.second;
		Image2D img = loadTexture(desc.path);
		if( !img.Empty() )
		{
			ptr = std::make_unique<Texture2D>();
			ptr->SetImage(img);
		}
		else
		{
			// log error
		}
	}
}

void ResourceManager::UnloadResources()
{
	for(auto &elem : _textures)
	{
		elem.second.second.reset();
	}
}

Texture2D::Ref ResourceManager::GetTexture(const std::string &name) const
{
	auto itr = _textures.find(name);
	if( itr != _textures.end() )
	{
		return itr->second.second.get();
	}
	return nullptr;
}