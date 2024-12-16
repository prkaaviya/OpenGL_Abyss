#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <functional>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;

    // Overload equality operator for hashing
    bool operator==(const Vertex& other) const {
        return position == other.position &&
               texCoords == other.texCoords &&
               normal == other.normal;
    }
};

struct MaterialMTL {
    std::string name;
    std::string map_Ka; // Ambient texture
    std::string map_Kd; // Diffuse texture
    std::string map_Ks; // Specular texture
};

// Custom hash function for Vertex struct
struct VertexHash {
    std::size_t operator()(const Vertex& vertex) const {
        const std::size_t h1 = std::hash<float>()(vertex.position.x) ^
                               (std::hash<float>()(vertex.position.y) << 1) ^
                               (std::hash<float>()(vertex.position.z) << 2);

        const std::size_t h2 = std::hash<float>()(vertex.texCoords.x) ^
                               (std::hash<float>()(vertex.texCoords.y) << 1);

        const std::size_t h3 = std::hash<float>()(vertex.normal.x) ^
                               (std::hash<float>()(vertex.normal.y) << 1) ^
                               (std::hash<float>()(vertex.normal.z) << 2);

        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

class OBJLoader {
public:
    static bool LoadOBJ(const std::string& filePath, std::vector<Vertex>& outVertices, std::vector<unsigned int>& outIndices);
    static std::unordered_map<std::string, MaterialMTL> LoadMTL(const std::string& mtlFilePath);
};

#endif // OBJLOADER_H