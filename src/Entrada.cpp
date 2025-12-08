#include "../include/Entrada.h"

namespace opengl {

    float Entrada::evaluarFuncion(float x, float y) {
        // Evaluamos la función seleccionada en el punto (x, y) de acuerdo a m_funcion
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
        
        // Limpiamos los vectores de vertices e indices antes de generar la malla
        vertices.clear();
        indices.clear();

        // Variables para rastrear los valores máximos y mínimos
        float verticeMax[] = {0.0f, 0.0f};
        float verticeMin[] = {999.0f, 999.0f};
        float minZ = 999.0f;
        float maxZ = -999.0f;

        // Calculamos el tamaño de cada paso en x e y
        float stepX = (xMax - xMin) / pasos;
        float stepY = (yMax - yMin) / pasos;

        // Generamos los vertices de la malla
        for (int i = 0; i <= pasos; ++i) {
            for (int j = 0; j <= pasos; ++j) {
                // Calculamos las coordenadas (x, y) para el vértice actual
                float x = xMin + i * stepX;
                float y = yMin + j * stepY;
                // Evaluamos la función en el punto (x, y)
                float z = evaluarFuncion(x, y);

                // Actualizamos los valores máximos y mínimos de z y sus posiciones
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

                // Coordenadas de textura normalizadas
                float u = (float)i / pasos; 
                float v = (float)j / pasos;
                // Agregamos el vértice al vector (x, y, z, u, v)
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                vertices.push_back(u);
                vertices.push_back(v);
            }
        }
        // Calculamos el ancho de la malla (número de vértices en una fila)
        int ancho = pasos + 1;
        // Generamos los índices para formar triángulos
        for (int i = 0; i < pasos; ++i) {
            for (int j = 0; j < pasos; ++j) {

                // Calculamos los índices de los vértices para los dos triángulos que forman un cuadrado
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

        // Imprimimos los valores máximos y mínimos encontrados (ADVERTENCIA: Aproximaciones numéricas)
        std::cout << "Vector max en (" << verticeMax[0] << ", " << verticeMax[1] << ") con z = " << maxZ << std::endl;
        std::cout << "Vector min en (" << verticeMin[0] << ", " << verticeMin[1] << ") con z = " << minZ << std::endl;
    }
    

    void Entrada::generarVectores(float xMin, float xMax, 
                            float yMin, float yMax, 
                            int pasos,
                            std::vector<float>& vectores){
        // Limpiamos el vector de vectores antes de generarlos
        vectores.clear();

        // Calculamos el tamaño de cada paso en x e y
        float stepX = (xMax - xMin) / pasos;
        float stepY = (yMax - yMin) / pasos;

        // Generamos los vectores de gradiente de la función
        for (int i = 0; i <= pasos; ++i) {
            for (int j = 0; j <= pasos; ++j) {
                // Calculamos las coordenadas (x, y) para el vértice actual
                float x = xMin + i * stepX;
                float y = yMin + j * stepY;
                // Evaluamos la función en el punto (x, y)
                float z = evaluarFuncion(x, y);

                // Calculamos el gradiente en el punto (x, y)
                glm::vec3 grad = gradiante(x, y);
                grad *= 0.25f; // Escalamos el vector para mejor visualización

                // Creamos el vector desde (x, y, z) en la dirección del gradiente
                glm::vec3 startPoint = glm::vec3(x, y, z);
                glm::vec3 endPoint = startPoint + grad;

                // Agregamos el vector al arreglo (línea desde startPoint hasta endPoint)
                vectores.push_back(startPoint.x);
                vectores.push_back(startPoint.y);
                vectores.push_back(startPoint.z);

                vectores.push_back(endPoint.x);
                vectores.push_back(endPoint.y);
                vectores.push_back(endPoint.z);
                
                // Agregamos una cabeza de flecha simple
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

        
    }

    glm::vec3 Entrada::gradiante(float x, float y, float h) {
        // Aproximación numérica del gradiente usando diferencias centrales
        float df_dx = (evaluarFuncion(x + h, y) - evaluarFuncion(x - h, y)) / (2 * h);
        float df_dy = (evaluarFuncion(x, y + h) - evaluarFuncion(x, y - h)) / (2 * h);
        float df_dz = 1.0f; // Asumiendo que z = f(x,y), la derivada parcial con respecto a z es 1

        return glm::normalize(glm::vec3(df_dx, df_dy, -df_dz));
    }
}