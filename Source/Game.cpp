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
	Entity *cube1 = CreateCube({-3.5, 0.0f, 0.0f}, 0.03f);
	Entity *cube2 = CreateCube({3.5f, 0.0f, 0.0f}, 0.03f);
	Entity *cube3 = CreateCube({0.0f, 3.5f, 0.0f}, 0.03f);
	Entity *cube4 = CreateCube({0.0f, -3.5f, 0.0f}, 0.03f);
	Entity *cam = CreateCamera({-6.0f, -6.0f, 3.0f}, {1.0f, 1.0f, -0.5f});
	Entity *plane = CreatePlane();
	Entity *light = CreateLight({0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f});
	
	cube1->AddComponent(new MyAnimComponent());
	cube2->AddComponent(new MyAnimComponent());
	cam->AddComponent(new CamControlComponent());

	_physics.Init();
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

Entity* TestScene::CreateLight(Vector3f pos, Vector3f color)
{
	Entity *light = entities.CreateEntity();
	TransformComponent *tc = new TransformComponent();
	tc->position = pos;
	tc->rotation = RotationToQuaternion({0,0,1}, 0.0f);
	tc->scale = 0.01f;
	PointLightComponent *lc = new PointLightComponent(Vector3f{0.8f, 1.0f, 1.0f}, Vector3f{1.0f, 0.0f, 0.1f});
	light->AddComponent(tc);
	light->AddComponent(lc);

	MeshComponent *mesh_comp = new MeshComponent();
	mesh_comp->SetMesh(Av::resourceManager.GetMesh("Cube"));
	MeshDrawComponent *md_comp = new MeshDrawComponent();
	md_comp->material = Av::resourceManager.GetMaterial("Metal");
	light->AddComponent(mesh_comp);
	light->AddComponent(md_comp);

	return light;
}

void TestScene::onUpdate(float dt)
{
	_animator.Update(entities, dt);

	_physics.Update(entities, dt);
	_render.Clear();
	_render.Draw(entities);
}