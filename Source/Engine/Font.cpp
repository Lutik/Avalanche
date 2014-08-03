#include "stdafx.h"
#include "Font.h"
#include "ImageLoaders.h"
#include <sstream>

void Font::Load(std::string description)
{
	_glyphs.clear();

	std::string dirName = description.substr(0, description.find_last_of('/')+1);

	std::ifstream file(description);

	std::string line;
	
	// 1st line: texture name
	std::getline(file, line);
	std::string texName = line.substr(10, std::string::npos);
	_tex = loadTexture(dirName + texName, _texWidth, _texHeight);

	// 2nd line: font name
	std::getline(file, line);

	// glyph info
	while (std::getline(file, line))
	{
		if (line == "kerning pairs:")
			break;

		GlyphInfo glyph;

		std::istringstream iss(line);

		iss >> glyph.code
			>> glyph.pos.x >> glyph.pos.y
			>> glyph.size.x >> glyph.size.y
			>> glyph.offset.x >> glyph.offset.y
			>> glyph.orig_size.x >> glyph.orig_size.y;

		// � ���������� ������� ������������ ������ ������� ���������
		glyph.pos.y = _texHeight - glyph.pos.y - glyph.size.y;
		glyph.offset.y = glyph.orig_size.y - glyph.size.y - glyph.offset.y;

		_glyphs.push_back(glyph);
	}

	// kerning pairs
	//while (std::getline(file, line))
	//{
	//}
}

Font::GlyphInfo* Font::GetGlyph(int code)
{
	for (GlyphInfo &glyph : _glyphs)
	{
		if (code == glyph.code)
			return &glyph;
	}
	return nullptr;
}

GLuint Font::GetTexID() const
{
	return _tex;
}

Vector2f Font::DrawGlyph(Vector2f pos, int code, float height, std::vector<VertexP2T2> &vb, std::vector<Uint16> &ib)
{
	GlyphInfo *g = GetGlyph(code);

	if (!g)
		return pos;

	Vector2f uv(g->pos.x / _texWidth, g->pos.y / _texHeight);
	Vector2f uvs(g->size.x / _texWidth, g->size.y / _texHeight);

	float scale = height / g->orig_size.y;
	Vector2f xy = g->offset * scale;
	Vector2f wh = g->size * scale;

	// calc indices
	Uint16 index = vb.size();
	ib.push_back(index);
	ib.push_back(index + 1);
	ib.push_back(index + 2);
	ib.push_back(index + 1);
	ib.push_back(index + 2);
	ib.push_back(index + 3);

	// calc vertices
	VertexP2T2 v[]
	{
		{ { xy.x, xy.y + wh.y }, { uv.x, uv.y + uvs.y } },
		{ { xy.x, xy.y }, { uv.x, uv.y } },
		{ { xy.x + wh.x, xy.y + wh.y }, { uv.x + uvs.x, uv.y + uvs.y } },
		{ { xy.x + wh.x, xy.y }, { uv.x + uvs.x, uv.y } }
	};
	for (VertexP2T2 &vert : v) vert.pos += pos;
	vb.push_back(v[0]);
	vb.push_back(v[1]);
	vb.push_back(v[2]);
	vb.push_back(v[3]);

	Vector2f new_pos = pos;
	new_pos.x += g->orig_size.x * scale;
	return new_pos;
}

void Font::DrawString(Vector2f pos, std::string str, float height, std::vector<VertexP2T2> &vb, std::vector<Uint16> &ib)
{
	for (unsigned char ch : str)
	{
		int code = ch;
		pos = DrawGlyph(pos, code, height, vb, ib);
	}
}