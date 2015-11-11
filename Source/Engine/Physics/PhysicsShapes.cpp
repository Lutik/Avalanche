#include "stdafx.h"

#include "PhysicsShapes.h"

inline btVector3 VectorToBullet(const Vector3f &vec) {
	return btVector3(vec.x, vec.y, vec.z);
}

CollisionShapePtr CubeShape(float size)
{
	size *= 0.5f;
	return std::make_unique<btBoxShape>(btVector3(size, size, size));
}

CollisionShapePtr BoxShape(float size_x, float size_y, float size_z)
{
	btVector3 boxSize(size_x * 0.5f, size_y * 0.5f, size_z * 0.5f);
	return std::make_unique<btBoxShape>(boxSize);
}

CollisionShapePtr PlaneShape(Vector3f n, float constant)
{
	return std::make_unique<btStaticPlaneShape>(VectorToBullet(n), constant);
}

CollisionShapePtr SphereShape(float radius)
{
	return std::make_unique<btSphereShape>(radius);
}

CollisionShapePtr CylinderShapeX(float size_x, float size_y, float size_z)
{
	return std::make_unique<btCylinderShapeX>(btVector3(size_x * 0.5f, size_y * 0.5f, size_z * 0.5f));
}

CollisionShapePtr CylinderShapeY(float size_x, float size_y, float size_z)
{
	return std::make_unique<btCylinderShape>(btVector3(size_x * 0.5f, size_y * 0.5f, size_z * 0.5f));
}

CollisionShapePtr CylinderShapeZ(float size_x, float size_y, float size_z)
{
	return std::make_unique<btCylinderShapeZ>(btVector3(size_x * 0.5f, size_y * 0.5f, size_z * 0.5f));
}

CollisionShapePtr CapsuleShape(float radius, float height)
{
	return std::make_unique<btCapsuleShape>(radius, height);
}

CollisionShapePtr MultiSphereShape(const std::vector<SphereDescription> &spheres)
{
	std::vector<btVector3> positions;
	std::vector<float> radiuses;
	positions.reserve(spheres.size());
	radiuses.reserve(spheres.size());
	for(const SphereDescription &sphere : spheres) {
		positions.push_back(VectorToBullet(sphere.position));
		radiuses.push_back(sphere.radius);
	}
	return std::make_unique<btMultiSphereShape>(positions.data(), radiuses.data(), spheres.size());
}

CollisionShapePtr ConvexHullShape(const std::vector<Vector3f> &points)
{
	return std::make_unique<btConvexHullShape>((const float*)points.data(), points.size());
}

SimpleCollisionModel::SimpleCollisionModel(CollisionShapePtr shape)
	: _shape(std::move(shape))
{
}

btCollisionShape* SimpleCollisionModel::getShape()
{
	return _shape.get();
}

CompoundCollisionModel::CompoundCollisionModel()
{
	_compound = std::make_unique<btCompoundShape>();
}

void CompoundCollisionModel::AddShape(CollisionShapePtr shape, const btTransform &localTransform)
{
	_compound->addChildShape(localTransform, shape.get());
	_shapes.push_back(std::move(shape));
}

btCollisionShape* CompoundCollisionModel::getShape()
{
	return _compound.get();
}

CollisionModelPtr ModelFromShape(CollisionShapePtr shape)
{
	return std::make_unique<SimpleCollisionModel>(std::move(shape));
}