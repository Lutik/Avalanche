#pragma once


template<GLenum bufferType>
class DeviceBuffer
{
	size_t _size = 0;
	size_t _elemSize = 1;
	GLuint _id = 0;
public:
	DeviceBuffer()
	{
		glGenBuffers(1, &_id);
	}

	~DeviceBuffer()
	{
		if(_id > 0) {
			glDeleteBuffers(1, &_id);
		}
	}

	DeviceBuffer(const DeviceBuffer&) = delete;
	DeviceBuffer& operator=(const DeviceBuffer&) = delete;

	DeviceBuffer(DeviceBuffer&& other)
	{
		std::swap(_size, other._size);
		std::swap(_elemSize, other._elemSize);
		std::swap(_id, other._id);
	}

	DeviceBuffer& operator=(DeviceBuffer&& other)
	{
		std::swap(_size, other._size);
		std::swap(_elemSize, other._elemSize);
		std::swap(_id, other._id);
		return *this;
	}

	size_t Size() const
	{
		return _size;
	}

	void Init(size_t size, const void *data = nullptr, size_t elemSize = 1, GLenum usage = GL_DYNAMIC_DRAW)
	{
		
		size_t oldSize = _size * _elemSize;
		size_t newSize = size * elemSize;
		if(data != nullptr || oldSize != newSize)
		{
			glBindBuffer(bufferType, _id);
			glBufferData(bufferType, newSize, data, usage);
		}
		_size = size;
		_elemSize = elemSize;
	}

	DeviceBuffer(size_t size, const void *data = nullptr, size_t elemSize = 1, GLenum usage = GL_DYNAMIC_DRAW)
		: DeviceBuffer()
	{
		Init(size, data, elemSize, usage);
	}

	void SetData(const void *data, size_t start, size_t count)
	{
		glBindBuffer(bufferType, _id);
		glBufferSubData(bufferType, start * _elemSize, count * _elemSize, data);
	}

	void Bind()
	{
		glBindBuffer(bufferType, _id);
	}
};

typedef DeviceBuffer<GL_ARRAY_BUFFER> VertexBuffer;
typedef DeviceBuffer<GL_ELEMENT_ARRAY_BUFFER> IndexBuffer;