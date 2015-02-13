#pragma once

#include "Avalanche.h"
#include "VertexBuffer.h"
#include "VertexTypes.h"

class AvalancheGame : public Av::Application
{
	Matrix4f _modelview;
	Matrix4f _projection;

	typedef VertexBuffer<VertexP2T2> VertexBufferP2T2;
	typedef IndexBuffer<Uint16> IndexBuffer16;

	std::unique_ptr<VertexBufferP2T2> vb;
	std::unique_ptr<IndexBuffer16>ib;

	void SetupMatrices();
	void SetupGL();

	Matrix4f GetMVPMatrix() const;
public:
	AvalancheGame();

	void onStart();

	void onRender();

	void onUpdate(float dt);

	void onKeyDown(int key);

	void onMouseDown(int key);

	void onMouseUp(int key);

	void onExit();

	//unused handlers
	void onKeyUp(int key) {}
};