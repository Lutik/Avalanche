#include "stdafx.h"

#include "Avalanche.h"
#include "Game.h"
#include "Utils.h"
#include "ResourceManager.h"

TestScene::TestScene()
{
	_model = Av::resourceManager.GetModel("MetalCube");

	_camera.SetPosition({0.0f, -6.0f, 3.0f});
	_camera.SetViewVector({0.0f, 1.0f, -0.5f});
	_camera.SetUpVector({0.0f, 0.0f, 1.0f});
	_camera.SetPerspective(45.0f, Av::application->GetAspectRatio(), 0.2f, 30.0f);

	_transform.position = {0,0,0};
	_transform.rotation = RotationToQuaternion({0,0,1}, 0.0f);
	_transform.scale = 0.06f;
}

void TestScene::onUpdate(float dt)
{
	_transform.Rotate({0,0,1}, 45.0f * dt);
}

void TestScene::onRender()
{
	Matrix4f modelMatrix = _transform.GetModelMatrix();

	Vector3f light_dir(1.0f, 1.0f, -5.0f);
	light_dir.Normalize();

	_render.Clear();
	_render.SetViewMatrix(_camera.GetViewMatrix());
	_render.SetProjectionMatrix(_camera.GetProjectionMatrix());
	_render.AddLight(light_dir);
	_render.AddModel(_model, modelMatrix);
	_render.Draw();
}