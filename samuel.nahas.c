#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
    } else if (v == 'Q') {
        return 12;
    } else if (v == 'K') {
        return 13;
    } else if (v == 'A') {
        return 14;
    } else if (isdigit(v)) {
        return v - '0'; 
    } else {
        return -1; 
    }
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
    
    ordenar_mao(&mao);
    
    // Verificação para TRINCA
    if ((mao->cartas[0].valor == mao->cartas[1].valor && mao->cartas[1].valor == mao->cartas[2].valor) ||
        (mao->cartas[1].valor == mao->cartas[2].valor && mao->cartas[2].valor == mao->cartas[3].valor) ||
        (mao->cartas[2].valor == mao->cartas[3].valor && mao->cartas[3].valor == mao->cartas[4].valor)) {
        return TRINCA;
    }
    
    // Adicionar verificação para outros tipos de mãos (Par, Full House, etc.)
    
    return PAR;  // Placeholder
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
            ordenar_mao(&mao1);
            printf("1 ");
            for (int j = 0; j < 5; j++) {
                printf("%d %c ", mao1.cartas[j].valor, mao1.cartas[j].naipe);
            }
            printf("\n");
        } else if (valor_mao2 > valor_mao1) {
            ordenar_mao(&mao2);
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
