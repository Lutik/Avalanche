#include "stdafx.h"
#include "ModelLoaders.h"
#include "Log.h"
#include "VertexTypes.h"

#include <numeric>

bool beginsWith(const std::string& line, const std::string &prefix)
{
	return (line.size() >= prefix.size()) && std::equal(prefix.begin(), prefix.end(), line.begin());
}

void stripPrefix(std::string &line, const std::string &prefix)
{
	line.erase(0, prefix.size());
}

struct FaceVertex
{
	unsigned int p, t, n;
};

Vector3f readVectorValue(std::string &line, const std::string &prefix)
{
	Vector3f result;
	size_t idx = 0;

	line.erase(0, prefix.size());
	result.x = std::stof(line, &idx);
	line.erase(0, idx);
	result.y = std::stof(line, &idx);
	line.erase(0, idx);
	result.z = std::stof(line, &idx);

	return result;
}

FaceVertex readFaceValue(std::string &line, const std::string &prefix)
{
	FaceVertex result;
	size_t idx = 0;

	line.erase(0, prefix.size());
	result.p = std::stoul(line, &idx);
	line.erase(0, idx+1);
	result.t = std::stoul(line, &idx);
	line.erase(0, idx+1);
	result.n = std::stoul(line, &idx);
	line.erase(0, idx+1);

	return result;
}

Mesh::Ptr LoadMeshOBJ(const std::string &fileName)
{
	std::ifstream fileStream(fileName, std::ios::in);

	if (!fileStream.is_open()) {
		Av::Log::log("Can't read file %s\n", fileName.c_str());
		return Mesh::Ptr();
	}

	const std::string vertPref("v ");
	const std::string normalPref("vn ");
	const std::string texCoordPref("vt ");
	const std::string facePref("f ");
	const std::string groupPref("g ");
	const std::string materialPref("usemtl ");
	const std::string smoothPref("s ");

	std::vector<Vector3f> positions;
	std::vector<Vector3f> texcoords;
	std::vector<Vector3f> normals;

	std::string currentGroup = "";

	std::vector< std::vector<FaceVertex> > faceGroups;

	while (!fileStream.eof())
	{
		std::string line = "";
		std::getline(fileStream, line);

		if( beginsWith(line, vertPref) )
		{
			positions.push_back( readVectorValue(line, vertPref) );
		}
		else if( beginsWith(line, texCoordPref) )
		{
			texcoords.push_back( readVectorValue(line, texCoordPref) );
		}
		else if( beginsWith(line, normalPref) )
		{
			normals.push_back( readVectorValue(line, normalPref) );
		}
		else if( beginsWith(line, groupPref) )
		{
			if(line.size() > groupPref.size())
				faceGroups.emplace_back();
		}
		else if( beginsWith(line, facePref) && !faceGroups.empty())
		{
			faceGroups.back().push_back( readFaceValue(line, facePref) );
			faceGroups.back().push_back( readFaceValue(line, "") );
			faceGroups.back().push_back( readFaceValue(line, "") );
		}
	}
	fileStream.close();

	if( faceGroups.empty() || faceGroups.front().empty() )
		return Mesh::Ptr();

	std::vector<VertexP3T2N3> vertices;
	for(auto &faces : faceGroups)
	{
		for(FaceVertex fv : faces)
		{
			VertexP3T2N3 v;
			v.pos = positions[fv.p-1];
			v.normal = normals[fv.n-1];
			v.uv = Vector2f(texcoords[fv.t-1].x, texcoords[fv.t-1].y);
			vertices.push_back(v);
		}
	}

	std::vector<uint16_t> indices;
	indices.resize(vertices.size());
	std::iota(indices.begin(), indices.end(), 0);

	Mesh::Ptr mesh = std::make_shared<Mesh>();
	mesh->SetVertices(VertexP3T2N3::GetVertexDescription(), vertices.size(), vertices.data());
	mesh->SetIndices(IndexType::SHORT, PrimitiveType::TRIANGLES, indices.size(), indices.data());

	return mesh;
}