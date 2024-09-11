#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

short valorar_carta_letra(char v) {
    // Converter as cartas com leta em valores
    if (v == 'J') {
        return 11;
    } else if (v == 'Q') {
        return 12;
    } else if (v == 'K') {
        return 13;
    } else if (v == 'A') {
        return 14;  
    }
    return -1; // Valor inválido
}

int compara_cartas(const void* a, const void* b) {
    t_carta* carta1 = (t_carta*)a;
    t_carta* carta2 = (t_carta*)b;

    // Comparar valores primeiro
    if (carta1->valor != carta2->valor) {
        return carta1->valor - carta2->valor;
    }

    // Se os valores forem iguais, compara os naipes
    return carta1->naipe - carta2->naipe;
}

void ordenar_mao(t_mao* mao) {
    // Fazer no passo a passo algum sort depois algum sort
    qsort(mao->cartas, 5, sizeof(t_carta), compara_cartas);
}

t_valor_m identificar_mao(t_mao* mao) {
    
    ordenar_mao(mao);  // Ordena pra verificar
    
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

        // Leitura das cartas da primeira capivara
        for (int j = 0; j < 5; j++) {
            char valor, naipe;
            scanf(" %c %c", &valor, &naipe);
            mao1.cartas[j].valor = valorar_carta_letra(valor);
            mao1.cartas[j].naipe = (t_naipe)naipe;
        }

        // Leitura das cartas da segunda capivara
        for (int j = 0; j < 5; j++) {
            char valor, naipe;
            scanf(" %c %c", &valor, &naipe);
            mao2.cartas[j].valor = valorar_carta_letra(valor);
            mao2.cartas[j].naipe = (t_naipe)naipe;
        }

        // Determinar os tipos de mão
        t_valor_m valor_mao1 = identificar_mao(&mao1);
        t_valor_m valor_mao2 = identificar_mao(&mao2);

        // Verificar quem venceu
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
            printf("E\n");
        }
    }

    return 0;
}
