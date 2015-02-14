#pragma once

#include "GameApp.h"
#include "VertexBuffer.h"
#include "VertexTypes.h"
#include "Font.h"

class TestLayer : public IGameLayer
{
	Matrix4f _modelview;
	Matrix4f _projection;

	typedef VertexBuffer<VertexP2T2> VertexBufferP2T2;
	typedef IndexBuffer<Uint16> IndexBuffer16;

	std::unique_ptr<VertexBufferP2T2> vb;
	std::unique_ptr<IndexBuffer16> ib;

	std::unique_ptr<Font> font;

	void SetupMatrices();
	void SetupGL();

	Matrix4f GetMVPMatrix() const;

public:
	TestLayer();
	~TestLayer();

	virtual void onRender() override;
	virtual void onUpdate(float dt) override;
	virtual void onKeyDown(int key) override;
	//virtual void onMouseDown(int key) override;
	//virtual void onMouseUp(int key) override;
};