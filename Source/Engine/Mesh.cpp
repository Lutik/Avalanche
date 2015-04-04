#include "stdafx.h"
#include "Mesh.h"

GLenum IndexTypeGL(IndexType type)
{
	const GLenum gl_types[] = {GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT};
	return gl_types[(int)type];
}

size_t IndexTypeSize(IndexType type)
{
	const size_t sizes[] = {1, 2, 4};
	return sizes[(int)type];
}

Mesh::Mesh(Mesh&& other)
{
	std::swap(_vb, other._vb);
	std::swap(_ib, other._ib);
	std::swap(_vertexDescription, other._vertexDescription);
	std::swap(_indexType, other._indexType);
}

Mesh& Mesh::operator=(Mesh&& other)
{
	std::swap(_vb, other._vb);
	std::swap(_ib, other._ib);
	std::swap(_vertexDescription, other._vertexDescription);
	std::swap(_indexType, other._indexType);
	return *this;
}

void Mesh::SetVertices(const VertexDescription &vertDesc, size_t count, const void *data)
{
	_vertexDescription = vertDesc;
	_vb.Init(count, data, _vertexDescription.vertexSize, GL_DYNAMIC_DRAW);
}

void Mesh::SetIndices(IndexType indexType, size_t count, const void *data)
{
	_indexType = indexType;
	_ib.Init(count, data, IndexTypeSize(_indexType), GL_DYNAMIC_DRAW);
}

IndexType Mesh::GetIndexType() const
{
	return _indexType;
}

GLenum Mesh::GetIndexTypeGL() const
{
	return IndexTypeGL(_indexType);
}

GLenum Mesh::GetPrimitiveTypeGL() const
{
	return GL_TRIANGLES;
}

size_t Mesh::GetIndexCount() const
{
	return _ib.Size();
}

void Mesh::SetupVertexArray()
{
	_vb.Bind();
	_ib.Bind();
	_vertexDescription.Apply();
}