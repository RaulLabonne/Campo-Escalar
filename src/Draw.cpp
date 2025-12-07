/**
 * @file Draw.cpp
 * @brief Implementación de la clase Draw.
 */

#include "../include/Draw.h"

namespace opengl {

    Draw::Draw(Compiler* compiler, Compiler* vectorCompiler, Entrada::Funciones func) : m_compiler(compiler), m_vectorCompiler(vectorCompiler) {

        /* m_vertices = {
            //   x      y      z      u     v
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // v0
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // v1
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // v2
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // v3
        };

        m_indices = {
            0, 1, 2,
            2, 3, 0
        }; */

        Entrada entrada(func);
        entrada.generarMalla(-8.0f, 8.0f,
                             -8.0f, 8.0f,
                             100,
                             m_vertices,
                             m_indices);

        entrada.generarVectores(-8.0f, 8.0f,
                             -8.0f, 8.0f,
                             40,
                             m_vectores);
    }

    void Draw::init() {
        modelmat = glm::mat4(1.0f);
            // Crear y enlazar el VAO y VBO
        
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

        // Especificar el layout del vertex shader
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
    }

    void Draw::initVectors() {
        glGenVertexArrays(1, &m_VAO_vectors);
        glGenBuffers(1, &m_VBO_vectors);

        glBindVertexArray(m_VAO_vectors);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO_vectors);
        glBufferData(GL_ARRAY_BUFFER, m_vectores.size()*sizeof(float), m_vectores.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void Draw::drawObject(glm::mat4 view, glm::mat4 projection) {
        m_compiler->use();

        m_compiler->setMat4x4("model", modelmat);
        m_compiler->setMat4x4("view", view);
        m_compiler->setMat4x4("projection", projection);

        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, m_indices.size() , GL_UNSIGNED_INT, 0);
    }

    void Draw::drawVectorArray(glm::mat4 view, glm::mat4 projection) {
        m_vectorCompiler->use();

        m_vectorCompiler->setMat4x4("model", modelmat);
        m_vectorCompiler->setMat4x4("view", view);
        m_vectorCompiler->setMat4x4("projection", projection);
        glBindVertexArray(m_VAO_vectors);
        glDrawArrays(GL_LINES, 0 , m_vectores.size());
    }

    void Draw::stop() {
        m_compiler->finish();
        delete m_compiler;

        glDeleteVertexArrays(1, &m_VAO);
        glDeleteVertexArrays(1, &m_VAO_vectors);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_VBO_vectors);
        glDeleteBuffers(1, &m_EBO);
    }


}
