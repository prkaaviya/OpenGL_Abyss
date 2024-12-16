#include "Skybox.h"

Skybox::Skybox() {

}

Skybox::Skybox(const std::vector<std::string>& faceLocations) {
	printf("[DEBUG] Creating skybox now.\n");
    skyShader = new Shader();
    skyShader->CreateFromFiles("/Users/prkaaviya/CLionProjects/try8/Shaders/skybox_vert.glsl",
        "/Users/prkaaviya/CLionProjects/try8/Shaders/skybox_frag.glsl");

    uniformProjection = skyShader->GetProjectionLocation();
    uniformView = skyShader->GetViewLocation();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, bitDepth;

    for (size_t i = 0; i < 6; i++) {
        unsigned char *texData = stbi_load(faceLocations[i].c_str(), &width, &height, &bitDepth, 3);
        if (!texData) {
            printf("ERROR: Failed to load cubemap texture from %s.\n", faceLocations[i].c_str());
            return;
        } else {
        	printf("[DEBUG] Loaded cubemap texture from %s (%d x %d x %d).\n", faceLocations[i].c_str(), width, height, bitDepth);
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        stbi_image_free(texData);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned int skyboxIndices[] = {
		// front
		0, 1, 2,
		2, 1, 3,
		// right
		2, 3, 5,
		5, 3, 7,
		// back
		5, 7, 4,
		4, 7, 6,
		// left
		4, 6, 0,
		0, 6, 1,
		// top
		4, 0, 5,
		5, 0, 2,
		// bottom
		1, 6, 3,
		3, 6, 7
	};

    GLfloat skyboxVertices[24] = {
	    -1.0f, 1.0f, -1.0f,
	    -1.0f, -1.0f, -1.0f,
	    1.0f, 1.0f, -1.0f,
	    1.0f, -1.0f, -1.0f,

	    -1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    -1.0f, -1.0f, 1.0f,
	    1.0f, -1.0f, 1.0f,
    };

	const std::vector<int> &skyboxAttributeSizes = {3};

	skyMesh = new Mesh();
	skyMesh->CreateMesh(skyboxVertices, skyboxIndices, 8, 36, skyboxAttributeSizes);
}

void Skybox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) const {
	viewMatrix = glm::mat4(glm::mat3(viewMatrix));

	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);

	skyShader->UseShader();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glUniform1i(glGetUniformLocation(textureID, "skybox"), 1);

	skyMesh->RenderMesh();

	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
}

Skybox::~Skybox() {
	glDeleteTextures(1, &textureID);
}

