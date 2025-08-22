# BigInt

Implémentation d’un **entier arbitrairement grand** (BigInt) en C++.
La structure de base s’appuie sur un **tableau dynamique** pour représenter des nombres au-delà des limites des types natifs.

## Fichiers
- `bigint.h` — Implémentation de `BigInt`.
- `tableau.h` — Structure de tableau dynamique utilisée par `BigInt`.

## Tester / Compiler
Les commandes suivantes compilent et lancent des tests/démos (selon ton `Makefile`) :
```bash
make bint
make tableau
