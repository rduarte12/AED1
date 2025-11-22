# BigInt — Biblioteca de inteiros grandes (blocos de 3 dígitos)

Resumo
- Implementação em C de números inteiros arbitrariamente grandes usando uma lista duplamente encadeada.
- Dígitos armazenados em blocos de 3 (centena, dezena, unidade) por nó, podendo ser positivo ou negativo.

Design e Convenções
- Estruturas (opacas no header):
  - `BigInt` (definição interna em BigInt.c): possui `start`, `end`, `size`, `sinal`.
  - `Node` (definição interna): `unidade`, `dezena`, `centena`, `numDigitos`, `next`, `prev`.
- Ordem e direção:
  - `start` = bloco menos-significativo (LSB).
  - `end` = bloco mais-significativo (MSB).
  - `next` navega do menos-significativo para o mais-significativo.
  - `prev` navega do mais-significativo para o menos-significativo.
- Sinal: armazenado apenas em `BigInt->sinal` (`'+'` ou `'-'`).

Funções públicas (prototipadas em BigInt.h)

- BigInt* createBigInt(char* str);
- void freeBigInt(BigInt* bigInt);
- void printBigInt(const BigInt* bigInt);
- int isGreaterThan(const BigInt* a, const BigInt* b);
- int isLessThan(const BigInt* a, const BigInt* b);
- int isEqualTo(const BigInt* a, const BigInt* b);
- BigInt* addBigInt(BigInt* a, BigInt* b);
- BigInt* subtractBigInt(BigInt* a, BigInt* b);

Funções e retornos no arquivo .h

