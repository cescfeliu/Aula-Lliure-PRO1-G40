🌐 **Català** | [Castellano](README.es.md)

# Introducció a les matrius

## 1. Definició de tipus amb `typedef`

En C++ podem donar un nom nou a un tipus de dades amb `typedef` per fer el codi més llegible:

```cpp
#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Fila;
typedef vector<Fila> Matriu;
```

### Regles d'estil
* Els noms de tipus comencen per **majúscula** (`Fila`, `Matriu`, ...).
* Les definicions `typedef` es posen just després dels `#include` i `using namespace std;`, separades per una línia en blanc.

## 2. Una matriu és un vector de files

Una matriu d'enters `m × n` (`m` files i `n` columnes) es representa com un vector on cada element és una `Fila`:

```cpp
Matriu mat(3, Fila(2));   // 3 files, cadascuna una Fila de mida 2
```

També podem inicialitzar totes les caselles a un valor concret (per exemple, `0`):

```cpp
Matriu mat(3, Fila(2, 0));
```

### Mides i accés a `mat`

| Operació | Expressió | Significat |
| :--- | :--- | :--- |
| **Nombre de files** | `mat.size()` | Quantes files té la matriu (`m`). |
| **Nombre de columnes** | `mat[0].size()` | Quantes columnes té la matriu (`n`). |
| **Accés a una fila** | `mat[i]` | Retorna la fila `i` (és de tipus `Fila`). |
| **Accés a una casella** | `mat[i][j]` | Element de la fila `i` i columna `j`. |

> **Memòria:** Una matriu quadrada $n \times n$ guarda $n^2$ valors (espai $O(n^2)$). Per exemple, una matriu de $10\,000 \times 10\,000$ enters ocupa uns 400 MB.

## 3. Recorreguts bàsics i cost

Sigui `mat` una matriu de `m` files i `n` columnes ($0 \le i < m$, $0 \le j < n$):

* **Recórrer la fila `i`** — $O(n)$:
  ```cpp
  for (int j = 0; j < n; ++j) {
      // tractar mat[i][j]
  }
  ```

* **Recórrer la columna `j`** — $O(m)$:
  ```cpp
  for (int i = 0; i < m; ++i) {
      // tractar mat[i][j]
  }
  ```

* **Recórrer les diagonals (en matrius quadrades $m = n$)** — $O(n)$:
  ```cpp
  // Diagonal principal
  for (int i = 0; i < n; ++i) {
      // tractar mat[i][i]
  }

  // Diagonal secundària (fila + columna == n - 1)
  for (int i = 0; i < n; ++i) {
      // tractar mat[i][n - 1 - i]
  }
  ```

* **Recórrer tota la matriu** — $O(m \cdot n)$:
  ```cpp
  for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
          // tractar mat[i][j]
      }
  }
  ```

## 4. Lectura i escriptura de matrius

Normalment llegim i escrivim les matrius **fila per fila**:

```cpp
// pre: m > 0, n > 0
// post: retorna la matriu m x n llegida de l'entrada
Matriu llegir_matriu(int m, int n) {
    Matriu mat(m, Fila(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> mat[i][j];
    return mat;
}

// pre: mat no és buida
// post: escriu mat fila per fila, separant els valors amb un espai
void escriure_matriu(const Matriu& mat) {
    int m = mat.size();
    int n = mat[0].size();
    for (int i = 0; i < m; ++i) {
        cout << mat[i][0];
        for (int j = 1; j < n; ++j) cout << ' ' << mat[i][j];
        cout << endl;
    }
}
```

## 5. Exemples pràctics

### Construir la matriu identitat

Té `1`s a la diagonal principal i `0`s a la resta. Podem inicialitzar tot a `0` i posar els `1`s en un sol bucle:

```cpp
Matriu identitat(int n) {
    Matriu id(n, Fila(n, 0));
    for (int i = 0; i < n; ++i) id[i][i] = 1;
    return id;
}
```

### Matrius de Hankel (esquema de cerca en 2D)

Una matriu quadrada $m \times m$ és de **Hankel** si totes les anti-diagonals tenen valors iguals, és a dir, `mat[i][j] == mat[i-1][j+1]` per a tot $1 \le i < m$ i $0 \le j < m - 1$.

Quan trobem un error, aturem **tots dos bucles** de seguida:

```cpp
bool es_hankel(const Matriu& mat) {
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

* **Pitjor cas:** $O(m^2)$ (si és de Hankel, revisa totes les caselles).

## 6. Disseny descendent (Top-Down) i producte de matrius

Per resoldre problemes complexos, comencem pel `main()` dividint el problema en subtasques i refinant cada subtasca en una funció petita i clara.

Per exemple, per multiplicar una matriu $A$ ($m \times k$) per una matriu $B$ ($k \times n$), cada casella $C[i][j]$ és el producte escalar de la fila $i$ d'$A$ per la columna $j$ de $B$:

```cpp
int producte_escalar(const Matriu& a, const Matriu& b, int i, int j) {
    int k = a[0].size();
    int res = 0;
    for (int t = 0; t < k; ++t) res += a[i][t] * b[t][j];
    return res;
}

Matriu producte(const Matriu& a, const Matriu& b) {
    int m = a.size();
    int n = b[0].size();
    Matriu prod(m, Fila(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            prod[i][j] = producte_escalar(a, b, i, j);
    return prod;
}

int main() {
    int m, k, n;
    cin >> m >> k >> n;
    Matriu a = llegir_matriu(m, k);
    Matriu b = llegir_matriu(k, n);
    Matriu c = producte(a, b);
    escriure_matriu(c);
}
```

* **Per què passem les matrius senceres i els índexs `i`, `j`?** Perquè amb `const Matriu&` evitem copiar files o columnes a cada una de les $m \cdot n$ crides.
* **Cost del producte:** $m \cdot k \cdot n$ passos. Per a matrius quadrades $n \times n$, és **$O(n^3)$**.

## 7. Errors habituals

* **Confondre files i columnes:** `mat.size()` són les files (`m`) i `mat[0].size()` les columnes (`n`). Comprova sempre que $0 \le i < m$ i $0 \le j < n$.
* **Passar matrius per valor:** Oblidar `&` a `const Matriu&` copia tota la matriu ($m \cdot n$ elements) a cada crida.
* **Accedir a `mat[0]` en una matriu buida:** Si `m == 0`, `mat[0].size()` provoca un *Segmentation Fault*.

## 8. Idees clau

* Defineix `typedef vector<int> Fila;` i `typedef vector<Fila> Matriu;` per escriure codi clar.
* Una matriu $m \times n$ es declara amb `Matriu mat(m, Fila(n));`.
* Recórrer una fila, columna o diagonal costa $O(n)$ o $O(m)$; recórrer tota la matriu costa $O(m \cdot n)$.
* Fes servir **disseny descendent (Top-Down)**: escriu primer el `main()` i delega cada subtasca en una funció.
