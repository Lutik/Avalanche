#include "stdafx.h"

#include "Shader.h"
#include "Utils.h"

Shader::Shader()
	: _id(0)
{
}

void Shader::Init(std::string fileName, GLenum shaderType)
{
	std::string source = ReadFile(fileName);
	const char *src = source.c_str();

	_id = glCreateShader(shaderType);

	glShaderSource(_id, 1, &src, nullptr);
	glCompileShader(_id);

	ShaderLog(_id);
}

void Shader::Release()
{
	glDeleteShader(_id);
	_id = 0;
}

GLuint Shader::GetID() const
{
	return _id;
}



ShaderProgram::ShaderProgram()
	: _id(0)
{
}

void ShaderProgram::Init(std::string vertex, std::string fragment)
{
	_id = glCreateProgram();

	glBindFragDataLocation(_id, 0, "fragColor");

	vsh.Init(vertex, GL_VERTEX_SHADER);
	fsh.Init(fragment, GL_FRAGMENT_SHADER);

	glAttachShader(_id, vsh.GetID());
	glAttachShader(_id, fsh.GetID());

	glLinkProgram(_id);

	ProgramLog(_id);
}

void ShaderProgram::Release()
{
	glDeleteProgram(_id);
}

void ShaderProgram::Bind()
{
	glUseProgram(_id);
}

GLuint ShaderProgram::GetID() const
{
	return _id;
}