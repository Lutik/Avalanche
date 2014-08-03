#include "stdafx.h"

#include "Shader.h"
#include "Utils.h"

Shader::Shader()
	: _id(0)
{
}

void Shader::InitFromFile(std::string fileName, GLenum shaderType)
{
	std::string source = ReadFile(fileName);
	InitFromSource(source, shaderType);
}

void Shader::InitFromSource(std::string source, GLenum shaderType)
{
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

void ShaderProgram::Init()
{
	_id = glCreateProgram();	
}

void ShaderProgram::AttachShader(const Shader *shader)
{
	glAttachShader(_id, shader->GetID());
}

void ShaderProgram::Link()
{
	glBindFragDataLocation(_id, 0, "fragColor");
	glLinkProgram(_id);
	ProgramLog(_id);
}

void ShaderProgram::Release()
{
	glDeleteProgram(_id);
	_id = 0;
}

void ShaderProgram::Bind()
{
	glUseProgram(_id);
}

GLuint ShaderProgram::GetID() const
{
	return _id;
}