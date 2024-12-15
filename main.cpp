#define STB_IMAGE_IMPLEMENTATION

#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
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

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

const std::string vShader = "/Users/prkaaviya/CLionProjects/try8/Shaders/default_vert.glsl";
const std::string fShader = "/Users/prkaaviya/CLionProjects/try8/Shaders/default_frag.glsl";

void CreateObjects() {
	unsigned int indices[] = {
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
		// x      y      z      u     v
		// Front face
		-1.0f, -1.0f,  1.0f,   0.0f, 0.0f, // Bottom-left
		 1.0f, -1.0f,  1.0f,   1.0f, 0.0f, // Bottom-right
		 1.0f,  1.0f,  1.0f,   1.0f, 1.0f, // Top-right
		-1.0f,  1.0f,  1.0f,   0.0f, 1.0f, // Top-left

		// Back face
		-1.0f, -1.0f, -1.0f,   1.0f, 0.0f, // Bottom-left
		 1.0f, -1.0f, -1.0f,   0.0f, 0.0f, // Bottom-right
		 1.0f,  1.0f, -1.0f,   0.0f, 1.0f, // Top-right
		-1.0f,  1.0f, -1.0f,   1.0f, 1.0f, // Top-left

		// Left face
		-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, // Bottom-left
		-1.0f, -1.0f,  1.0f,   1.0f, 0.0f, // Bottom-right
		-1.0f,  1.0f,  1.0f,   1.0f, 1.0f, // Top-right
		-1.0f,  1.0f, -1.0f,   0.0f, 1.0f, // Top-left

		// Right face
		 1.0f, -1.0f, -1.0f,   0.0f, 0.0f, // Bottom-left
		 1.0f, -1.0f,  1.0f,   1.0f, 0.0f, // Bottom-right
		 1.0f,  1.0f,  1.0f,   1.0f, 1.0f, // Top-right
		 1.0f,  1.0f, -1.0f,   0.0f, 1.0f, // Top-left

		// Top face
		-1.0f,  1.0f, -1.0f,   0.0f, 0.0f, // Bottom-left
		 1.0f,  1.0f, -1.0f,   1.0f, 0.0f, // Bottom-right
		 1.0f,  1.0f,  1.0f,   1.0f, 1.0f, // Top-right
		-1.0f,  1.0f,  1.0f,   0.0f, 1.0f, // Top-left

		// Bottom face
		-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, // Bottom-left
		 1.0f, -1.0f, -1.0f,   1.0f, 0.0f, // Bottom-right
		 1.0f, -1.0f,  1.0f,   1.0f, 1.0f, // Top-right
		-1.0f, -1.0f,  1.0f,   0.0f, 1.0f, // Top-left
	};

    Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 120, 36);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 120, 36);
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
	containerTexture.LoadTexture();
	metalBoxTexture = Texture("/Users/prkaaviya/CLionProjects/try8/Resources/Textures/metalbox.jpg");
	metalBoxTexture.LoadTexture();

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
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
