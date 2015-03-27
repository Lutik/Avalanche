#pragma once

#include "Texture.h"

struct TextureDesc
{
	std::string path;

	TextureDesc(const Json::Value &value, const std::string &basePath);

	bool IsValid() const;
};

typedef std::unique_ptr<Texture2D> TexturePtr;

class ResourceManager
{
	std::map<std::string, std::pair<TextureDesc, TexturePtr>> _textures;

public:
	void LoadDescriptions(const std::string &fileName);

	void LoadResources();
	void UnloadResources();

	Texture2D::Ref GetTexture(const std::string &name) const;
};

namespace Av
{
	extern ResourceManager resourceManager;
}