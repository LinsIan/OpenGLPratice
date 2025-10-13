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
    for (int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.emplace_back(processMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh::Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;

    // vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Mesh::Vertex vertex;
        glm::vec3 vector;

        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        // texture coordinates
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 texCoords;
            texCoords.x = mesh->mTextureCoords[0][i].x;
            texCoords.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = texCoords;
        }
    }

    // indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.emplace_back(face.mIndices[j]);
    }

    // materials
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *aimaterial = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffTextures = LoadMaterialTextures(aimaterial, aiTextureType_DIFFUSE, "texture_diffuse");
        std::vector<Texture> specTextures = LoadMaterialTextures(aimaterial, aiTextureType_SPECULAR, "texture_specular");
        Material material("res/shaders/LightCaster/DirLight.shader");
        unsigned int slot = 0;
        for (auto& texture : diffTextures)
            material.AddTexture(std::make_shared<Texture>(texture), slot++, "u_DiffuseTexture");
        for (auto& texture : specTextures)
            material.AddTexture(std::make_shared<Texture>(texture), slot++, "u_SpecsularTexture");
        materials.emplace_back(material);
    }

    return Mesh::Mesh();
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;

    for (int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        str = directory + str.C_Str();
        bool skip = false;

        // TODO: 我的texture會初始化，所以texture相關vector和物件要改成用shared_ptr處理
        // for (auto& texture : textures_loaded)
        // {
        //     if (std::strcmp(texture.GetFilePath().c_str(), str.C_Str()) == 0)
        //     {
        //         textures.emplace_back(texture);
        //         skip = true;
        //         break;
        //     }
        // }

        if (!skip)
        {
            std::cout << "Texture loaded: " << directory + str.C_Str() << std::endl;
            Texture texture(directory + str.C_Str(), typeName);
            textures.emplace_back(texture);
        }
    }
    
    return textures;
}
