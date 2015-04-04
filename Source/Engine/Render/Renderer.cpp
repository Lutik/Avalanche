#include "stdafx.h"

#include "Renderer.h"
#include "Shader.h"

void Renderer::SetViewMatrix(const Matrix4f &mat)
{
	_view = mat;
}

void Renderer::SetProjectionMatrix(const Matrix4f &mat)
{
	_projection = mat;
}

void Renderer::AddModel(Model *model, const Matrix4f &mat)
{
	_models.push_back( {model, mat} );
}

void Renderer::AddLight(Vector3f light_dir)
{
	_light_direction = light_dir;
}

void Renderer::Clear()
{
	_models.clear();
}

void Renderer::Draw()
{
	ShaderProgram *cnt_shader = nullptr;
	ShaderProgram *prev_shader = nullptr;

	for(ModelRenderData &md : _models)
	{
		cnt_shader = md.model->GetMaterial()->GetShader();

		md.model->Bind();

		if( cnt_shader != prev_shader ){
			cnt_shader->SetUniform("light_dir", _light_direction);
			cnt_shader->SetUniform("modelview", _view * md.matrix);
			cnt_shader->SetUniform("projection", _projection);
		}

		md.model->Draw();

		prev_shader = cnt_shader;
	}
}