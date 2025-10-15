#include "Model.h"

Model::Model(string const &path)
{
    transform = std::make_unique<Transform>();
    LoadModel(path);
}

Model::~Model()
{
}

void Model::OnRender(const glm::mat4& proj, const glm::mat4& view)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        int materialIndex = meshToMaterialIndex[i];
        materialMap[materialIndex]->BindShader();
        materialMap[materialIndex]->GetShader().SetUniformMat4f("u_MVP", proj * view * transform->GetMatrix());
        materialMap[materialIndex]->GetShader().SetUniformMat4f("u_Model", transform->GetMatrix());
        Renderer::Draw(meshes[i].GetVertexArray(), materialMap[materialIndex]->GetShader(), meshes[i].GetIndexBuffer().GetCount());
	}
}

void Model::LoadModel(string const &path)
{
	Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes);

	// check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ASSIMP Load Model Error " << importer.GetErrorString() << std::endl;
		return;
    }

	directory = path.substr(0, string(path).find_last_of('/'));
    std::cout << "Model directory: " << directory << std::endl;

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
    vector<Mesh::Vertex> vertices;
    vector<unsigned int> indices;

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

        vertices.emplace_back(vertex);
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
        int materialIndex = mesh->mMaterialIndex;
        if (materialMap.find(materialIndex) == materialMap.end())
        {
            std::cout << "create new material, index: " << materialIndex << std::endl;
            aiMaterial *aimaterial = scene->mMaterials[materialIndex];
            vector<shared_ptr<Texture>> diffTextures = LoadMaterialTextures(aimaterial, aiTextureType_DIFFUSE, "texture_diffuse");
            vector<shared_ptr<Texture>> specTextures = LoadMaterialTextures(aimaterial, aiTextureType_SPECULAR, "texture_specular");
            auto material = make_shared<Material>("res/shaders/MultiLights.shader");
            unsigned int slot = 0;
            for (auto& texture : diffTextures)
                material->AddTexture(texture, slot++, "material.diffuse");
            for (auto& texture : specTextures)
                material->AddTexture(texture, slot++, "material.specular");

            material->BindTextures();
            material->SetMaterialShininess(64.0f);
            materialMap[materialIndex] = material;
        }

        meshToMaterialIndex.emplace_back(materialIndex);
    }

    return Mesh::Mesh(vertices, indices);
}

vector<shared_ptr<Texture>> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
    vector<shared_ptr<Texture>> textures;

    for (int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        str = directory + '/' + str.C_Str();
        bool skip = false;

        for (auto texture : textures_loaded)
        {
            if (strcmp(texture->GetFilePath().c_str(), str.C_Str()) == 0)
            {
                textures.emplace_back(texture);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            std::cout << "Texture loaded: " << str.C_Str() << std::endl;
            auto texture = make_shared<Texture>(str.C_Str(), true, typeName);
            textures.emplace_back(texture);
            textures_loaded.emplace_back(texture);
        }
    }
    
    return textures;
}
