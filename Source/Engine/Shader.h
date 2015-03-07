#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"

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

	void SetUniform(const std::string &name, const Matrix4f &mat);
	void SetUniform(const std::string &name, GLint v0);
	void SetUniform(const std::string &name, const Vector3f &vec);
	void SetUniform(const std::string &name, const Vector4f &vec);
private:
	GLuint _id;
};