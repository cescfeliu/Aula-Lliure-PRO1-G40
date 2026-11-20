# Introducción a la recursividad

## 1. ¿Qué es la recursividad?

Una **función recursiva** es una función que se llama a sí misma para resolver un problema.

La idea es dividir un problema en versiones más pequeñas del mismo problema, hasta llegar a un caso que se pueda resolver directamente.

Por ejemplo, podemos contar desde el número 5 hasta el 1 con un bucle:

```cpp
int i = 5;

while (i > 0) {
    cout << i << endl;
    i--;
}
```

También podemos hacerlo utilizando una función recursiva. En este caso, la función se llama a sí misma con un valor más pequeño.

## 2. Los dos elementos imprescindibles

Cualquier función recursiva necesita dos elementos:

### Caso base

Es la situación más sencilla del problema, aquella que podemos resolver directamente sin volver a llamar a la función. El caso base es el que permite detener la recursividad.

### Caso recursivo

Es la parte en la que la función se vuelve a llamar a sí misma, pero con un problema más pequeño o más sencillo.

| Elemento | Función |
|---|---|
| **Caso base** | Detiene la recursividad. |
| **Caso recursivo** | Reduce el problema y vuelve a llamar a la función. |

> **Importante:** si no llegamos nunca al caso base, la función continuará llamándose indefinidamente.

## 3. Ejemplo: cuenta atrás

Consideremos la siguiente función:

```cpp
void cuenta_atras(int n) {
    if (n == 0) {
        cout << "¡Final!" << endl;
    }
    else {
        cout << n << endl;
        cuenta_atras(n - 1);
    }
}
```

Si ejecutamos:

```cpp
cuenta_atras(3);
```

Obtendremos esta salida:

```text
3
2
1
¡Final!
```

El funcionamiento es el siguiente:

1. La función recibe el valor `3`.
2. Como `3` no es `0`, imprime `3`.
3. Se vuelve a llamar con el valor `2`.
4. Después se vuelve a llamar con el valor `1`.
5. Finalmente llega a `0` y ejecuta el caso base.

En este ejemplo:

- `if (n == 0)` es el **caso base**.
- `cuenta_atras(n - 1)` es la **llamada recursiva**.

## 4. Las llamadas y los retornos

Cuando una función se llama a sí misma, cada llamada queda pendiente hasta que la siguiente llamada devuelve un resultado. Estas llamadas se gestionan mediante una estructura llamada **pila de llamadas** (*call stack*).

Consideremos esta función, que calcula la suma de los números entre `1` y `n`:

```cpp
int suma(int n) {
    if (n == 0) {
        return 0;
    }
    else {
        return n + suma(n - 1);
    }
}
```

Si ejecutamos:

```cpp
cout << suma(3) << endl;
```

Las llamadas se van produciendo de la siguiente manera:

```text
suma(3)
    = 3 + suma(2)
            = 2 + suma(1)
                    = 1 + suma(0)
                            = 0
```

Cuando llegamos al caso base, las llamadas empiezan a devolver los resultados:

```text
suma(0) = 0

suma(1) = 1 + 0 = 1

suma(2) = 2 + 1 = 3

suma(3) = 3 + 3 = 6
```

Por lo tanto, `suma(3)` devuelve `6`.

La recursividad tiene dos fases:

- **Ida:** las funciones se van llamando hasta llegar al caso base.
- **Vuelta:** las funciones van devolviendo los resultados a las llamadas anteriores.

Se puede representar así:

```text
       suma(3)
          |
       suma(2)
          |
       suma(1)
          |
       suma(0)  <- CASO BASE
          |
          v
       devuelve 0
          |
       devuelve 1
          |
       devuelve 3
          |
       devuelve 6
```

**Para comprobar que lo has entendido:** ¿qué valor devuelve `suma(4)`? Puedes calcularlo siguiendo las llamadas y los retornos.

## 5. Recursividad y bucles

La recursividad y los bucles permiten repetir operaciones, pero lo hacen de maneras diferentes:

- Con un **bucle**, repetimos un conjunto de instrucciones mientras se cumple una condición.
- Con la **recursividad**, resolvemos un problema mediante la resolución de versiones más pequeñas del mismo problema.

Algunos problemas se pueden resolver tanto con bucles como con recursividad. La elección depende de la naturaleza del problema y de qué enfoque facilita más la solución.

## 6. ¿Cómo resolver un ejercicio de recursividad?

Cuando tengas que diseñar una función recursiva, sigue estos pasos:

1. **Identifica el caso base.** ¿Cuál es el caso más sencillo que puedes resolver directamente?
2. **Define el caso recursivo.** ¿Cómo puedes transformar el problema en una versión más pequeña o más sencilla?
3. **Decide qué haces con el resultado.** ¿Tienes que sumarlo, multiplicarlo, compararlo, devolverlo o utilizarlo de alguna otra manera?
4. **Comprueba que llegarás al caso base.** Cada llamada recursiva debe acercarte al caso base.

## 7. Errores habituales

### No definir el caso base

Si no hay ninguna condición que detenga las llamadas, la función continuará ejecutándose hasta que se produzca un error por exceso de llamadas recursivas.

### No reducir el problema

Por ejemplo, llamar a `suma(n)` en lugar de `suma(n - 1)` hace que la función se vuelva a llamar con el mismo valor. No hay ningún progreso hacia el caso base.

### No tener en cuenta los retornos

En una función recursiva que devuelve un valor, hay que entender qué devuelve cada llamada y cómo se utiliza este resultado en la llamada anterior.

## 8. Ideas clave

- Una función recursiva es una función que se llama a sí misma.
- Toda recursividad necesita un **caso base** y un **caso recursivo**.
- Cada llamada recursiva debe acercar el problema al caso base.
- Cuando se llega al caso base, las llamadas pendientes empiezan a devolver los resultados.

## 9. Ejercicios de clase
- P51222 - Número de dígitos recursivo
- P12509 - Factorial recursivo
- P35537 - Números crecientes
- P26041 - Girando una lista de palabras (1)
