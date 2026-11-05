# Introducció a la recursivitat

## 1. Què és la recursivitat?

Una **funció recursiva** és una funció que es crida a si mateixa per resoldre un problema.

La idea és dividir un problema en versions més petites del mateix problema, fins a arribar a un cas que es pugui resoldre directament.

Per exemple, podem comptar des del número 5 fins a l'1 amb un bucle:

```cpp
int i = 5;

while (i > 0) {
    cout << i << endl;
    i--;
}
```

També podem fer-ho utilitzant una funció recursiva. En aquest cas, la funció es crida a si mateixa amb un valor més petit.

## 2. Els dos elements imprescindibles

Qualsevol funció recursiva necessita dos elements:

### Cas base

És la situació més senzilla del problema, aquella que podem resoldre directament sense tornar a cridar la funció. El cas base és el que permet aturar la recursivitat.

### Cas recursiu

És la part en què la funció es torna a cridar a si mateixa, però amb un problema més petit o més senzill.

| Element | Funció |
|---|---|
| **Cas base** | Atura la recursivitat. |
| **Cas recursiu** | Redueix el problema i torna a cridar la funció. |

> **Important:** si no arribem mai al cas base, la funció continuarà cridant-se indefinidament.

## 3. Exemple: compte enrere

Considerem la funció següent:

```cpp
void compte_enrere(int n) {
    if (n == 0) {
        cout << "Final!" << endl;
    }
    else {
        cout << n << endl;
        compte_enrere(n - 1);
    }
}
```

Si executem:

```cpp
compte_enrere(3);
```

Obtindrem aquesta sortida:

```text
3
2
1
Final!
```

El funcionament és el següent:

1. La funció rep el valor `3`.
2. Com que `3` no és `0`, imprimeix `3`.
3. Es torna a cridar amb el valor `2`.
4. Després es torna a cridar amb el valor `1`.
5. Finalment arriba a `0` i executa el cas base.

En aquest exemple:

- `if (n == 0)` és el **cas base**.
- `compte_enrere(n - 1)` és la **crida recursiva**.

## 4. Les crides i els retorns

Quan una funció es crida a si mateixa, cada crida queda pendent fins que la crida següent retorna un resultat. Aquestes crides es gestionen mitjançant una estructura anomenada **pila de crides** (*call stack*).

Considerem aquesta funció, que calcula la suma dels nombres entre `1` i `n`:

```cpp
int suma(int n) {
    if (n == 0) {
        return 0;
    }
    else {
        return n + suma(n - 1);
    }
}
```

Si executem:

```cpp
cout << suma(3) << endl;
```

Les crides es van produint de la manera següent:

```text
suma(3)
    = 3 + suma(2)
            = 2 + suma(1)
                    = 1 + suma(0)
                            = 0
```

Quan arribem al cas base, les crides comencen a retornar els resultats:

```text
suma(0) = 0

suma(1) = 1 + 0 = 1

suma(2) = 2 + 1 = 3

suma(3) = 3 + 3 = 6
```

Per tant, `suma(3)` retorna `6`.

La recursivitat té dues fases:

- **Anada:** les funcions es van cridant fins a arribar al cas base.
- **Tornada:** les funcions van retornant els resultats a les crides anteriors.

Es pot representar així:

```text
       suma(3)
          |
       suma(2)
          |
       suma(1)
          |
       suma(0)  <- CAS BASE
          |
          v
       retorna 0
          |
       retorna 1
          |
       retorna 3
          |
       retorna 6
```

**Per comprovar que ho has entès:** quin valor retorna `suma(4)`? Pots calcular-lo seguint les crides i els retorns.

## 5. Recursivitat i bucles

La recursivitat i els bucles permeten repetir operacions, però ho fan de maneres diferents:

- Amb un **bucle**, repetim un conjunt d'instruccions mentre es compleix una condició.
- Amb la **recursivitat**, resolem un problema mitjançant la resolució de versions més petites del mateix problema.

Alguns problemes es poden resoldre tant amb bucles com amb recursivitat. L'elecció depèn de la naturalesa del problema i de quin enfocament en facilita la solució.

## 6. Com resoldre un exercici de recursivitat?

Quan hagis de dissenyar una funció recursiva, segueix aquests passos:

1. **Identifica el cas base.** Quin és el cas més senzill que pots resoldre directament?
2. **Defineix el cas recursiu.** Com pots transformar el problema en una versió més petita o més senzilla?
3. **Decideix què fas amb el resultat.** Has de sumar-lo, multiplicar-lo, comparar-lo, retornar-lo o utilitzar-lo d'alguna altra manera?
4. **Comprova que arribaràs al cas base.** Cada crida recursiva ha d'apropar-te al cas base.

## 7. Errors habituals

### No definir el cas base

Si no hi ha cap condició que aturi les crides, la funció continuarà executant-se fins que es produeixi un error per excés de crides recursives.

### No reduir el problema

Per exemple, cridar `suma(n)` en lloc de `suma(n - 1)` fa que la funció es torni a cridar amb el mateix valor. No hi ha cap progrés cap al cas base.

### No tenir en compte els retorns

En una funció recursiva que retorna un valor, cal entendre què retorna cada crida i com s'utilitza aquest resultat en la crida anterior.

## 8. Idees clau

- Una funció recursiva és una funció que es crida a si mateixa.
- Tota recursivitat necessita un **cas base** i un **cas recursiu**.
- Cada crida recursiva ha d'apropar el problema al cas base.
- Quan s'arriba al cas base, les crides pendents comencen a retornar els resultats.
