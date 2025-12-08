#include "../include/Entrada.h"

namespace opengl {

    float Entrada::evaluarFuncion(float x, float y) {
        switch (m_funcion) {
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
                float z = evaluarFuncion(x, y);

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

        float verticeMax[] = {0.0f, 0.0f};
        float verticeMin[] = {999.0f, 999.0f};
        float minZ = 999.0f;
        float maxZ = -999.0f;

        float stepX = (xMax - xMin) / pasos;
        float stepY = (yMax - yMin) / pasos;
        for (int i = 0; i <= pasos; ++i) {
            for (int j = 0; j <= pasos; ++j) {
                float x = xMin + i * stepX;
                float y = yMin + j * stepY;
                float z = evaluarFuncion(x, y);

                if (z > maxZ) {
                    maxZ = z;
                    verticeMax[0] = x;
                    verticeMax[1] = y;
                }
                if (z < minZ) {
                    minZ = z;
                    verticeMin[0] = x;
                    verticeMin[1] = y;
                }

                glm::vec3 grad = gradiante(x, y);
                grad *= 0.25f; // Escalar el vector para mejor visualización

                glm::vec3 startPoint = glm::vec3(x, y, z);
                glm::vec3 endPoint = startPoint + grad;

                vectores.push_back(startPoint.x);
                vectores.push_back(startPoint.y);
                vectores.push_back(startPoint.z);

                vectores.push_back(endPoint.x);
                vectores.push_back(endPoint.y);
                vectores.push_back(endPoint.z);
                
                // ---- Crear cabeza de flecha ----
                glm::vec3 dir = glm::normalize(endPoint - startPoint);

                float headSize = 0.1f;

                // Rotación simple en 2D del vector
                glm::vec3 left(
                    -dir.y,
                    dir.x,
                    dir.z
                );

                glm::vec3 right(
                    dir.y,
                    -dir.x,
                    dir.z
                );

                left  = glm::normalize(left)  * headSize;
                right = glm::normalize(right) * headSize;

                glm::vec3 headL = endPoint - dir * 0.1f + left;
                glm::vec3 headR = endPoint - dir * 0.1f + right;

                // Línea izquierda de la cabeza
                vectores.push_back(endPoint.x);
                vectores.push_back(endPoint.y);
                vectores.push_back(endPoint.z);
                vectores.push_back(headL.x);
                vectores.push_back(headL.y);
                vectores.push_back(headL.z);

                // Línea derecha de la cabeza
                vectores.push_back(endPoint.x);
                vectores.push_back(endPoint.y);
                vectores.push_back(endPoint.z);
                vectores.push_back(headR.x);
                vectores.push_back(headR.y);
                vectores.push_back(headR.z);
            }
        }

        std::cout << "Vector max en (" << verticeMax[0] << ", " << verticeMax[1] << ") con z = " << maxZ << std::endl;
        std::cout << "Vector min en (" << verticeMin[0] << ", " << verticeMin[1] << ") con z = " << minZ << std::endl;
    }

    glm::vec3 Entrada::gradiante(float x, float y, float h) {
        float df_dx = (evaluarFuncion(x + h, y) - evaluarFuncion(x - h, y)) / (2 * h);
        float df_dy = (evaluarFuncion(x, y + h) - evaluarFuncion(x, y - h)) / (2 * h);
        float df_dz = 1.0f; // Asumiendo que z = f(x,y), la derivada parcial con respecto a z es 1

        return glm::normalize(glm::vec3(df_dx, df_dy, -df_dz));
    }
}