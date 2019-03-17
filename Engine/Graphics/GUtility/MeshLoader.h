#pragma once

#include <string>
#include <vector>
#include "../../Libraries/obj_loader/obj_loader.h"

class MeshLoader
{
public:
	MeshLoader(const std::string & filename);
	~MeshLoader();
	std::vector<float> vertices;
	std::vector<unsigned> indices;
	std::vector<unsigned> layout;
private:
	void InitModel(const IndexedModel& model);
};

