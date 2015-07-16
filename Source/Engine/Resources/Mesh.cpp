#include "stdafx.h"
#include "Mesh.h"

GLenum IndexTypeGL(IndexType type)
{
	static const GLenum gl_types[] = {GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT};
	return gl_types[(int)type];
}

GLenum PrimitiveTypeGL(PrimitiveType type)
{
	static const GLenum gl_types[] = {GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN};
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
	std::swap(_primitiveType, other._primitiveType);
	std::swap(_vao, other._vao);
}

Mesh& Mesh::operator=(Mesh&& other)
{
	std::swap(_vb, other._vb);
	std::swap(_ib, other._ib);
	std::swap(_vertexDescription, other._vertexDescription);
	std::swap(_indexType, other._indexType);
	std::swap(_primitiveType, other._primitiveType);
	std::swap(_vao, other._vao);
	return *this;
}

void Mesh::SetVertices(const VertexDescription &vertDesc, size_t count, const void *data)
{
	_vertexDescription = vertDesc;
	_vao.Bind();
	_vb.Init(count, data, _vertexDescription.vertexSize, GL_DYNAMIC_DRAW);	
	if(_ib.Size() > 0) {
		_vertexDescription.Apply();
	}
}

void Mesh::SetIndices(IndexType indexType, PrimitiveType primType, size_t count, const void *data)
{
	_indexType = indexType;
	_primitiveType = primType;
	_vao.Bind();
	_ib.Init(count, data, IndexTypeSize(_indexType), GL_DYNAMIC_DRAW);
	if(_vb.Size() > 0) {
		_vertexDescription.Apply();
	}
}

IndexType Mesh::GetIndexType() const
{
	return _indexType;
}

GLenum Mesh::GetIndexTypeGL() const
{
	return IndexTypeGL(_indexType);
}

PrimitiveType Mesh::GetPrimitiveType() const
{
	return _primitiveType;
}

GLenum Mesh::GetPrimitiveTypeGL() const
{
	return PrimitiveTypeGL(_primitiveType);
}

size_t Mesh::GetIndexCount() const
{
	return _ib.Size();
}

void Mesh::Bind()
{
	_vao.Bind();
}

void Mesh::Draw()
{
	glDrawElements(GetPrimitiveTypeGL(), _ib.Size(), GetIndexTypeGL(), 0);
}