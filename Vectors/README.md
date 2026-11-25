🌐 **Català** | [Castellano](README.es.md)

# Introducció als vectors

## 1. Què és un vector?

Un **vector** és un contenidor que emmagatzema una seqüència ordenada de valors del **mateix tipus**. Permet accedir directament a qualsevol element mitjançant la seva posició o **índex**.

A diferència de les variables simples, un vector ens permet guardar desenes, centenars o milers de dades sota un mateix nom.

Per exemple, un vector de 6 enters es representa així:

```text
Valors:   |  7 | -2 | 15 |  0 |  4 |  9 |
Índexs:      0    1    2    3    4    5
```

> **Important:** En C++, les posicions sempre comencen a comptar des del **`0`**, no des de l'`1`.

## 2. Declaració, mida i accés als elements

Per poder utilitzar vectors cal incloure la llibreria `<vector>` a l'inici del programa:

```cpp
#include <iostream>
#include <vector>
using namespace std;
```

### Sintaxi bàsica

| Operació | Sintaxi | Descripció |
| :--- | :--- | :--- |
| **Declaració** | `vector<tipus> nom(mida);` | Crea un vector de `mida` elements sense inicialitzar. |
| **Amb valor inicial** | `vector<tipus> nom(mida, val);` | Crea el vector amb totes les caselles iguals a `val`. |
| **Accés / Modificació** | `nom[i]` | Accedeix a l'element de la posició `i`. |
| **Mida del vector** | `nom.size()` | Retorna quants elements té el vector. |

Per exemple:

```cpp
vector<int> v(4);       // Crea un vector de 4 enters: v[0], v[1], v[2], v[3]
v[0] = 8;               // Assigna el valor 8 a la primera posició
int n = v.size();       // n val 4
```

> **Recomanació:** El mètode `v.size()` retorna un enter sense signe (`unsigned int`), cosa que pot donar problemes si fas restes o comparacions amb nombres negatius. Guarda sempre la mida en una variable entera abans d'un bucle: `int n = v.size();`.

## 3. Exemple: freqüència d'anys de naixement

Suposem que llegim per l'entrada una seqüència d'anys de naixement entre `1991` i `2020` i volem saber quanta gent va néixer cada any.

Sense vectors necessitaríem 30 variables diferents (`comptador1991`, `comptador1992`, etc.). Amb un vector de 30 posicions ho resolem fent correspondre cada any `y` amb l'índex `y - 1991`:

```text
Any:     1991   1992   1993   ...   2020
Índex:     0      1      2    ...    29
```

El codi complet és el següent:

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    const int MIN = 1991;
    const int MAX = 2020;

    // Vector de 30 enters inicialitzats a 0
    vector<int> comptadors(MAX - MIN + 1, 0);

    int any;
    while (cin >> any) {
        ++comptadors[any - MIN];
    }

    int n = comptadors.size();
    for (int i = 0; i < n; ++i) {
        cout << "Naixements l'any " << MIN + i << ": " << comptadors[i] << endl;
    }
}
```

**Per comprovar que ho has entès:** si volguéssim comptar quantes vegades apareix cada lletra minúscula (`'a'`..`'z'`) en un text, quina mida tindria el vector i quin índex li correspondria a una lletra `c`?

## 4. Els `string` com a vectors de caràcters

Si incloem `<string>`, podem tractar qualsevol cadena de text (`string`) exactament igual que un `vector<char>`:

```cpp
string s = "hola";
```

```text
Caràcters: | 'h' | 'o' | 'l' | 'a' |
Índexs:       0     1     2     3
```

* `s[0]` és `'h'` i `s[3]` és `'a'`.
* Per saber la longitud podem fer servir tant `s.length()` com `s.size()`.

## 5. Vectors com a paràmetres de funcions

Els vectors poden ocupar molta memòria. Si passem un vector **per valor** (sense `&`), C++ en fa una còpia sencera cada vegada que es crida la funció, fet que alenteix molt el programa.

Segons el paper que tingui el vector a la funció, tenim **tres maneres** de passar-lo:

| Rol del vector | Com es passa | Sintaxi | Quan s'utilitza |
| :--- | :--- | :--- | :--- |
| **Entrada** (només lectura) | Referència constant | `const vector<T>& v` | **Gairebé sempre.** Evita copiar el vector i impedeix modificar-lo per error. |
| **Sortida / Entrada-Sortida** | Referència | `vector<T>& v` | **Freqüent.** Quan la funció ha d'omplir o modificar el vector original. |
| **Entrada (còpia necessària)** | Valor | `vector<T> v` | **Molt poc freqüent.** Només si volem modificar una còpia i retornar-la sense alterar l'original. |

### Exemple de cada cas

```cpp
// 1. Entrada (referència constant): només llegim els valors
int suma(const vector<int>& v) {
    int s = 0;
    int n = v.size();
    for (int i = 0; i < n; ++i) s += v[i];
    return s;
}

