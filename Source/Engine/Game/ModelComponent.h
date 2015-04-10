#pragma once

#include "Component.h"

#include "VertexArrayObject.h"
#include "Mesh.h"
#include "Material.h"

struct MeshComponent : public Component
{
	std::unique_ptr<VertexArrayObject> vao;
	Mesh *mesh = nullptr;

	void SetMesh(Mesh *m);

	virtual ComponentType getType() const override { return ComponentType::MESH; }
};

struct MeshDrawComponent : public Component
{
	Material *material;

	virtual ComponentType getType() const override { return ComponentType::MESH_DRAWER; }
};