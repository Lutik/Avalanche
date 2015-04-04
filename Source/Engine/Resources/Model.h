#pragma once

#include "VertexArrayObject.h"
#include "Material.h"
#include "Mesh.h"

class Model
{
public:
	VertexArrayObject _vao;
	Mesh *_mesh = nullptr;
	Material *_material = nullptr;
public:
	Model(Mesh *mesh, Material *material);

	void Bind();
	void Draw();
};