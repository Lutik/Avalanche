#pragma once

#include "Mesh.h"

namespace Shapes
{

Mesh::Ptr MakePlane(float size_x, float size_y, int segments_x = 4, int segments_y = 4, float uv_scale_x = 1.0f, float uv_scale_y = 1.0f);

Mesh::Ptr MakeBox(float size_x, float size_y, float size_z, int segments_x, int segments_y, int segments_z);

//Mesh::Ptr MakeSphere(float radius, int segments_h, int segments_v);

}