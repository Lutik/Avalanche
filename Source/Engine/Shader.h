#pragma once

class Shader
{
public:
	Shader();

	void InitFromFile(std::string fileName, GLenum shaderType);
	void InitFromSource(std::string source, GLenum shaderType);
	void Release();

	GLuint GetID() const;
private:
	GLuint _id;

};

class ShaderProgram
{
public:
	ShaderProgram();

	void Init();
	void AttachShader(const Shader *shader);
	void Link();

	void Release();

	void Bind();

	GLuint GetID() const;
private:
	GLuint _id;
	Shader vsh;
	Shader fsh;
};