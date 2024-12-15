#include "Model.h"

Model::Model() {

}

void Model::RenderModel() {
    for (size_t i = 0; i < meshList.size(); i++) {
        unsigned int materialIndex = meshToTex[i];

        if (materialIndex < textureList.size() && textureList[materialIndex]) {
            textureList[materialIndex]->UseTexture();
        }

        meshList[i]->RenderMesh();
    }
}

void Model::LoadModel(const std::string &fileName) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if (!scene) {
        printf("ERROR: Failed to load model from %s: %s\n", fileName.c_str(), importer.GetErrorString());
        return;
    }

    LoadNode(scene->mRootNode, scene);

    LoadMaterials(scene);
}

void Model::LoadNode(aiNode *node, const aiScene *scene) {
    for (size_t i = 0; i < node->mNumMeshes; i++) {
        LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }

    for (size_t i = 0; i < node->mNumChildren; i++) {
        LoadNode(node->mChildren[i], scene);
    }
}

void Model::LoadMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y + mesh->mVertices[i].z });
        if (mesh->mTextureCoords[0]) {
            vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
        }
        else {
            vertices.insert(vertices.end(), { 0.0f, 0.0f });
        }
    }

    for (size_t i = 0; i < mesh->mNumFaces; i++) {
        const aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    const auto newMesh = new Mesh();
    newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
    meshList.push_back(newMesh);
    meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene *scene) {
    textureList.resize(scene->mNumMaterials);

    for (size_t i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial *material = scene->mMaterials[i];
        textureList[i] = nullptr;

        printf("[DEBUG] Material %zu has %u diffuse textures.\n", i, material->GetTextureCount(aiTextureType_DIFFUSE));

        if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
            printf("[DEBUG] inside aiTextureType_DIFFUSE.\n");
            aiString path;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
                printf("[DEBUG] for path: %s\n", path.data);
                const int idx = std::string(path.data).rfind('/');
                printf("[DEBUG] for idx: %s\n", std::string(path.data).substr(0, idx).c_str());
                std::string filename = std::string(path.data).substr(idx + 1);
                printf("[DEBUG] for filename: %s\n", filename.c_str());
                std::string texPath = std::string("/Users/prkaaviya/CLionProjects/try8/Textures/") + filename;
                printf("Loading texture: %s\n", texPath.c_str());

                textureList[i] = new Texture(texPath.c_str());

                if (!textureList[i]->LoadTexture()) {
                    printf("ERROR: Failed to load texture from %s: %s\n", filename.c_str(), texPath.c_str());
                    delete textureList[i];
                    textureList[i] = nullptr;
                }
            }
        }

        if (!textureList[i]) {
            textureList[i] = new Texture("/Users/prkaaviya/CLionProjects/try8/Textures/plain.png");
            textureList[i]->LoadTextureA();
        }
    }
}

void Model::ClearModel() {
    for (auto & mesh : meshList) {
        if (mesh) {
            delete mesh;
            mesh = nullptr;
        }
    }
    for (auto & texture : textureList) {
        if (texture) {
            delete texture;
            texture = nullptr;
        }
    }
}

Model::~Model() {

}

