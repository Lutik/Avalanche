#pragma once

#include "VertexBuffer.h"
#include "VertexDescription.h"
#include "VertexArrayObject.h"

enum class IndexType : int
{
	BYTE  = 0,
	SHORT = 1,
	INT   = 2
};

class Mesh
{
	VertexArrayObject _vao;
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

	IndexType GetIndexType() const;
	GLenum GetIndexTypeGL() const;
	size_t GetIndexCount() const;
	GLenum GetPrimitiveTypeGL() const;

	void UpdateVertexArray();

	void Bind();
	void Draw();
};