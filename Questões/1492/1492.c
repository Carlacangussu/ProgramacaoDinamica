#include <stdio.h>
#include <string.h>
#include <unistd.h>

long long int memoizacao[60][60][2];

long long int contarUns(const long long int *numero, int bitAtual, int acumulado, int limiteSuperior) {
    if (bitAtual == -1) {
        return acumulado;
    }

    if (memoizacao[bitAtual][acumulado][limiteSuperior] != -1) {
        return memoizacao[bitAtual][acumulado][limiteSuperior];
    }
    long long int resultado = contarUns(numero, bitAtual - 1, acumulado, !(((*numero) >> bitAtual) & (long long int)1) && limiteSuperior);

    if (!limiteSuperior || (((*numero) >> bitAtual) & 1)) {
        resultado += contarUns(numero, bitAtual - 1, acumulado + 1, (((*numero) >> bitAtual) & (long long int)1) && limiteSuperior);
    }

    return memoizacao[bitAtual][acumulado][limiteSuperior] = resultado;
}

long long int contarUnsIntervalo(long long int numeroA, long long int numeroB) {
    numeroA--;
    memset(memoizacao, -1, sizeof(memoizacao));
    long long int qtdUnsB = contarUns(&numeroB, 55, 0, 1);
    memset(memoizacao, -1, sizeof(memoizacao));
    long long int qtdUnsA = contarUns(&numeroA, 55, 0, 1);
    return qtdUnsB - qtdUnsA;
}

int main() {
    long long int numeroA, numeroB;

    while (scanf("%lld %lld", &numeroA, &numeroB) != EOF) {
        printf("%lld\n", contarUnsIntervalo(numeroA, numeroB));
    }

    return 0;
}
