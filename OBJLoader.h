#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;

    bool operator==(const Vertex& other) const {
        return position == other.position && texCoords == other.texCoords && normal == other.normal;
    }
};

struct VertexHash {
    std::size_t operator()(const Vertex& vertex) const {
        return ((std::hash<float>()(vertex.position.x) ^
                 (std::hash<float>()(vertex.position.y) << 1)) >> 1) ^
                (std::hash<float>()(vertex.position.z) << 1);
    }
};

class OBJLoader {
public:
    static bool LoadOBJ(const std::string& filePath, std::vector<Vertex>& outVertices, std::vector<unsigned int>& outIndices);
};

#endif