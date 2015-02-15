#pragma once

#include "VertexBuffer.h"
#include "VertexDescription.h"

enum class IndexType : int
{
	BYTE  = 0,
	SHORT = 1,
	INT   = 2
};

class Mesh
{
	VertexBuffer _vb;
	IndexBuffer _ib;
	VertexDescription _vertexDescription;
	IndexType _indexType;
public:
	Mesh() = default;

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	Mesh(Mesh&& other);
	Mesh& operator=(Mesh&& other);

	void SetVertices(const VertexDescription &vertDesc, size_t count, const void *data);
	void SetIndices(IndexType indexType, size_t count, const void *data);

	void Draw();
};