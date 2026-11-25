🌐 [Català](README.md) | **Castellano**

# Funciones y acciones (procedimientos)

## 1. ¿Qué son?

Una cápsula de código encapsula una pieza de lógica reutilizable para evitar repeticiones, mejorar la legibilidad y dividir un problema grande en partes pequeñas. En C++ distinguimos dos tipos:

* **Función:** calcula y devuelve **exactamente un valor** (`return` obligatorio).
* **Acción (procedimiento):** realiza una tarea (escribir por pantalla, modificar varias variables...) y **no devuelve ningún valor** (`void`).

### Comparativa rápida

| Característica | Función | Acción (Procedimiento) |
| :--- | :--- | :--- |
| **Tipo de retorno** | `int`, `bool`, `double`, ... | `void` |
| **Instrucción `return`** | Obligatoria | No se utiliza |
| **Número de resultados** | Exactamente uno | Ninguno, uno o varios |
| **Cómo se llama** | Dentro de una expresión (`cout << f(x);`) | Como instrucción independiente (`p(x);`) |
| **Paso de parámetros** | Por valor (o `const &` en vectores/strings) | Por valor y por referencia (`&`) |

## 2. Ejemplos básicos

### Función
```cpp
// pre: a >= 1
// post: devuelve true sii a es una potencia de 2
bool es_pot_dos(int a) {
    while (a % 2 == 0) a = a / 2;
    return a == 1;  // más limpio que: if (a == 1) return true; else return false;
}
```

### Acción (`void`)
```cpp
// pre: ---
// post: felicita en pantalla a 'nombre'
void felicitar(string nombre) {
    cout << "¡Buenos días, " << nombre << "!" << endl;
}
```

## 3. Paso de parámetros: valor vs. referencia (`&`)

Según cómo fluyen los datos entre quien llama y la función/acción:

| Rol del parámetro | Cómo se pasa | Sintaxis | Efecto |
| :--- | :--- | :--- | :--- |
| **Entrada** | Por valor | `int a` | Solo entra una **copia**. Modificar `a` dentro no afecta a la variable original. |
| **Salida / Entrada-Salida** | Por referencia | `int& a` | Canal bidireccional (**alias**). Los cambios dentro **sí** modifican la variable original. |

> **Regla en PRO1:** Los parámetros de salida y de entrada/salida (`&`) se utilizan **solo en acciones (`void`)**. Al llamar con un parámetro por referencia, hay que pasar una **variable** (no una expresión como `x + 1`).

### Ejemplos con referencia

```cpp
// Entrada/Salida: intercambia los valores de dos variables
// pre: ---
// post: a y b tienen los valores intercambiados
void intercambiar(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Entrada (a, b) y Salida (c, r): división entera
// pre: a >= 0 y b > 0
// post: c es el cociente y r el resto de a dividido por b
void division_entera(int a, int b, int& c, int& r) {
    c = a / b;
    r = a % b;
}
```

## 4. Ideas clave

* **Regla de oro:** escribe siempre las **precondiciones** (`// pre:`) y **postcondiciones** (`// post:`) como comentarios antes de cada función o acción.
* Si necesitas devolver **1 solo valor**, haz una **función**. Si necesitas **0, 2 o más**, haz una **acción (`void`)** con parámetros por referencia `&`.
* En funciones booleanas, devuelve directamente la condición (`return a == 1;`) en lugar de hacer `if (...) return true; else return false;`.
