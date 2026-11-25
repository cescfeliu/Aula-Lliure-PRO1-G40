🌐 [Català](README.md) | **Castellano**

# Introducción a los vectores

## 1. ¿Qué es un vector?

Un **vector** es un contenedor que almacena una secuencia ordenada de valores del **mismo tipo**. Permite acceder directamente a cualquier elemento mediante su posición o **índice**.

A diferencia de las variables simples, un vector nos permite guardar decenas, cientos o miles de datos bajo un mismo nombre.

Por ejemplo, un vector de 6 enteros se representa así:

```text
Valores:  |  7 | -2 | 15 |  0 |  4 |  9 |
Índices:     0    1    2    3    4    5
```

> **Importante:** En C++, las posiciones siempre empiezan a contar desde el **`0`**, no desde el `1`.

## 2. Declaración, tamaño y acceso a los elementos

Para poder utilizar vectores hay que incluir la librería `<vector>` al inicio del programa:

```cpp
#include <iostream>
#include <vector>
using namespace std;
```

### Sintaxis básica

| Operación | Sintaxis | Descripción |
| :--- | :--- | :--- |
| **Declaración** | `vector<tipo> nombre(tam);` | Crea un vector de `tam` elementos sin inicializar. |
| **Con valor inicial** | `vector<tipo> nombre(tam, val);` | Crea el vector con todas las casillas iguales a `val`. |
| **Acceso / Modificación** | `nombre[i]` | Accede al elemento de la posición `i`. |
| **Tamaño del vector** | `nombre.size()` | Devuelve cuántos elementos tiene el vector. |

Por ejemplo:

```cpp
vector<int> v(4);       // Crea un vector de 4 enteros: v[0], v[1], v[2], v[3]
v[0] = 8;               // Asigna el valor 8 a la primera posición
int n = v.size();       // n vale 4
```

> **Recomendación:** El método `v.size()` devuelve un entero sin signo (`unsigned int`), lo que puede dar problemas si haces restas o comparaciones con números negativos. Guarda siempre el tamaño en una variable entera antes de un bucle: `int n = v.size();`.

## 3. Ejemplo: frecuencia de años de nacimiento

Supongamos que leemos por la entrada una secuencia de años de nacimiento entre `1991` y `2020` y queremos saber cuánta gente nació cada año.

Sin vectores necesitaríamos 30 variables diferentes (`contador1991`, `contador1992`, etc.). Con un vector de 30 posiciones lo resolvemos haciendo corresponder cada año `y` con el índice `y - 1991`:

```text
Año:     1991   1992   1993   ...   2020
Índice:    0      1      2    ...    29
```

El código completo es el siguiente:

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    const int MIN = 1991;
    const int MAX = 2020;

    // Vector de 30 enteros inicializados a 0
    vector<int> contadores(MAX - MIN + 1, 0);

    int anio;
    while (cin >> anio) {
        ++contadores[anio - MIN];
    }

    int n = contadores.size();
    for (int i = 0; i < n; ++i) {
        cout << "Nacimientos el año " << MIN + i << ": " << contadores[i] << endl;
    }
}
```

**Para comprobar que lo has entendido:** si quisiéramos contar cuántas veces aparece cada letra minúscula (`'a'`..`'z'`) en un texto, ¿qué tamaño tendría el vector y qué índice le correspondería a una letra `c`?

## 4. Los `string` como vectores de caracteres

Si incluimos `<string>`, podemos tratar cualquier cadena de texto (`string`) exactamente igual que un `vector<char>`:

```cpp
string s = "hola";
```

```text
Caracteres: | 'h' | 'o' | 'l' | 'a' |
Índices:       0     1     2     3
```

* `s[0]` es `'h'` y `s[3]` es `'a'`.
* Para saber la longitud podemos usar tanto `s.length()` como `s.size()`.

## 5. Vectores como parámetros de funciones

Los vectores pueden ocupar mucha memoria. Si pasamos un vector **por valor** (sin `&`), C++ hace una copia entera cada vez que se llama a la función, lo que ralentiza mucho el programa.

Según el papel que tenga el vector en la función, tenemos **tres maneras** de pasarlo:

| Rol del vector | Cómo se pasa | Sintaxis | Cuándo se utiliza |
| :--- | :--- | :--- | :--- |
| **Entrada** (solo lectura) | Referencia constante | `const vector<T>& v` | **Casi siempre.** Evita copiar el vector e impide modificarlo por error. |
| **Salida / Entrada-Salida** | Referencia | `vector<T>& v` | **Frecuente.** Cuando la función debe rellenar o modificar el vector original. |
| **Entrada (copia necesaria)** | Valor | `vector<T> v` | **Muy poco frecuente.** Solo si queremos modificar una copia y devolverla sin alterar el original. |

### Ejemplo de cada caso

```cpp
// 1. Entrada (referencia constante): solo leemos los valores
int suma(const vector<int>& v) {
    int s = 0;
    int n = v.size();
    for (int i = 0; i < n; ++i) s += v[i];
    return s;
}

