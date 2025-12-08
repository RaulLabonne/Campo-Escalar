#ifndef COMANDO_H
#define COMANDO_H

#include "Window.h"
// Aquí puedes agregar el contenido del archivo Comando.h

namespace opengl {
    // Declaraciones y definiciones relacionadas con Comando
    class Comando {

        private:
            float yaw   = 0.0f;
            float pitch = 0.0f;
            float dist  = 20.0f;

        public:

        Comando() {}

        void updateRender(int keyState, int key, int* renderMode);

        void updateRotation(int keyState, int key, Window* window);
    };
}

#endif // COMANDO_H