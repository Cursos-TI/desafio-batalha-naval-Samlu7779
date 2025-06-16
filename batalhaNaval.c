#include <stdio.h>
#include <stdlib.h>

// Dimensões do tabuleiro e da matriz de habilidade
#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // Água
        }
    }
}

// Função para inicializar matriz de habilidade com zeros
void inicializarHabilidade(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
}

// Função para criar habilidade em forma de cone
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // O cone aponta para baixo, com topo na linha 0, coluna central
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Define a área do cone: expande com base na linha
            if (j >= (TAM_HABILIDADE / 2) - i && j <= (TAM_HABILIDADE / 2) + i) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Função para criar habilidade em forma de cruz
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // Cruz centrada na posição central da matriz
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Marca a linha e coluna central como afetadas
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Função para criar habilidade em forma de octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // Octaedro forma um losango centrado na matriz
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Usa distância de Manhattan para formar um losango
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Função para sobrepor a habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    // Calcula o deslocamento para centrar a habilidade
    int offset = TAM_HABILIDADE / 2;
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Calcula as coordenadas correspondentes no tabuleiro
            int tabLinha = origemLinha + (i - offset);
            int tabColuna = origemColuna + (j - offset);
            
            // Verifica se está dentro dos limites do tabuleiro
            if (tabLinha >= 0 && tabLinha < TAM_TABULEIRO && tabColuna >= 0 && tabColuna < TAM_TABULEIRO) {
                // Aplica a habilidade (valor 5) apenas nas posições afetadas (1) e se não for navio (3)
                if (habilidade[i][j] == 1 && tabuleiro[tabLinha][tabColuna] != 3) {
                    tabuleiro[tabLinha][tabColuna] = 5;
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n  ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("~ "); // Água
            } else if (tabuleiro[i][j] == 3) {
                printf("N "); // Navio
            } else if (tabuleiro[i][j] == 5) {
                printf("* "); // Área afetada
            }
        }
        printf("\n");
    }
}

// Função para exibir a matriz de habilidade (para depuração)
void exibirHabilidade(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    printf("\nMatriz de Habilidade:\n");
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Declaração do tabuleiro e das matrizes de habilidade
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int habilidadeCone[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidadeCruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidadeOctaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    
    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);
    
    // Adiciona alguns navios para teste
    tabuleiro[2][2] = 3;
    tabuleiro[3][3] = 3;
    tabuleiro[4][4] = 3;
    
    // Inicializa as matrizes de habilidade
    inicializarHabilidade(habilidadeCone);
    inicializarHabilidade(habilidadeCruz);
    inicializarHabilidade(habilidadeOctaedro);
    
    // Cria as habilidades
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);
    
    // Exibe as matrizes de habilidade para depuração
    printf("Habilidade Cone:\n");
    exibirHabilidade(habilidadeCone);
    printf("Habilidade Cruz:\n");
    exibirHabilidade(habilidadeCruz);
    printf("Habilidade Octaedro:\n");
    exibirHabilidade(habilidadeOctaedro);
    
    // Aplica as habilidades no tabuleiro em diferentes posições
    printf("\nTabuleiro com Habilidade Cone (origem: 3,3):\n");
    aplicarHabilidade(tabuleiro, habilidadeCone, 3, 3);
    exibirTabuleiro(tabuleiro);
    
    // Reinicializa o tabuleiro para próxima habilidade
    inicializarTabuleiro(tabuleiro);
    tabuleiro[2][2] = 3;
    tabuleiro[3][3] = 3;
    tabuleiro[4][4] = 3;
    
    printf("\nTabuleiro com Habilidade Cruz (origem: 5,5):\n");
    aplicarHabilidade(tabuleiro, habilidadeCruz, 5, 5);
    exibirTabuleiro(tabuleiro);
    
    // Reinicializa o tabuleiro para próxima habilidade
    inicializarTabuleiro(tabuleiro);
    tabuleiro[2][2] = 3;
    tabuleiro[3][3] = 3;
    tabuleiro[4][4] = 3;
    
    printf("\nTabuleiro com Habilidade Octaedro (origem: 7,7):\n");
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 7, 7);
    exibirTabuleiro(tabuleiro);
    
    return 0;
}