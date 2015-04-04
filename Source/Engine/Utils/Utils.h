#pragma once

namespace File
{
	std::string ReadFile(const std::string &fileName);

	std::string FolderFromPath(const std::string &path);

	bool Exists(const std::string &fileName);
}