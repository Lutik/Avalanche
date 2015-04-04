#include "stdafx.h"
#include "Utils.h"
#include "Log.h"

namespace File
{

std::string ReadFile(const std::string &fileName)
{
	std::string content;
	std::ifstream fileStream(fileName, std::ios::in);

	if (!fileStream.is_open()) {
		Av::Log::log("Can't read file %s\n", fileName.c_str());
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

std::string FolderFromPath(const std::string &path)
{
	size_t pos = path.find_last_of("/");
	return (pos == std::string::npos) ? path : path.substr(0, pos+1);
}

bool Exists(const std::string &fileName)
{
	std::ifstream file(fileName);
	bool result = file.good();
	file.close();
	return result;
}

} // end of namespace File