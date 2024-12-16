#pragma once

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include "CommonValues.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	static std::string ReadFile(const char* fileLocation);

	[[nodiscard]] GLuint GetShaderID() const;
	[[nodiscard]] GLuint GetProjectionLocation() const;
	[[nodiscard]] GLuint GetModelLocation() const;
	[[nodiscard]] GLuint GetViewLocation() const;
	[[nodiscard]] GLuint GetAmbientIntensityLocation() const;
	[[nodiscard]] GLuint GetAmbientColourLocation() const;
	[[nodiscard]] GLuint GetDiffuseIntensityLocation() const;
	[[nodiscard]] GLuint GetDirectionLocation() const;
	[[nodiscard]] GLuint GetSpecularIntensityLocation() const;
	[[nodiscard]] GLuint GetShininessLocation() const;
	[[nodiscard]] GLuint GetEyePositionLocation() const;

	void SetDirectionalLight(DirectionalLight * dLight) const;
	void SetPointLights(PointLight * pLight, unsigned int lightCount) const;
	void SetSpotLights(SpotLight * sLight, unsigned int lightCount) const;

	void UseShader() const;
	void ClearShader();

	~Shader();

private:
	int pointLightCount;
	int spotLightCount;

	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
		uniformSpecularIntensity, uniformShininess;

	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
	} uniformDirectionalLight;

	GLuint uniformPointLightCount;

	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLight[MAX_POINT_LIGHTS];

	GLuint uniformSpotLightCount;

	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;

		GLuint uniformDirection;
		GLuint uniformEdge;
	} uniformSpotLight[MAX_SPOT_LIGHTS];


	void CompileShader(const char* vertexCode, const char* fragmentCode);
	static void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

