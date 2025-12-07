#version 410 core
in vec2 coordTex;
out vec4 FragColor;
uniform int funcion;

float func(float x, float y){

    switch(funcion){
        case 0:
            return sin(x*y);  // se queda 
        case 1:
            return 0.5 + 0.5 * sin( sqrt(x*x + y*y) ); // talvez
        default:
            return exp(-(x * x + y * y));
    }
    //return exp( -x*x - y*y);
    //return x * x + 3 * x * y + 2 * (y * y);
    

}

vec3 arcoiris(float val){

    float dx = 0.8;
    float f = clamp(val,0,1);
    float g = (6.0 - 2.0*dx) * f + dx;
    vec3 color = vec3(1.0);
    color.r = max(0,(3.0- abs(g-4.0) - abs(g-5.0)) / 2.0);
    color.g = max(0,(4.0- abs(g-2.0) - abs(g-4.0)) / 2.0);
    color.b = max(0,(3.0- abs(g-1.0) - abs(g-2.0)) / 2.0);
    return color;
}

vec3 contorno(float val, float val_cont ,vec3 col){
    float epsilon = 0.001;
    if( val_cont - epsilon <= val  &&  val <= val_cont + epsilon)
       return vec3(0.0);
    return col;
}

void main()
{
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
        float val = func(x1, y1);

        //3. Pintamos el valor Rojo cercano a 1, azul cercano a 0
        vec3 col = arcoiris(val);

        //4. Pintamos los contornos en valores específicos
        //col = contorno(val,0.75, col);
        //col = contorno(val,0.5, col);
        //col = contorno(val,0.25, col);
   
   FragColor = vec4(col, 1.0);
}