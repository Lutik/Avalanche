#include "stdafx.h"

#include "Model.h"

Model::Model(Mesh *mesh, Material *material)
	: _mesh(mesh)
	, _material(material)
{
	_vao.Bind();
	_mesh->SetupVertexArray();
}

Material* Model::GetMaterial() const
{
	return _material;
}

void Model::Bind()
{
	_vao.Bind();
	_material->Bind();
}

void Model::Draw()
{
	GLenum primType = _mesh->GetPrimitiveTypeGL();
	GLenum indexType = _mesh->GetIndexTypeGL();
	size_t indexCount = _mesh->GetIndexCount();

	glDrawElements(primType, indexCount, indexType, 0);
}