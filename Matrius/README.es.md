🌐 [Català](README.md) | **Castellano**

# Introducción a las matrices

## 1. Definición de tipos con `typedef`

En C++ podemos dar un nombre nuevo a un tipo de datos con `typedef` para hacer el código más legible:

```cpp
#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Fila;
typedef vector<Fila> Matriz;
```

### Reglas de estilo
* Los nombres de tipo empiezan por **mayúscula** (`Fila`, `Matriz`, ...).
* Las definiciones `typedef` se ponen justo después de los `#include` y `using namespace std;`, separadas por una línea en blanco.

## 2. Una matriz es un vector de filas

Una matriz de enteros `m × n` (`m` filas y `n` columnas) se representa como un vector donde cada elemento es una `Fila`:

```cpp
Matriz mat(3, Fila(2));   // 3 filas, cada una una Fila de tamaño 2
```

También podemos inicializar todas las casillas a un valor concreto (por ejemplo, `0`):

```cpp
Matriz mat(3, Fila(2, 0));
```

### Tamaños y acceso a `mat`

| Operación | Expresión | Significado |
| :--- | :--- | :--- |
| **Número de filas** | `mat.size()` | Cuántas filas tiene la matriz (`m`). |
| **Número de columnas** | `mat[0].size()` | Cuántas columnas tiene la matriz (`n`). |
| **Acceso a una fila** | `mat[i]` | Devuelve la fila `i` (es de tipo `Fila`). |
| **Acceso a una casilla** | `mat[i][j]` | Elemento de la fila `i` y columna `j`. |

> **Memoria:** Una matriz cuadrada $n \times n$ guarda $n^2$ valores (espacio $O(n^2)$). Por ejemplo, una matriz de $10\,000 \times 10\,000$ enteros ocupa unos 400 MB.

## 3. Recorridos básicos y coste

Sea `mat` una matriz de `m` filas y `n` columnas ($0 \le i < m$, $0 \le j < n$):

* **Recorrer la fila `i`** — $O(n)$:
  ```cpp
  for (int j = 0; j < n; ++j) {
      // tratar mat[i][j]
  }
  ```

* **Recorrer la columna `j`** — $O(m)$:
  ```cpp
  for (int i = 0; i < m; ++i) {
      // tratar mat[i][j]
  }
  ```

* **Recorrer las diagonales (en matrices cuadradas $m = n$)** — $O(n)$:
  ```cpp
  // Diagonal principal
  for (int i = 0; i < n; ++i) {
      // tratar mat[i][i]
  }

  // Diagonal secundaria (fila + columna == n - 1)
  for (int i = 0; i < n; ++i) {
      // tratar mat[i][n - 1 - i]
  }
  ```

* **Recorrer toda la matriz** — $O(m \cdot n)$:
  ```cpp
  for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
          // tratar mat[i][j]
      }
  }
  ```

## 4. Lectura y escritura de matrices

Normalmente leemos y escribimos las matrices **fila por fila**:

```cpp
// pre: m > 0, n > 0
// post: devuelve la matriz m x n leída de la entrada
Matriz leer_matriz(int m, int n) {
    Matriz mat(m, Fila(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> mat[i][j];
    return mat;
}

// pre: mat no es vacía
// post: escribe mat fila por fila, separando los valores con un espacio
void escribir_matriz(const Matriz& mat) {
    int m = mat.size();
    int n = mat[0].size();
    for (int i = 0; i < m; ++i) {
        cout << mat[i][0];
        for (int j = 1; j < n; ++j) cout << ' ' << mat[i][j];
        cout << endl;
    }
}
```

## 5. Ejemplos prácticos

### Construir la matriz identidad

Tiene `1`s en la diagonal principal y `0`s en el resto. Podemos inicializar todo a `0` y poner los `1`s en un solo bucle:

```cpp
Matriz identidad(int n) {
    Matriz id(n, Fila(n, 0));
    for (int i = 0; i < n; ++i) id[i][i] = 1;
    return id;
}
```

### Matrices de Hankel (esquema de búsqueda en 2D)

Una matriz cuadrada $m \times m$ es de **Hankel** si todas las anti-diagonales tienen valores iguales, es decir, `mat[i][j] == mat[i-1][j+1]` para todo $1 \le i < m$ y $0 \le j < m - 1$.

Cuando encontramos un error, detenemos **ambos bucles** enseguida:

```cpp
bool es_hankel(const Matriz& mat) {
    int m = mat.size();
    bool error = false;
    int i = 1;
    while (not error and i < m) {
        int j = 0;
        while (not error and j < m - 1) {
            if (mat[i][j] != mat[i - 1][j + 1]) error = true;
            else ++j;
        }
        ++i;
    }
    return not error;
}
```

* **Peor caso:** $O(m^2)$ (si es de Hankel, revisa todas las casillas).

## 6. Diseño descendente (Top-Down) y producto de matrices

Para resolver problemas complejos, empezamos por el `main()` dividiendo el problema en subtareas y refinando cada subtarea en una función pequeña y clara.

Por ejemplo, para multiplicar una matriz $A$ ($m \times k$) por una matriz $B$ ($k \times n$), cada casilla $C[i][j]$ es el producto escalar de la fila $i$ de $A$ por la columna $j$ de $B$:

```cpp
int producto_escalar(const Matriz& a, const Matriz& b, int i, int j) {
    int k = a[0].size();
    int res = 0;
    for (int t = 0; t < k; ++t) res += a[i][t] * b[t][j];
    return res;
}

Matriz producto(const Matriz& a, const Matriz& b) {
    int m = a.size();
    int n = b[0].size();
    Matriz prod(m, Fila(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            prod[i][j] = producto_escalar(a, b, i, j);
    return prod;
}

int main() {
    int m, k, n;
    cin >> m >> k >> n;
    Matriz a = leer_matriz(m, k);
    Matriz b = leer_matriz(k, n);
    Matriz c = producto(a, b);
    escribir_matriz(c);
}
```

* **¿Por qué pasamos las matrices enteras y los índices `i`, `j`?** Porque con `const Matriz&` evitamos copiar filas o columnas en cada una de las $m \cdot n$ llamadas.
* **Coste del producto:** $m \cdot k \cdot n$ pasos. Para matrices cuadradas $n \times n$, es **$O(n^3)$**.

## 7. Errores habituales

* **Confundir filas y columnas:** `mat.size()` son las filas (`m`) y `mat[0].size()` las columnas (`n`). Comprueba siempre que $0 \le i < m$ y $0 \le j < n$.
* **Pasar matrices por valor:** Olvidar `&` en `const Matriz&` copia toda la matriz ($m \cdot n$ elementos) en cada llamada.
* **Acceder a `mat[0]` en una matriz vacía:** Si `m == 0`, `mat[0].size()` provoca un *Segmentation Fault*.

## 8. Ideas clave

* Define `typedef vector<int> Fila;` y `typedef vector<Fila> Matriz;` para escribir código claro.
* Una matriz $m \times n$ se declara con `Matriz mat(m, Fila(n));`.
* Recorrer una fila, columna o diagonal cuesta $O(n)$ o $O(m)$; recorrer toda la matriz cuesta $O(m \cdot n)$.
* Usa **diseño descendente (Top-Down)**: escribe primero el `main()` y delega cada subtarea en una función.
