#ifndef COMANDO_H
#define COMANDO_H


#include <GLFW/glfw3.h>

// Aquí puedes agregar el contenido del archivo Comando.h

namespace opengl {
    // Declaraciones y definiciones relacionadas con Comando
    class Comando {

        public:

        static void updateRender(int keyState, int key, int* renderMode);

        static void updateRotation(int key);
    };
}

#endif // COMANDO_H