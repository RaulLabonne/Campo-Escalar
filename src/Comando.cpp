#include "../include/Comando.h"


namespace opengl {

    void Comando::updateRender(int keyState, int key, int* renderMode) {
        if (keyState == GLFW_PRESS) {
            if (key == GLFW_KEY_1) *renderMode = 0;
            if (key == GLFW_KEY_2) *renderMode = 1;
        }
    }

    void Comando::updateRotation(int key) {
        // Lógica para actualizar la rotación del objeto según la tecla presionada
        // Por ejemplo, rotar el objeto en diferentes ejes
    }

}