// 2. Sortida / Modificació (referència): alterem el vector original
void elevar_al_quadrat(vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n; ++i) v[i] = v[i] * v[i];
}

// 3. Còpia (valor): treballem sobre una còpia i la retornem
vector<int> primers_seguents(vector<int> v) {
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        while (not es_primer(v[i])) ++v[i];
    }
    return v;
}
```

## 6. Com resoldre un exercici amb vectors?

Quan hagis d'afrontar un problema amb vectors, segueix aquests passos:

1. **Decideix la mida i el tipus.** Quants elements ha de guardar el vector i de quin tipus són?
2. **Vigila els límits dels índexs.** Si el vector té mida `n`, el teu bucle ha d'anar de `0` a `n - 1` (`i < n`).
3. **Tria bé els paràmetres de les funcions.** Pensa si la funció només consulta el vector (`const vector<T>&`) o si l'ha de modificar (`vector<T>&`).
4. **Dissenya modularment (Top-Down).** Divideix el problema en accions i funcions petites (ex: `llegir_vector`, `processar`, `escriure_vector`) per mantenir un `main()` curt i llegible.

## 7. Errors habituals

### Accedir fora de rang (*Out of bounds*)

Si un vector té mida `n`, accedir a `v[n]` o a `v[-1]` és un error greu. L'últim element vàlid sempre és `v[n - 1]`.

### Oblidar el `&` en paràmetres d'entrada

Escriure `int suma(vector<int> v)` en lloc de `int suma(const vector<int>& v)` fa que es copiï tot el vector a cada crida. En vectors grans al Jutge.org, això provoca un error de temps excedit (*Time Limit Exceeded*).

### Intentar modificar un `const vector<T>&`

Si passes un vector com a `const` i a dins escrius `v[0] = 5;`, el programa no compilarà. El compilador et protegeix perquè has promès que no el modificaries.

## 8. Cerca lineal (seqüencial)

Donat un vector `v` i un valor `x`, volem trobar una posició `i` tal que `v[i] == x`, o retornar `-1` si `x` no hi és.

La **cerca lineal** recorre el vector element a element d'esquerra a dreta:

```cpp
// pre: ---
// post: retorna l'índex i tal que v[i] == x, o -1 si x no és a v
int cerca_lineal(const vector<int>& v, int x) {
    int n = v.size();
    int i = 0;
    // Inv: x no és a v[0..i-1]
    while (i < n and v[i] != x) ++i;
    if (i < n) return i;
    else return -1;
}
```

> **Important (avaluació en curtcircuit):** En `i < n and v[i] != x`, si `i == n`, la segona condició no s'avalua. Escriure `while (v[i] != x and i < n)` és un **error greu**: quan `x` no és al vector, accedeix a `v[n]` (fora de rang).

* **Millor cas:** `x` és a la posició `0` → `1` comprovació.
* **Pitjor cas:** `x` és al final o no hi és → `n` comprovacions. És un algorisme **$O(n)$**.

## 9. Cost dels algorismes (Notació $O$ gran)

La **complexitat temporal** mesura com creix el nombre de passos (comparacions, accessos) en funció de la mida de l'entrada `n`, quedant-nos amb el terme dominant i ignorant constants:

| Notació | Creixement | Exemple |
| :--- | :--- | :--- |
| $O(1)$ | Constant | Accedir a `v[i]` |
| $O(\log n)$ | Logarítmic (molt lent) | Cerca binària |
| $O(n)$ | Lineal | Cerca lineal |
| $O(n \log n)$ | Lineal-logarítmic | `sort()` |
| $O(n^2)$ | Quadràtic | Dos bucles imbricats sobre `v` |

> **Nota:** En informàtica, $\log n$ significa $\log_2 n$ (quantes vegades podem dividir `n` per la meitat fins arribar a `1`). Per a $n = 1\,000\,000$, $\log_2 n \approx 20$.

## 10. Cerca binària (dicotòmica)

**Precondició:** el vector `v` ha d'estar **ordenat** de petit a gran.

En lloc d'anar d'un en un, mirem l'element del mig `mid` i descartem la meitat on sabem segur que no pot ser `x`:

```cpp
// pre: v està ordenat de petit a gran
// post: retorna i tal que v[i] == x, o -1 si x no és a v
int cerca_binaria(const vector<int>& v, int x) {
    int esq = 0;
    int dre = int(v.size()) - 1;
    // Inv: si x és a v, és dins de v[esq..dre]
    while (esq < dre) {
        int mid = (esq + dre) / 2;
        if (x > v[mid]) esq = mid + 1;  // descartem v[esq..mid]
        else dre = mid;                 // descartem v[mid+1..dre]
    }
    if (esq == dre and v[esq] == x) return esq;
    else return -1;
}
```

També es pot escriure de manera **recursiva** passant `esq` i `dre` com a paràmetres:

```cpp
int cerca_binaria_rec(const vector<int>& v, int x, int esq, int dre) {
    if (esq > dre) return -1;
    int mid = (esq + dre) / 2;
    if (x > v[mid]) return cerca_binaria_rec(v, x, mid + 1, dre);
    else if (x < v[mid]) return cerca_binaria_rec(v, x, esq, mid - 1);
    else return mid;
}
```

* Cada iteració divideix la zona activa per la meitat: el cost és **$O(\log n)$**.
* En $10\,000\,000$ d'elements ordenats, la cerca lineal fa fins a $10\,000\,000$ de passos; la cerca binària, com a màxim **24**.

## 11. Ordenació amb `sort()`

Per ordenar un vector de petit a gran cal incloure `<algorithm>` i cridar:

```cpp
#include <algorithm>

