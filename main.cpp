#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

constexpr GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

std::string ReadFile(const char* filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        printf("ERROR::FILE_NOT_FOUND: %s\n", filePath);
        return "";
    }

    std::stringstream fileStream;
    fileStream << file.rdbuf();
    file.close();

    return fileStream.str();
}

void CreateTriangle() {
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void AddShader(GLuint program, const char *shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);

    const GLchar *theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    char eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
        printf("ERROR::SHADER_COMPILE_ERROR for %d:\n%s\n", shaderType, eLog);
    }

    glAttachShader(program, theShader);
    glDeleteShader(theShader);
}

void CompileShaders() {
    shader = glCreateProgram();
    if (!shader) {
        printf("ERROR: Failed to create shader.\n");
        return;
    }

    std::string vShaderString = ReadFile("/Users/prkaaviya/CLionProjects/try8/Shaders/default_vert.glsl");
    std::string fShaderString = ReadFile("/Users/prkaaviya/CLionProjects/try8/Shaders/default_frag.glsl");

    if (vShaderString.empty() || fShaderString.empty()) {
        printf("ERROR: Failed to load shader files.\n");
        return;
    }

    const char* vShader = vShaderString.c_str();
    const char* fShader = fShaderString.c_str();

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    char eLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        printf("ERROR::PROGRAM_LINK_ERROR:\n%s\n", eLog);
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        printf("ERROR::PROGRAM_VALIDATION_ERROR:\n%s\n", eLog);
    }

}

int main()
{
    if (!glfwInit()) {
        printf("ERROR : GLFW could not be initialised.\n");
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Abyss", nullptr, nullptr);
    if (!mainWindow) {
        printf("ERROR : GLFW window creation failed.\n");
        glfwTerminate();
        return -2;
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    glfwMakeContextCurrent(mainWindow);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        printf("ERROR : GLEW could not be initialised.\n");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return -3;
    }

    glViewport(0, 0, bufferWidth, bufferHeight);

    CreateTriangle();
    CompileShaders();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.0f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader);

    glfwDestroyWindow(mainWindow);
    glfwTerminate();

    return 0;
}