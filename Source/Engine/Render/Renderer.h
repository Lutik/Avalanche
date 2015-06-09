#pragma once

#include "Matrix.h"
#include "Mesh.h"
#include "Material.h"
#include "VertexArrayObject.h"
#include "EntityContainer.h"
#include "System.h"

struct TransformComponent;
struct CameraComponent;

class Renderer : public GameSystem
{
	struct CameraData {
		Entity *entity = nullptr;
		TransformComponent *transform = nullptr;
		CameraComponent *camera = nullptr;
	};
	CameraData _currentCamera;

	struct ModelRenderData
	{
		Entity *entity;
		Mesh *mesh;
		Material *material;
		TransformComponent *transform;
	};
	std::vector<ModelRenderData> _models;

	struct LightData
	{
		Entity *entity;
		Vector3f *pos;
		Vector3f color;
		Vector3f attenuation;
	};
	std::vector<LightData> _lights;

	void AddLight(Entity *entity);
	void AddMesh(Entity *entity);
	void AddCamera(Entity *entity);

	void CollectLightData();
	void CollectCameraData();
	void CollectRenderData();
public:
	void Init(EntityContainer *entities) override;
	void Update(float dt) override;

	void OnAddComponent(Entity *entity, ComponentType compType) override;
	void OnRemoveComponent(Entity *entity, ComponentType compType) override;
};