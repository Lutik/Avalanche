#pragma once



class Image2D
{
	int _width = 0;
	int _height = 0;
	GLint _format = GL_RGB;
	GLenum _type = GL_UNSIGNED_BYTE;
	std::unique_ptr<uint8_t[]> _data;

public:
	Image2D() = default;
	Image2D(int width, int height, GLint format, GLenum type, size_t dataSize);

	Image2D(Image2D&&);
	Image2D& operator=(Image2D&&);

	uint8_t *data() const;
	int Width() const;
	int Height() const;
	GLint Format() const;
	GLenum Type() const;
	bool Empty() const;
};

Image2D loadTexture(const std::string filename);