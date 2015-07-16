#include "stdafx.h"

#include "FpsCounter.h"

#include "ResourceManager.h"

FpsCounter::FpsCounter()
{
	_font.Load("Resources/Font/Presquire_32.fnt");
	_material = Av::resourceManager.GetMaterial("Font_Presquire_32");
	UpdateMesh(_fps);
}

void FpsCounter::UpdateMesh(float fps)
{
	std::string fps_str = std::to_string((int)fps);
	_mesh = _font.MakeStringMesh({-0.98f, 0.91f}, fps_str, 0.06f);
}

void FpsCounter::Update(float dt)
{
	_time += dt;
	++_frames;
	if(_frames >= _interval)
	{
		_fps = _frames / _time;
		_frames = 0;
		_time = 0.0f;
		UpdateMesh(_fps);
	}
}

void FpsCounter::Draw()
{
	glDisable(GL_DEPTH_TEST);
	_mesh.Bind();
	_material->Bind();
	_mesh.Draw();
	glEnable(GL_DEPTH_TEST);
}