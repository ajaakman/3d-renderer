#include "MeshLoader.h"


MeshLoader::MeshLoader(const std::string & filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	for (int i = 0; i < model.positions.size(); ++i)
	{
		vertices.push_back(model.positions[i].x);
		vertices.push_back(model.positions[i].y);
		vertices.push_back(model.positions[i].z);
		vertices.push_back(model.texCoords[i].x);
		vertices.push_back(model.texCoords[i].y);
		vertices.push_back(model.normals[i].x);
		vertices.push_back(model.normals[i].y);
		vertices.push_back(model.normals[i].z);
	}
	layout = {3, 2, 3};
	indices = model.indices;
}

MeshLoader::~MeshLoader()
{
}

void MeshLoader::InitModel(const IndexedModel & model)
{
}
