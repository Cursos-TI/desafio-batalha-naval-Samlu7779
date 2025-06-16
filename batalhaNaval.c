include <stdio.h>
#include <stdbool.h>

// Dimensões do tabuleiro (fixo: 10x10)
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3 // Tamanho fixo dos navios

// Definições para os tipos de célula no tabuleiro
#define AGUA 0
#define NAVIO 3

// Enumeração para facilitar a leitura da orientação do navio
typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_PRINCIPAL,     // Linha e coluna aumentam (ex: (0,0), (1,1), (2,2))
    DIAGONAL_SECUNDARIA    // Linha aumenta, coluna diminui (ex: (0,9), (1,8), (2,7))
} OrientacaoNavio;

// Função para inicializar o tabuleiro com zeros (água)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA; // 0 representa água
        }
    }
}

// Função para validar se o navio cabe no tabuleiro, considerando todas as orientações
bool validarNavio(int linha, int coluna, int tamanho, OrientacaoNavio orientacao) {
    switch (orientacao) {
        case HORIZONTAL:
            // Verifica se o navio horizontal cabe no tabuleiro
            if (coluna + tamanho > TAM_TABULEIRO) {
                return false;
            }
            break;
        case VERTICAL:
            // Verifica se o navio vertical cabe no tabuleiro
            if (linha + tamanho > TAM_TABULEIRO) {
                return false;
            }
            break;
        case DIAGONAL_PRINCIPAL:
            // Verifica se o navio diagonal principal cabe no tabuleiro
            if (linha + tamanho > TAM_TABULEIRO || coluna + tamanho > TAM_TABULEIRO) {
                return false;
            }
            break;
        case DIAGONAL_SECUNDARIA:
            // Verifica se o navio diagonal secundária cabe no tabuleiro
            // A linha aumenta, a coluna diminui
            if (linha + tamanho > TAM_TABULEIRO || coluna - tamanho + 1 < 0) {
                return false;
            }
            break;
    }
    return true;
}

// Função para verificar se há sobreposição com outro navio, considerando todas as orientações
bool verificarSobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, OrientacaoNavio orientacao) {
    switch (orientacao) {
        case HORIZONTAL:
            for (int j = coluna; j < coluna + tamanho; j++) {
                if (tabuleiro[linha][j] != AGUA) {
                    return true; // Há sobreposição
                }
            }
            break;
        case VERTICAL:
            for (int i = linha; i < linha + tamanho; i++) {
                if (tabuleiro[i][coluna] != AGUA) {
                    return true; // Há sobreposição
                }
            }
            break;
        case DIAGONAL_PRINCIPAL:
            for (int k = 0; k < tamanho; k++) {
                if (tabuleiro[linha + k][coluna + k] != AGUA) {
                    return true; // Há sobreposição
                }
            }
            break;
        case DIAGONAL_SECUNDARIA:
            for (int k = 0; k < tamanho; k++) {
                if (tabuleiro[linha + k][coluna - k] != AGUA) {
                    return true; // Há sobreposição
                }
            }
            break;
    }
    return false; // Não há sobreposição
}

// Função para posicionar um navio no tabuleiro
bool posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int tamanho, OrientacaoNavio orientacao) {
    // Valida se o navio cabe no tabuleiro
    if (!validarNavio(linha, coluna, tamanho, orientacao)) {
        printf("Erro: Navio fora dos limites do tabuleiro! Coordenadas (%d, %d), Tamanho %d, Orientacao %d\n", linha, coluna, tamanho, orientacao);
        return false;
    }

    // Verifica se há sobreposição
    if (verificarSobreposicao(tabuleiro, linha, coluna, tamanho, orientacao)) {
        printf("Erro: Sobreposicao de navios detectada! Coordenadas (%d, %d), Tamanho %d, Orientacao %d\n", linha, coluna, tamanho, orientacao);
        return false;
    }

    // Posiciona o navio (valor NAVIO)
    switch (orientacao) {
        case HORIZONTAL:
            for (int j = coluna; j < coluna + tamanho; j++) {
                tabuleiro[linha][j] = NAVIO;
            }
            break;
        case VERTICAL:
            for (int i = linha; i < linha + tamanho; i++) {
                tabuleiro[i][coluna] = NAVIO;
            }
            break;
        case DIAGONAL_PRINCIPAL:
            for (int k = 0; k < tamanho; k++) {
                tabuleiro[linha + k][coluna + k] = NAVIO;
            }
            break;
        case DIAGONAL_SECUNDARIA:
            for (int k = 0; k < tamanho; k++) {
                tabuleiro[linha + k][coluna - k] = NAVIO;
            }
            break;
    }
    return true;
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval:\n");
    // Imprime os índices das colunas
    printf("   "); // Espaço para alinhar com os índices das linhas
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    // Imprime a linha de separação
    printf("  +-");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("---");
    }
    printf("+\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d|", i); // Imprime índices das linhas e separador
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            // Usa '0' para água e '#' para navio para melhor visualização
            if (tabuleiro[i][j] == AGUA) {
                printf(" %c ", '0');
            } else {
                printf(" %c ", '#');
            }
        }
        printf("|\n"); // Fecha a linha do tabuleiro
    }
    // Imprime a linha de separação final
    printf("  +-");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("---");
    }
    printf("+\n");
}

