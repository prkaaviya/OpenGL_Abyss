#pragma once

#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

#include "Mesh.h"
#include "Shader.h"
#include "CommonValues.h"

class Skybox {
public:
    Skybox();

    Skybox(const std::vector<std::string>& faceLocations);
    void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) const;
    ~Skybox();

private:
    Mesh *skyMesh;
    Shader *skyShader;

    GLuint textureID;
    GLuint uniformProjection, uniformView;
};

#endif //SKYBOX_H
