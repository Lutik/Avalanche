#include "stdafx.h"

#include "Renderer.h"
#include "Shader.h"

#include "TransformComponent.h"
#include "ModelComponent.h"

void Renderer::SetViewMatrix(const Matrix4f &mat)
{
	_view = mat;
}

void Renderer::SetProjectionMatrix(const Matrix4f &mat)
{
	_projection = mat;
}

void Renderer::AddLight(Vector3f light_dir)
{
	_light_direction = light_dir;
}

void Renderer::Clear()
{
	_models.clear();
}

void Renderer::CollectRenderData(EntityContainer &entities)
{
	_models.clear();

	static const std::vector<ComponentType> compTypes = {ComponentType::TRANSFORM, ComponentType::MESH, ComponentType::MESH_DRAWER};

	auto objects = entities.GetEntitiesWithComponentTypes(compTypes);

	for(Entity *ent : objects)
	{
		TransformComponent *ctransform = ent->GetComponent<TransformComponent>(ComponentType::TRANSFORM);
		MeshComponent *cmesh = ent->GetComponent<MeshComponent>(ComponentType::MESH);
		MeshDrawComponent *cmeshdraw = ent->GetComponent<MeshDrawComponent>(ComponentType::MESH_DRAWER);

		_models.push_back( {cmesh->vao.get(), cmesh->mesh, cmeshdraw->material, ctransform->GetModelMatrix()} );
	}
}

void Renderer::Draw(EntityContainer &entities)
{
	CollectRenderData(entities);

	ShaderProgram *cnt_shader = nullptr;
	ShaderProgram *prev_shader = nullptr;

	for(ModelRenderData &md : _models)
	{
		cnt_shader = md.material->GetShader();

		md.vao->Bind();
		md.material->Bind();

		cnt_shader->SetUniform("modelview", _view * md.matrix);
		if( cnt_shader != prev_shader ){
			cnt_shader->SetUniform("light_dir", _light_direction);
			cnt_shader->SetUniform("projection", _projection);
		}

		GLenum primType = md.mesh->GetPrimitiveTypeGL();
		GLenum indexType = md.mesh->GetIndexTypeGL();
		size_t indexCount = md.mesh->GetIndexCount();
		glDrawElements(primType, indexCount, indexType, 0);

		prev_shader = cnt_shader;
	}
}