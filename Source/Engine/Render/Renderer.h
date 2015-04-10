#pragma once

#include "Matrix.h"
#include "Mesh.h"
#include "Material.h"
#include "VertexArrayObject.h"
#include "EntitySystem.h"

class Renderer
{
	Matrix4f _view;
	Matrix4f _projection;

	struct ModelRenderData
	{
		VertexArrayObject *vao;
		Mesh *mesh;
		Material *material;
		Matrix4f matrix;
	};
	std::vector<ModelRenderData> _models;

	Vector3f _light_direction;

	void CollectRenderData(EntityContainer &entities);
public:
	void SetViewMatrix(const Matrix4f &mat);
	void SetProjectionMatrix(const Matrix4f &mat);

	void AddLight(Vector3f light_dir);

	void Clear();

	void Draw(EntityContainer &entities);
};