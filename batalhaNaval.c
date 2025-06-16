[13:29, 16/06/2025] SamBorges: Desafio: nível novato
Posicionando Navios no Tabuleiro


Neste primeiro desafio, você dará o primeiro passo na construção do seu jogo de Batalha Naval. Você utilizará seus conhecimentos de vetores (arrays unidimensionais) em C para representar um tabuleiro simplificado e posicionar dois navios nele: um na vertical e outro na horizontal. Continue o desenvolvimento no mesmo programa iniciado anteriormente.


O que você vai fazer


Represente o Tabuleiro: Utilize uma matriz (array bidimensional) para representar o tabuleiro do Batalha Naval. Neste nível novato, o tabuleiro terá um tamanho fixo 10x10. Inicialize todas as posições do tabuleiro com o valor 0, representando água.
 
Posicione os Navios: Declare e inicialize dois vetores (arrays unidimensionais) para…
[13:30, 16/06/2025] SamBorges: #include <stdio.h>
#include <stdbool.h>

// Dimensões do tabuleiro (fixo: 10x10)
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Função para inicializar o tabuleiro com zeros (água)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // 0 representa água
        }
    }
}

// Função para validar se o navio cabe no tabuleiro
bool validarNavio(int linha, int coluna, int tamanho, bool horizontal) {
    if (horizontal) {
        // Verifica se o navio horizontal cabe no tabuleiro
        if (coluna + tamanho > TAM_TABULEIRO) {
            return false;
        }
    } else {
        // Verifica se o navio vertical cabe no tabuleiro
        if (linha + tamanho > TAM_TABULEIRO) {
            return false;
        }
    }
    return true;
}

// Função para verificar se há sobreposição com outro navio
bool verificarSobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, bool horizontal) {
    if (horizontal) {
        for (int j = coluna; j < coluna + tamanho; j++) {
            if (tabuleiro[linha][j] != 0) {
                return true; // Há sobreposição
            }
        }
    } else {
        for (int i = linha; i < linha + tamanho; i++) {
            if (tabuleiro[i][coluna] != 0) {
                return true; // Há sobreposição
            }
        }
    }
    return false; // Não há sobreposição
}

// Função para posicionar um navio no tabuleiro
bool posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, bool horizontal) {
    // Valida se o navio cabe no tabuleiro
    if (!validarNavio(linha, coluna, tamanho, horizontal)) {
        printf("Erro: Navio fora dos limites do tabuleiro!\n");
        return false;
    }

    // Verifica se há sobreposição
    if (verificarSobreposicao(tabuleiro, linha, coluna, tamanho, horizontal)) {
        printf("Erro: Sobreposicao de navios detectada!\n");
        return false;
    }

    // Posiciona o navio (valor 3)
    if (horizontal) {
        for (int j = coluna; j < coluna + tamanho; j++) {
            tabuleiro[linha][j] = 3; // 3 representa parte do navio
        }
    } else {
        for (int i = linha; i < linha + tamanho; i++) {
            tabuleiro[i][coluna] = 3; // 3 representa parte do navio
        }
    }
    return true;
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval:\n");
    printf("  ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j); // Imprime índices das colunas
    }
    printf("\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i); // Imprime índices das linhas
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]); // Imprime valor da célula
        }
        printf("\n");
    }
}

int main() {
    // Declaração do tabuleiro
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa o tabuleiro com água (0)
    inicializarTabuleiro(tabuleiro);

    // Coordenadas fixas para os navios
    int navio1_linha = 2, navio1_coluna = 3; // Navio horizontal
    int navio2_linha = 5, navio2_coluna = 7; // Navio vertical

    // Posiciona o primeiro navio (horizontal)
    if (posicionarNavio(tabuleiro, navio1_linha, navio1_coluna, TAM_NAVIO, true)) {
        printf("Navio horizontal posicionado em (%d, %d)\n", navio1_linha, navio1_coluna);
    } else {
        return 1; // Encerra se houver erro
    }

    // Posiciona o segundo navio (vertical)
    if (posicionarNavio(tabuleiro, navio2_linha, navio2_coluna, TAM_NAVIO, false)) {
        printf("Navio vertical posicionado em (%d, %d)\n", navio2_linha, navio2_coluna);
    } else {
        return 1; // Encerra se houver erro
    }

    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);

    return 0;
}