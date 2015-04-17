#include "stdafx.h"

#include "Renderer.h"
#include "Shader.h"

#include "TransformComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"

void Renderer::SetViewMatrix(const Matrix4f &mat)
{
	_view = mat;
}

void Renderer::SetProjectionMatrix(const Matrix4f &mat)
{
	_projection = mat;
}

void Renderer::Clear()
{
	_models.clear();
	_lights.clear();
}

bool Renderer::CollectCameraData(EntityContainer &entities)
{
	auto objects = entities.GetEntitiesWithComponentTypes({ComponentType::TRANSFORM, ComponentType::CAMERA});
	if( !objects.empty() )
	{
		TransformComponent *ctransform = objects[0]->GetComponent<TransformComponent>(ComponentType::TRANSFORM);
		CameraComponent *ccam = objects[0]->GetComponent<CameraComponent>(ComponentType::CAMERA);

		_view = ccam->GetViewMatrix(ctransform);
		_projection = ccam->GetProjectionMatrix();

		return true;
	}
	else
	{
		return false;
	}
}

void Renderer::CollectLightData(EntityContainer &entities)
{
	_lights.clear();

	auto objects = entities.GetEntitiesWithComponentTypes({ComponentType::TRANSFORM, ComponentType::POINT_LIGHT});

	for(Entity *ent : objects)
	{
		TransformComponent *ctransform = ent->GetComponent<TransformComponent>(ComponentType::TRANSFORM);
		PointLightComponent *clight = ent->GetComponent<PointLightComponent>(ComponentType::POINT_LIGHT);

		_lights.push_back({ctransform->position, clight->color, clight->attenuation});
	}
}

void Renderer::CollectRenderData(EntityContainer &entities)
{
	_models.clear();

	auto objects = entities.GetEntitiesWithComponentTypes({ComponentType::TRANSFORM, ComponentType::MESH, ComponentType::MESH_DRAWER});

	for(Entity *ent : objects)
	{
		TransformComponent *ctransform = ent->GetComponent<TransformComponent>(ComponentType::TRANSFORM);
		MeshComponent *cmesh = ent->GetComponent<MeshComponent>(ComponentType::MESH);
		MeshDrawComponent *cmeshdraw = ent->GetComponent<MeshDrawComponent>(ComponentType::MESH_DRAWER);

		_models.push_back( {cmesh->mesh.get(), cmeshdraw->material, ctransform->GetModelMatrix()} );
	}
}

void Renderer::Draw(EntityContainer &entities)
{
	if( !CollectCameraData(entities) )
		return;

	CollectLightData(entities);
	CollectRenderData(entities);

	ShaderProgram *cnt_shader = nullptr;
	ShaderProgram *prev_shader = nullptr;

	for(ModelRenderData &md : _models)
	{
		cnt_shader = md.material->GetShader();

		md.mesh->Bind();

		md.material->Bind();
		cnt_shader->SetUniform("model", md.matrix);
		cnt_shader->SetUniform("view", _view);
		if( cnt_shader != prev_shader ){
			cnt_shader->SetUniform("light_position", _lights[0].pos);
			cnt_shader->SetUniform("light_color", _lights[0].color);
			cnt_shader->SetUniform("light_attenuation", _lights[0].attenuation);
			cnt_shader->SetUniform("projection", _projection);
		}
		
		md.mesh->Draw();

		prev_shader = cnt_shader;
	}
}