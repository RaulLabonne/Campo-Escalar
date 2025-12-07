#version 410 core
in vec2 coordTex;
out vec4 FragColor;


float func(float x, float y){

    //return exp( -x*x - y*y);
    //return x * x + 3 * x * y + 2 * (y * y);
    return sin(x*y);  // se queda 
    //return 0.5 + 0.5 * sin( sqrt(x*x + y*y) ); // talvez
    

}

vec3 blancoCafe(float val) {
    val = clamp(val, 0.0, 1.0) ;

    vec3 blanco = vec3(1.0);
    vec3 cafe   = vec3(0.40, 0.26, 0.13);

    return mix(blanco, cafe, val);
}

void main() {
        // Función e^(-x*x-y*y)
        // Dominio Reales
        // Rango [0,1]

        //Definimos el dominio utilizando coordenadas de textura 
        //
        //1. (0,0) x (1,1) a (-1,-1) x (1,1) // Nuevo dominio (-8,8) x (-8,8)
        float x = coordTex.x;
        float y = coordTex.y;
        float x1 = 16.0 * x - 8.0;
        float y1 = 16.0 * y - 8.0;

        //2. Evaluamos la función
        float val = func(x1, y1) * 0.5;

        //3. Pintamos el valor Rojo cercano a 1, azul cercano a 0
        vec3 col = blancoCafe(val);

        //4. Pintamos los contornos en valores específicos
        //col = contorno(val,0.75, col);
        //col = contorno(val,0.5, col);
        //col = contorno(val,0.25, col);
   
   FragColor = vec4(col, 1.0);
}