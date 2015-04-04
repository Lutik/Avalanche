#pragma once

#include "Matrix.h"
#include "Model.h"

class Renderer
{
	Matrix4f _view;
	Matrix4f _projection;

	struct ModelRenderData
	{
		Model *model;
		Matrix4f matrix;
	};
	std::vector<ModelRenderData> _models;

	Vector3f _light_direction;
public:
	void SetViewMatrix(const Matrix4f &mat);
	void SetProjectionMatrix(const Matrix4f &mat);
	void AddModel(Model *model, const Matrix4f &mat);

	void AddLight(Vector3f light_dir);

	void Clear();
	void Draw();
};