#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LIN 3 
#define COL 3

char tabuleiro[LIN][COL];

int i, j;

void inicioTabuleiro() {
    for (i = 0; i < LIN; i++)
        for (j = 0; j < COL; j++)
            tabuleiro[i][j] = ' ';
}

void exibirTabuleiro() {
    printf("   1   2   3\n");
    for (i = 0; i < LIN; i++) {
        printf("%c ", 'A' + i);
        for (j = 0; j < COL; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < 2) printf("|");
        }
        if (i < 2) printf("\n  ---+---+---\n");
    }
    printf("\n");
}

int posicaoValida(char *entrada, int *linha, int *coluna) {
    if (strlen(entrada) != 2)
        return 0;
    
    entrada[0] = toupper(entrada[0]);
    if (entrada[0] < 'A' || entrada[0] > 'C') return 0;
    if (entrada[1] < '1' || entrada[1] > '3') return 0;

    *linha = entrada[0] - 'A';
    *coluna = entrada[1] - '1';

    if (tabuleiro[*linha][*coluna] != ' ')
        return 0;

    return 1;
}

int verificaGanhador() {
    for (int i = 0; i < 3; i++) {
        // Linhas
        if (tabuleiro[i][0] != ' ' && tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2])
            return tabuleiro[i][0] == 'X' ? 1 : 2;

        // Colunas
        if (tabuleiro[0][i] != ' ' && tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i])
            return tabuleiro[0][i] == 'X' ? 1 : 2;
    }

    // Diagonais
    if (tabuleiro[0][0] != ' ' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2])
        return tabuleiro[0][0] == 'X' ? 1 : 2;

    if (tabuleiro[0][2] != ' ' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0])
        return tabuleiro[0][2] == 'X' ? 1 : 2;

    return 0;
}

int tabuleiroCheio() {
    for (i = 0; i < LIN; i++)
        for (j = 0; j < COL; j++)
            if (tabuleiro[i][j] == ' ')
                return 0;
    return 1;
}

int main (){

    int jogador = 1;
    char jogada[3];
    int linha;
    int coluna;
    int vencedor = 0;

    inicioTabuleiro();

    while (!vencedor && !tabuleiroCheio()) {
        exibirTabuleiro();
        printf("Jogador %d, informe sua jogada (ex: B2): ", jogador);
        scanf("%s", jogada);

        if (!posicaoValida(jogada, &linha, &coluna)) {
            printf("Jogada inválida! Tente novamente.\n\n");
            continue;
        }

        tabuleiro[linha][coluna] = (jogador == 1) ? 'X' : '0';
        vencedor = verificaGanhador();
        jogador = (jogador == 1) ? 2 : 1;
    }

    exibirTabuleiro();
    if (vencedor)
        printf("O Jogador %d venceu!\n", vencedor);
    else
        printf("Nenhum jogador venceu.\n");

    return 0;
}
