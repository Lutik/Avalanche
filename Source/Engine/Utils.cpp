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

} // end of namespace File