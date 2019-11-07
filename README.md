# Introdução a criptografia computacional

T1 de ICC Facom, 2019-2.


## Método de execução do código

gcc -o soueu soueu.c -std=99 -pedantic


Implementar o protocolo Feige-Fiat-Shamir de conhecimento zero.


### Relação de Variáveis

p, q = primos mantindos em segredo.

n = p * q

s, v = dois números tais que s² * v = 1 (mod n). Ou seja o inverso de v é resíduo quadrático de s. (v é tornado público)

r = número aleatório entre 1 e n tal que p não é múltiplo de r e q não é múltiplo de r.

x = r² (mod n), Fábio torna x público.

b = valor de bit, 0 ou 1 escolhido por Patrícia.

se b = 0, Fábio envia r.

se b = 1, Fábio envia y = r * s (mod n).

se b = 0, Patrícia verifica que r² = x (mod n), se b = 1 Patrícia verifica que v * y² = x (mod n), se o teste falhar, Patrícia rejeita a indentificação de Fábio.

Todos os valores fornecidos serão entre 0 e 2^64 - 1 (unsigned long long int em C).

Para multiplicações, por exemplo n, x, y e afins, é necessário uma varíavel de 128 bits.

s e t = Calcular tal que a*s + t*b = mdc(a, n). O inverso de a será o inteiro s. Se s for negativo ele deverá ser convertido para um inteiro equivalente positivo.
