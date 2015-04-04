#pragma once

#include "Mesh.h"

std::unique_ptr<Mesh> LoadMeshOBJ(const std::string &fileName);