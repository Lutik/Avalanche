#pragma once

#include "math3d.h"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;

	void Link(const std::string& vs, const std::string& ps);

	void Bind();

	GLuint GetID() const;

	void SetUniform(const std::string& name, Matrix4f &mat);
	void SetUniform(const std::string& name, GLint v0);
	void SetUniform(const std::string& name, Vector4f &vec);
private:
	GLuint _id;
};