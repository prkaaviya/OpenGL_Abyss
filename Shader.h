#pragma once

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	static std::string ReadFile(const char* fileLocation);

	[[nodiscard]] GLuint GetProjectionLocation() const;
	[[nodiscard]] GLuint GetModelLocation() const;
	[[nodiscard]] GLuint GetViewLocation() const;

	void UseShader() const;
	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	static void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

