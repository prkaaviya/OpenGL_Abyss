#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

class Mesh {
public:
    Mesh();

    void CreateMesh(const GLfloat *vertices, const unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void RenderMesh() const;
    void ClearMesh();

    ~Mesh();

private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
};



#endif //MESH_H
