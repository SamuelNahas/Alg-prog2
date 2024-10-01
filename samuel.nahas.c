#include <stdio.h>
#include <stdbool.h>

typedef enum {
    COPAS = 'C',
    ESPADAS = 'E',
    OUROS = 'O',
    PAUS = 'P'
} t_naipe;

typedef struct {
short valor;
t_naipe naipe;
} t_carta;

typedef enum {
PAR = 15,
DOISPARES = 16,
TRINCA = 17,
SEQUENCIA = 18,
FLUSH = 19,
FULL = 20,
QUADRA = 21,
SFLUSH = 22,
RFLUSH = 23
} t_valor_m;

typedef struct {
t_carta cartas[5];
t_valor_m valor;
} t_mao;

int valorar_carta(char v) {

    if (v == 'J') {
        return 11;
    } if (v == 'Q') {
        return 12;
    } if (v == 'K') {
        return 13;
    } if (v == 'A') {
        return 14;
    }
    return v - '0';

}

void ordena_mao(t_mao *mao){

    t_carta aux;

    for(int j = 1; j < 5; j++){
        for(int i = 0; i < 5 - j; i++){
            if(mao->cartas[i].valor > mao->cartas[i+1].valor){
                aux = mao->cartas[i];
                mao->cartas[i+1] = mao->cartas[i];
                mao->cartas[i] = aux;
            }
        }
    }

}


t_valor_m identificar_mao(t_mao *mao) {

    int contagem[15] = {0};

    for (int i = 0; i < 5; i++) {
        contagem[mao->cartas[i].valor]++;
    }

    bool tem_par = false;
    bool tem_dois_pares = false;
    bool tem_trinca = false;
    bool tem_quadra = false;
    int pares = 0;

    for (int i = 2; i <= 14; i++) {
        if (contagem[i] == 2) {
            pares++;
            tem_par = true;
        } else if (contagem[i] == 3) {
            tem_trinca = true;
        } else if (contagem[i] == 4) {
            tem_quadra = true;
        }
    }

    if (tem_quadra) {
        return QUADRA;
    }

    if (tem_trinca) {
        return TRINCA;
    }

    if (pares == 2) {
        return DOISPARES;
    }

    if (tem_par) {
        return PAR;
    }
    
    return PAR;
}



int main() {
    int k;
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        t_mao mao1, mao2;

        for (int j = 0; j < 5; j++) {
            char valor, naipe;
            scanf("%c %c", &valor, &naipe);
            mao1.cartas[j].valor = valorar_carta(valor);
            mao1.cartas[j].naipe = (t_naipe)naipe;
        }

        for (int j = 0; j < 5; j++) {
            char valor, naipe;
            scanf("%c %c", &valor, &naipe);
            mao2.cartas[j].valor = valorar_carta(valor);
            mao2.cartas[j].naipe = (t_naipe)naipe;
        }

        t_valor_m valor_mao1 = identificar_mao(&mao1);
        t_valor_m valor_mao2 = identificar_mao(&mao2);

        if (valor_mao1 > valor_mao2) {
            ordena_mao(&mao1);
            printf("1 ");
            for (int j = 0; j < 5; j++) {
                printf("%d %c ", mao1.cartas[j].valor, mao1.cartas[j].naipe);
            }
            printf("\n");
        } else if (valor_mao2 > valor_mao1) {
            ordena_mao(&mao2);
            printf("2 ");
            for (int j = 0; j < 5; j++) {
                printf("%d %c ", mao2.cartas[j].valor, mao2.cartas[j].naipe);
            }
            printf("\n");
        } else {
            printf("Empate\n");
        }
    }

    return 0;
}