// 2. Salida / Modificación (referencia): alteramos el vector original
void elevar_al_cuadrado(vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n; ++i) v[i] = v[i] * v[i];
}

// 3. Copia (valor): trabajamos sobre una copia y la devolvemos
vector<int> siguientes_primos(vector<int> v) {
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        while (not es_primo(v[i])) ++v[i];
    }
    return v;
}
```

## 6. ¿Cómo resolver un ejercicio con vectores?

Cuando tengas que afrontar un problema con vectores, sigue estos pasos:

1. **Decide el tamaño y el tipo.** ¿Cuántos elementos debe guardar el vector y de qué tipo son?
2. **Vigila los límites de los índices.** Si el vector tiene tamaño `n`, tu bucle debe ir de `0` a `n - 1` (`i < n`).
3. **Elige bien los parámetros de las funciones.** Piensa si la función solo consulta el vector (`const vector<T>&`) o si lo tiene que modificar (`vector<T>&`).
4. **Diseña modularmente (Top-Down).** Divide el problema en acciones y funciones pequeñas (ej: `leer_vector`, `procesar`, `escribir_vector`) para mantener un `main()` corto y legible.

## 7. Errores habituales

### Acceder fuera de rango (*Out of bounds*)

Si un vector tiene tamaño `n`, acceder a `v[n]` o a `v[-1]` es un error grave. El último elemento válido siempre es `v[n - 1]`.

### Olvidar el `&` en parámetros de entrada

Escribir `int suma(vector<int> v)` en lugar de `int suma(const vector<int>& v)` hace que se copie todo el vector en cada llamada. En vectores grandes en Jutge.org, esto provoca un error de tiempo excedido (*Time Limit Exceeded*).

### Intentar modificar un `const vector<T>&`

Si pasas un vector como `const` y dentro escribes `v[0] = 5;`, el programa no compilará. El compilador te protege porque has prometido que no lo modificarías.

## 8. Búsqueda lineal (secuencial)

Dado un vector `v` y un valor `x`, queremos encontrar una posición `i` tal que `v[i] == x`, o devolver `-1` si `x` no está.

La **búsqueda lineal** recorre el vector elemento a elemento de izquierda a derecha:

```cpp
// pre: ---
// post: devuelve el índice i tal que v[i] == x, o -1 si x no está en v
int busqueda_lineal(const vector<int>& v, int x) {
    int n = v.size();
    int i = 0;
    // Inv: x no está en v[0..i-1]
    while (i < n and v[i] != x) ++i;
    if (i < n) return i;
    else return -1;
}
```

> **Importante (evaluación en cortocircuito):** En `i < n and v[i] != x`, si `i == n`, la segunda condición no se evalúa. Escribir `while (v[i] != x and i < n)` es un **error grave**: cuando `x` no está en el vector, accede a `v[n]` (fuera de rango).

* **Mejor caso:** `x` está en la posición `0` → `1` comprobación.
* **Peor caso:** `x` está al final o no está → `n` comprobaciones. Es un algoritmo **$O(n)$**.

## 9. Coste de los algoritmos (Notación $O$ grande)

La **complejidad temporal** mide cómo crece el número de pasos (comparaciones, accesos) en función del tamaño de la entrada `n`, quedándonos con el término dominante e ignorando constantes:

| Notación | Crecimiento | Ejemplo |
| :--- | :--- | :--- |
| $O(1)$ | Constante | Acceder a `v[i]` |
| $O(\log n)$ | Logarítmico (muy lento) | Búsqueda binaria |
| $O(n)$ | Lineal | Búsqueda lineal |
| $O(n \log n)$ | Lineal-logarítmico | `sort()` |
| $O(n^2)$ | Cuadrático | Dos bucles anidados sobre `v` |

> **Nota:** En informática, $\log n$ significa $\log_2 n$ (cuántas veces podemos dividir `n` por la mitad hasta llegar a `1`). Para $n = 1\,000\,000$, $\log_2 n \approx 20$.

## 10. Búsqueda binaria (dicotómica)

**Precondición:** el vector `v` debe estar **ordenado** de menor a mayor.

En lugar de ir uno a uno, miramos el elemento central `mid` y descartamos la mitad donde sabemos seguro que no puede estar `x`:

```cpp
// pre: v está ordenado de menor a mayor
// post: devuelve i tal que v[i] == x, o -1 si x no está en v
int busqueda_binaria(const vector<int>& v, int x) {
    int izq = 0;
    int der = int(v.size()) - 1;
    // Inv: si x está en v, está en v[izq..der]
    while (izq < der) {
        int mid = (izq + der) / 2;
        if (x > v[mid]) izq = mid + 1;  // descartamos v[izq..mid]
        else der = mid;                 // descartamos v[mid+1..der]
    }
    if (izq == der and v[izq] == x) return izq;
    else return -1;
}
```

También se puede escribir de forma **recursiva** pasando `izq` y `der` como parámetros:

```cpp
int busqueda_binaria_rec(const vector<int>& v, int x, int izq, int der) {
    if (izq > der) return -1;
    int mid = (izq + der) / 2;
    if (x > v[mid]) return busqueda_binaria_rec(v, x, mid + 1, der);
    else if (x < v[mid]) return busqueda_binaria_rec(v, x, izq, mid - 1);
    else return mid;
}
```

* Cada iteración divide la zona activa por la mitad: el coste es **$O(\log n)$**.
* En $10\,000\,000$ de elementos ordenados, la búsqueda lineal hace hasta $10\,000\,000$ de pasos; la búsqueda binaria, como máximo **24**.

## 11. Ordenación con `sort()`

Para ordenar un vector de menor a mayor hay que incluir `<algorithm>` y llamar a:

```cpp
#include <algorithm>

