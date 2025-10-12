#include "Model.h"

Model::Model(char* path)
{
}

Model::~Model()
{
}

void Model::OnRender(const glm::mat4& proj, const glm::mat4& view, const glm::vec3& camPos)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        materials[i].BindShader();
        materials[i].GetShader().SetUniformMat4f("u_MVP", proj * view * transform->GetMatrix());
        materials[i].GetShader().SetUniformMat4f("u_Model", transform->GetMatrix());
        Renderer::Draw(meshes[i].GetVertexArray(), materials[i].GetShader(), meshes[i].GetIndexBuffer().GetCount());
	}
}

void Model::LoadModel(std::string path)
{
	Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	// check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ASSIMP Load Model Error " << importer.GetErrorString() << std::endl;
		return;
    }

	directory = path.substr(0, std::string(path).find_last_of('/'));

	// process ASSIMP's root node recursively
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
}

Mesh::Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    return Mesh::Mesh();
}

void Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
}
