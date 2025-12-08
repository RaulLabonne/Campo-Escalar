# Campo-Escalar

#### Alumno: Labonne Arizmendi Raul Emiliano

En este repositorio se encuentra un programa en OpenGL el cual se encarga de visualizar campos escalares y vectoriales.

## Compilacion y ejecucion del programa

Dentro del repositorio crea un [directorio](build/) `build/`. Una vez creado el directorio mencionado, nos movemos a el y debemos crear los archivos para compilar el proyecto con Make, para esto ejecute los siguientes comando:

```bash
$ cmake ..
$ make
```

Se creara un ejecutable llamado `opengl_intro`, basta con poner en terminal `./opengl_intro` para ejecutar el programa.

### Consideraciones

Al compilar es posible que suelte advertencias, esto son por como se esta implementando funciones como `keyCallBack` o en la funcion `renderObjeto` que para la clase `Ejes` no utiliza un parametro.

## Como usar el programa.

Una vez se ejecute el programa, en terminal le preguntara cual de las 3 funciones definidas le gustaria visualizar, debe escoger entre las siguientes opciones:
```bash
Escoja la funcion a visualizar: 

0: TRIGONOMETRICA (sin(xy))
1: FUNCION_A (0.5 + 0.5 * sin(sqrt(x^2 + y^2)))
2: FUNCION_B (exp(-(x^2 + y^2)))

```

Una vez seleccionado su funcion, se mostrara una imagen de dicha funcion en vista ortogonal, es posible ver alrededor del plano, al igual que hacer un acercamiento al plano con los comandos definidos. Cabe mencionar que al realizar algun comando que cambie la posicion de la camara, pasaremos a una vista de perspectiva en lugar de ortogonal, pero es posible restaurar la vista inicial.

Estos son los comandos que puede realizar en el programa:

| Tecla | Uso |
|-------|-----|
| `<ESCAPE>` | Cierra el programa |
| `<RIGHT>` | Gira la camara a la derecha |
| `<LEFT>` | Gira la camara a la izquierda |
| `<UP>` | Gira la camara hacia arriba |
| `<DOWN>` | Gira la camara hacia abajo |
| `<W>` | Realiza un acercamiento al plano|
| `<S>` | Realiza un alejamiento al plano |
| `<R>` | Reestablece la camara en vista ortogonal |
| `<1>` | Cambia a renderizado de superficie o solido |
| `<2>` | Cambia a renderizado de conjunto de lineas |