#pragma once

#include "Mesh.h"
#include "Font.h"
#include "Material.h"

class FpsCounter
{
	unsigned int _interval = 32;
	unsigned int _frames = 0;
	float _time = 0.0f;
	float _fps = 0.0f;

	Mesh _mesh;
	Font _font;
	Material *_material;

	void UpdateMesh(float fps);
public:
	FpsCounter();

	void Update(float dt);
	void Draw();
};