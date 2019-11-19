/*
    Celso Antonio Uliana Junior,
    Nov 2019
*/

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
ll generateRandom64(ll n) {
    /*
        Duas variáveis inteiras de 32 bits, para gerar um int x de 64 bits no range.
        0 < x < n < INT64MAX
    */

    ll x;

    first = rand();
    second = rand();


    return x;
}



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

    ulll n;
    ull s, v, x;

    do{

        scanf("%c", &comando);

        if(comando == 'I'){
            X();
        }

        if(comando == 'X'){
            X();
        }

        if(comando == 'P'){
            X();
        }

        if(comando == 'R'){
            X();
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