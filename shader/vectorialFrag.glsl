#version 410 core
in vec3 fragPos;
out vec4 FragColor;


float func(float x, float y){

    //return exp( -x*x - y*y);
    //return x * x + 3 * x * y + 2 * (y * y);
    return sin(x*y);  // se queda 
    //return 0.5 + 0.5 * sin( sqrt(x*x + y*y) ); // talvez
    

}

vec3 blancoCafe(float val) {
    /* float dx = 0.8;
    float f = clamp(val, 0.0, 1.0);
    float g = (6.0 - 2.0 * dx) * f + dx;

    // Pico que crece hacia la derecha (g grande = blanco)
    float m = max(0.0, (6.0 - abs(g - 6.0)) / 6.0);

    return vec3(m); */
    float dx = 0.8;
    float f = clamp(val, 0.0, 1.0);
    float g = (6.0 - 2.0 * dx) * f + dx;

    // pico que crecía hacia la derecha
    float m = max(0.0, (6.0 - abs(g - 6.0)) / 6.0);

    // invertido: blanco → gris → negro
    float inv = 1.0 - m;

    return vec3(inv);
}

void main() {
        // Función e^(-x*x-y*y)
        // Dominio Reales
        // Rango [0,1]

        //Definimos el dominio utilizando coordenadas de textura 
        //
        //1. (0,0) x (1,1) a (-1,-1) x (1,1) // Nuevo dominio (-8,8) x (-8,8)
        float x = fragPos.x;
        float y = fragPos.y;
        /* float x1 = 16.0 * x - 8.0;
        float y1 = 16.0 * y - 8.0; */
        float x1 = x;
        float y1 = y;

        //2. Evaluamos la función
        float val = func(x1, y1);

        //3. Pintamos el valor Rojo cercano a 1, azul cercano a 0
        vec3 col = blancoCafe(val);

        //4. Pintamos los contornos en valores específicos
        //col = contorno(val,0.75, col);
        //col = contorno(val,0.5, col);
        //col = contorno(val,0.25, col);
   
   FragColor = vec4(col, 1.0);
}