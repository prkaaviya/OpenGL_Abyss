#include "Mesh.h"

Mesh::Mesh() {
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indexCount = 0;
}

void Mesh::CreateMesh(const GLfloat *vertices, const unsigned int *indices, const unsigned int numOfVertices, const unsigned int numOfIndices, const std::vector<int> &attributeSizes) {
    printf("[DEBUG] In CreateMesh with attributeSizes:\n");
    for (const auto &size : attributeSizes) {
        printf("%d ", size);
    }
    printf("\n");

    indexCount = numOfIndices;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

    int stride = 0;
    for (const auto &size : attributeSizes) {
        stride += size;
    }
    stride *= sizeof(GLfloat);
    printf("[DEBUG] Final value of stride: %d\n", stride);

    intptr_t offset = 0;
    for (int i = 0; i < attributeSizes.size(); i++) {
        printf("[DEBUG] Value of offset for attribute loc %d: %ld\n", i, offset);
        glVertexAttribPointer(i, attributeSizes[i], GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(offset));
        glEnableVertexAttribArray(i);
        offset += attributeSizes[i] * sizeof(GLfloat);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    if (const GLenum err = glGetError(); err != GL_NO_ERROR) {
        printf("OpenGL Error (after CreateMesh): %d\n", err);
    }
}

void Mesh::RenderMesh() const {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::ClearMesh() {
    if (IBO != 0) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    indexCount = 0;
}


Mesh::~Mesh() {
    ClearMesh();
}