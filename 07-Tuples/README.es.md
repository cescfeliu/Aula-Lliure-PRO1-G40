🌐 [Català](README.md) | **Castellano**

# Introducción a las tuplas (`struct`)

## 1. ¿Qué es una tupla?

Mientras que un `vector` agrupa valores del **mismo tipo**, una **tupla (`struct`)** agrupa datos de **tipos diferentes** que juntos representan una única entidad (por ejemplo, una dirección postal o una persona). Cada dato dentro de la tupla se llama **campo** (o atributo).

```cpp
struct Direccion {
    string codigo_postal;
    string calle;
    int numero;
};
```

### Reglas de estilo
* El nombre del tipo empieza por **mayúscula** (`Direccion`, `Persona`, `Racional`, ...).
* Las definiciones `struct` se ponen justo después de los `#include` y `using namespace std;`.
* **¡No olvides el punto y coma `;`** después de la llave de cierre `}`!

## 2. Uso de una tupla y composición

Accedemos a cada campo con el operador punto (`.`):

```cpp
Direccion casa;
casa.calle = "Diagonal";
casa.numero = 354;
casa.codigo_postal = "08031";
```

Una tupla puede contener otra tupla como campo, o estar dentro de un `vector`:

```cpp
struct Persona {
    string dni;
    string nombre;
    Direccion direccion;  // una tupla dentro de otra tupla
    int edad;
};

vector<Persona> censo(n);
censo[i].nombre = "Anna";
censo[i].direccion.calle = "Aragó";  // primero el índice [i], después el campo .direccion.calle
```

## 3. Copia, comparación y paso a funciones

* **Asignación (`=`):** copia todos los campos automáticamente (`Persona p2 = p1;`).
* **Comparación (`==`):** **no funciona directamente** en tuplas (`p1 == p2` da error de compilación). Hay que comparar los campos necesarios o escribir una función booleana:
  ```cpp
  bool direcciones_iguales(const Direccion& a, const Direccion& b) {
      return a.codigo_postal == b.codigo_postal
         and a.calle == b.calle
         and a.numero == b.numero;
  }
  ```
* **Parámetros de funciones:** siguen las mismas reglas que los vectores:
  * Entrada (solo lectura): `const Persona& p`
  * Salida / Modificación: `Persona& p`

## 4. Ordenar un vector de tuplas

Como `sort()` no sabe cómo ordenar un `struct` propio, le pasamos una función comparadora `cmp`:

```cpp
struct Producto {
    string id;
    double ingresos;
};

// Ordenar por ingresos de mayor a menor; empates por id alfabéticamente
bool cmp(const Producto& a, const Producto& b) {
    if (a.ingresos == b.ingresos) return a.id < b.id;
    return a.ingresos > b.ingresos;
}

// En el main:
sort(v_prod.begin(), v_prod.end(), cmp);
```

## 5. Vectores dinámicos: `push_back()` y `pop_back()`

Cuando no sabemos de antemano cuántos elementos tendrá un vector:

* `v.push_back(x)`: añade `x` al **final** del vector (el tamaño crece en `1`). Coste promedio: **$O(1)$**.
* `v.pop_back()`: elimina el **último** elemento (el vector no puede estar vacío). Coste: **$O(1)$**.

```cpp
vector<int> v;        // vector vacío
v.push_back(7);       // v = [7]
v.push_back(3);       // v = [7, 3]
v.pop_back();         // v = [7]
v.push_back(5);       // v = [7, 5]
```

> **Pilas (*Stacks*):** Con `push_back()` y `pop_back()`, un vector funciona como una pila (el último elemento en entrar es el primero en salir).

## 6. Diseño descendente (Top-Down) con tuplas

Las tuplas simplifican mucho el diseño modular: un solo parámetro puede transportar todos los datos de una entidad (por ejemplo `struct Racional { int num; int den; };`), manteniendo el `main()` y cada función cortos y claros.

```cpp
struct Racional {
    int num;
    int den;
};

// Inicialización directa de los campos en orden:
Racional total = {0, 1};
```

## 7. Errores habituales

* **Olvidar el `;` al final del `struct`:** `struct Punto { double x, y; };`.
* **Intentar comparar dos tuplas con `==`:** hay que comparar campo a campo.
* **Pasar un `vector<Tupla>` o una tupla grande por valor** en lugar de `const &`, provocando copias innecesarias.
* **Hacer `pop_back()` en un vector vacío:** provoca un error de ejecución.

## 8. Ideas clave

* Una tupla (`struct`) agrupa campos de tipos diferentes bajo un mismo tipo (`NombreMayuscula`).
* Se accede a los campos con `.`, y en vectores de tuplas con `v[i].campo`.
* Para ordenar un `vector<Tupla>` con `sort()`, escribe una función `cmp(const Tupla& a, const Tupla& b)`.
* `push_back()` y `pop_back()` permiten hacer crecer o reducir un vector al final en $O(1)$.
