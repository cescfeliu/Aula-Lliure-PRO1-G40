🌐 **Català** | [Castellano](README.es.md)

# Algorismes d'ordenació

## 1. El problema d'ordenar (*In-place*)

Volem ordenar un vector `v` de `n` elements de petit a gran. Preferim algorismes que treballin **sobre el mateix vector** (*in-place*) per estalviar memòria.

Existeixen dues grans famílies d'algorismes:
* **Algorismes simples — $O(n^2)$:** inserció, selecció i bombolla (*bubble sort*). Fàcils d'escriure, només aptes per a vectors petits.
* **Algorismes eficients — $O(n \log n)$:** *Mergesort* (ordenació per fusió), *Quicksort* i *Heapsort*. Molt més ràpids per a `n` gran.

## 2. Ordenació per inserció (*Insertion sort*)

**Idea:** Si `v[0..i-1]` ja està ordenat, inserim `v[i]` al seu lloc desplaçant cap a la dreta els elements més grans:

```cpp
// pre: ---
// post: v queda ordenat de petit a gran
void insertion_sort(vector<int>& v) {
    int n = v.size();
    // Inv: v[0..i-1] està ordenat
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

> **Vigila l'ordre a la condició:** `j > 0 and v[j - 1] > x`. Gràcies al curtcircuit de l'`and`, quan `j == 0` no s'accedeix a `v[-1]`.

* **Millor cas (vector ja ordenat):** $O(n)$ ($n - 1$ comparacions).
* **Pitjor cas (ordenat al revés):** $O(n^2)$ ($\frac{n(n-1)}{2}$ comparacions).
* És molt ràpid en vectors **quasi ordenats** (per això `sort()` el fa servir en trossos petits).

## 3. Ordenació per selecció (*Selection sort*)

**Idea:** Al pas `i`, busquem la posició `pos_min` del mínim dins `v[i..n-1]` i l'intercanviem amb `v[i]`:

```cpp
// pre: ---
// post: v queda ordenat de petit a gran
void selection_sort(vector<int>& v) {
    int n = v.size();
    // Inv: v[0..i-1] està ordenat i conté els i valors més petits de v
    for (int i = 0; i < n - 1; ++i) {
        int pos_min = i;
        for (int j = i + 1; j < n; ++j)
            if (v[j] < v[pos_min]) pos_min = j;
        swap(v[i], v[pos_min]);
    }
}
```

* **Cost:** sempre fa $\frac{n(n-1)}{2}$ comparacions (**$O(n^2)$** en tots els casos), però només $n - 1$ intercanvis (`swap`).

*(L'algorisme de **bombolla / bubble sort** també és $O(n^2)$ però sol ser més lent que el d'inserció.)*

## 4. Fusió de dos vectors ordenats (*Merge*)

Donats dos vectors ordenats `u` (mida `n`) i `v` (mida `m`), podem fusionar-los en un sol vector ordenat en **$O(n + m)$** sense tornar a ordenar: mantenim un índex `i` per `u` i un índex `j` per `v`, i anem copiant el més petit dels dos.

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

## 5. Ordenació per fusió (*Mergesort*)

**Estratègia *Divideix i venceràs* (recursiva):**
1. **Cas base:** un tros de mida 0 o 1 (`esq >= dre`) ja està ordenat.
2. **Cas recursiu:** ordena la meitat esquerra, ordena la meitat dreta i **fusiona** totes dues meitats amb `merge`.

```cpp
void merge(vector<int>& v, int esq, int mid, int dre) {
    vector<int> aux(dre - esq + 1);
    int i = esq, j = mid + 1, k = 0;
    while (i <= mid and j <= dre) {
        if (v[i] <= v[j]) { aux[k] = v[i]; ++i; }
        else { aux[k] = v[j]; ++j; }
        ++k;
    }
    while (i <= mid) { aux[k] = v[i]; ++i; ++k; }
    while (j <= dre) { aux[k] = v[j]; ++j; ++k; }
    for (int p = 0; p < int(aux.size()); ++p) v[esq + p] = aux[p];
}

void mergesort(vector<int>& v, int esq, int dre) {
    if (esq < dre) {
        int mid = (esq + dre) / 2;
        mergesort(v, esq, mid);
        mergesort(v, mid + 1, dre);
        merge(v, esq, mid, dre);
    }
}
// Crida inicial: mergesort(v, 0, int(v.size()) - 1);
```

* **Cost:** $\approx \log_2 n$ nivells i $O(n)$ passos per nivell → **$O(n \log n)$ en tots els casos**.
* **Punt feble:** necessita un vector auxiliar `aux`, per tant fa servir **$O(n)$ memòria extra**.

## 6. Comparativa resum

| Algorisme | Millor cas | Pitjor cas | Memòria extra | Quan fer-lo servir |
| :--- | :--- | :--- | :--- | :--- |
| **Inserció** | $O(n)$ | $O(n^2)$ | No | Vectors petits o quasi ordenats |
| **Selecció** | $O(n^2)$ | $O(n^2)$ | No | Vectors petits |
| **Bombolla** | $O(n^2)$ | $O(n^2)$ | No | (Millor evitar-lo) |
| **Mergesort** | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ | Vectors grans |
| **`sort()` (C++)** | $O(n \log n)$ | $O(n \log n)$ | Poca | **Quasi sempre** |

> En 1 milió d'elements, inserció pot trigar més d'un minut, mentre que *Mergesort* o `sort()` triguen **mil·lisegons**.

## 7. Idees clau

* Inserció i selecció són $O(n^2)$ i treballen *in-place*; inserció destaca quan les dades ja estan quasi ordenades.
* Fusionar dos vectors ordenats costa només $O(n + m)$.
* *Mergesort* aplica recursivitat (*divideix i venceràs*) per garantir $O(n \log n)$ sempre, a canvi de $O(n)$ memòria auxiliar.
* A la pràctica, fes servir `sort(v.begin(), v.end())`.
