#include "stdafx.h"
#include "Game.h"
#include "ImageLoaders.h"
#include "Shader.h"

Shader vsh, fsh;
ShaderProgram shader;

GLuint vao;

void TestLayer::SetupGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

TestLayer::TestLayer()
{
	SetupMatrices();
	SetupGL();

	font.reset(new Font());
	font->Load("Resources/Font/Presquire_32.fnt");

	CheckGLError();

	std::vector<VertexP2T2> vert;
	std::vector<Uint16> ind;

	font->DrawString(Vector2f(-0.5f, 0.0f), "Hello, World!", 0.15f, vert, ind);

	vb = std::make_unique<VertexBufferP2T2>(vert.size(), vert.data(), GL_STATIC_DRAW);
	vb->Bind();
	ib = std::make_unique<IndexBuffer16>(ind.size(), ind.data(), GL_STATIC_DRAW);
	ib->Bind();

	font->GetTexture().Bind(0);

	vsh.InitFromFile("Resources/Shaders/Simple.vsh", GL_VERTEX_SHADER);
	fsh.InitFromFile("Resources/Shaders/Simple.fsh", GL_FRAGMENT_SHADER);

	shader.Init();
	shader.AttachShader(&vsh);
	shader.AttachShader(&fsh);
	shader.Link();

	VertexBufferP2T2::ElemType::GetVertexDescription().Apply();
}

void TestLayer::onUpdate(float dt)
{
}

void TestLayer::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Bind();
	glBindVertexArray(vao);

	GLuint texLoc = glGetUniformLocation(shader.GetID(), "tex");
	glUniform1i(texLoc, 0);

	GLuint mvpLoc = glGetUniformLocation(shader.GetID(), "mvp");
	Matrix4f mvp = GetMVPMatrix();
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvp.ptr());

	glDrawElements(GL_TRIANGLES, ib->Size(), GL_UNSIGNED_SHORT, 0);
}

void TestLayer::onKeyDown(int key)
{
	if(key == SDL_SCANCODE_ESCAPE)
		application->Shutdown();
	else if(key == SDL_SCANCODE_C)
		glClearColor( randf(), randf(), randf(), 1.0f);
}

TestLayer::~TestLayer()
{
	shader.Release();
	vsh.Release();
	fsh.Release();
}

void TestLayer::SetupMatrices()
{
	_modelview.LoadIdentity();

	float aspect = application->GetAspectRatio();
	_projection.LoadIdentity();
	_projection.Ortho2D(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
}

Matrix4f TestLayer::GetMVPMatrix() const
{
	Matrix4f result = _modelview;
	result.MultMatrix(_projection);
	return result;
}