#include "Model.h"

Model::Model(): attributeSizes({}) {

}

void Model::LoadModelWithoutAssimp(const std::string &fileName) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Use OBJLoader to parse the OBJ file
    if (OBJLoader::LoadOBJ(fileName, vertices, indices)) {
        std::string mtlFilePath = fileName.substr(0, fileName.find_last_of(".")) + ".mtl";
        printf("[DEBUG] Load material : %s\n", mtlFilePath.c_str());
        auto materials = OBJLoader::LoadMTL(mtlFilePath);

        // For each mesh, load texture based on its material
        for (auto &mat : materials) {
            if (!mat.second.map_Kd.empty()) {
                std::string texturePath = mat.second.map_Kd; // Adjust path
                printf("[DEBUG] Load texture Kd: %s\n", texturePath.c_str());
                auto *newTexture = new Texture(texturePath.c_str());
                newTexture->LoadTextureA();
                textureList.push_back(newTexture);
            }
            if (!mat.second.map_Ka.empty()) {
                std::string texturePath = mat.second.map_Ka; // Adjust path
                printf("[DEBUG] Load texture Ka: %s\n", texturePath.c_str());
                auto *newTexture = new Texture(texturePath.c_str());
                newTexture->LoadTextureA();
                textureList.push_back(newTexture);
            }
            if (!mat.second.map_Ks.empty()) {
                std::string texturePath = mat.second.map_Ks; // Adjust path
                printf("[DEBUG] Load texture Ks: %s\n", texturePath.c_str());
                auto *newTexture = new Texture(texturePath.c_str());
                newTexture->LoadTextureA();
                textureList.push_back(newTexture);
            }
        }

        // Attribute sizes: Position(3), Texture Coordinates(2), Normals(3)
        attributeSizes = {3, 2, 3};

        // Convert Vertex vector to GLfloat array
        std::vector<GLfloat> vertexData;
        for (const auto &v : vertices) {
            vertexData.push_back(v.position.x);
            vertexData.push_back(v.position.y);
            vertexData.push_back(v.position.z);
            vertexData.push_back(v.texCoords.x);
            vertexData.push_back(v.texCoords.y);
            vertexData.push_back(v.normal.x);
            vertexData.push_back(v.normal.y);
            vertexData.push_back(v.normal.z);
        }

        // Create a new mesh using the loaded vertices and indices
        auto *newMesh = new Mesh();
        newMesh->CreateMesh(vertexData.data(), indices.data(),
                            static_cast<unsigned int>(vertexData.size()),
                            static_cast<unsigned int>(indices.size()),
                            attributeSizes);

        meshList.push_back(newMesh);
        printf("[DEBUG] Model loaded: %s\n", fileName.c_str());
    } else {
        printf("Failed to load OBJ file: %s\n", fileName.c_str());
    }
}

void Model::RenderModelWithoutAssimp() const {
    for (size_t i = 0; i < meshList.size(); ++i) {
        if (i < textureList.size() && textureList[i]) {
            textureList[i]->UseTexture(); // Bind the texture
        }

        meshList[i]->RenderMesh();
    }
}

void Model::ClearModelWithoutAssimp() {
    for (auto &mesh : meshList) {
        mesh->ClearMesh();
        delete mesh;
        mesh = nullptr;
    }
    meshList.clear();
}

void Model::RenderModel() const {
    for (size_t i = 0; i < meshList.size(); i++) {
        if (const unsigned int materialIndex = meshToTex[i]; materialIndex < textureList.size() && textureList[materialIndex]) {
            textureList[materialIndex]->UseTexture();
        }

        meshList[i]->RenderMesh();
    }
}

void Model::SetAttributeSizeAssimp(const aiScene *scene) {
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* mesh = scene->mMeshes[i];
        attributeSizes.clear();

        // Check for Positions
        if (mesh->HasPositions()) {
            attributeSizes.push_back(3); // x, y, z
            printf("Positions: 3 components\n");
        }

        // Check for Texture Coordinates
        if (mesh->HasTextureCoords(0)) {
            attributeSizes.push_back(2); // u, v
            printf("Texture Coordinates: 2 components\n");
        }

        // Check for Normals
        if (mesh->HasNormals()) {
            attributeSizes.push_back(3); // nx, ny, nz
            printf("Normals: 3 components\n");
        }

        // Check for Tangents
        if (mesh->HasTangentsAndBitangents()) {
            attributeSizes.push_back(3); // Tangents (optional)
            printf("Tangents: 3 components\n");
        }

        printf("Attribute Sizes for Mesh %d :\n", i);
        for (const int size : attributeSizes) {
            printf("%d\n", size);
        }
    }
}

void Model::LoadModel(const std::string &fileName) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if (!scene) {
        printf("ERROR: Failed to load model from %s: %s\n", fileName.c_str(), importer.GetErrorString());
        return;
    }

    SetAttributeSizeAssimp(scene);

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
    newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size(), attributeSizes);
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
                std::string fullPath = path.data;
                size_t lastSlash = fullPath.find_last_of("/\\"); // Handles both '/' and '\\'

                std::string filename;
                if (lastSlash != std::string::npos) {
                    filename = fullPath.substr(lastSlash + 1); // Extract from after the last slash
                } else {
                    filename = fullPath; // If no slashes are found, use the full path
                }
                printf("[DEBUG] for filename: %s\n", filename.c_str());

                std::string texPath = std::string("/Users/prkaaviya/CLionProjects/try8/Textures/") + filename;
                printf("Loading texture: %s\n", texPath.c_str());

                textureList[i] = new Texture(texPath.c_str());

                if (!textureList[i]->LoadTextureA()) {
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

