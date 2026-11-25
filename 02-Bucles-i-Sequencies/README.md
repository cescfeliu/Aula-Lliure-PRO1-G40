🌐 **Català** | [Castellano](README.es.md)

# Bucles i processament de seqüències

## 1. El bucle `while`

Executa repetidament un bloc d'instruccions mentre la condició booleana sigui `true`:

```cpp
int i = 1;
while (i <= n) {
    cout << i << endl;
    ++i;
}
```

### Exemples clàssics d'eficiència amb `while`
* **MCD (Algorisme d'Euclides):** la versió amb mòdul (`a % b`) triga com a màxim $5 \log_{10}(b)$ iteracions, molt més ràpida que anar restant:
  ```cpp
  while (b != 0) {
      int r = a % b;
      a = b;
      b = r;
  }
  // el resultat queda a 'a'
  ```
* **Nombres primers:** si `n` no és primer, té algun divisor $\le \sqrt{n}$. N'hi ha prou amb comprovar `divisor * divisor <= n`:
  ```cpp
  int d = 2;
  bool es_primer = (n != 1);
  while (es_primer and d * d <= n) {
      es_primer = (n % d != 0);
      ++d;
  }
  ```

## 2. El bucle `for` i bucles imbricats

El bucle `for` compacta la inicialització, la condició i l'actualització en una sola línia:

```cpp
for (int i = n; i <= m; ++i) {
    cout << i << endl;
}
```

Quan treballem amb figures 2D o taules, imbriquem un `for` dins d'un altre:

```cpp
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) cout << '*';
    cout << endl;
}
```

## 3. Esquemes algorísmics sobre seqüències

Quasi tots els problemes sobre una seqüència d'entrada (`while (cin >> x)`) pertanyen a un d'aquests dos esquemes:

### Esquema de RECORREGUT (*Treat-All*)
Cal visitar **tots** els elements per calcular el resultat (comptar, sumar, trobar el màxim...). **El bucle no es pot aturar abans d'hora.**

```cpp
// Exemple: comptar quantes vegades apareix "anna"
int comptador = 0;
string nom;
while (cin >> nom) {
    if (nom == "anna") ++comptador;
}
cout << comptador << endl;
```

### Esquema de CERCA (*Search*)
Només volem saber si **algun** element compleix una propietat. **El bucle s'ha d'aturar tan bon punt es troba.**

```cpp
// Exemple: comprovar si apareix "pere"
bool trobat = false;
string nom;
while (not trobat and cin >> nom) {
    trobat = (nom == "pere");
}
cout << trobat << endl;
```

> **Avaluació peresosa (*short-circuit*):** En `not trobat and cin >> nom`, quan `trobat` passa a ser `true`, `not trobat` és `false` i **no es llegeix cap dada més** de `cin`.

## 4. Tècnica de la finestra (*Window*)

Una **finestra** manté un petit nombre fix de valors consecutius (o un valor calculat a partir dels anteriors, com una suma acumulada) i es va **lliscant** a cada iteració.

### Finestra de 2 elements consecutius
```cpp
// Comptar vols Madrid -> Barcelona en una seqüència acabada en "###"
int comptador = 0;
string origen, desti;
cin >> origen >> desti;          // finestra <origen, desti>
while (desti != "###") {
    if (origen == "Madrid" and desti == "Barcelona") ++comptador;
    origen = desti;              // llisquem la finestra
    cin >> desti;
}
```

### Finestra amb valor calculat
```cpp
// Cerca el primer z igual a la suma de tots els anteriors
bool trobat = false;
int suma_prev = 0;               // la finestra guarda la suma acumulada
int z;
while (not trobat and cin >> z) {
    if (z == suma_prev) trobat = true;
    suma_prev += z;              // llisquem la finestra
}
```

## 5. Seqüències de seqüències

Molts problemes combinen un bucle exterior (un cas per cada iteració) amb un bucle interior (processant la seqüència d'aquell cas). Cada nivell pot ser un recorregut, una cerca o fer servir una finestra independentment.

## 6. Idees clau

* **Recorregut:** processa tots els elements (`while (cin >> x)`).
* **Cerca:** atura't de seguida que trobis el que busques (`while (not trobat and cin >> x)`).
* **Finestra:** guarda l'element anterior (o la suma/màxim fins ara) i actualitza'l al final de cada iteració.
* Optimitza la condició del bucle quan puguis (ex: `d * d <= n` en lloc de `d < n` per a nombres primers).
