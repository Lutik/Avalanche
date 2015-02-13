#pragma once


template<GLenum bufferType, typename DataType>
class DeviceBuffer
{
	size_t _size = 0;
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
		_size = other._size;
		_id = other._id;
		other._size = 0;
		other._id = 0;
	}

	size_t Size() const
	{
		return _size;
	}

	void Init(size_t size, const DataType *data = nullptr, GLenum usage = GL_DYNAMIC_DRAW)
	{
		if(data != nullptr || size != _size)
		{
			glBindBuffer(bufferType, _id);
			glBufferData(bufferType, size * sizeof(DataType), data, usage);
		}
		_size = size;
	}

	DeviceBuffer(size_t size, const DataType *data = nullptr, GLenum usage = GL_DYNAMIC_DRAW)
		: DeviceBuffer()
	{
		Init(size, data, usage);
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