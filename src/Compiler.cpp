/**
 * @file Compiler.cpp
 * @brief Implementacion de la clase Compiler
 */

#include "../include/Compiler.h"

namespace opengl {

    Compiler::Compiler(const std::string& vertexPath, const std::string& fragmentPath) {
        // Compilamos los shaders de los vertices
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, loadShader(vertexPath));

        // Compilamos los shaders de los fragmentos
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, loadShader(fragmentPath));

        // Los enlazamos
        shaderProgram = linkProgram(vertexShader, fragmentShader);

        // Una vez enlazados, los shaders ya no son necesarios
        cleanUpShader(vertexShader);
        cleanUpShader(fragmentShader);
    }

    GLuint Compiler::compileShader(GLenum type, const std::string& source) {
        // Similar al ejemplo de opengl
        GLuint shader = glCreateShader(type);
        // Pasamos un string a un const char* para poder usar glShaderSource
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            return 0;
        }

        return shader;
    }

    GLuint Compiler::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
        // El shader final, similar al ejemplo de opengl
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Verificamos si no hubo algun error al enlazar
        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            return -1;
        }
        return shaderProgram;
    }

    void Compiler::cleanUpShader(GLuint shader) {
        // Cada que terminemos de usar un shader, lo limpiamos
        glDeleteShader(shader);
    }

    void Compiler::setInt(const std::string &name, int value) const {
        // Establece un valor entero en el shader de acuedo a su nombre
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }

    void Compiler::setMat4x4(const std::string &name,  const glm::mat4 &value) const{
        // Establece una matriz 4x4 en el shader de acuedo a su nombre
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
}


