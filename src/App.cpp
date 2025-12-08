/**
 * @file App.cpp
 * @brief Implementacion de la clase App
 */

#include "../include/App.h"

namespace opengl
{

    App::~App() {
        // Terminada la ejecucion, borramos los objetos creados y terminamos GLFW
        delete m_draw;
        delete m_compiler;
        glfwTerminate();
    }

    int App::run() {

        // Inicializamos la ventana
        if (m_window.init() != 0) {
            return -1;
        }

        m_window.initViewProyection();

        m_compiler = new Compiler("../shader/escalarVert.glsl", "../shader/escalarFrag.glsl");
        m_vectorCompiler = new Compiler("../shader/vectorialVert.glsl", "../shader/vectorialFrag.glsl");
        m_draw = new Draw(m_compiler, m_vectorCompiler, m_funcion);

        // Inicializamos los buffers de vertices y colores
        m_draw->init();
        m_draw->initVectors();

        int renderMode = 0; // 0: plano, 1: malla

        // Render loop
        while (!glfwWindowShouldClose(m_window.getWindow())) {
            if (glfwGetKey(m_window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(m_window.getWindow(), true);

            glClearColor(0.0,0.0,0.0,0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            m_draw->drawObject(m_window.getView(), m_window.getProjection(), renderMode);
            m_draw->drawVectorArray(m_window.getView(), m_window.getProjection());

            // Manejo de entradas
            m_comando.updateRender(glfwGetKey(m_window.getWindow(), GLFW_KEY_1), GLFW_KEY_1, &renderMode);
            m_comando.updateRender(glfwGetKey(m_window.getWindow(), GLFW_KEY_2), GLFW_KEY_2, &renderMode);

            m_comando.updateRotation(glfwGetKey(m_window.getWindow(), GLFW_KEY_UP), GLFW_KEY_UP, &m_window);
            m_comando.updateRotation(glfwGetKey(m_window.getWindow(), GLFW_KEY_DOWN), GLFW_KEY_DOWN, &m_window);
            m_comando.updateRotation(glfwGetKey(m_window.getWindow(), GLFW_KEY_LEFT), GLFW_KEY_LEFT, &m_window);
            m_comando.updateRotation(glfwGetKey(m_window.getWindow(), GLFW_KEY_RIGHT), GLFW_KEY_RIGHT, &m_window);
            m_comando.updateRotation(glfwGetKey(m_window.getWindow(), GLFW_KEY_W), GLFW_KEY_W, &m_window);
            m_comando.updateRotation(glfwGetKey(m_window.getWindow(), GLFW_KEY_S), GLFW_KEY_S, &m_window);
            m_comando.updateRotation(glfwGetKey(m_window.getWindow(), GLFW_KEY_R), GLFW_KEY_R, &m_window);

            glfwSwapBuffers(m_window.getWindow());
            glfwPollEvents();
        }
        return 0;
    }

    void App::finish() {
        m_draw->stop();
    }
} 


