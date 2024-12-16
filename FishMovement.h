#pragma once

#ifndef FISHMOVEMENT_H
#define FISHMOVEMENT_H

#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

struct FishMovement {
    float radius;
    float swimSpeed;
    float oscillationAmp;
    float oscillationFreq;
};

glm::mat4 CalculateFishMovement(float& angle, float deltaTime, const FishMovement& params);

#endif
