#pragma once
#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Renderer.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <memory>
#include <string>
#include <vector>

class Model
{
public:
	Model(char *path);
	~Model();
	void OnRender(const glm::mat4& proj, const glm::mat4& view, const glm::vec3& camPos);

protected:
	std::string directory;
	std::vector<Mesh::Mesh> meshes;
	std::vector<Material> materials;
	std::unique_ptr<Transform> transform;

	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh::Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

