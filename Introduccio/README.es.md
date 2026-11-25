🌐 [Català](README.md) | **Castellano**

# Introducción a la programación, tipos de datos y visibilidad

## 1. Variables, literales y asignación

* Una **variable** es una caja con un nombre simbólico que guarda un valor de un tipo concreto. En C++, hay que declararla antes de usarla.
* Un **literal** es un valor constante escrito directamente en el código (por ejemplo: `-4`, `3.14159`, `true`, `'a'`, `"UPC"`).
* La **asignación** (`variable = expresion;`) evalúa la expresión de la derecha y guarda el resultado en la variable (perdiendo el valor anterior).

> **Recomendación:** Declara e inicializa las variables en el punto donde se necesitan por primera vez (`double pi = 3.14159;`).

### Intercambiar dos variables (*Swap*)

Para intercambiar `x` e `y` necesitamos una variable auxiliar:

```cpp
int z = x;
x = y;
y = z;
```

## 2. Entrada y salida básica (`cin` / `cout`)

* `cin >> variable;` lee de la entrada estándar (teclado).
* `cout << expresion;` escribe en la salida estándar (pantalla). `endl` hace un salto de línea.

```cpp
int a, b;
cin >> a >> b;
cout << "División: " << a / b << ", Resto: " << a % b << endl;
```

## 3. Instrucciones condicionales (`if` / `else`)

```cpp
if (condicion) {
    // se ejecuta si condicion es true
}
else {
    // se ejecuta si condicion es false (el bloque else es opcional)
}
```

Cuando hay varias alternativas podemos encadenar `else if`:

```cpp
if (a >= b and a >= c) m = a;
else if (b >= c) m = b;
else m = c;
```

## 4. Tipos de datos básicos en C++

Un **tipo de datos** define el conjunto de valores posibles y las operaciones que se pueden hacer con ellos:

| Tipo | Qué representa | Operadores / Notas | Ejemplo |
| :--- | :--- | :--- | :--- |
| `int` | Enteros (32 bits) | `+`, `-`, `*`, `/` (división entera), `%` (resto). Rango: $[-2^{31}, 2^{31}-1]$. | `13 / 3` → `4`, `13 % 3` → `1` |
| `double` | Reales (IEEE 754) | `+`, `-`, `*`, `/` (división real). | `13.0 / 4.0` → `3.25` |
| `bool` | Booleanos | Valores `true` / `false`. Operadores: `not`, `and`, `or`. | `(a != b) and (x > 0)` |
| `char` | Caracteres | Codificados como enteros (ASCII). Letras y dígitos son consecutivos. | `'A'`, `'z'`, `'3'` |
| `string` | Cadenas de texto | Requiere `#include <string>`. Comparación en orden lexicográfico. | `"Hola"`, `""` (vacía) |

### Operaciones útiles con `char`
Como `'a'..'z'`, `'A'..'Z'` y `'0'..'9'` tienen códigos consecutivos, podemos convertir una mayúscula en minúscula sin saber su código numérico:

```cpp
if ('A' <= c and c <= 'Z') {
    cout << char(c - 'A' + 'a') << endl;
}
```

## 5. Precedencia de operadores

De mayor a menor prioridad:

1. **Unarios:** `+`, `-`, `not`
2. **Multiplicativos:** `*`, `/`, `%`
3. **Aditivos:** `+`, `-`
4. **Desigualdades:** `>`, `>=`, `<`, `<=`
5. **Igualdades:** `==`, `!=`
6. **Conjunción:** `and`
7. **Disyunción:** `or`

> **Consejo:** En caso de duda, ¡usa paréntesis!

## 6. Conversiones de tipo

C++ realiza conversiones implícitas silenciosamente, lo que puede provocar errores sutiles (sobre todo con la división entera):

```cpp
int i = 3, j = 2;
double x;
x = i / j;          // x = 1.0  (¡división entera!)
x = double(i) / j;  // x = 1.5  (¡correcto!)
x = double(i / j);  // x = 1.0  (¡demasiado tarde!)
```

* Usa **conversiones explícitas**: `double(i)`, `char(i)`, `int('a')`.
* No dependas nunca de códigos ASCII concretos: escribe `c == 'A'`, no `c == 65`.

## 7. Visibilidad (ámbito de las variables)

* Una variable solo es visible **después de su declaración** y **dentro del bloque `{ ... }`** donde se ha declarado.
* Las variables de un bloque exterior son visibles dentro de los bloques interiores.
* Si un bloque interior declara una variable con el mismo nombre que una exterior, la interior **enmascara** (*masks*) a la exterior mientras dure el bloque.

```cpp
{
    int a = 1, b = 20;
    {
        cout << a + b << endl;  // escribe 21
        int b = 3, c = 4;       // esta b enmascara la exterior
        cout << b << endl;      // escribe 3
    }
    // c ya no existe aquí
    cout << b << endl;          // escribe 20
}
```

## 8. Ideas clave

* `int / int` siempre hace división entera; convierte un operando a `double(...)` si quieres decimales.
* `char` usa comillas simples (`'A'`) y `string` comillas dobles (`"A"`).
* Evita los números mágicos ASCII (`'A'`, no `65`).
* Declara las variables dentro del bloque más pequeño posible y justo cuando las necesites.
