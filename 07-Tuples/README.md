🌐 **Català** | [Castellano](README.es.md)

# Introducció a les tuples (`struct`)

## 1. Què és una tupla?

Mentre que un `vector` agrupa valors del **mateix tipus**, una **tupla (`struct`)** agrupa dades de **tipus diferents** que juntes representen una única entitat (per exemple, una adreça postal o una persona). Cada dada dins la tupla s'anomena **camp** (o atribut).

```cpp
struct Adreca {
    string codi_postal;
    string carrer;
    int numero;
};
```

### Regles d'estil
* El nom del tipus comença per **majúscula** (`Adreca`, `Persona`, `Racional`, ...).
* Les definicions `struct` es posen just després dels `#include` i `using namespace std;`.
* **No oblidis el punt i coma `;`** després de la clau de tancament `}`!

## 2. Ús d'una tupla i composició

Accedim a cada camp amb l'operador punt (`.`):

```cpp
Adreca casa;
casa.carrer = "Diagonal";
casa.numero = 354;
casa.codi_postal = "08031";
```

Una tupla pot contenir una altra tupla com a camp, o estar dins d'un `vector`:

```cpp
struct Persona {
    string dni;
    string nom;
    Adreca adreca;      // una tupla dins d'una altra tupla
    int edat;
};

vector<Persona> cens(n);
cens[i].nom = "Anna";
cens[i].adreca.carrer = "Aragó";   // primer l'índex [i], després el camp .adreca.carrer
```

## 3. Còpia, comparació i pas a funcions

* **Assignació (`=`):** copia tots els camps automàticament (`Persona p2 = p1;`).
* **Comparació (`==`):** **no funciona directament** en tuples (`p1 == p2` dona error de compilació). Cal comparar els camps necessaris o escriure una funció booleana:
  ```cpp
  bool adreces_iguals(const Adreca& a, const Adreca& b) {
      return a.codi_postal == b.codi_postal
         and a.carrer == b.carrer
         and a.numero == b.numero;
  }
  ```
* **Paràmetres de funcions:** segueixen les mateixes regles que els vectors:
  * Entrada (només lectura): `const Persona& p`
  * Sortida / Modificació: `Persona& p`

## 4. Ordenar un vector de tuples

Com que `sort()` no sap com ordenar un `struct` propi, li passem una funció comparadora `cmp`:

```cpp
struct Producte {
    string id;
    double ingressos;
};

// Ordenar per ingressos de gran a petit; empats per id alfabèticament
bool cmp(const Producte& a, const Producte& b) {
    if (a.ingressos == b.ingressos) return a.id < b.id;
    return a.ingressos > b.ingressos;
}

// Al main:
sort(v_prod.begin(), v_prod.end(), cmp);
```

## 5. Vectors dinàmics: `push_back()` i `pop_back()`

Quan no sabem per endavant quants elements tindrà un vector:

* `v.push_back(x)`: afegeix `x` al **final** del vector (la mida creix en `1`). Cost mitjà: **$O(1)$**.
* `v.pop_back()`: elimina l'**últim** element (el vector no pot ser buit). Cost: **$O(1)$**.

```cpp
vector<int> v;        // vector buit
v.push_back(7);       // v = [7]
v.push_back(3);       // v = [7, 3]
v.pop_back();         // v = [7]
v.push_back(5);       // v = [7, 5]
```

> **Piles (*Stacks*):** Amb `push_back()` i `pop_back()`, un vector funciona com una pila (l'últim element que entra és el primer que surt).

## 6. Disseny descendent (Top-Down) amb tuples

Les tuples simplifiquen molt el disseny modular: un sol paràmetre pot transportar totes les dades d'una entitat (per exemple `struct Racional { int num; int den; };`), mantenint el `main()` i cada funció curts i clars.

```cpp
struct Racional {
    int num;
    int den;
};

// Inicialització directa dels camps en ordre:
Racional total = {0, 1};
```

## 7. Errors habituals

* **Oblidar el `;` al final de l'`struct`:** `struct Punt { double x, y; };`.
* **Intentar comparar dues tuples amb `==`:** cal comparar camp per camp.
* **Passar un `vector<Tupla>` o una tupla gran per valor** en lloc de `const &`, provocant còpies innecessàries.
* **Fer `pop_back()` en un vector buit:** provoca un error d'execució.

## 8. Idees clau

* Una tupla (`struct`) agrupa camps de tipus diferents sota un mateix tipus (`NomMajuscula`).
* Els camps s'accedeixen amb `.`, i en vectors de tuples amb `v[i].camp`.
* Per ordenar un `vector<Tupla>` amb `sort()`, escriu una funció `cmp(const Tupla& a, const Tupla& b)`.
* `push_back()` i `pop_back()` permeten fer créixer o reduir un vector al final en $O(1)$.
