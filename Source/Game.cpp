#include "stdafx.h"

#include "Avalanche.h"
#include "Game.h"
#include "ResourceManager.h"

#include "MeshComponent.h"
#include "MyComponents.h"
#include "CameraComponent.h"
#include "Shapes.h"

TestScene::TestScene()
{
	Entity *cube1 = CreateCube({-3.5, 0.0f, 0.0f}, 0.03f);
	Entity *cube2 = CreateCube({3.5f, 0.0f, 0.0f}, 0.03f);
	Entity *cube3 = CreateCube({0.0f, 3.5f, 0.0f}, 0.03f);
	Entity *cube4 = CreateCube({0.0f, -3.5f, 0.0f}, 0.03f);
	Entity *cam = CreateCamera({-6.0f, -6.0f, 3.0f}, {1.0f, 1.0f, -0.5f});
	Entity *plane = CreatePlane();
	
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

// рассчитываем кватернион для камеры при котором вектор взгляда будет равен заданному,
// и при этом направление вверх никуда не уедет
Quaternion CalcCameraRotation(Vector3f view)
{
	Vector3f view_hor = {view.x, view.y, 0.0f};
	Quaternion q1 = RotationFromVectors({1,0,0}, view_hor);
	Quaternion q2 = RotationFromVectors(view_hor, view);
	return UnitQuatProduct(q2, q1);
}

Entity* TestScene::CreateCamera(Vector3f pos, Vector3f view)
{
	Entity *cam = entities.CreateEntity();
	TransformComponent *tc = new TransformComponent();
	tc->position = pos;
	tc->rotation = CalcCameraRotation(view);
	tc->scale = 1.0f;
	cam->AddComponent(tc);
	cam->AddComponent(new PerspectiveCameraComponent(45.0f, Av::application->GetAspectRatio(), 0.2f, 30.0f));
	return cam;
}

Entity* TestScene::CreatePlane()
{
	Entity *plane = entities.CreateEntity();
	TransformComponent *tc = new TransformComponent();
	tc->position = {0.0f, 0.0f, -0.74f};
	tc->rotation = RotationToQuaternion({0,0,1}, 0.0f);
	tc->scale = 1.0f;
	MeshComponent *sc = new MeshComponent();
	sc->SetMesh( Shapes::MakePlane(10.0f, 10.0f, 8, 8, 3.0f, 3.0f) );
	MeshDrawComponent *mdc = new MeshDrawComponent();
	mdc->material = Av::resourceManager.GetMaterial("Concrete");
	plane->AddComponent(tc);
	plane->AddComponent(sc);
	plane->AddComponent(mdc);
	return plane;
}

void TestScene::onUpdate(float dt)
{
	_animator.Update(entities, dt);

	Vector3f light_dir(0.0f, 0.0f, -5.0f);
	light_dir.Normalize();

	_render.Clear();
	_render.AddLight(light_dir);
	_render.Draw(entities);
}