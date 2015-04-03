#include "stdafx.h"

#include "ResourceDescriptions.h"
#include "Utils.h"


TextureDesc::TextureDesc(const Json::Value &value, const std::string &basePath)
{
	path = basePath + value.get("path", "").asString();
}

bool TextureDesc::IsValid() const
{
	return File::Exists(path);
}


MeshDesc::MeshDesc(const Json::Value &value, const std::string &basePath)
{
	path = basePath + value.get("path", "").asString();
}

bool MeshDesc::IsValid() const
{
	return File::Exists(path);
}


ShaderDesc::ShaderDesc(const Json::Value &value, const std::string &basePath)
{
	vs_path = basePath + value.get("vs", "").asString();
	fs_path = basePath + value.get("fs", "").asString();
}

bool ShaderDesc::IsValid() const
{
	return File::Exists(vs_path) && File::Exists(fs_path);
}