int main() {
    // Declaração do tabuleiro
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa o tabuleiro com água (0)
    inicializarTabuleiro(tabuleiro);

    // Variáveis para controlar o sucesso do posicionamento de cada navio
    bool sucessoPosicionamento;

    // Posiciona o primeiro navio (horizontal)
    printf("Tentando posicionar Navio 1 (Horizontal) em (2, 3)...\n");
    sucessoPosicionamento = posicionarNavio(tabuleiro, 2, 3, TAM_NAVIO, HORIZONTAL);
    if (sucessoPosicionamento) {
        printf("Navio 1 posicionado com sucesso.\n");
    } else {
        printf("Falha ao posicionar Navio 1.\n");
        return 1; // Encerra se houver erro
    }

    // Posiciona o segundo navio (vertical)
    printf("Tentando posicionar Navio 2 (Vertical) em (5, 7)...\n");
    sucessoPosicionamento = posicionarNavio(tabuleiro, 5, 7, TAM_NAVIO, VERTICAL);
    if (sucessoPosicionamento) {
        printf("Navio 2 posicionado com sucesso.\n");
    } else {
        printf("Falha ao posicionar Navio 2.\n");
        return 1; // Encerra se houver erro
    }

    // Posiciona o terceiro navio (diagonal principal)
    // Exemplo: começa em (1,1), ocupará (1,1), (2,2), (3,3)
    printf("Tentando posicionar Navio 3 (Diagonal Principal) em (1, 1)...\n");
    sucessoPosicionamento = posicionarNavio(tabuleiro, 1, 1, TAM_NAVIO, DIAGONAL_PRINCIPAL);
    if (sucessoPosicionamento) {
        printf("Navio 3 posicionado com sucesso.\n");
    } else {
        printf("Falha ao posicionar Navio 3.\n");
        return 1; // Encerra se houver erro
    }

    // Posiciona o quarto navio (diagonal secundária)
    // Exemplo: começa em (0,8), ocupará (0,8), (1,7), (2,6)
    printf("Tentando posicionar Navio 4 (Diagonal Secundária) em (0, 8)...\n");
    sucessoPosicionamento = posicionarNavio(tabuleiro, 0, 8, TAM_NAVIO, DIAGONAL_SECUNDARIA);
    if (sucessoPosicionamento) {
        printf("Navio 4 posicionado com sucesso.\n");
    } else {
        printf("Falha ao posicionar Navio 4.\n");
        return 1; // Encerra se houver erro
    }

    // Tentar posicionar um navio que sobreponha (para teste de sobreposição)
    printf("\n--- Teste de sobreposicao ---\n");
    printf("Tentando posicionar Navio de teste (Horizontal) em (2, 4) para causar sobreposicao...\n");
    sucessoPosicionamento = posicionarNavio(tabuleiro, 2, 4, TAM_NAVIO, HORIZONTAL);
    if (sucessoPosicionamento) {
        printf("Navio de teste posicionado com sucesso (ISSO NAO DEVERIA ACONTECER SE HOUVER SOBREPOSICAO!).\n");
    } else {
        printf("Falha esperada ao posicionar Navio de teste devido a sobreposicao ou limites.\n");
    }

    // Tentar posicionar um navio fora dos limites (para teste de limite)
    printf("\n--- Teste de limites ---\n");
    printf("Tentando posicionar Navio de teste (Vertical) em (9, 0) para causar erro de limite...\n");
    sucessoPosicionamento = posicionarNavio(tabuleiro, 9, 0, TAM_NAVIO, VERTICAL);
    if (sucessoPosicionamento) {
        printf("Navio de teste posicionado com sucesso (ISSO NAO DEVERIA ACONTECER SE ESTIVER FORA DOS LIMITES!).\n");
    } else {
        printf("Falha esperada ao posicionar Navio de teste devido a limites.\n");
    }


    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);

    return 0;
   }
