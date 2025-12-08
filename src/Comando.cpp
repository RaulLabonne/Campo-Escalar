/**
 * @file Comando.cpp
 * @brief Implementacion de la clase App
 */
#include "../include/Comando.h"

namespace opengl {

    void Comando::updateRender(int keyState, int key, int* renderMode) {
        if (keyState == GLFW_PRESS) {
            if (key == GLFW_KEY_1) *renderMode = 0;
            if (key == GLFW_KEY_2) *renderMode = 1;
        }
    }

    void Comando::updateRotation(int keyState, int key, Window* window) {
        if (keyState == GLFW_PRESS) {
            // Ajustes de sensibilidad para giro y zoom
            const float angleStep = 1.0f;
            const float distStep = 0.5f;

            // Giro de camara
            if (key == GLFW_KEY_UP)    pitch += angleStep;
            if (key == GLFW_KEY_DOWN)  pitch -= angleStep;
            if (key == GLFW_KEY_LEFT)  yaw   -= angleStep;
            if (key == GLFW_KEY_RIGHT) yaw   += angleStep;

            // Zoom in/out
            if (key == GLFW_KEY_W)     dist  -= distStep;
            if (key == GLFW_KEY_S)     dist  += distStep;

            // Actualizamos la vista de la ventana
            window->updateViewProyection(yaw, pitch, dist);

            // Resetear vista
            if (key == GLFW_KEY_R) window->initViewProyection();
        }
    }

}