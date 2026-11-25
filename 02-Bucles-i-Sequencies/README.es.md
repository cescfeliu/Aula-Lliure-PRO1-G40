🌐 [Català](README.md) | **Castellano**

# Bucles y procesamiento de secuencias

## 1. El bucle `while`

Ejecuta repetidamente un bloque de instrucciones mientras la condición booleana sea `true`:

```cpp
int i = 1;
while (i <= n) {
    cout << i << endl;
    ++i;
}
```

### Ejemplos clásicos de eficiencia con `while`
* **MCD (Algoritmo de Euclides):** la versión con módulo (`a % b`) tarda como máximo $5 \log_{10}(b)$ iteraciones, mucho más rápida que ir restando:
  ```cpp
  while (b != 0) {
      int r = a % b;
      a = b;
      b = r;
  }
  // el resultado queda en 'a'
  ```
* **Números primos:** si `n` no es primo, tiene algún divisor $\le \sqrt{n}$. Basta con comprobar `divisor * divisor <= n`:
  ```cpp
  int d = 2;
  bool es_primo = (n != 1);
  while (es_primo and d * d <= n) {
      es_primo = (n % d != 0);
      ++d;
  }
  ```

## 2. El bucle `for` y bucles anidados

El bucle `for` compacta la inicialización, la condición y la actualización en una sola línea:

```cpp
for (int i = n; i <= m; ++i) {
    cout << i << endl;
}
```

Cuando trabajamos con figuras 2D o tablas, anidamos un `for` dentro de otro:

```cpp
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) cout << '*';
    cout << endl;
}
```

## 3. Esquemas algorítmicos sobre secuencias

Casi todos los problemas sobre una secuencia de entrada (`while (cin >> x)`) pertenecen a uno de estos dos esquemas:

### Esquema de RECORRIDO (*Treat-All*)
Hay que visitar **todos** los elementos para calcular el resultado (contar, sumar, encontrar el máximo...). **El bucle no puede detenerse antes de tiempo.**

```cpp
// Ejemplo: contar cuántas veces aparece "anna"
int contador = 0;
string nombre;
while (cin >> nombre) {
    if (nombre == "anna") ++contador;
}
cout << contador << endl;
```

### Esquema de BÚSQUEDA (*Search*)
Solo queremos saber si **algún** elemento cumple una propiedad. **El bucle debe detenerse en cuanto se encuentra.**

```cpp
// Ejemplo: comprobar si aparece "pere"
bool encontrado = false;
string nombre;
while (not encontrado and cin >> nombre) {
    encontrado = (nombre == "pere");
}
cout << encontrado << endl;
```

> **Evaluación perezosa (*short-circuit*):** En `not encontrado and cin >> nombre`, cuando `encontrado` pasa a ser `true`, `not encontrado` es `false` y **no se lee ningún dato más** de `cin`.

## 4. Técnica de la ventana (*Window*)

Una **ventana** mantiene un pequeño número fijo de valores consecutivos (o un valor calculado a partir de los anteriores, como una suma acumulada) y se va **deslizando** en cada iteración.

### Ventana de 2 elementos consecutivos
```cpp
// Contar vuelos Madrid -> Barcelona en una secuencia acabada en "###"
int contador = 0;
string origen, destino;
cin >> origen >> destino;          // ventana <origen, destino>
while (destino != "###") {
    if (origen == "Madrid" and destino == "Barcelona") ++contador;
    origen = destino;              // deslizamos la ventana
    cin >> destino;
}
```

### Ventana con valor calculado
```cpp
// Busca el primer z igual a la suma de todos los anteriores
bool encontrado = false;
int suma_prev = 0;                 // la ventana guarda la suma acumulada
int z;
while (not encontrado and cin >> z) {
    if (z == suma_prev) encontrado = true;
    suma_prev += z;                // deslizamos la ventana
}
```

## 5. Secuencias de secuencias

Muchos problemas combinan un bucle exterior (un caso por cada iteración) con un bucle interior (procesando la secuencia de ese caso). Cada nivel puede ser un recorrido, una búsqueda o usar una ventana de forma independiente.

## 6. Ideas clave

* **Recorrido:** procesa todos los elementos (`while (cin >> x)`).
* **Búsqueda:** detente en cuanto encuentres lo que buscas (`while (not encontrado and cin >> x)`).
* **Ventana:** guarda el elemento anterior (o la suma/máximo hasta ahora) y actualízalo al final de cada iteración.
* Optimiza la condición del bucle cuando puedas (ej: `d * d <= n` en lugar de `d < n` para números primos).
