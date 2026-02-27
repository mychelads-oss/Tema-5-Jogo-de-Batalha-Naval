#include <stdio.h>

#define TAM 10
#define TAM_NAVIO 3

// Representação das células
#define AGUA  0
#define NAVIO 3

// Direções possíveis
typedef enum {
    HORIZONTAL,
    VERTICAL
} Direcao;


// ======================================================
// FUNÇÕES AUXILIARES
// ======================================================

// Verifica se a posição está dentro do tabuleiro
int posicaoValida(int linha, int coluna) {
    return linha >= 0 && linha < TAM &&
           coluna >= 0 && coluna < TAM;
}

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = AGUA;
}

// Exibe o tabuleiro formatado
void exibirTabuleiro(int tab[TAM][TAM]) {

    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n   ");

    for (int j = 0; j < TAM; j++)
        printf("%d ", j);

    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++)
            printf("%d ", tab[i][j]);
        printf("\n");
    }

    printf("\nLegenda: 0 = Água | 3 = Navio\n\n");
}


// ======================================================
// LÓGICA DE NAVIOS
// ======================================================

// Calcula próxima posição com base na direção
void calcularPosicao(int linha, int coluna, int deslocamento,
                     Direcao dir, int *novaL, int *novaC) {

    if (dir == HORIZONTAL) {
        *novaL = linha;
        *novaC = coluna + deslocamento;
    } else { // VERTICAL
        *novaL = linha + deslocamento;
        *novaC = coluna;
    }
}

// Verifica se há sobreposição ou saída do tabuleiro
int podePosicionar(int tab[TAM][TAM],
                   int linha, int coluna,
                   Direcao dir, int tamanho) {

    for (int i = 0; i < tamanho; i++) {

        int l, c;
        calcularPosicao(linha, coluna, i, dir, &l, &c);

        if (!posicaoValida(l, c) || tab[l][c] == NAVIO)
            return 0;
    }

    return 1;
}

// Posiciona o navio no tabuleiro
int posicionarNavio(int tab[TAM][TAM],
                    int linha, int coluna,
                    Direcao dir, int tamanho) {

    if (!podePosicionar(tab, linha, coluna, dir, tamanho)) {
        printf("Erro: posição inválida ou sobreposição detectada.\n");
        return 0;
    }

    for (int i = 0; i < tamanho; i++) {

        int l, c;
        calcularPosicao(linha, coluna, i, dir, &l, &c);
        tab[l][c] = NAVIO;
    }

    return 1;
}


// ======================================================
// MAIN
// ======================================================

int main() {

    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    printf("=== JOGO DE BATALHA NAVAL ===\n\n");

    // Navio Horizontal
    printf("Posicionando navio horizontal (2,3)...\n");
    if (posicionarNavio(tabuleiro, 2, 3, HORIZONTAL, TAM_NAVIO))
        printf("Navio horizontal posicionado com sucesso.\n\n");

    // Navio Vertical
    printf("Posicionando navio vertical (5,7)...\n");
    if (posicionarNavio(tabuleiro, 5, 7, VERTICAL, TAM_NAVIO))
        printf("Navio vertical posicionado com sucesso.\n");

    exibirTabuleiro(tabuleiro);

    return 0;
}