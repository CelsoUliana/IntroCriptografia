/*
    Celso Antonio Uliana Junior,
    Nov 2019
*/

#include <math.h>
#include <time.h> 
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


ulll extendedEuclid(ulll a, ulll b, ulll *x, ulll *y)	{
    ulll t, d;
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

ulll modInverse(ulll a, ulll n)  {
    ulll x, y;
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
            Resto da divisão com 10^19 cabe em um unsigned long long, que é recursivamente
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
        printf("\n");
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
    I (Inicializar)                 Parâmetro(s): <p> <q>           | Saída: C (Sucesso) <n> ou E (Erro)
    A (Autenticar)                  Parâmetro(s):                   | Saída: C (Sucesso) <v> <s> ou E (Erro)
    T (Terminar)                    Parâmetro(s):                   | Saída: C (Sucesso) 

*/
void doTeodoro(){

    ull n = 0;

    do{

        scanf("%c", &comando);

        if(comando == 'I'){
            // Done.
            ll p, q;
            scanf(" %lld %lld", &p, &q);

            n = (ull) p * q;

            printf("C %llu\n", n);

            /*
            n = ((ulll)UINT64_MAX + 1) * 0x1234567890ABCDEFULL +
                      0xFEDCBA9876543210ULL;
            */

            //print128(n);  
            //printf("\n");
        }

        if(comando == 'A'){
            // Not done.
            if(!n)
                E();

            else{
                X();
            }
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

    ulll n = 0;
    ulll r = 0;
    ull s = 0;
    ull v = 0;
    ulll x = 0;
    int flag = 0;

    do{
        scanf("%c", &comando);

        if(comando == 'I'){

            // Done.

            if(s || v){
                E();
            }

            else{
                ull temp;
                scanf(" %llu %llu %llu", &temp, &s, &v);
                n = temp;

                if(n < s || v > n || 2 > n)
                    E();
                else
                    C();
            }
        }

        if(comando == 'X'){
            // Not done.
            X();
        }

        if(comando == 'P'){
            
            // Done(?).

            ull temp;
            scanf(" %llu", &temp);
            r = temp;

            if(!n || r > n)
                E();
            else{

                x = (r * r) % n;
                printf("C ");
                print128(x);
                flag = 1;
                //printf("C %llu\n", x); 
            }
        }

        if(comando == 'R'){
            // Not done.
            int bit;
            scanf(" %d", &bit);

            if(!x){
                E();
            }

            else{
                if(bit == 1 && flag){
                    ulll y = ((r * s) % n);
                    printf("C ");
                    print128(y);
                    flag = 0;
                }
                else if(bit == 0 && flag){
                    printf("C ");
                    print128(r);
                    flag = 0;
                }
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

    ull v = 0;
    ull x = 0;
    ulll n = 0;
    ull xb = 0;

    int globalt, t = 0;
    int bit, flag = 0;

    do{

        scanf("%c", &comando);

        if(comando == 'I'){
            //Done.
            ull temp;
            scanf(" %llu %llu %d", &temp, &v, &globalt);
            t = globalt;
            n = temp;

            if(v > n || t > n)
                E();
            else
                C();
        }

        if(comando == 'Q'){

            //Done.
            if(flag)
                E();
            else{
                scanf(" %llu", &x);
                bit = (rand() % 2);

                printf("C %d\n", bit);
                flag = 1;
            }
        }

        if(comando == 'V'){
            //Not done.
            scanf(" %llu", &xb);

            //Realmente validar o breguete.

            t--;

            if(!t)
                E();
            else{

                if(bit){
                    ulll y = xb;
                    ulll tempv = v;
                    ulll temp = ((y * y) * v) % n;
                    if(temp == x)
                        printf("C %d\n", t);
                    else{
                        printf("E %d\n", t);
                        t = globalt;
                    }
                }

                else{
                    // xb == r
                    ulll r = xb;
                    ulll temp = (r * r) % n;
                    if(temp == x)
                        printf("C %d\n", t);
                    else{
                        printf("E %d\n", t);
                        t = globalt;
                    }
                }

                flag = 0;
            }
        }

        if(comando == 'C'){
            ulll x, xb;
            int localbit;
            ull tempx, tempxb;
            scanf(" %llu %d %llu", &tempx, &localbit, &tempxb);

            x = tempx;
            xb = tempxb;

            if(!t)
                printf("E %d\n", t);
            else{

                if(localbit){

                    ulll y = xb;
                    ulll tempv = v;
                    ulll temp = ((y * y) * v) % n;

                    if(temp == x){
                        t--;
                        printf("C %d\n", t);
                    }
                    else{
                        printf("E %d\n", t);
                        t = globalt;
                    }
                }

                else{

                    ulll r = xb;
                    ulll temp = (r * r) % n;

                    if(temp == x){
                        t--;
                        printf("C %d\n", t);
                    }
                    else{
                        printf("E %d\n", t);
                        t = globalt;
                    }
                }

                flag = 0;
            }
        }

    } while (comando != 'T');

    C();
}

/*
    Modo Ester, comandos disponiveis: 
    I (Inicializar)                 Parâmetro(s): <n> <v>           | Saída: C (Sucesso) ou E (Erro)
    P (Preparar)                    Parâmetro(s): <b>               | Saída: C (Sucesso) <x> <xb> ou E (Erro)
    T (Terminar)                    Parâmetro(s): <xb>              | Saída: C (Sucesso)
    S (Sorte)                       Parâmetro(s): <x0> <x1>         | Saída: C (Sucesso) <s>

*/
void doEster(){

    ulll n = 0;
    ull v = 0;
    ull x = 0;
    ulll s = 0;
    ull xb = 0;
    ull x0 = 0;
    ull x1 = 0;
    int bit = -1;


    do{

        scanf("%c", &comando);

        if(comando == 'I'){
            //Done.
            ull temp;
            scanf(" %llu %llu", &temp, &v);
            n = temp;


            if(v > n || 2 > n)
                E();
            else
                C();
        }

        if(comando == 'P'){
            //Not done.
            scanf(" %d", &bit);

            printf("C %llu %llu\n", x, xb);
        }

        if(comando == 'S'){
            //Not Done.
            ull xtemp0, xtemp1;
            scanf(" %llu %llu", &xtemp0, &xtemp1);
            x0 = xtemp0;
            x1 = xtemp1;

            s = x0 / x1;
            //s = s % n;

            print128(s);
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

    srand(time(0)); 

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
            doEster();
            break;
    }
}