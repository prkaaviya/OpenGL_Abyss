#pragma once
#ifndef CORAL_ANIMATOR_H
#define CORAL_ANIMATOR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "CommonValues.h"

class CoralAnimator {
public:
    CoralAnimator(float frequency, float amplitude)
        : wiggleFreq(frequency), wiggleAmp(amplitude) {}

    [[nodiscard]] glm::mat4 GetWiggleTransform(glm::vec3 position, glm::vec3 scale, const bool rotate=false) const {
        const float wiggleAngle = sin(glfwGetTime() * wiggleFreq) * wiggleAmp;

        auto model = glm::mat4(1.0f);
        if (rotate) model = glm::rotate(model, -90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(wiggleAngle), glm::vec3(0.0f, 0.0f, 1.0f)); // Oscillate around Z-axis
        model = glm::scale(model, scale);

        return model;
    }

private:
    float wiggleFreq; // Frequency of the wiggle
    float wiggleAmp;  // Amplitude of the wiggle

};

#endif // CORAL_ANIMATOR_H