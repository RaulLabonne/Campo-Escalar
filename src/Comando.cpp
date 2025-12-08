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
            const float angleStep = 1.0f;
            const float distStep = 0.5f;

            if (key == GLFW_KEY_UP)    pitch += angleStep;
            if (key == GLFW_KEY_DOWN)  pitch -= angleStep;
            if (key == GLFW_KEY_LEFT)  yaw   -= angleStep;
            if (key == GLFW_KEY_RIGHT) yaw   += angleStep;
            if (key == GLFW_KEY_W)     dist  -= distStep;
            if (key == GLFW_KEY_S)     dist  += distStep;

            window->updateViewProyection(yaw, pitch, dist);

            if (key == GLFW_KEY_R) window->initViewProyection();
        }
    }

}