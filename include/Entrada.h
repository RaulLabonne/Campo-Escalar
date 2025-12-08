/**
 * @file Entrada.h
 * @brief Clase para manejar la entrada de datos y funciones en OpenGL
 */

#ifndef ENTRADA_H
#define ENTRADA_H

#include <cmath>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

namespace opengl {

    /** 
     * @class Entrada
     * @brief Clase para manejar la entrada de datos y funciones en OpenGL
    */
    class Entrada{

        public: 
            /**
             * @enum Funciones
             * @brief Tipos de funciones disponibles
             */
            enum Funciones {
                TRIGONOMETRICA,
                FUNCION_A,
                FUNCION_B,
            };
        
        /* Constructor */
        Entrada(Funciones func): m_funcion(func) {}

        /** 
         * @brief Evalua la función en un punto (x, y)
         * @param x Coordenada x
         * @param y Coordenada y
         * @return Valor de la función en (x, y)
        */
        float evaluarFuncion(float x, float y);

        /** 
         * @brief Genera una malla de la función en el rango especificado
         * @param xMin Mínimo valor de x
         * @param xMax Máximo valor de x
         * @param yMin Mínimo valor de y
         * @param yMax Máximo valor de y
         * @param pasos Número de pasos en cada dirección
         * @param vertices Vector para almacenar los vértices generados
         * @param indices Vector para almacenar los índices generados
        */
        void generarMalla(float xMin, float xMax, 
                            float yMin, float yMax, 
                            int pasos,
                            std::vector<float>& vertices,
                            std::vector<unsigned int>& indices);

        /** 
         * @brief Genera vectores de gradiente de la función en el rango especificado
         * @param xMin Mínimo valor de x
         * @param xMax Máximo valor de x
         * @param yMin Mínimo valor de y
         * @param yMax Máximo valor de y
         * @param pasos Número de pasos en cada dirección
         * @param vectores Vector para almacenar los vectores generados
        */
        void generarVectores(float xMin, float xMax, 
                            float yMin, float yMax, 
                            int pasos,
                            std::vector<float>& vectores);
        
        /** 
         * @brief Calcula el gradiente de la función en un punto (x, y)
         * @param x Coordenada x
         * @param y Coordenada y
         * @param z Valor de la función en (x, y)
         * @param h Paso pequeño para la aproximación numérica
         * @return Vector gradiente en (x, y)
        */
        glm::vec3 gradiante(float x, float y, float h = 0.01f);

        private:
            /* La funcion escogida */
            Funciones m_funcion;
    };
}


#endif // FUNCIONES_H