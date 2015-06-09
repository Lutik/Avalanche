#include "stdafx.h"

#include "Renderer.h"
#include "Shader.h"

#include "TransformComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"

void Renderer::Init(EntityContainer *entities)
{
	GameSystem::Init(entities);
	_entities->AddListener(ComponentType::TRANSFORM, this);
	_entities->AddListener(ComponentType::MESH, this);
	_entities->AddListener(ComponentType::MESH_DRAWER, this);
	_entities->AddListener(ComponentType::CAMERA, this);
	_entities->AddListener(ComponentType::POINT_LIGHT, this);

	CollectCameraData();
	CollectLightData();
	CollectRenderData();
}

void Renderer::OnAddComponent(Entity *entity, ComponentType compType)
{
	const ComponentTypeSet meshComps = {ComponentType::TRANSFORM, ComponentType::MESH, ComponentType::MESH_DRAWER};
	const ComponentTypeSet lightComps = {ComponentType::TRANSFORM, ComponentType::POINT_LIGHT};
	const ComponentTypeSet cameraComps = {ComponentType::TRANSFORM, ComponentType::CAMERA};

	if(_entities->HasComponents(entity, meshComps ))
		AddMesh(entity);
	if(_entities->HasComponents(entity, cameraComps))
		AddCamera(entity);
	if(_entities->HasComponents(entity, lightComps))
		AddLight(entity);
}

void Renderer::OnRemoveComponent(Entity *entity, ComponentType compType)
{
	assert(entity != nullptr);

	// check meshes
	const ComponentTypeSet meshComps = {ComponentType::TRANSFORM, ComponentType::MESH, ComponentType::MESH_DRAWER};
	auto itr_m = std::find_if(_models.begin(), _models.end(), [=](const ModelRenderData &model){
		return model.entity == entity;
	});
	if( itr_m != _models.end() && !_entities->HasComponents(entity, meshComps) ) {
		_models.erase(itr_m);
	}

	// check lights
	const ComponentTypeSet lightComps = {ComponentType::TRANSFORM, ComponentType::POINT_LIGHT};
	auto itr_l = std::find_if(_lights.begin(), _lights.end(), [=](const LightData &light){
		return light.entity == entity;
	});
	if( itr_l != _lights.end() && !_entities->HasComponents(entity, lightComps)) {
		_lights.erase(itr_l);
	}

	// check camera
	const ComponentTypeSet cameraComps = {ComponentType::TRANSFORM, ComponentType::CAMERA};
	if(_currentCamera.entity == entity && !_entities->HasComponents(entity, cameraComps) ) {
		_currentCamera = CameraData();
	}
}

void Renderer::AddLight(Entity *entity)
{
	TransformComponent *ctransform = _entities->GetComponent<TransformComponent>(entity, ComponentType::TRANSFORM);
	PointLightComponent *clight = _entities->GetComponent<PointLightComponent>(entity, ComponentType::POINT_LIGHT);

	_lights.push_back( {entity, &ctransform->position, clight->color, clight->attenuation} );
}

void Renderer::AddMesh(Entity *entity)
{
	TransformComponent *ctransform = _entities->GetComponent<TransformComponent>(entity, ComponentType::TRANSFORM);
	MeshComponent *cmesh = _entities->GetComponent<MeshComponent>(entity, ComponentType::MESH);
	MeshDrawComponent *cmeshdraw = _entities->GetComponent<MeshDrawComponent>(entity,ComponentType::MESH_DRAWER);

	_models.push_back( {entity, cmesh->mesh.get(), cmeshdraw->material, ctransform} );
}

void Renderer::AddCamera(Entity *entity)
{
	TransformComponent *ctransform = _entities->GetComponent<TransformComponent>(entity, ComponentType::TRANSFORM);
	CameraComponent *ccam = _entities->GetComponent<CameraComponent>(entity, ComponentType::CAMERA);

	_currentCamera.transform = ctransform;
	_currentCamera.camera = ccam;
}

void Renderer::CollectCameraData()
{
	auto objects = _entities->GetEntitiesWithComponentTypes({ComponentType::TRANSFORM, ComponentType::CAMERA});
	if( !objects.empty() )
	{
		AddCamera(objects[0]);
	}
}

void Renderer::CollectLightData()
{
	_lights.clear();

	auto objects = _entities->GetEntitiesWithComponentTypes({ComponentType::TRANSFORM, ComponentType::POINT_LIGHT});

	for(Entity *ent : objects)
	{
		AddLight(ent);
	}
}

void Renderer::CollectRenderData()
{
	_models.clear();

	auto objects = _entities->GetEntitiesWithComponentTypes({ComponentType::TRANSFORM, ComponentType::MESH, ComponentType::MESH_DRAWER});

	for(Entity *ent : objects)
	{
		AddMesh(ent);
	}
}

void Renderer::Update(float dt)
{
	if( !_currentCamera.camera || _lights.empty() || _models.empty() )
		return;

	ShaderProgram *cnt_shader = nullptr;
	ShaderProgram *prev_shader = nullptr;

	Matrix4f view = _currentCamera.camera->GetViewMatrix(_currentCamera.transform);
	Matrix4f projection = _currentCamera.camera->GetProjectionMatrix();

	for(ModelRenderData &md : _models)
	{
		cnt_shader = md.material->GetShader();

		md.mesh->Bind();

		md.material->Bind();
		cnt_shader->SetUniform("model", md.transform->GetModelMatrix());
		if( cnt_shader != prev_shader ){
			cnt_shader->SetUniform("view", view);
			cnt_shader->SetUniform("light_position", *_lights[0].pos);
			cnt_shader->SetUniform("light_color", _lights[0].color);
			cnt_shader->SetUniform("light_attenuation", _lights[0].attenuation);
			cnt_shader->SetUniform("projection", projection);
		}
		
		md.mesh->Draw();

		prev_shader = cnt_shader;
	}
}