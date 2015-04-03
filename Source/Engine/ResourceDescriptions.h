struct TextureDesc
{
	std::string path;

	TextureDesc(const Json::Value &value, const std::string &basePath);
	bool IsValid() const;
};

struct MeshDesc
{
	std::string path;

	MeshDesc(const Json::Value &value, const std::string &basePath);
	bool IsValid() const;
};

struct ShaderDesc
{
	std::string vs_path, fs_path;

	ShaderDesc(const Json::Value &value, const std::string &basePath);
	bool IsValid() const;
};