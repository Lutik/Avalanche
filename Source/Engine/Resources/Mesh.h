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

enum class PrimitiveType : int
{
	TRIANGLES      = 0,
	TRIANGLE_STRIP = 1,
	TRIANGLE_FAN   = 2
};

class Mesh
{
	VertexArrayObject _vao;
	VertexBuffer _vb;
	IndexBuffer _ib;
	VertexDescription _vertexDescription;
	IndexType _indexType;
	PrimitiveType _primitiveType;
public:
	Mesh() = default;

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	Mesh(Mesh&& other);
	Mesh& operator=(Mesh&& other);

	void SetVertices(const VertexDescription &vertDesc, size_t count, const void *data);
	void SetIndices(IndexType indexType, PrimitiveType primType, size_t count, const void *data);

	IndexType GetIndexType() const;
	GLenum GetIndexTypeGL() const;
	PrimitiveType GetPrimitiveType() const;
	GLenum GetPrimitiveTypeGL() const;
	size_t GetIndexCount() const;

	void Bind();
	void Draw();
};