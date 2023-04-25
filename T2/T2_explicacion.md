# EVALUACIÓN T2 

1. Realizar un modelo jerárquico el cual tenga como mínimo 10 partes y 5 niveles. Probar los movimientos de la jerarquía (de todas las partes y niveles) con una animación. Mostrar también el uso de spotligth (moverla para ver el cono de luz dentro de la escena)

2. Realizar una animación de una escena (de mínimo 1 minuto). Debe tener en cuenta que esta debe cumplir con lo siguiente: 

    - Mostrar como mínimo 2 modelos jerárquicos, cado uno debe tener como mínimo 5 niveles en su jerarquía y debe mostrarse el movimiento en cada nivel demostrando la jerarquía; los 2 modelos jerárquicos deben ser de cosas diferentes (por ejemplo, no repetir 2 robots) 

    - Aplicar luces, como mínimo colocar 2 fuentes de luz; mostrar el uso y la aplicación en su escena de una luz direccional y puntual. 

    - Mostrar en su animación que sus fuentes de luz se pueden activar o desactivar. 

    - Mostrar un entorno de su escena dependiendo de lo que está realizando (piso, paredes, plantas, etc.) 

    - Mostrar realismo a sus modelos jerárquicos de su animación, por ejemplo, si hace un humanoide y este camina, simular el movimiento de las piernas al caminar levantando la rodilla y desplazando la pierna.

# Explicación

## Primera parte

Primero se pide un modelo jerarquico, el cual es como un conjunto de figuras las cuales estan unidas o relacionadas de alguna forma. Su principal característica es que funciona como un arbol y sirve para poder hacer movimiento, rotaciones o escalados de forma consistente.

![Modelo jerarquico 3d](https://celcliptipsprod.s3-ap-northeast-1.amazonaws.com/tips_article_body/e023/913514/774c094f0a46839ad4d33c5ce2e74da3)
Este en un ejemplo de un humanoide usando un modelo jerarquico, el cual funciona con un arbol. Aca un ejemplo:

::: mermaid
graph TD;
    Tronco-->Cabeza
    Tronco-->Brazo_Derecho
    Tronco-->Brazo_Izquierdo
    Tronco-->Pierna_Derecha
    Tronco-->Pierna_Izquierda
    Brazo_Derecho-->Ante_Brazo_Derecho-->Mano_Derecha
    Brazo_Izquierdo-->Ante_Brazo_Izquierdo-->Mano_Izquierdo
    Pierna_Derecha-->Pie_Derecho
    Pierna_Izquierda-->Pie_Izquierdo
:::

En OpenGL se trabaja de una manera similar con ayuda de `glPopMatrix()` y `glPushMatrix()`

```C++
glPushMatrix();
    graficar_Tronco();
    glPushMatrix();
        graficar_Cabeza();
        graficar_Brazo_Derecho();
        glPushMatrix();
            graficar_Ante_Brazo_Derecho();
        glPopMatrix();
        //etc
        graficar_Brazo_Izquierdo();
        graficar_Pierna_Derecha();
        graficar_Pierna_Izquierda();
    glPopMatrix();
glPopMatrix();
```
Los movimientos que se apliquen iran según el nivel del arbol, por ejemplo si mueves un brazo, el antebrazo y la mano respectiva se moverá, pero el resto de partes como una pierna o la cabeza no lo harán.
___

Para la iluminación se debe de tener en cuenta muchos parámetros pero son esenciales. Aca más información de las [luces](https://drive.google.com/drive/folders/1dYzXhQPZhvu1fu1SbSbg3_GsJZ-NsiCf)
___

Lo que se requiere como mínimo es:

- Un modelo jerarquico con mínimo 10 partes que se puede resumir en 10 figuras 3d geométricas como mínimo, como máximo el que se requiera. Tener en cuenta que para que se cuente un nivel, se debe mover esa parte individualmente

- El modelo debe contener mínimamente 5 niveles, osea que en el arbol de jerarquización, deben estar los 5 niveles como mínimo, como máximo los que se requiera igualmente.

- Todas las partes se deben mover, absolutamente todas, tanto niveles como cada figura creada.

- Incluir SpotLight o foco (osea iluminación en pocas palabras) el cual se tendrá que mover con lo que ya se conoce del OpenGL. Aclarar que se debe ver algo asi:

![Spotlight](https://enduringword.com/wp-content/uploads/2016/05/spotlight.jpg)

## Segunda parte

Se requiere de hacer lo siguiente:
- Una animación de 1 minuto como mínimo:
    - 2 modelos jerarquicos diferentes, con un mínimo de 5 niveles donde todos los niveles se muevan.
    - 2 luces o más que deben contener si o si estos tipos de luces:
        - Puntual
        - Direccional
    - Las luces colocadas se tienen que poder prender y apagar
    - Crear entorno, por ejemplo una habitación si es un humano o una obra si es una maquina de construcción.
