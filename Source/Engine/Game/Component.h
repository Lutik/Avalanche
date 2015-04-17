#pragma once

enum class ComponentType
{
	NONE,
	TRANSFORM,   // положение в пространстве
	MESH,        // 3д-модель
	MESH_DRAWER, // параметры и материалы для отрисовки мешей
	ANIMATOR,    // тип компонентов, которые меняют положение/ориентацию обектов
	CAMERA,
	POINT_LIGHT
};

struct Component
{
	virtual ~Component() {};
	virtual ComponentType getType() const = 0;
};