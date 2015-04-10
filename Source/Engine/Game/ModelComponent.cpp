#include "stdafx.h"

#include "ModelComponent.h"

void MeshComponent::SetMesh(Mesh *m)
{
	mesh = m;
	if( mesh ) {
		vao = std::make_unique<VertexArrayObject>();
		vao->Bind();
		mesh->SetupVertexArray();
	} else {
		vao.reset();
	}
}