/**
 * @file Comando.h
 * @brief Clase Comando para manejar los comandos de la aplicación
 */
#ifndef COMANDO_H
#define COMANDO_H

#include "Window.h"


namespace opengl {
    /**
     * @class Comando
     * @brief Clase para manejar los comandos de la aplicación
     */
    class Comando {

        private:
            /* Rotacion horizontal */
            float yaw   = 0.0f;
            /* Rotacion vertical */
            float pitch = 0.0f;
            /* Distancia de la cámara */
            float dist  = 20.0f;

        public:

        /**
         * @brief Constructor de la clase Comando
         */
        Comando() {}

        /**
         * @brief Actualiza el modo de renderizado
         * @param keyState Estado de la tecla
         * @param key Tecla presionada
         * @param renderMode Modo de renderizado
         */
        void updateRender(int keyState, int key, int* renderMode);

        /**
         * @brief Actualiza la rotación de la cámara
         * @param keyState Estado de la tecla
         * @param key Tecla presionada
         * @param window Puntero a la ventana para actualizar la vista
         */
        void updateRotation(int keyState, int key, Window* window);
    };
}

#endif // COMANDO_H