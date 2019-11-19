/*
    Celso Antonio Uliana Junior,
    Nov 2019
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define Ester 'E'
#define Fabio 'F'
#define Teodoro 'T'
#define Patricia 'P'

#define ulll __uint128_t
#define l long
#define ll long long
#define ul unsigned long
#define ull unsigned long long


/*
    UINT64_MAX 18446744073709551615ULL 
*/
#define P10_UINT64 10000000000000000000ULL   /* 19 zeroes */
#define E10_UINT64 19

#define STRINGIZER(x)   # x
#define TO_STRING(x)    STRINGIZER(x)


char comando;


/*
###############################################################################
Funções auxiliares.
###############################################################################
*/

void C(){
    printf("C\n");
}

void E(){
    printf("E\n");
}

void X(){
    printf("X\n");
}


ll extendedEuclid(ll a, ll b, ll *x, ll *y)	{
    ll t, d;
    if (b == 0)	{
        *x = 1; 
        *y = 0; 
        return a;
    }
    d = extendedEuclid(b, a % b, x, y);
    t = *x;
    *x = *y; 
    *y = t - (a / b) * (*y);
    return d;
}

ll modInverse(ll a, ll n)  {
    ll x, y;
    extendedEuclid(a, n, &x, &y);
    return (x < 0) ? (x + n) : x;
}


/*
    Função auxiliar de printar digitos de um inteiro de 128 bits sem sinal,
    retorna a quantidade de digitos em decimal desse inteiro.
*/
void print128(ulll u128){

    /*
        Maior valor definido por uma variável 64 bits sem sinal.
        definida no <inttypes.h>
    */
    if (u128 > UINT64_MAX){

        /*
            Resto da divisão com 10^19 vira um unsigned long long, que é recursivamente
            chamado para entrar no else.
        */

        ulll leading  = u128 / P10_UINT64;
        ull trailing = u128 % P10_UINT64;
        print128(leading);
        printf("%." TO_STRING(E10_UINT64) PRIu64, trailing);
    }

    else{

        ull u64 = u128;
        printf("%" PRIu64, u64);
    }
}


/*
    Gera um número random num range N(Pode não ser potencia de 2) uniformemente distrubuido.
    rand() gera um valor int entre 0...2^31 - 1(RAND_MAX)
*/

/*
ll generateRandom64(ll n) {
    /*
        Duas variáveis inteiras de 32 bits, para gerar um int x de 64 bits no range.
        0 < x < n < INT64MAX
    

    ll x;

    first = rand();
    second = rand();


    return x;
}
*/


/*
###############################################################################
Funções core do trabalho.
###############################################################################
*/

/*
    Modo Teodoro, comandos disponiveis: 
    I (Inicializar)                 Parâmetro(s): <p> <q>           | Saída: C (Sucesso) ou E (Erro)
    A (Autenticar)                  Parâmetro(s):                   | Saída: C (Sucesso) <v> <s> ou E (Erro)
    T (Terminar)                    Parâmetro(s):                   | Saída: C (Sucesso) 

*/
void doTeodoro(){

    ll n = 0;

    do{

        scanf("%c", &comando);

        if(comando == 'I'){
            l p, q;
            scanf(" %ld %ld", &p, &q);

            n = (ll) p * q;

            /*
            n = ((ulll)UINT64_MAX + 1) * 0x1234567890ABCDEFULL +
                      0xFEDCBA9876543210ULL;
            */

            //print128(n);  
            //printf("\n");

            C();
        }

        if(comando == 'A'){

            ll temp = modInverse(27, 221);

            temp = (((ll) pow(temp, 2)) % 221);  

            printf("modinverso = %lld r = %lld n = %lld", temp, 27, 221);

            /*
            if(!n)
                E();

            else{
                X();
            }
            */
        }

    } while (comando != 'T');
    
    C();
}

/*
    Modo Fábio, comandos disponiveis: 
    I (Identificar)                 Parâmetro(s): <n> <s> <v>       | Saída: C (Sucesso) ou E (Erro)
    X (Iniciar)                     Parâmetro(s):                   | Saída: C (Sucesso) <x> ou E (Erro)
    P (Preparar)                    Parâmetro(s): <r>               | Saída: C (Sucesso) <x> ou E (Erro)
    R (Responder)                   Parâmetro(s): <b>               | Saída: C (Sucesso) <xb> ou E (Erro)
    T (Terminar)                    Parâmetro(s):                   | Saída: C (Sucesso) 

*/
void doFabio(){

    ull n = 0;
    ull r = 0;
    ull s = 0;
    ull v = 0;
    ull x = 0;

    do{
        scanf("%c", &comando);

        if(comando == 'I'){

            if(n || s || v){
                E();
            }

            else{

                scanf(" %llu %llu %llu", &n, &s, &v);

                C();
            }
        }

        if(comando == 'X'){
            X();
        }

        if(comando == 'P'){

            scanf(" %llu", &r);

            if(!n)
                E();
            else{

                x = (((r % n) * (r % n)) % n);

                printf("C %llu\n", x); 
            }
        }

        if(comando == 'R'){

            int bit;
            scanf(" %d", &bit);

            if(!x){
                E();
            }

            else{
                if(bit == 0){
                    ull y = ((r * s) % n);
                    printf("C %llu\n", y);
                }
                else if(bit == 1)
                    printf("C %llu\n", r);
                else
                    E();
            }
        }

    } while (comando != 'T');

    C();
}

/*
    Modo Patrícia, comandos disponiveis: 
    I (Inicializar)                 Parâmetro(s): <n> <v> <t>       | Saída: C (Sucesso) ou E (Erro)
    Q (Receber Compromisso)         Parâmetro(s): <x>               | Saída: C (Sucesso) <b> ou E (Erro)
    V (Valida Resposta)             Parâmetro(s): <xb>              | Saída: C (Sucesso) <i> ou E (Erro)
    T (Finalizar)                   Parâmetro(s):                   | Saída: C (Sucesso) <i> <f>

*/
void doPatricia(){

    ulll n;
    ull v, t, x, xb;

    do{

        scanf("%c", &comando);

        if(comando == 'I'){
            X();
        }

        if(comando == 'Q'){
            X();
        }

        if(comando == 'V'){
            X();
        }

    } while (comando != 'T');

    C();
}

/*
    Modo Ester, comandos disponiveis: 
    I (Inicializar)                 Parâmetro(s): <n> <v>           | Saída: C (Sucesso) ou E (Erro)
    P (Preparar)                    Parâmetro(s): <b>               | Saída: C (Sucesso) <x> <xb> ou E (Erro)
    T (Terminar)                    Parâmetro(s): <xb>              | Saída: C (Sucesso)
    S (Sorte)                       Parâmetro(s): <x0> <x1)         | Saída: C (Sucesso) <s>

*/
void doEster(){

    ulll n;
    ull v, x, xb, s;

    do{

        scanf("%c", &comando);

        if(comando == 'I'){
            X();
        }

        if(comando == 'P'){
            X();
        }

        if(comando == 'S'){
            X();
        }

    } while (comando != 'T');

    C();
}

/*
###############################################################################
Seção da main.
###############################################################################
*/
int main(int argc, char **argv){

    char modo;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <modo: F | P | T | E >\n", argv[0]);
        exit(1);
    }

    modo = argv[1][0];

    switch(modo){
        case Teodoro:
            doTeodoro();
            break;

        case Fabio:
            doFabio();
            break;

        case Patricia:
            doPatricia();
            break;

        case Ester:
            doPatricia();
            break;
    }
}