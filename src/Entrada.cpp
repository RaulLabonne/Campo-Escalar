#include "../include/Entrada.h"

namespace opengl {
    float Entrada::evaluarFuncion(float x, float y, Funciones func) {
        switch (func) {
            case TRIGONOMETRICA:
                return sinf(x*y);
            case FUNCION_A:
                return 0.5 + 0.5 * sin( sqrt(x*x + y*y) );
            case FUNCION_B:
                return expf(-(x * x + y * y));
            default:
                return sinf(x*y);
        }
    }

    void Entrada::generarMalla(float xMin, float xMax, 
                                float yMin, float yMax, 
                                int pasos,
                                std::vector<float>& vertices,
                                std::vector<unsigned int>& indices) {

        vertices.clear();
        indices.clear();

        float stepX = (xMax - xMin) / pasos;
        float stepY = (yMax - yMin) / pasos;

        for (int i = 0; i <= pasos; ++i) {
            for (int j = 0; j <= pasos; ++j) {
                float x = xMin + i * stepX;
                float y = yMin + j * stepY;
                float z = evaluarFuncion(x, y, m_funcion);

                // Coordenadas de textura normalizadas
                float u = (float)i / pasos; 
                float v = (float)j / pasos;
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                vertices.push_back(u);
                vertices.push_back(v);
            }
        }

        int ancho = pasos + 1;

        for (int i = 0; i < pasos; ++i) {
            for (int j = 0; j < pasos; ++j) {

                int idx0 =  i      * ancho + j;
                int idx1 =  i      * ancho + j + 1;
                int idx2 = (i + 1) * ancho + j;
                int idx3 = (i + 1) * ancho + j + 1;

                // triángulo 1
                indices.push_back(idx0);
                indices.push_back(idx2);
                indices.push_back(idx1);

                // triángulo 2
                indices.push_back(idx1);
                indices.push_back(idx2);
                indices.push_back(idx3);
            }
        }
    }
    

    void Entrada::generarVectores(float xMin, float xMax, 
                            float yMin, float yMax, 
                            int pasos,
                            std::vector<float>& vectores){
        vectores.clear();
        float stepX = (xMax - xMin) / pasos;
        float stepY = (yMax - yMin) / pasos;
        for (int i = 0; i <= pasos; ++i) {
            for (int j = 0; j <= pasos; ++j) {
                float x = xMin + i * stepX;
                float y = yMin + j * stepY;
                float z = evaluarFuncion(x, y, m_funcion);

                glm::vec3 grad = gradiante(x, y, z);
                grad *= 0.3f; // Escalar el vector para mejor visualización

                glm::vec3 startPoint = glm::vec3(x, y, z);
                glm::vec3 endPoint = startPoint + grad;

                vectores.push_back(startPoint.x);
                vectores.push_back(startPoint.y);
                vectores.push_back(startPoint.z);

                vectores.push_back(endPoint.x);
                vectores.push_back(endPoint.y);
                vectores.push_back(endPoint.z);
            }
        }
    }

    glm::vec3 Entrada::gradiante(float x, float y, float z, float h) {
        float df_dx = (evaluarFuncion(x + h, y, m_funcion) - evaluarFuncion(x - h, y, m_funcion)) / (2 * h);
        float df_dy = (evaluarFuncion(x, y + h, m_funcion) - evaluarFuncion(x, y - h, m_funcion)) / (2 * h);
        float df_dz = 1.0f; // Asumiendo que z = f(x,y), la derivada parcial con respecto a z es 1

        return glm::normalize(glm::vec3(df_dx, df_dy, -df_dz));
    }
}