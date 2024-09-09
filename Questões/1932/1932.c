#include <stdio.h>

#define TAMANHO_MAXIMO 200100

unsigned calcularLucroMaximo(int *precos, int dias, int taxa) {

    unsigned i;
    int precoCompra, precoVenda, lucroAcumulado;

    lucroAcumulado = 0;
    precoCompra = precoVenda = precos[0];

    for (i = 1; i < dias; ++i) {

        if ((precoVenda > precos[i] && (precoVenda - precos[i] >= taxa)) || precos[i] < precoCompra) {

            if (precoVenda - precoCompra - taxa > 0) {
                lucroAcumulado += precoVenda - precoCompra - taxa;
            }

            precoVenda = precoCompra = precos[i];
        }

        if (precos[i] > precoVenda) {
            precoVenda = precos[i];
        }
    }

    if (precoVenda - precoCompra - taxa > 0) {
        lucroAcumulado += precoVenda - precoCompra - taxa;
    }

    return lucroAcumulado;
}

int main() {
    unsigned i;
    int dias, taxa;
    int precos[TAMANHO_MAXIMO];

    scanf("%d %d", &dias, &taxa);

    for (i = 0; i < dias; ++i) {
        scanf("%d", &precos[i]);
    }

    printf("%u\n", calcularLucroMaximo(precos, dias, taxa));

    return 0;
}
