/** 
 * @file Window.h
 * @brief Clase Window para manejar la ventana de OpenGL usando GLFW.
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace opengl {
    /**
     * @class Window
     * @brief Constructor de la clase Window.
     */
    class Window {
        private:
            /* Puntero a la ventana de GLFW */
            GLFWwindow* m_window;
            /* Ancho de la ventana */
            int m_width;
            /* Alto de la ventana */
            int m_height;
            /* Título de la ventana */
            const char* m_title;

            glm::mat4 view, projection;
        public:

            /**
             * @brief Constructor de la clase Window.
             * @param width Ancho de la ventana.
             * @param height Alto de la ventana.
             * @param title Título de la ventana.
             */
            Window(int width, int height, const char* title) : m_width(width), m_height(height), m_title(title) {}

            Window() {}

            /**
             * @brief Destructor de la clase Window.
             */
            ~Window() {
                if (m_window) {
                    glfwDestroyWindow(m_window);
                }
                glfwTerminate();
            }

            /**
             * @brief Inicializa la ventana de OpenGL.
             * @return 0 si la ventana se inicializó correctamente, -1 en caso contrario.
             */
            int init();

            /**
             * @brief Devuelve el puntero a la ventana de GLFW.
             * @return Puntero a la ventana de GLFW.
             */
            GLFWwindow* getWindow() const { return m_window; }

            void initViewProyection();

            glm::mat4 getView() const { return view; }
            glm::mat4 getProjection() const { return projection; }
    };
    
}
#endif // WINDOW_H