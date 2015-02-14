#pragma once

#include "ImageLoaders.h"

class Texture2D
{
	GLuint _id = 0;
	int _width = 0;
	int _height = 0;
public:
	Texture2D();
	~Texture2D();

	explicit Texture2D(const Image2D &image);

	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;

	Texture2D(Texture2D&&);
	Texture2D& operator=(Texture2D&&);

	void SetImage(const Image2D &image);

	void Bind(int texUnit) const;

	int Width() const;
	int Height() const;
};