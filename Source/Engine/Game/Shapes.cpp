#include "stdafx.h"

#include "Shapes.h"
#include "VertexTypes.h"

namespace Shapes
{

Mesh::Ptr MakePlane(float size_x, float size_y, int segments_x, int segments_y, float uv_scale_x, float uv_scale_y)
{
	int vertexCount = (segments_x + 1) * (segments_y + 1);

	float offset_x = -0.5f * size_x;
	float offset_y = -0.5f * size_y;
	float dx = size_x / segments_x;
	float dy = size_y / segments_y;

	float du = uv_scale_x / segments_x;
	float dv = uv_scale_y / segments_y;

	std::vector<VertexP3T2N3> vertices;
	for(int y = 0; y <= segments_y; ++y)
	{
		for(int x = 0; x <= segments_x; ++x)
		{
			VertexP3T2N3 vertex;
			vertex.pos = {offset_x + dx*x, offset_y + dy*y, 0.0f};
			vertex.uv = {x * du, y * dv};
			vertex.normal = {0.0f, 0.0f, 1.0f};

			vertices.push_back(vertex);
		}
	}

	std::vector<uint16_t> indices;
	for(int strip = 0; strip < segments_y; ++strip)
	{
		int baseIdx = strip * (segments_x + 1);
		if(strip > 0) {
			indices.push_back(baseIdx + segments_x + 1);
		}
		for(int x = 0; x <= segments_x; ++x)
		{
			indices.push_back(baseIdx + x + (segments_x+1));
			indices.push_back(baseIdx + x);
		}
		if(strip < segments_y-1) {
			indices.push_back(baseIdx + segments_x);
		}
	}

	Mesh::Ptr mesh = std::make_shared<Mesh>();
	mesh->SetVertices(VertexP3T2N3::GetVertexDescription(), vertices.size(), vertices.data());
	mesh->SetIndices(IndexType::SHORT, PrimitiveType::TRIANGLE_STRIP, indices.size(), indices.data());

	return mesh;
}

void MakeSide(Vector3f start,
	Vector3f dx, Vector3f dy,
	int segs_x, int segs_y,
	std::vector<VertexP3T2N3> &vertices,
	std::vector<uint16_t> &indices,
	Vector3f normal,
	float du, float dv)
{
	uint16_t startIndex = vertices.size();

	for(int y = 0; y <= segs_y; ++y)
	{
		for(int x = 0; x <= segs_x; ++x)
		{
			VertexP3T2N3 vert;
			vert.pos = start + dx * x + dy * y;
			vert.uv = {x * du, y * dv};
			vert.normal = normal;

			vertices.push_back(vert);
		}
	}

	for(int y = 0; y < segs_y; ++y)
	{
		for(int x = 0; x < segs_x; ++x)
		{
			uint16_t idx1 = startIndex + y * (segs_x + 1) + x;
			uint16_t idx[4] = {idx1, idx1 + 1, idx1 + segs_x + 1, idx1 + segs_x + 2};

			indices.push_back(idx[0]);
			indices.push_back(idx[1]);
			indices.push_back(idx[2]);

			indices.push_back(idx[2]);
			indices.push_back(idx[1]);
			indices.push_back(idx[3]);
		}
	}
}

Mesh::Ptr MakeBox(float size_x, float size_y, float size_z, int segs_x, int segs_y, int segs_z)
{
	std::vector<VertexP3T2N3> vertices;
	std::vector<uint16_t> indices;

	Vector3f start;
	Vector3f dx, dy;

	// upper side
	start = {-0.5f * size_x, -0.5f * size_y, 0.5f * size_z};
	dx = {size_x/segs_x, 0.0f, 0.0f};
	dy = {0.0f, size_y/segs_y, 0.0f};
	MakeSide(start, dx, dy, segs_x, segs_y, vertices, indices, {0,0,1}, 1.0f/segs_x, 1.0f/segs_y);

	// lower side
	start = {-0.5f * size_x, 0.5f * size_y, -0.5f * size_z};
	dx = {size_x/segs_x, 0.0f, 0.0f};
	dy = {0.0f, -size_y/segs_y, 0.0f};
	MakeSide(start, dx, dy, segs_x, segs_y, vertices, indices, {0,0,-1}, 1.0f/segs_x, 1.0f/segs_y);

	// front side
	start = {-0.5f * size_x, -0.5f * size_y, -0.5f * size_z};
	dx = {size_x/segs_x, 0.0f, 0.0f};
	dy = {0.0f, 0.0f, size_z/segs_z};
	MakeSide(start, dx, dy, segs_x, segs_z, vertices, indices, {0,-1,0}, 1.0f/segs_x, 1.0f/segs_z);

	// back side
	start = {0.5f * size_x, 0.5f * size_y, -0.5f * size_z};
	dx = {-size_x/segs_x, 0.0f, 0.0f};
	dy = {0.0f, 0.0f, size_z/segs_z};
	MakeSide(start, dx, dy, segs_x, segs_z, vertices, indices, {0,1,0}, 1.0f/segs_x, 1.0f/segs_z);

	// left side
	start = {-0.5f * size_x, 0.5f * size_y, -0.5f * size_z};
	dx = {0.0f, -size_y/segs_y, 0.0f};
	dy = {0.0f, 0.0f, size_z/segs_z};
	MakeSide(start, dx, dy, segs_y, segs_z, vertices, indices, {-1,0,0}, 1.0f/segs_y, 1.0f/segs_z);

	// right side
	start = {0.5f * size_x, -0.5f * size_y, -0.5f * size_z};
	dx = {0.0f, size_y/segs_y, 0.0f};
	dy = {0.0f, 0.0f, size_z/segs_z};
	MakeSide(start, dx, dy, segs_y, segs_z, vertices, indices, {1,0,0}, 1.0f/segs_y, 1.0f/segs_z);

	Mesh::Ptr mesh = std::make_shared<Mesh>();
	mesh->SetVertices(VertexP3T2N3::GetVertexDescription(), vertices.size(), vertices.data());
	mesh->SetIndices(IndexType::SHORT, PrimitiveType::TRIANGLES, indices.size(), indices.data());

	return mesh;
}

} // end of Shapes namespace