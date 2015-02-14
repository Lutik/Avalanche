#include "stdafx.h"
#include "ImageLoaders.h"
#include <png.h>

Image2D::Image2D(int w, int h, GLint f, GLenum t, size_t dataSize)
	: _width(w)
	, _height(h)
	, _format(f)
	, _type(t)
{
	_data.reset( new uint8_t[dataSize] );
}

Image2D::Image2D(Image2D &&other)
{
	std::swap(_data, other._data);
	_width = other._width;
	_height = other._height;
	_format = other._format;
	_type = other._type;
}

Image2D& Image2D::operator=(Image2D &&other)
{
	std::swap(_data, other._data);
	_width = other._width;
	_height = other._height;
	_format = other._format;
	_type = other._type;
	return *this;
}

uint8_t *Image2D::data() const
{
	return _data.get();
}

int Image2D::width() const
{
	return _width;
}

int Image2D::height() const
{
	return _height;
}

GLint Image2D::format() const
{
	return _format;
}

GLenum Image2D::type() const
{
	return _type;
}

static const GLuint TEXTURE_LOAD_ERROR = 0;

Image2D loadTexture(const std::string filename) 
 {
	Image2D image;

   //header for testing if it is a png
   png_byte header[8];
 
   //open file as binary
   FILE *fp = fopen(filename.c_str(), "rb");
   if (!fp) {
     return image;
   }
 
   //read the header
   fread(header, 1, 8, fp);
 
   //test if png
   int is_png = !png_sig_cmp(header, 0, 8);
   if (!is_png) {
     fclose(fp);
     return image;
   }
 
   //create png struct
   png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
       NULL, NULL);
   if (!png_ptr) {
     fclose(fp);
     return image;
   }
 
   //create png info struct
   png_infop info_ptr = png_create_info_struct(png_ptr);
   if (!info_ptr) {
     png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
     fclose(fp);
     return image;
   }
 
   //create png info struct
   png_infop end_info = png_create_info_struct(png_ptr);
   if (!end_info) {
     png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
     fclose(fp);
     return image;
   }
 
   //png error stuff, not sure libpng man suggests this.
   if (setjmp(png_jmpbuf(png_ptr))) {
     png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
     fclose(fp);
     return image;
   }
 
   //init png reading
   png_init_io(png_ptr, fp);
 
   //let libpng know you already read the first 8 bytes
   png_set_sig_bytes(png_ptr, 8);
 
   // read all the info up to the image data
   png_read_info(png_ptr, info_ptr);
 
   //variables to pass to get info
   int bit_depth, color_type;
   png_uint_32 twidth, theight;
 
   // get info about png
   png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
       NULL, NULL, NULL);
 
   // Update the png info struct.
   png_read_update_info(png_ptr, info_ptr);
 
   // Row size in bytes.
   int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

   image = Image2D(twidth, theight, GL_RGBA, GL_UNSIGNED_BYTE, rowbytes * theight);
 
   //row_pointers is for pointing to image_data for reading the png with libpng
   png_bytep *row_pointers = new png_bytep[theight];
   if (!row_pointers) {
     //clean up memory and close stuff
     png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
     fclose(fp);
     return image;
   }
   // set the individual row_pointers to point at the correct offsets of image_data
   for (int i = 0; i < theight; ++i)
     row_pointers[theight - 1 - i] = image.data() + i * rowbytes;
 
   //read the png into image_data through row_pointers
   png_read_image(png_ptr, row_pointers);
 
   //clean up memory and close stuff
   png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
   delete[] row_pointers;
   fclose(fp);
 
   return image;
 }