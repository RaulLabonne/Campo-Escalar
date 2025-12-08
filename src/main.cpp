#include "../include/App.h"
#include <vector>
#include <iostream>

/* Metodo principal */
int main() {

    int choice;
    std::cout << "Escoja la funcion a visualizar: \n" << std::endl;
    std::cout << "0: TRIGONOMETRICA (sin(xy))" << std::endl;
    std::cout << "1: FUNCION_A (0.5 + 0.5 * sin(sqrt(x^2 + y^2)))" << std::endl;
    std::cout << "2: FUNCION_B (-x * x - y * y)" << std::endl;
    std::cin >> choice;

    // Creamos la aplicacion
    opengl::App app(choice);
    // Disfrute :DD
    return app.run();

}