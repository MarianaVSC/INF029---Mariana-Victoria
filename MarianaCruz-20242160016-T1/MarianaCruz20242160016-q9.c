#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 10
#define MAX_NAVIOS 7

char AGUA[] = " [ ] ";
char NAVIO[] = " [N] ";
char ACERTO[] = " [0] ";
char ERRO[] = " [X] ";

int tamanhos_navios[MAX_NAVIOS] = {4, 3, 1, 1, 1, 2, 2};  

void inicializar_tabuleiro(char tabuleiro[TAMANHO][TAMANHO][5]) {
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            strcpy(tabuleiro[i][j], AGUA);
}

void imprimir_tabuleiro(char tabuleiro[TAMANHO][TAMANHO][5], int mostrar_navios) {
    printf("   ");
    for (int i = 0; i < TAMANHO; i++) printf("%2d ", i);
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            if (!mostrar_navios && strcmp(tabuleiro[i][j], NAVIO) == 0)
                printf("%s", AGUA);
            else
                printf("%s", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int posicao_valida(char tabuleiro[TAMANHO][TAMANHO][5], int linha, int coluna, int tamanho, char orientacao) {
    if (orientacao == 'H') {
        if (coluna + tamanho > TAMANHO) return 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(tabuleiro[linha][coluna + i], AGUA) != 0)
                return 0;
    } else {
        if (linha + tamanho > TAMANHO) return 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(tabuleiro[linha + i][coluna], AGUA) != 0)
                return 0;
    }
    return 1;
}

void posicionar_navio(char tabuleiro[TAMANHO][TAMANHO][5], int linha, int coluna, int tamanho, char orientacao) {
    if (orientacao == 'H') {
        for (int i = 0; i < tamanho; i++)
            strcpy(tabuleiro[linha][coluna + i], NAVIO);
    } else {
        for (int i = 0; i < tamanho; i++)
            strcpy(tabuleiro[linha + i][coluna], NAVIO);
    }
}

void posicionar_navios(char tabuleiro[TAMANHO][TAMANHO][5], int jogador) {
    int linha, coluna;
    char orientacao;
    printf("\n--- Jogador %d: Posicione seus navios ---\n", jogador);
    for (int i = 0; i < MAX_NAVIOS; i++) {
        while (1) {
            printf("\nNavio %d (tamanho %d)\n", i + 1, tamanhos_navios[i]);
            printf("Linha: ");
            scanf("%d", &linha);
            printf("Coluna: ");
            scanf("%d", &coluna);
            printf("Orientação (H/V): ");
            scanf(" %c", &orientacao);

            if (posicao_valida(tabuleiro, linha, coluna, tamanhos_navios[i], orientacao)) {
                posicionar_navio(tabuleiro, linha, coluna, tamanhos_navios[i], orientacao);
                imprimir_tabuleiro(tabuleiro, 1);
                break;
            } else {
                printf("Posição inválida. Tente novamente.\n");
            }
        }
    }
}

void atirar(char tabuleiro[TAMANHO][TAMANHO][5], char visao[TAMANHO][TAMANHO][5], int jogador) {
    int linha, coluna;
    printf("\n--- Jogador %d: Sua vez de atirar ---\n", jogador);
    while (1) {
        printf("Linha: ");
        scanf("%d", &linha);
        printf("Coluna: ");
        scanf("%d", &coluna);

        if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO) {
            printf("Coordenadas inválidas. Tente novamente.\n");
            continue;
        }

        if (strcmp(visao[linha][coluna], AGUA) != 0) {
            printf("Você já atirou aqui. Tente outro lugar.\n");
            continue;
        }

        if (strcmp(tabuleiro[linha][coluna], NAVIO) == 0) {
            printf("Acertou!\n");
            strcpy(tabuleiro[linha][coluna], ACERTO);
            strcpy(visao[linha][coluna], ACERTO);
        } else {
            printf("Errou!\n");
            strcpy(visao[linha][coluna], ERRO);
        }
        break;
    }
}

int venceu(char tabuleiro[TAMANHO][TAMANHO][5]) {
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            if (strcmp(tabuleiro[i][j], NAVIO) == 0)
                return 0;
    return 1;
}

int main() {
    char tabuleiro1[TAMANHO][TAMANHO][5];
    char tabuleiro2[TAMANHO][TAMANHO][5];
    char visao1[TAMANHO][TAMANHO][5];
    char visao2[TAMANHO][TAMANHO][5];

    inicializar_tabuleiro(tabuleiro1);
    inicializar_tabuleiro(tabuleiro2);
    inicializar_tabuleiro(visao1);
    inicializar_tabuleiro(visao2);

    posicionar_navios(tabuleiro1, 1);
    posicionar_navios(tabuleiro2, 2);

    int jogador_atual = 1;
    while (1) {
        if (jogador_atual == 1) {
            printf("\n--- Jogador 1 ---\n");
            printf("Seu tabuleiro:\n");
            imprimir_tabuleiro(tabuleiro1, 1);
            printf("Tabuleiro do inimigo:\n");
            imprimir_tabuleiro(visao1, 0);
            atirar(tabuleiro2, visao1, 1);
            if (venceu(tabuleiro2)) {
                printf("\nJogador 1 venceu!\n");
                break;
            }
            jogador_atual = 2;
        } else {
            printf("\n--- Jogador 2 ---\n");
            printf("Seu tabuleiro:\n");
            imprimir_tabuleiro(tabuleiro2, 1);
            printf("Tabuleiro do inimigo:\n");
            imprimir_tabuleiro(visao2, 0);
            atirar(tabuleiro1, visao2, 2);
            if (venceu(tabuleiro1)) {
                printf("\nJogador 2 venceu!\n");
                break;
            }
            jogador_atual = 1;
        }
    }

    return 0;
}