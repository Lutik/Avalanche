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

} // end of Shapes namespace