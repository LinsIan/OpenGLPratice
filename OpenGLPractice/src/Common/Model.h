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

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;

class Model
{
public:
	Model(string const &path);
	~Model();
	void OnRender(const glm::mat4& proj, const glm::mat4& view);

protected:
	string directory;
	vector<Mesh::Mesh> meshes;
	vector<Material> materials;
	vector<shared_ptr<Texture>> textures_loaded;
	shared_ptr<Transform> transform;

	void LoadModel(string const &path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh::Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

