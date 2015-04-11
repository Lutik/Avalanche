#include "stdafx.h"

#include "Avalanche.h"
#include "Game.h"
#include "ResourceManager.h"

#include "ModelComponent.h"
#include "MyComponents.h"
#include "CameraComponent.h"


TestScene::TestScene()
{
	Entity *cube1 = CreateCube({-3.5, 0.0f, 0.0f}, 0.035f);
	Entity *cube2 = CreateCube({3.5f, 0.0f, 0.0f}, 0.03f);
	Entity *cube3 = CreateCube({0.0f, 3.5f, 0.0f}, 0.03f);
	Entity *cube4 = CreateCube({0.0f, -3.5f, 0.0f}, 0.03f);
	Entity *cam = CreateCamera({-6.0f, -6.0f, 3.0f}, {1.0f, 1.0f, -0.5f});
	
	cube1->AddComponent(new MyAnimComponent());
	cube2->AddComponent(new MyAnimComponent());
	//cam->AddComponent(new MyAnimComponent());
}

Entity* TestScene::CreateCube(Vector3f pos, float scale)
{
	Entity *cube = entities.CreateEntity();
	TransformComponent *tc = new TransformComponent();
	tc->position = pos;
	tc->rotation = RotationToQuaternion({0,0,1}, 0.0f);
	tc->scale = scale;
	MeshComponent *mesh_comp = new MeshComponent();
	mesh_comp->SetMesh(Av::resourceManager.GetMesh("Cube"));
	MeshDrawComponent *md_comp = new MeshDrawComponent();
	md_comp->material = Av::resourceManager.GetMaterial("Metal");
	cube->AddComponent(tc);
	cube->AddComponent(mesh_comp);
	cube->AddComponent(md_comp);
	return cube;
}

Entity* TestScene::CreateCamera(Vector3f pos, Vector3f view)
{
	Entity *cam = entities.CreateEntity();
	TransformComponent *tc = new TransformComponent();
	tc->position = pos;
	tc->rotation = RotationFromVectors({1,0,0}, view);
	tc->scale = 1.0f;
	cam->AddComponent(tc);
	cam->AddComponent(new PerspectiveCameraComponent(45.0f, Av::application->GetAspectRatio(), 0.2f, 30.0f));
	return cam;
}

void TestScene::onUpdate(float dt)
{
	_animator.Update(entities, dt);

	Vector3f light_dir(1.0f, 1.0f, -5.0f);
	light_dir.Normalize();

	_render.Clear();
	_render.AddLight(light_dir);
	_render.Draw(entities);
}