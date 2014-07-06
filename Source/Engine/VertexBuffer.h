#pragma once

#include "math3d.h"


struct VertexP2T2
{
	Vector2f pos;
	Vector2f uv;
};

template<class VertexType>
class VertexBuffer
{
	size_t _size;
	GLuint _id;
public:
	VertexBuffer()
		: _size(0)
		, _id(0)
	{}

	bool IsValid() const
	{
		return (_id != 0);
	}

	size_t Size() const
	{
		return _size;
	}

	void Init(size_t size, const VertexType *data = NULL)
	{
		if( !IsValid() ) {
			glGenBuffers(1, &_id);
		}

		if(data != NULL || size != _size)
		{
			glBindBuffer(GL_ARRAY_BUFFER, _id);
			glBufferData(GL_ARRAY_BUFFER, _size * sizeof(VertexType), data, GL_DYNAMIC_DRAW);
		}

		_size = size;
	}

	void Release()
	{
		glDeleteBuffers(1, &_id);
		_size = 0;
	}

	void SetData(const VertexType *data, size_t start, size_t count)
	{
		size_t stride = sizeof(VertexType);
		glBindBuffer(GL_ARRAY_BUFFER, _id);
		glBufferSubData(GL_ARRAY_BUFFER, start * stride, count * stride, data);
	}

	void Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _id);
	}

	void Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};

class IndexBuffer
{
};



void DrawArrays();