#include <cstdio>
#include "FishMovement.h"

glm::mat4 CalculateFishMovement(float& angle, float deltaTime, const FishMovement& params) {
    // Increment angle with proper scaling for speed
    angle += deltaTime * params.swimSpeed; // Adjust the multiplier for speed
    if (angle > 360.0f) angle -= 360.0f;

    // Scale the radius to increase movement range
    float effectiveRadius = params.radius; // Adjust this multiplier as needed

    // Calculate the fish's X and Z positions based on the circular path
    float fishX = cos(glm::radians(angle)) * effectiveRadius;
    float fishZ = sin(glm::radians(angle)) * effectiveRadius;

    // Oscillation effect for realistic vertical (Y-axis) movement
    float waggle = sin(glfwGetTime() * params.oscillationFreq) * params.oscillationAmp;

    // Combine transformations: position, direction, and slight tail waggle
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-3.8f, 2.6f, -5.0f)); // Position with oscillation
    model = glm::translate(model, glm::vec3(fishX, 0.4f + waggle * 0.01f, fishZ)); // Position with oscillation
    model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(0.0f, 1.0f, 1.0f)); // Align vertically
    model = glm::rotate(model, glm::radians(-angle), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate to face direction
    model = glm::rotate(model, glm::radians(waggle * 2.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Tail/body waggle

    return model;
}