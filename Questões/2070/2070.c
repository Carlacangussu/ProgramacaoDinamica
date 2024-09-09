#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int k;
int tam[3];        
int seq[3][205];   
int prox[3][205][25]; 
int menorDist[205][205][205]; 
int contagem[205][205][205];  

typedef struct {
    int a, b, c;
} Tripla;

typedef struct {
    int menor, quantidade;
} Par;

Par busca_em_largura();

int main() {
    int i, j, valor;
    scanf("%d %d %d %d", &k, &tam[0], &tam[1], &tam[2]);

    for (i = 0; i < 3; ++i)
        for (j = 1; j <= tam[i]; ++j)
            scanf("%d", &seq[i][j]);

    
    for (i = 0; i < 3; ++i)
        for (j = 1; j <= tam[i]; ++j)
            for (valor = 0; valor <= k; ++valor)
                prox[i][j][valor] = tam[i] + 1;

    
    for (i = 0; i < 3; ++i)
        for (j = 1; j <= tam[i]; ++j)
            for (valor = j - 1; valor >= 0; --valor) {
                prox[i][valor][seq[i][j]] = j;
                if (seq[i][valor] == seq[i][j])
                    break;
            }

    Par resposta = busca_em_largura();
    printf("%d %d\n", resposta.menor, resposta.quantidade);

    return 0;
}

Par busca_em_largura() {
    int qts = 0;
    int i, inicio, fim;
    int menor = 1000000;
    Tripla fila[100000];

    inicio = fim = 0;
    Tripla temp = {0};
    fila[fim++] = temp;

    memset(menorDist, 0, sizeof(menorDist));
    memset(contagem, 0, sizeof(contagem));

    contagem[0][0][0] = 1;

    while (inicio < fim) {
        int p1 = fila[inicio].a;
        int p2 = fila[inicio].b;
        int p3 = fila[inicio].c;

        inicio++;

        if (menor <= menorDist[p1][p2][p3])
            break;

        for (i = 1; i <= k; ++i) {
            if (prox[0][p1][i] > tam[0] || prox[1][p2][i] > tam[1] || prox[2][p3][i] > tam[2])
                menor = menorDist[p1][p2][p3] + 1, qts += contagem[p1][p2][p3];
            if (qts)
                continue;

            int np1 = prox[0][p1][i];
            int np2 = prox[1][p2][i];
            int np3 = prox[2][p3][i];

            if (!menorDist[np1][np2][np3]) {
                menorDist[np1][np2][np3] = menorDist[p1][p2][p3] + 1;
                contagem[np1][np2][np3] = contagem[p1][p2][p3];
                Tripla nova = {np1, np2, np3};
                fila[fim++] = nova;
            } else if (menorDist[np1][np2][np3] == menorDist[p1][p2][p3] + 1)
                contagem[np1][np2][np3] += contagem[p1][p2][p3];
        }
    }

    Par resultado;
    resultado.menor = menor;
    resultado.quantidade = qts;

    return resultado;
}
