/**
 * @file App.h
 * @brief Clase App para manejar la aplicación
 */

#ifndef APP_H
#define APP_H

#include "Compiler.h"
#include "Draw.h"
#include "Window.h"
#include "Entrada.h"
#include <vector>

namespace opengl {
/**
 * @class App
 * @brief Clase para manejar la aplicación
 */
class App {

private:
  /* La ventana donde dibujaremos */
  Window m_window;
  /* Compilador de los shaders */
  Compiler *m_compiler;
  Compiler *m_vectorCompiler;
  Entrada::Funciones m_funcion;
  /* Los objetos para dibujar */
  Draw *m_draw;

public:
  /**
   * @brief Constructor de la clase App
   * Inicializamos la ventana similar al ejemplo de OpenGL
   * Para el resto, solo inicializamos los objetos predeterminados
   */
  App(int n) : m_window(800, 800, "OpenGL App") {
      m_compiler = nullptr;
      m_vectorCompiler = nullptr;
      m_draw = nullptr;
      m_funcion = static_cast<Entrada::Funciones>(n);
  }

  /**
   * @brief Destructor de la clase App
   */
  ~App();

  /**
   * @brief Ejecuta la aplicación
   * @return 0 si la aplicación se ejecutó correctamente, -1 en caso contrario
   */
  int run();

  void finish();
};

} // namespace opengl

#endif // APP_H
