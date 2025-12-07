#ifndef ENTRADA_H
#define ENTRADA_H

#include <cmath>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

namespace opengl {

    class Entrada{

        public: 
            enum Funciones {
                TRIGONOMETRICA,
                FUNCION_A,
                FUNCION_B,
            };
        
        Entrada(Funciones func): m_funcion(func) {}
        

        float evaluarFuncion(float x, float y);

        void generarMalla(float xMin, float xMax, 
                            float yMin, float yMax, 
                            int pasos,
                            std::vector<float>& vertices,
                            std::vector<unsigned int>& indices);

        void generarVectores(float xMin, float xMax, 
                            float yMin, float yMax, 
                            int pasos,
                            std::vector<float>& vectores);
        
        glm::vec3 gradiante(float x, float y, float z, float h = 0.01f);

        private:
            Funciones m_funcion;
    };
}


#endif // FUNCIONES_H