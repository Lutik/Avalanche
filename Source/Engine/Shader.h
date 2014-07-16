#pragma once

class Shader
{
public:
	Shader();

	void Init(std::string fileName, GLenum shaderType);
	void Release();

	GLuint GetID() const;
private:
	GLuint _id;

};

class ShaderProgram
{
public:
	ShaderProgram();
	void Init(std::string vertex, std::string fragment);
	void Release();

	void Bind();

	GLuint GetID() const;
private:
	GLuint _id;
	Shader vsh;
	Shader fsh;
};