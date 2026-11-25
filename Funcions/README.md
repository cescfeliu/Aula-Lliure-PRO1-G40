🌐 **Català** | [Castellano](README.es.md)

# Funcions i accions (procediments)

## 1. Què són?

Una càpsula de codi encapsula una peça de lògica reutilitzable per evitar repeticions, millorar la llegibilitat i dividir un problema gran en parts petites. En C++ distingim dos tipus:

* **Funció:** calcula i retorna **exactament un valor** (`return` obligatori).
* **Acció (procediment):** fa una tasca (escriure per pantalla, modificar diverses variables...) i **no retorna cap valor** (`void`).

### Comparativa ràpida

| Característica | Funció | Acció (Procediment) |
| :--- | :--- | :--- |
| **Tipus de retorn** | `int`, `bool`, `double`, ... | `void` |
| **Instrucció `return`** | Obligatòria | No s'utilitza |
| **Nombre de resultats** | Exactament un | Cap, un o diversos |
| **Com es crida** | Dins d'una expressió (`cout << f(x);`) | Com a instrucció independent (`p(x);`) |
| **Pas de paràmetres** | Per valor (o `const &` en vectors/strings) | Per valor i per referència (`&`) |

## 2. Exemples bàsics

### Funció
```cpp
// pre: a >= 1
// post: retorna true sii a és una potència de 2
bool es_pot_dos(int a) {
    while (a % 2 == 0) a = a / 2;
    return a == 1;  // més net que: if (a == 1) return true; else return false;
}
```

### Acció (`void`)
```cpp
// pre: ---
// post: felicita en pantalla a 'nom'
void felicitar(string nom) {
    cout << "Bon dia, " << nom << "!" << endl;
}
```

## 3. Pas de paràmetres: valor vs. referència (`&`)

Segons com flueixen les dades entre qui crida i la funció/acció:

| Rol del paràmetre | Com es passa | Sintaxi | Efecte |
| :--- | :--- | :--- | :--- |
| **Entrada** | Per valor | `int a` | Només entra una **còpia**. Modificar `a` dins no afecta la variable original. |
| **Sortida / Entrada-Sortida** | Per referència | `int& a` | Canal bidireccional (**àlies**). Els canvis dins **sí** modifiquen la variable original. |

> **Regla a PRO1:** Els paràmetres de sortida i d'entrada/sortida (`&`) s'utilitzen **només en accions (`void`)**. Quan cridem amb un paràmetre per referència, cal passar una **variable** (no una expressió com `x + 1`).

### Exemples amb referència

```cpp
// Entrada/Sortida: intercanvia els valors de dues variables
// pre: ---
// post: a i b tenen els valors intercanviats
void intercanviar(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Entrada (a, b) i Sortida (c, r): divisió entera
// pre: a >= 0 i b > 0
// post: c és el quocient i r el residu d'a dividit per b
void divisio_entera(int a, int b, int& c, int& r) {
    c = a / b;
    r = a % b;
}
```

## 4. Idees clau

* **Regla d'or:** escriu sempre les **precondicions** (`// pre:`) i **postcondicions** (`// post:`) com a comentaris abans de cada funció o acció.
* Si necessites retornar **1 sol valor**, fes una **funció**. Si en necessites **0, 2 o més**, fes una **acció (`void`)** amb paràmetres per referència `&`.
* En funcions booleanes, retorna directament la condició (`return a == 1;`) en lloc de fer `if (...) return true; else return false;`.
