#pragma once

#ifndef STARFISHMOVEMENT_H
#define STARFISHMOVEMENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class StarfishMovement {
public:
    StarfishMovement(float frequency, float amplitude)
        : wiggleFreq(frequency), wiggleAmp(amplitude) {}

    [[nodiscard]] glm::mat4 GetWiggleTransform(glm::vec3 position, glm::vec3 scale, glm::vec3 baseRotationAxis, float baseRotationAngle) const {
        // Get time-based oscillation value
        const float wiggleAngle = sin(glfwGetTime() * wiggleFreq) * wiggleAmp;

        // Combine base transformation with wiggle effect
        auto model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(wiggleAngle), glm::vec3(0.0f, 0.0f, 1.0f)); // Wiggle around Z-axis
        model = glm::rotate(model, glm::radians(baseRotationAngle), baseRotationAxis); // Base rotation
        model = glm::scale(model, scale);

        return model;
    }

private:
    float wiggleFreq; // Frequency of the wiggle
    float wiggleAmp;  // Amplitude of the wiggle
};

#endif //STARFISHMOVEMENT_H
