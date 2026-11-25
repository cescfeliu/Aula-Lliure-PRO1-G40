🌐 **Català** | [Castellano](README.es.md)

# Introducció a la programació, tipus de dades i visibilitat

## 1. Variables, literals i assignació

* Una **variable** és una caixa amb un nom simbòlic que guarda un valor d'un tipus concret. En C++, cal declarar-la abans d'usar-la.
* Un **literal** és un valor constant escrit directament al codi (per exemple: `-4`, `3.14159`, `true`, `'a'`, `"UPC"`).
* L'**assignació** (`variable = expressio;`) avalua l'expressió de la dreta i en guarda el resultat a la variable (perdent el valor anterior).

> **Recomanació:** Declara i inicialitza les variables al punt on es necessiten per primera vegada (`double pi = 3.14159;`).

### Intercanviar dues variables (*Swap*)

Per intercanviar `x` i `y` necessitem una variable auxiliar:

```cpp
int z = x;
x = y;
y = z;
```

## 2. Entrada i sortida bàsica (`cin` / `cout`)

* `cin >> variable;` llegeix de l'entrada estàndard (teclat).
* `cout << expressio;` escriu a la sortida estàndard (pantalla). `endl` fa un salt de línia.

```cpp
int a, b;
cin >> a >> b;
cout << "Divisió: " << a / b << ", Residu: " << a % b << endl;
```

## 3. Instruccions condicionals (`if` / `else`)

```cpp
if (condicio) {
    // s'executa si condicio és true
}
else {
    // s'executa si condicio és false (el bloc else és opcional)
}
```

Quan hi ha diverses alternatives podem encadenar `else if`:

```cpp
if (a >= b and a >= c) m = a;
else if (b >= c) m = b;
else m = c;
```

## 4. Tipus de dades bàsics en C++

Un **tipus de dades** defineix el conjunt de valors possibles i les operacions que s'hi poden fer:

| Tipus | Què representa | Operadors / Notes | Exemple |
| :--- | :--- | :--- | :--- |
| `int` | Enters (32 bits) | `+`, `-`, `*`, `/` (divisió entera), `%` (residu). Rang: $[-2^{31}, 2^{31}-1]$. | `13 / 3` → `4`, `13 % 3` → `1` |
| `double` | Reals (IEEE 754) | `+`, `-`, `*`, `/` (divisió real). | `13.0 / 4.0` → `3.25` |
| `bool` | Booleans | Valors `true` / `false`. Operadors: `not`, `and`, `or`. | `(a != b) and (x > 0)` |
| `char` | Caràcters | Codificats com a enters (ASCII). Lletres i dígits són consecutius. | `'A'`, `'z'`, `'3'` |
| `string` | Cadenes de text | Requereix `#include <string>`. Comparació en ordre lexicogràfic. | `"Hola"`, `""` (buida) |

### Operacions útils amb `char`
Com que `'a'..'z'`, `'A'..'Z'` i `'0'..'9'` tenen codis consecutius, podem convertir una majúscula en minúscula sense saber el codi numèric:

```cpp
if ('A' <= c and c <= 'Z') {
    cout << char(c - 'A' + 'a') << endl;
}
```

## 5. Precedència d'operadors

De major a menor prioritat:

1. **Unaris:** `+`, `-`, `not`
2. **Multiplicatius:** `*`, `/`, `%`
3. **Additius:** `+`, `-`
4. **Desigualtats:** `>`, `>=`, `<`, `<=`
5. **Igualtats:** `==`, `!=`
6. **Conjunció:** `and`
7. **Disjunció:** `or`

> **Consell:** En cas de dubte, fes servir parèntesis!

## 6. Conversions de tipus

C++ fa conversions implícites silenciosament, cosa que pot provocar errors subtils (sobretot amb la divisió entera):

```cpp
int i = 3, j = 2;
double x;
x = i / j;          // x = 1.0  (divisió entera!)
x = double(i) / j;  // x = 1.5  (correcte!)
x = double(i / j);  // x = 1.0  (massa tard!)
```

* Fes servir **conversions explícites**: `double(i)`, `char(i)`, `int('a')`.
* No depenguis mai de codis ASCII concrets: escriu `c == 'A'`, no `c == 65`.

## 7. Visibilitat (àmbit de les variables)

* Una variable només és visible **després de la seva declaració** i **dins del bloc `{ ... }`** on s'ha declarat.
* Les variables d'un bloc exterior són visibles dins dels blocs interiors.
* Si un bloc interior declara una variable amb el mateix nom que una d'exterior, la interior **emmascara** (*masks*) l'exterior mentre duri el bloc.

```cpp
{
    int a = 1, b = 20;
    {
        cout << a + b << endl;  // escriu 21
        int b = 3, c = 4;       // aquesta b emmascara l'exterior
        cout << b << endl;      // escriu 3
    }
    // c ja no existeix aquí
    cout << b << endl;          // escriu 20
}
```

## 8. Idees clau

* `int / int` sempre fa divisió entera; converteix un operand a `double(...)` si vols decimals.
* `char` usa cometes simples (`'A'`) i `string` cometes dobles (`"A"`).
* Evita els nombres màgics ASCII (`'A'`, no `65`).
* Declara les variables dins del bloc més petit possible i just quan les necessitis.