sort(v.begin(), v.end());
```

* Los `string` se ordenan alfabéticamente (orden lexicográfico) por defecto.
* El coste garantizado de `sort()` es **$O(n \log n)$**.

### Criterio de ordenación personalizado

Podemos pasar una función comparadora `cmp` como tercer argumento (sin paréntesis):

```cpp
// Ejemplo 1: ordenar enteros de mayor a menor
bool cmp_desc(int x, int y) {
    return x > y;
}

// Ejemplo 2: strings de más corto a más largo (y alfabéticamente en caso de empate)
bool cmp_len(const string& s1, const string& s2) {
    if (s1.length() == s2.length()) return s1 < s2;
    return s1.length() < s2.length();
}

// Uso:
sort(v.begin(), v.end(), cmp_desc);
```

### ¿Cuándo vale la pena ordenar?

* **No** ordenes para encontrar el mínimo (se hace en $O(n)$) ni para hacer **1 o pocas búsquedas** ($O(n \log n)$ es más caro que $O(n)$).
* **Sí** vale la pena ordenar cuando tienes que hacer **muchas búsquedas** ($k$ búsquedas):
  * $k$ búsquedas lineales: $\approx k \cdot n$
  * Ordenar + $k$ búsquedas binarias: $\approx n \log n + k \log n$

## 12. Ideas clave

* Un vector guarda datos homogéneos con acceso directo por índice (`0` hasta `n - 1`).
* Usa `int n = v.size();` para trabajar cómodamente con el tamaño del vector.
* Un `string` se comporta en la práctica como un `vector<char>`.
* Pasa siempre los vectores por **referencia constante** (`const vector<T>&`) a menos que tengas que modificarlos (`vector<T>&`).
* La búsqueda lineal funciona en cualquier vector en $O(n)$; la búsqueda binaria necesita el vector ordenado y cuesta $O(\log n)$.
* `sort(v.begin(), v.end())` ordena en $O(n \log n)$: ordena una vez y busca muchas veces.

## 13. Ejercicios Clase
- P14130 - Igual a l'últim (Igual al último)
- P67268 - Inversió de seqüències (Inversión de secuencias)
- P50497 - És un palíndrom? (¿Es un palíndromo?)
- P63414 - Comptant freqüències (Contando frecuencias)
- X41120 - Vector muntanyós (Vector montañoso)
- P12675 - Elements comuns (Elementos comunes)
