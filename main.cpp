#define STB_IMAGE_IMPLEMENTATION

#include <cmath>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

constexpr float toRadians = 3.14159265359f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

Texture containerTexture;
Texture metalBoxTexture;

Light mainLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

const std::string vShader = "/Users/prkaaviya/CLionProjects/try8/Shaders/default_vert.glsl";
const std::string fShader = "/Users/prkaaviya/CLionProjects/try8/Shaders/default_frag.glsl";

void calcAverageNormals(const unsigned int* indices, unsigned int indiceCount,
                        GLfloat* vertices, const unsigned int verticeCount,
						const unsigned int vLength, const unsigned int normalOffset) {
	for (unsigned int i = 0; i < indiceCount; i += 3) {
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++) {
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] += vec.x; vertices[nOffset + 1] += vec.y; vertices[nOffset + 2] += vec.z;
	}
}

void CreateObjects() {
	const unsigned int indices[] = {
		// Front face
		0, 1, 2,
		2, 3, 0,
		// Back face
		4, 5, 6,
		6, 7, 4,
		// Left face
		8, 9, 10,
		10, 11, 8,
		// Right face
		12, 13, 14,
		14, 15, 12,
		// Top face
		16, 17, 18,
		18, 19, 16,
		// Bottom face
		20, 21, 22,
		22, 23, 20
	};

	GLfloat vertices[] = {
		// x      y      z      u     v       nx    ny    nz
		// Front face
		-1.0f, -1.0f,  1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 0.0f, // Bottom-left
		 1.0f, -1.0f,  1.0f,   1.0f, 0.0f,   0.0f, 0.0f, 0.0f, // Bottom-right
		 1.0f,  1.0f,  1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 0.0f, // Top-right
		-1.0f,  1.0f,  1.0f,   0.0f, 1.0f,   0.0f, 0.0f, 0.0f, // Top-left

		// Back face
		-1.0f, -1.0f, -1.0f,   1.0f, 0.0f,   0.0f, 0.0f, 0.0f, // Bottom-left
		 1.0f, -1.0f, -1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 0.0f, // Bottom-right
		 1.0f,  1.0f, -1.0f,   0.0f, 1.0f,   0.0f, 0.0f, 0.0f, // Top-right
		-1.0f,  1.0f, -1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 0.0f, // Top-left

		// Left face
		-1.0f, -1.0f, -1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 0.0f, // Bottom-left
		-1.0f, -1.0f,  1.0f,   1.0f, 0.0f,   0.0f, 0.0f, 0.0f, // Bottom-right
		-1.0f,  1.0f,  1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 0.0f, // Top-right
		-1.0f,  1.0f, -1.0f,   0.0f, 1.0f,   0.0f, 0.0f, 0.0f, // Top-left

		// Right face
		 1.0f, -1.0f, -1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 0.0f,// Bottom-left
		 1.0f, -1.0f,  1.0f,   1.0f, 0.0f,   0.0f, 0.0f, 0.0f,// Bottom-right
		 1.0f,  1.0f,  1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 0.0f,// Top-right
		 1.0f,  1.0f, -1.0f,   0.0f, 1.0f,   0.0f, 0.0f, 0.0f,// Top-left

		// Top face
		-1.0f,  1.0f, -1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 0.0f, // Bottom-left
		 1.0f,  1.0f, -1.0f,   1.0f, 0.0f,   0.0f, 0.0f, 0.0f, // Bottom-right
		 1.0f,  1.0f,  1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 0.0f, // Top-right
		-1.0f,  1.0f,  1.0f,   0.0f, 1.0f,   0.0f, 0.0f, 0.0f, // Top-left

		// Bottom face
		-1.0f, -1.0f, -1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 0.0f, // Bottom-left
		 1.0f, -1.0f, -1.0f,   1.0f, 0.0f,   0.0f, 0.0f, 0.0f, // Bottom-right
		 1.0f, -1.0f,  1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 0.0f, // Top-right
		-1.0f, -1.0f,  1.0f,   0.0f, 1.0f,   0.0f, 0.0f, 0.0f, // Top-left
	};

	calcAverageNormals(indices, 36, vertices, 192, 8, 5);

	const auto obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 192, 36);
	meshList.push_back(obj1);

	const auto obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 192, 36);
	meshList.push_back(obj2);
}

void CreateShaders()
{
	auto *shader1 = new Shader();
	shader1->CreateFromFiles(vShader.c_str(), fShader.c_str());
	shaderList.push_back(*shader1);
}

int main()
{
    mainWindow = Window(800, 800);
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 1.0f, 0.5f);

	containerTexture = Texture("/Users/prkaaviya/CLionProjects/try8/Resources/Textures/container.jpg");
	containerTexture.LoadTextureA();
	metalBoxTexture = Texture("/Users/prkaaviya/CLionProjects/try8/Resources/Textures/metalbox.jpg");
	metalBoxTexture.LoadTextureA();

	mainLight = Light(1.0f, 1.0f, 1.0f, 0.2f,
					2.0f, -1.0f, -2.0f, 1.0f);

	GLfloat uniformProjection = 0, uniformModel = 0, uniformView = 0,
			uniformAmbientIntensity = 0, uniformAmbientColor = 0,
			uniformDirection = 0, uniformDiffuseIntensity = 0;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<GLfloat>(mainWindow.getBufferWidth()) / mainWindow.getBufferHeight(), 0.1f, 100.0f);
    
    while (!mainWindow.getShouldClose())
	{
		const GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		glClearColor(0.2f, 0.0f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
    	uniformAmbientColor = shaderList[0].GetAmbientColourLocation();
    	uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
    	uniformDirection = shaderList[0].GetDirectionLocation();
    	uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();

    	mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColor,
    						uniformDiffuseIntensity, uniformDirection);

		glm::mat4 model(1.0f);	
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		// model = glm::scale(model, glm::vec3(0.2f, 0.2f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
    	containerTexture.UseTexture();
    	meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, -2.5f));
		// model = glm::scale(model, glm::vec3(0.2f, 0.2f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    	metalBoxTexture.UseTexture();
    	meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
