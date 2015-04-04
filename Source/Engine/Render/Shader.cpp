#include "stdafx.h"

#include "Shader.h"
#include "Utils.h"

ShaderProgram::ShaderProgram()
	: _id(0)
{
	_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	if(_id > 0)
		glDeleteProgram(_id);
}

void ShaderProgram::Link(const std::string& vs, const std::string& ps)
{
	std::string source;
	const char *src;

	source = File::ReadFile(vs);
	src = source.c_str();
	GLuint vert_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert_id, 1, &src, nullptr);
	glCompileShader(vert_id);
	ShaderLog(vert_id);
	glAttachShader(_id, vert_id);

	source = File::ReadFile(ps);
	src = source.c_str();
	GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_id, 1, &src, nullptr);
	glCompileShader(frag_id);
	ShaderLog(frag_id);
	glAttachShader(_id, frag_id);

	glBindFragDataLocation(_id, 0, "fragColor");
	glLinkProgram(_id);
	ProgramLog(_id);
}

void ShaderProgram::Bind()
{
	glUseProgram(_id);
}

GLint ShaderProgram::GetUniformLocation(const std::string &name) const
{
	return glGetUniformLocation(_id, name.c_str());
}

void ShaderProgram::SetUniform(GLint loc, const Matrix4f &mat)
{
	glUniformMatrix4fv(loc, 1, GL_FALSE, mat.ptr());
}

void ShaderProgram::SetUniform(GLint loc, const Vector3f &vec)
{
	glUniform3fv(loc, 1, vec.ptr());
}

void ShaderProgram::SetUniform(GLint loc, const Vector4f &vec)
{
	glUniform4fv(loc, 1, vec.ptr());
}

void ShaderProgram::SetUniform(GLint loc, GLint v0)
{
	glUniform1i(loc, v0);
}

void ShaderProgram::SetUniform(const std::string& name, const Matrix4f &mat)
{
	GLint loc = GetUniformLocation(name);
	if( loc >= 0 )
		SetUniform(loc, mat);
}

void ShaderProgram::SetUniform(const std::string& name, const Vector3f &vec)
{
	GLint loc = GetUniformLocation(name);
	if( loc >= 0 )
		SetUniform(loc, vec);
}

void ShaderProgram::SetUniform(const std::string& name, const Vector4f &vec)
{
	GLint loc = GetUniformLocation(name);
	if (loc >= 0)
		SetUniform(loc, vec);
}

void ShaderProgram::SetUniform(const std::string& name, GLint v0)
{
	GLint loc = GetUniformLocation(name);
	if (loc >= 0)
		SetUniform(loc, v0);
}

GLuint ShaderProgram::GetID() const
{
	return _id;
}