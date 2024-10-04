#include <stdio.h>
#include <stdbool.h>

typedef enum {
    PAUS = 'P',
    OUROS = 'O',
    COPAS = 'C',
    ESPADAS = 'E'
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

int valorar_carta(char *v) {
    if (v[0] == '1' && v[1] == '0') return 10;
    if (v[0] == 'J') return 11;
    if (v[0] == 'Q') return 12;
    if (v[0] == 'K') return 13;
    if (v[0] == 'A') return 14;
    return v[0] - '0';
}

int comparar_naipes(t_naipe n1, t_naipe n2) {
    if (n1 == n2) return 0;
    if (n1 == PAUS) return -1;
    if (n1 == OUROS && n2 != PAUS) return -1;
    if (n1 == COPAS && n2 == ESPADAS) return -1;
    return 1;
}

void ordena_mao(t_mao *mao) {
    t_carta aux;

    for (int j = 1; j < 5; j++) {
        for (int i = 0; i < 5 - j; i++) {
            if (mao->cartas[i].valor > mao->cartas[i + 1].valor ||
                (mao->cartas[i].valor == mao->cartas[i + 1].valor &&
                 comparar_naipes(mao->cartas[i].naipe, mao->cartas[i + 1].naipe) > 0)) {
                aux = mao->cartas[i];
                mao->cartas[i] = mao->cartas[i + 1];
                mao->cartas[i + 1] = aux;
            }
        }
    }
}

t_valor_m identificar_mao(t_mao *mao) {
    int contagem[15] = {0};
    bool flush = true;
    bool sequencia = true;

    for (int i = 0; i < 4; i++) {
        contagem[mao->cartas[i].valor]++;
        if (mao->cartas[i].naipe != mao->cartas[i+1].naipe) {
            flush = false;
        }
        if (mao->cartas[i].valor + 1 != mao->cartas[i+1].valor) {
            sequencia = false;
        }
    }


    bool tem_par = false, tem_trinca = false, tem_quadra = false;
    int pares = 0;

    for (int i = 2; i <= 14; i++) {
        if (contagem[i] == 2) pares++, tem_par = true;
        else if (contagem[i] == 3) tem_trinca = true;
        else if (contagem[i] == 4) tem_quadra = true;
    }

    if (flush && sequencia && mao->cartas[0].valor == 10) return RFLUSH;
    if (flush && sequencia) return SFLUSH;
    if (tem_quadra) return QUADRA;
    if (tem_trinca && tem_par) return FULL;
    if (flush) return FLUSH;
    if (sequencia) return SEQUENCIA;
    if (tem_trinca) return TRINCA;
    if (pares == 2) return DOISPARES;
    if (tem_par) return PAR;

    return mao->cartas[4].valor;
}

void imprimir_mao(t_mao *mao) {
    for (int i = 0; i < 5; i++) {
        if (mao->cartas[i].valor == 11) printf("J %c ", mao->cartas[i].naipe);
        else if (mao->cartas[i].valor == 12) printf("Q %c ", mao->cartas[i].naipe);
        else if (mao->cartas[i].valor == 13) printf("K %c ", mao->cartas[i].naipe);
        else if (mao->cartas[i].valor == 14) printf("A %c ", mao->cartas[i].naipe);
        else printf("%d %c ", mao->cartas[i].valor, mao->cartas[i].naipe);
    }
    printf("\n");
}

int main() {
    int k;
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        t_mao mao1, mao2;

        for (int j = 0; j < 5; j++) {
            char valor[3], naipe;
            scanf("%s %c", valor, &naipe);
            mao1.cartas[j].valor = valorar_carta(valor);
            mao1.cartas[j].naipe = (t_naipe)naipe;
        }

        for (int j = 0; j < 5; j++) {
            char valor[3], naipe;
            scanf("%s %c", valor, &naipe);
            mao2.cartas[j].valor = valorar_carta(valor);
            mao2.cartas[j].naipe = (t_naipe)naipe;
        }

        ordena_mao(&mao1);
        ordena_mao(&mao2);
        t_valor_m valor_mao1 = identificar_mao(&mao1);
        t_valor_m valor_mao2 = identificar_mao(&mao2);

        if (valor_mao1 > valor_mao2) {
            printf("1 ");
            imprimir_mao(&mao1);
        } else if (valor_mao2 > valor_mao1) {
            printf("2 ");
            imprimir_mao(&mao2);
        } else {
            printf("Empate\n");
        }
    }

    return 0;
}
