#pragma once

#include <btBulletDynamicsCommon.h>

#include "Vector3.h"

typedef std::unique_ptr<btCollisionShape> CollisionShapePtr;

class CollisionModel
{
public:
	virtual btCollisionShape *getShape() = 0;
};

class SimpleCollisionModel : public CollisionModel
{
	CollisionShapePtr _shape;
public:
	SimpleCollisionModel(CollisionShapePtr shape);
	btCollisionShape *getShape() override;
};

class CompoundCollisionModel : public CollisionModel
{
	std::vector<CollisionShapePtr> _shapes;
	std::unique_ptr<btCompoundShape> _compound;
public:
	CompoundCollisionModel();
	void AddShape(CollisionShapePtr shape, const btTransform &localTransform);
	btCollisionShape *getShape() override;
};

typedef std::unique_ptr<CollisionModel> CollisionModelPtr;


CollisionShapePtr CubeShape(float size);
CollisionShapePtr BoxShape(float size_x, float size_y, float size_z);
CollisionShapePtr PlaneShape(Vector3f normal, float constant);
CollisionShapePtr SphereShape(float radius);
CollisionShapePtr CylinderShapeX(float size_x, float size_y, float size_z);
CollisionShapePtr CylinderShapeY(float size_x, float size_y, float size_z);
CollisionShapePtr CylinderShapeZ(float size_x, float size_y, float size_z);
CollisionShapePtr CapsuleShape(float radius, float height);

struct SphereDescription {
	Vector3f position;
	float radius;
};
CollisionShapePtr MultiSphereShape(const std::vector<SphereDescription> &spheres);

CollisionShapePtr ConvexHullShape(const std::vector<Vector3f> &points);

CollisionModelPtr ModelFromShape(CollisionShapePtr shape);