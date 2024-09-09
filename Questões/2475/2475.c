#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define INFINITO 0x3F3F3F3F
#define LONGO_INFINITO 0x3F3F3F3F3F3F3F3FLL
#define MAX_PRODUTOS 10100
#define MAX_ACOES 600

int quantidadeProdutos, quantidadeAcoes;
long long int somaAcumuladaProdutos[MAX_PRODUTOS];
long long int tabelaCustos[MAX_ACOES][MAX_PRODUTOS];

long long int calcularValor(int esquerda, int direita) {
    return (direita - esquerda + 1) * (somaAcumuladaProdutos[direita] - somaAcumuladaProdutos[esquerda - 1]);
}

void resolverCustoMinimo(int acaoAtual, int esquerda, int direita, int limiteEsquerda, int limiteDireita) {
    if (esquerda > direita) 
        return;

    int meio = (esquerda + direita) / 2;
    int melhorIndice = limiteEsquerda;
    tabelaCustos[acaoAtual][meio] = LONGO_INFINITO;

    for (int i = (meio > limiteEsquerda ? meio : limiteEsquerda); i <= limiteDireita; i++) {
        long long int custoAtual = tabelaCustos[acaoAtual - 1][i + 1] + calcularValor(meio + 1, i + 1);
        if (tabelaCustos[acaoAtual][meio] > custoAtual) {
            tabelaCustos[acaoAtual][meio] = custoAtual;
            melhorIndice = i;
        }
    }

    resolverCustoMinimo(acaoAtual, esquerda, meio - 1, limiteEsquerda, melhorIndice);
    resolverCustoMinimo(acaoAtual, meio + 1, direita, melhorIndice, limiteDireita);
}

int main() {
    scanf("%d %d", &quantidadeProdutos, &quantidadeAcoes);
    for (int i = 1; i <= quantidadeProdutos; i++) {
        long long int produto;
        scanf("%lld", &produto);
        somaAcumuladaProdutos[i] = somaAcumuladaProdutos[i - 1] + produto;
    }

    for (int i = 0; i <= quantidadeProdutos; i++) {
        tabelaCustos[0][i] = LONGO_INFINITO;
    }

    for (int i = 0; i <= quantidadeAcoes; i++) {
        tabelaCustos[i][quantidadeProdutos] = 0;
    }

    for (int i = 1; i <= quantidadeAcoes; i++) {
        resolverCustoMinimo(i, 0, quantidadeProdutos - 1, 0, quantidadeProdutos - 1);
    }

    printf("%lld\n", tabelaCustos[quantidadeAcoes][0]);

    return 0;
}
