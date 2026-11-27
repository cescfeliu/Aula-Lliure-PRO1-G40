🌐 [Català](README.md) | **Castellano**

# Algoritmos de ordenación

## 1. El problema de ordenar (*In-place*)

Queremos ordenar un vector `v` de `n` elementos de menor a mayor. Preferimos algoritmos que trabajen **sobre el propio vector** (*in-place*) para ahorrar memoria.

Existen dos grandes familias de algoritmos:
* **Algoritmos simples — $O(n^2)$:** inserción, selección y burbuja (*bubble sort*). Fáciles de escribir, solo aptos para vectores pequeños.
* **Algoritmos eficientes — $O(n \log n)$:** *Mergesort* (ordenación por fusión), *Quicksort* y *Heapsort*. Mucho más rápidos para `n` grande.

## 2. Ordenación por inserción (*Insertion sort*)

**Idea:** Si `v[0..i-1]` ya está ordenado, insertamos `v[i]` en su sitio desplazando hacia la derecha los elementos mayores:

```cpp
// pre: ---
// post: v queda ordenado de menor a mayor
void insertion_sort(vector<int>& v) {
    int n = v.size();
    // Inv: v[0..i-1] está ordenado
    for (int i = 1; i < n; ++i) {
        int x = v[i];
        int j = i;
        while (j > 0 and v[j - 1] > x) {
            v[j] = v[j - 1];
            --j;
        }
        v[j] = x;
    }
}
```

> **Vigila el orden en la condición:** `j > 0 and v[j - 1] > x`. Gracias al cortocircuito del `and`, cuando `j == 0` no se accede a `v[-1]`.

* **Mejor caso (vector ya ordenado):** $O(n)$ ($n - 1$ comparaciones).
* **Peor caso (ordenado al revés):** $O(n^2)$ ($\frac{n(n-1)}{2}$ comparaciones).
* Es muy rápido en vectores **casi ordenados** (por eso `sort()` lo usa en trozos pequeños).

## 3. Ordenación por selección (*Selection sort*)

**Idea:** En el paso `i`, buscamos la posición `pos_min` del mínimo dentro de `v[i..n-1]` y lo intercambiamos con `v[i]`:

```cpp
// pre: ---
// post: v queda ordenado de menor a mayor
void selection_sort(vector<int>& v) {
    int n = v.size();
    // Inv: v[0..i-1] está ordenado y contiene los i valores más pequeños de v
    for (int i = 0; i < n - 1; ++i) {
        int pos_min = i;
        for (int j = i + 1; j < n; ++j)
            if (v[j] < v[pos_min]) pos_min = j;
        swap(v[i], v[pos_min]);
    }
}
```

* **Coste:** siempre hace $\frac{n(n-1)}{2}$ comparaciones (**$O(n^2)$** en todos los casos), pero solo $n - 1$ intercambios (`swap`).

*(El algoritmo de **burbuja / bubble sort** también es $O(n^2)$ pero suele ser más lento que el de inserción.)*

## 4. Fusión de dos vectores ordenados (*Merge*)

Dados dos vectores ordenados `u` (tamaño `n`) y `v` (tamaño `m`), podemos fusionarlos en un solo vector ordenado en **$O(n + m)$** sin volver a ordenar: mantenemos un índice `i` para `u` y un índice `j` para `v`, y vamos copiando el menor de los dos.

```cpp
vector<int> merge_vectors(const vector<int>& u, const vector<int>& v) {
    int n = u.size(), m = v.size();
    vector<int> res(n + m);
    int i = 0, j = 0, k = 0;
    while (i < n and j < m) {
        if (u[i] <= v[j]) { res[k] = u[i]; ++i; }
        else { res[k] = v[j]; ++j; }
        ++k;
    }
    while (i < n) { res[k] = u[i]; ++i; ++k; }
    while (j < m) { res[k] = v[j]; ++j; ++k; }
    return res;
}
```

## 5. Ordenación por fusión (*Mergesort*)

**Estrategia *Divide y vencerás* (recursiva):**
1. **Caso base:** un trozo de tamaño 0 o 1 (`izq >= der`) ya está ordenado.
2. **Caso recursivo:** ordena la mitad izquierda, ordena la mitad derecha y **fusiona** ambas mitades con `merge`.

```cpp
void merge(vector<int>& v, int izq, int mid, int der) {
    vector<int> aux(der - izq + 1);
    int i = izq, j = mid + 1, k = 0;
    while (i <= mid and j <= der) {
        if (v[i] <= v[j]) { aux[k] = v[i]; ++i; }
        else { aux[k] = v[j]; ++j; }
        ++k;
    }
    while (i <= mid) { aux[k] = v[i]; ++i; ++k; }
    while (j <= der) { aux[k] = v[j]; ++j; ++k; }
    for (int p = 0; p < int(aux.size()); ++p) v[izq + p] = aux[p];
}

void mergesort(vector<int>& v, int izq, int der) {
    if (izq < der) {
        int mid = (izq + der) / 2;
        mergesort(v, izq, mid);
        mergesort(v, mid + 1, der);
        merge(v, izq, mid, der);
    }
}
// Llamada inicial: mergesort(v, 0, int(v.size()) - 1);
```

* **Coste:** $\approx \log_2 n$ niveles y $O(n)$ pasos por nivel → **$O(n \log n)$ en todos los casos**.
* **Punto débil:** necesita un vector auxiliar `aux`, por lo que usa **$O(n)$ memoria extra**.

## 6. Comparativa resumen

| Algoritmo | Mejor caso | Peor caso | Memoria extra | Cuándo usarlo |
| :--- | :--- | :--- | :--- | :--- |
| **Inserción** | $O(n)$ | $O(n^2)$ | No | Vectores pequeños o casi ordenados |
| **Selección** | $O(n^2)$ | $O(n^2)$ | No | Vectores pequeños |
| **Burbuja** | $O(n^2)$ | $O(n^2)$ | No | (Mejor evitarlo) |
| **Mergesort** | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ | Vectores grandes |
| **`sort()` (C++)** | $O(n \log n)$ | $O(n \log n)$ | Poca | **Casi siempre** |

> En 1 millón de elementos, inserción puede tardar más de un minuto, mientras que *Mergesort* o `sort()` tardan **milisegundos**.

## 7. Ideas clave

* Inserción y selección son $O(n^2)$ y trabajan *in-place*; inserción destaca cuando los datos ya están casi ordenados.
* Fusionar dos vectores ordenados cuesta solo $O(n + m)$.
* *Mergesort* aplica recursividad (*divide y vencerás*) para garantizar $O(n \log n)$ siempre, a cambio de $O(n)$ memoria auxiliar.
* En la práctica, usa `sort(v.begin(), v.end())`.
