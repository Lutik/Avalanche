#include "stdafx.h"

#include "Avalanche.h"
#include "Game.h"
#include "ResourceManager.h"

#include "MeshComponent.h"
#include "MyComponents.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "Shapes.h"

TestScene::TestScene()
{
	_render.Init(&entities);
	_animator.Init(&entities);
	_physics.Init(&entities);



	_cubeMesh = Shapes::MakeBox(1.5f, 1.5f, 1.5f, 2, 2, 2);

	Entity *cube1 = CreateCube({-3.5, 0.0f, 0.0f}, 0.03f);
	Entity *cube2 = CreateCube({3.5f, 0.0f, 0.0f}, 0.03f);
	Entity *cube3 = CreateCube({0.0f, 3.5f, 0.0f}, 0.03f);
	Entity *cube4 = CreateCube({0.0f, -3.5f, 0.0f}, 0.03f);
	Entity *cam = CreateCamera({-6.0f, -6.0f, 3.0f}, {1.0f, 1.0f, -0.5f});
	Entity *plane = CreatePlane();
	Entity *light = CreateLight({0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f});
	
	entities.AddComponent(cube1, new MyAnimComponent());
	entities.AddComponent(cube2, new MyAnimComponent());
	entities.AddComponent(cam, new CamControlComponent());
	entities.AddComponent(light, new MyInputComponent(1.5f));
}

Entity* TestScene::CreateCube(Vector3f pos, float scale)
{
	Entity *cube = entities.CreateEntity();
	TransformComponent *tc = new TransformComponent();
	tc->position = pos;
	tc->rotation = {1,0,0,0};
	tc->scale = 1.0f;
	MeshComponent *mesh_comp = new MeshComponent();
	mesh_comp->SetMesh(_cubeMesh);
	MeshDrawComponent *md_comp = new MeshDrawComponent();
	md_comp->material = Av::resourceManager.GetMaterial("Metal");
	entities.AddComponent(cube, tc);
	entities.AddComponent(cube, mesh_comp);
	entities.AddComponent(cube, md_comp);
	return cube;
}

// рассчитываем кватернион для камеры при котором вектор взгляда будет равен заданному,
// и при этом направление вверх никуда не уедет
Quaternion CalcCameraRotation(Vector3f view)
{
	const Vector3f ref_view = {1,0,0};

	Vector3f view_hor = {view.x, view.y, 0.0f};
	Quaternion q1 = RotationFromVectors(ref_view, view_hor);

	Vector3f view_ver = RotateVector(view, Conjugate(q1));
	Quaternion q2 = RotationFromVectors(ref_view, view_ver);

	return UnitQuatProduct(q1, q2);
}

Entity* TestScene::CreateCamera(Vector3f pos, Vector3f view)
{
	Entity *cam = entities.CreateEntity();
	TransformComponent *tc = new TransformComponent();
	tc->position = pos;
	tc->rotation = CalcCameraRotation(view);
	tc->scale = 1.0f;
	entities.AddComponent(cam, tc);
	entities.AddComponent(cam, new PerspectiveCameraComponent(45.0f, Av::application->GetAspectRatio(), 0.2f, 30.0f));
	return cam;
}

Entity* TestScene::CreatePlane()
{
	Entity *plane = entities.CreateEntity();
	TransformComponent *tc = new TransformComponent();
	tc->position = {0.0f, 0.0f, -1.0f};
	tc->rotation = RotationToQuaternion({0,0,1}, 0.0f);
	tc->scale = 1.0f;
	MeshComponent *sc = new MeshComponent();
	sc->SetMesh( Shapes::MakePlane(10.0f, 10.0f, 8, 8, 3.0f, 3.0f) );
	MeshDrawComponent *mdc = new MeshDrawComponent();
	mdc->material = Av::resourceManager.GetMaterial("Concrete");
	entities.AddComponent(plane, tc);
	entities.AddComponent(plane, sc);
	entities.AddComponent(plane, mdc);
	return plane;
}

Entity* TestScene::CreateLight(Vector3f pos, Vector3f color)
{
	Entity *light = entities.CreateEntity();
	TransformComponent *tc = new TransformComponent();
	tc->position = pos;
	tc->rotation = RotationToQuaternion({0,0,1}, 0.0f);
	tc->scale = 0.01f;
	PointLightComponent *lc = new PointLightComponent(Vector3f{0.8f, 1.0f, 1.0f}, Vector3f{1.0f, 0.0f, 0.1f});
	entities.AddComponent(light, tc);
	entities.AddComponent(light, lc);

	MeshComponent *mesh_comp = new MeshComponent();
	mesh_comp->SetMesh(Av::resourceManager.GetMesh("Cube"));
	MeshDrawComponent *md_comp = new MeshDrawComponent();
	md_comp->material = Av::resourceManager.GetMaterial("Metal");
	entities.AddComponent(light, mesh_comp);
	entities.AddComponent(light, md_comp);

	return light;
}

void TestScene::onUpdate(float dt)
{
	_animator.Update( dt);
	_physics.Update(dt);
	_render.Update(dt);
}