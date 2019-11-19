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

### Algoritmo extendido de euclides, explicação:
Exemplos da execução do Algoritmo Estendido de Euclides.

Formato:

mdc(a,b) = s*a + t*b

mdc(221,38) =

1 = -11 * 221 + 64 * 38
mdc(221, 196) =

1 = -47 * 221 + 53 * 196
mdc(221,77) =

1 = 23 * 221 + -66 * 77
 
Por isso, temos os seguintes inversos no módulo 221:

64 é o inverso de 38

53 é o inverso de 196

155 = 221 - 66 é o inverso de 77

Para conferir se x é o inverso de a no módulo n basta verificar que xa-1 é divisível por n. Ou seja:

221 | 64 x 38 - 1 e assim por diante.



Números maiores para seus testes:

mdc(227692200981, 679269927437) = 1 e o inverso de 227692200981 no módulo 679269927437 é  176064432930.

1 = -59017036717 * 679269927437 + 176064432930 * 227692200981



mdc(404751702281, 679269927437) = 1 e o inverso de 404751702281 no módulo 679269927437 é  537666816849.

1 =  84376030417 * 679269927437 + -141603110588 * 404751702281
Por curiosidade, 679269927437 = 736091 x 922807 .