#pragma once

#include "Component.h"

#include "Mesh.h"
#include "Material.h"

struct MeshComponent : public Component
{
	Mesh::Ptr mesh;

	void SetMesh(Mesh::Ptr m);

	virtual ComponentType getType() const override { return ComponentType::MESH; }
};

struct MeshDrawComponent : public Component
{
	Material *material;

	virtual ComponentType getType() const override { return ComponentType::MESH_DRAWER; }
};