#include "OBJLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool OBJLoader::LoadOBJ(const std::string& filePath, std::vector<Vertex>& outVertices, std::vector<unsigned int>& outIndices) {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;

    std::unordered_map<Vertex, unsigned int, VertexHash> vertexMap;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        printf("ERROR: Failed to open OBJ file: %s\n", filePath.c_str());
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream s(line);
        std::string prefix;
        s >> prefix;

        if (prefix == "v") { // Vertex position
            glm::vec3 position;
            s >> position.x >> position.y >> position.z;
            positions.push_back(position);
        }
        else if (prefix == "vt") { // Texture coordinate
            glm::vec2 tex;
            s >> tex.x >> tex.y;
            texCoords.push_back(tex);
        }
        else if (prefix == "vn") { // Normal
            glm::vec3 normal;
            s >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }
        else if (prefix == "f") { // Face
            std::string vertexString;
            for (int i = 0; i < 3; i++) {
                s >> vertexString;

                std::istringstream vertexData(vertexString);
                std::string v, vt, vn;

                size_t pos1 = vertexString.find('/');
                size_t pos2 = vertexString.find('/', pos1 + 1);

                int vIndex = std::stoi(vertexString.substr(0, pos1)) - 1;
                int vtIndex = std::stoi(vertexString.substr(pos1 + 1, pos2 - pos1 - 1)) - 1;
                int vnIndex = std::stoi(vertexString.substr(pos2 + 1)) - 1;

                Vertex vertex = { positions[vIndex], texCoords[vtIndex], normals[vnIndex] };

                // Check for duplicate vertex
                if (vertexMap.count(vertex) == 0) {
                    vertexMap[vertex] = static_cast<unsigned int>(outVertices.size());
                    outVertices.push_back(vertex);
                }

                outIndices.push_back(vertexMap[vertex]);
            }
        }
    }

    file.close();
    return true;
}


std::unordered_map<std::string, MaterialMTL> OBJLoader::LoadMTL(const std::string& mtlFilePath) {
    std::unordered_map<std::string, MaterialMTL> materials;
    std::ifstream file(mtlFilePath);
    std::string line, prefix;

    MaterialMTL currentMaterial;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> prefix;

        if (prefix == "newmtl") {
            if (!currentMaterial.name.empty()) {
                materials[currentMaterial.name] = currentMaterial;
            }
            iss >> currentMaterial.name;
            currentMaterial.map_Ka = "";
            currentMaterial.map_Kd = "";
            currentMaterial.map_Ks = "";
        } else if (prefix == "map_Ka") {
            iss >> currentMaterial.map_Ka;
        } else if (prefix == "map_Kd") {
            iss >> currentMaterial.map_Kd;
        } else if (prefix == "map_Ks") {
            iss >> currentMaterial.map_Ks;
        }
    }

    // Save the last material
    if (!currentMaterial.name.empty()) {
        materials[currentMaterial.name] = currentMaterial;
    }

    return materials;
}