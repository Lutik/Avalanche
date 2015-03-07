#include "stdafx.h"
#include "Texture.h"


Texture2D::Texture2D()
{
	glGenTextures(1, &_id);
}

Texture2D::~Texture2D()
{
	if(_id > 0) {
		glDeleteTextures(1, &_id);
	}
}

Texture2D::Texture2D(const Image2D &image)
	: Texture2D()
{
	SetImage(image);
}

Texture2D::Texture2D(Texture2D &&other)
{
	std::swap(_id, other._id);
	std::swap(_width, other._width);
	std::swap(_height, other._height);
}

Texture2D& Texture2D::operator=(Texture2D &&other)
{
	std::swap(_id, other._id);
	std::swap(_width, other._width);
	std::swap(_height, other._height);
	return *this;
}

void Texture2D::SetImage(const Image2D &image)
{
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexImage2D(GL_TEXTURE_2D, 0, image.Format(), image.Width(), image.Height(), 0, image.Format(), image.Type(), image.data());
	_width = image.Width();
	_height = image.Height();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::Bind(int texUnit) const
{
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, _id);
}

int Texture2D::Width() const
{
	return _width;
}
	
int Texture2D::Height() const
{
	return _height;
}

GLuint Texture2D::GetID() const
{
	return _id;
}