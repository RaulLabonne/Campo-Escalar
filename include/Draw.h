/**
 * @file Draw.h
 * @brief Clase para manejar el dibujo de objetos en OpenGL
 */

#ifndef DRAW_H
#define DRAW_H

#include <GL/glew.h>
#include <vector>
#include "Compiler.h"
#include "Entrada.h"

namespace opengl {

/**
 * @class Draw
 * @brief Clase para manejar el dibujo de objetos en OpenGL
 */
class Draw {

private:
  Compiler* m_compiler;

  Compiler* m_vectorCompiler;

  std::vector<GLfloat> m_vertices; // Utilizamos un vector para poder manejar
                                 // cualquier cantidad de vertices
  /* Los colores que usaremos para pintar nuestro objeto */
  std::vector<GLuint> m_indices; // Similar a los vertices, un vector para manejar
                               // cualquier cantidad de colores
  std::vector<GLfloat> m_vectores;
  /* La configuracion de los vertices */
  GLuint m_VAO, m_VAO_vectors;
  /* El buffer de los vertices */
  GLuint m_VBO, m_VBO_vectors;

  GLuint m_EBO;

  glm::mat4 modelmat;

  Entrada::Funciones m_funcion;

public:
  /**
   * @brief Constructor de la clase Draw
   */
  Draw(Compiler* compiler, Compiler* vectorCompiler, Entrada::Funciones func);

  /**
   * @brief Destructor de la clase Draw
   */
  ~Draw() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
  }

  /**
   * @brief Devuelve el ID del VAO
   * @return ID del VAO
   */
  GLuint getVAO() const { return m_VAO; }

  /**
   * @brief Devuelve el ID del VBO
   * @return ID del VBO
   */
  GLuint getVBO() const { return m_VBO; }

  void init();

  void initVectors();

  /**
   * @brief Dibuja un objeto en OpenGL
   * @param count Número de vértices a dibujar
   */
  void drawObject(glm::mat4 view, glm::mat4 projection, int renderMode);

  void drawVectorArray(glm::mat4 view, glm::mat4 projection);

  void stop();
};
} // namespace opengl

#endif // DRAW_H
