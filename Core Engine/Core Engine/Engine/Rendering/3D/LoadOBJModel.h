#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include "Mesh.h"
#include "../../Graphics/TextureHandler.h"
#include <sstream>
#include "../../Math/BoundingBox.h"
#include "../../Graphics/FX/MaterialLoader.h"


class LoadOBJModel
{
public:
	LoadOBJModel();
	~LoadOBJModel();

	void LoadModel(const std::string& fileName_);
	void LoadModel(const std::string& fileName_, const std::string& matName_);
	std::vector<Vertex> GetVerts();
	std::vector<GLuint> GetIndices();
	std::vector<SubMesh> GetMeshes();
	BoundingBox GetBoundingBox();

private:
	void PostProcessing();
	void LoadMaterial(const std::string& fileName_);
	void loadMaterialLibrary(const std::string matName_);
	Material currentmaterial;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;

	std::vector<GLuint> indices;
	std::vector<GLuint> normalIndices;
	std::vector<GLuint> textureIndices;

	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> meshes;
	BoundingBox boundingBox;

	bool firstPass;
};

#endif 

