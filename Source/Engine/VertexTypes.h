#pragma once

#include "math3d.h"
#include "VertexDescription.h"

struct VertexP2T2
{
	Vector2f pos;
	Vector2f uv;

	static VertexDescription GetVertexDescription()
	{
		VertexDescription desc;
		desc.vertexSize = sizeof(VertexP2T2);
		desc.AddAttrib({0, 2, GL_FLOAT, GL_FALSE, offsetof(VertexP2T2, pos), VertexAttribType::POSITION});
		desc.AddAttrib({1, 2, GL_FLOAT, GL_FALSE, offsetof(VertexP2T2, uv), VertexAttribType::TEXCOORD});
		return desc;
	}
};

struct VertexP3T2
{
	Vector3f pos;
	Vector2f uv;

	static VertexDescription GetVertexDescription()
	{
		VertexDescription desc;
		desc.vertexSize = sizeof(VertexP2T2);
		desc.AddAttrib({0, 3, GL_FLOAT, GL_FALSE, offsetof(VertexP3T2, pos), VertexAttribType::POSITION});
		desc.AddAttrib({1, 2, GL_FLOAT, GL_FALSE, offsetof(VertexP3T2, uv), VertexAttribType::TEXCOORD});
		return desc;
	}
};

struct VertexP3T2N3
{
	Vector3f pos;
	Vector2f uv;
	Vector3f normal;

	static VertexDescription GetVertexDescription()
	{
		VertexDescription desc;
		desc.vertexSize = sizeof(VertexP2T2);
		desc.AddAttrib({0, 3, GL_FLOAT, GL_FALSE, offsetof(VertexP3T2N3, pos), VertexAttribType::POSITION});
		desc.AddAttrib({1, 2, GL_FLOAT, GL_FALSE, offsetof(VertexP3T2N3, uv), VertexAttribType::TEXCOORD});
		desc.AddAttrib({3, 3, GL_FLOAT, GL_FALSE, offsetof(VertexP3T2N3, normal), VertexAttribType::NORMAL});
		return desc;
	}
};

