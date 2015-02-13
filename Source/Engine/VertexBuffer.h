#pragma once


template<GLenum bufferType, typename DataType>
class DeviceBuffer
{
	size_t _size = 0;
	GLuint _id = 0;
public:
	DeviceBuffer() = default;
	DeviceBuffer(const DeviceBuffer&) = delete;
	DeviceBuffer& operator=(const DeviceBuffer&) = delete;

	bool IsValid() const
	{
		return (_id != 0);
	}

	size_t Size() const
	{
		return _size;
	}

	void Init(size_t size, const DataType *data = nullptr, GLenum usage = GL_DYNAMIC_DRAW)
	{
		if( !IsValid() ) {
			glGenBuffers(1, &_id);
		}

		if(data != nullptr || size != _size)
		{
			glBindBuffer(bufferType, _id);
			glBufferData(bufferType, size * sizeof(DataType), data, usage);
		}

		_size = size;
	}

	void Release()
	{
		glDeleteBuffers(1, &_id);
		_size = 0;
		_id = 0;
	}

	void SetData(const DataType *data, size_t start, size_t count)
	{
		size_t stride = sizeof(DataType);
		glBindBuffer(bufferType, _id);
		glBufferSubData(bufferType, start * stride, count * stride, data);
	}

	void Bind()
	{
		glBindBuffer(bufferType, _id);
	}

	void Unbind()
	{
		glBindBuffer(bufferType, 0);
	}
};

template<class VertexType> using VertexBuffer = DeviceBuffer<GL_ARRAY_BUFFER, VertexType>;
template<class IndexType> using IndexBuffer = DeviceBuffer<GL_ELEMENT_ARRAY_BUFFER, IndexType>;