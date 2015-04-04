#pragma once

class VertexArrayObject
{
	GLuint _id = 0;
public:
	VertexArrayObject()
	{
		glGenVertexArrays(1, &_id);
	}

	~VertexArrayObject()
	{
		if(_id > 0) {
			glDeleteVertexArrays(1, &_id);
		}
	}

	VertexArrayObject(const VertexArrayObject&) = delete;
	VertexArrayObject& operator=(const VertexArrayObject&) = delete;

	VertexArrayObject(VertexArrayObject&& other)
	{
		std::swap(_id, other._id);
	}

	VertexArrayObject& operator=(VertexArrayObject&& other)
	{
		std::swap(_id, other._id);
		return *this;
	}

	void Bind()
	{
		glBindVertexArray(_id);
	}
};