sort(v.begin(), v.end());
```

* Els `string` s'ordenen alfabèticament (ordre lexicogràfic) per defecte.
* El cost garantit de `sort()` és **$O(n \log n)$**.

### Criteri d'ordenació personalitzat

Podem passar una funció comparadora `cmp` com a tercer argument (sense parèntesis):

```cpp
// Exemple 1: ordenar enters de gran a petit
bool cmp_desc(int x, int y) {
    return x > y;
}

// Exemple 2: strings de més curt a més llarg (i alfabèticament en cas d'empat)
bool cmp_len(const string& s1, const string& s2) {
    if (s1.length() == s2.length()) return s1 < s2;
    return s1.length() < s2.length();
}

// Ús:
sort(v.begin(), v.end(), cmp_desc);
```

### Quan val la pena ordenar?

* **No** ordenis per trobar el mínim (es fa en $O(n)$) ni per fer **1 o poques cerques** ($O(n \log n)$ és més car que $O(n)$).
* **Sí** val la pena ordenar quan has de fer **moltes cerques** ($k$ cerques):
  * $k$ cerques lineals: $\approx k \cdot n$
  * Ordenar + $k$ cerques binàries: $\approx n \log n + k \log n$

## 12. Idees clau

* Un vector guarda dades homogènies amb accés directe per índex (`0` fins a `n - 1`).
* Fes servir `int n = v.size();` per treballar còmodament amb la mida del vector.
* Un `string` es comporta a la pràctica com un `vector<char>`.
* Passa sempre els vectors per **referència constant** (`const vector<T>&`) tret que els hagis de modificar (`vector<T>&`).
* La cerca lineal funciona en qualsevol vector en $O(n)$; la cerca binària necessita el vector ordenat i costa $O(\log n)$.
* `sort(v.begin(), v.end())` ordena en $O(n \log n)$: ordena una vegada i cerca moltes vegades.

## 13. Exercicis Classe
- P14130 - Igual a l'últim
- P67268 - Inversió de seqüències
- P50497 - És un palíndrom?
- P63414 - Comptant freqüències
- X41120 - Vector muntanyós
- P12675 - Elements comuns
