#pragma once
#include "math3d.h"
#include "VertexTypes.h"
#include "Texture.h"

class Font
{
	Texture2D _tex;

	struct GlyphInfo
	{
		int code;
		Vector2f pos;
		Vector2f size;
		Vector2f offset;
		Vector2f orig_size;
	};

	std::vector<GlyphInfo> _glyphs;

	GlyphInfo* GetGlyph(int code);
public:
	void Load(std::string description);

	Vector2f DrawGlyph(Vector2f pos, int code, float height, std::vector<VertexP2T2> &vb, std::vector<Uint16> &ib);
	void DrawString(Vector2f pos, std::string str, float height, std::vector<VertexP2T2> &vb, std::vector<Uint16> &ib);

	const Texture2D& GetTexture() const;
};