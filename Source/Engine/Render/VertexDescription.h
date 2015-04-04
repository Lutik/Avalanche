#pragma once

enum class VertexAttribType
{
	POSITION,
	TEXCOORD,
	NORMAL,
	COLOR,
	CUSTOM
};
struct VertexAttribute
{
	GLuint location;
	int size;
	GLenum type; // GL_FLOAT, GL_UNSIGNED_BYTE etc.
	GLboolean normalized;
	size_t offset;
	VertexAttribType content;
};

struct VertexDescription
{
	GLsizei vertexSize;
	std::vector<VertexAttribute> _attribs;

	void AddAttrib(const VertexAttribute& attr);
	void Apply() const;
};