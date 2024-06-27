// Nome: Iago Rosa de Oliveira -> RA: 24.123.056-4

#include <stdio.h>
#include "funcoes.h"

int main() {

    // Colocando o struct numa lista com máximo de clientes.
    cliente clientes[MAX_CLIENTES];

    // Criando um contador para controlar a quantidade de clientes.
    int total_clientes = 0;

    // Arquivo para os dados dos clientes.
    FILE *f = fopen("clientes", "rb");
    if (f != NULL) {
        fread(clientes, sizeof(cliente), MAX_CLIENTES, f);
        fclose(f);
    }

    // Arquivo para contagem dos clientes.
    f = fopen("total", "rb");
    if (f != NULL) {
        fread(&total_clientes, sizeof(int), 1, f);
        fclose(f);
    }

    int opcao;

    // Loop para selecionar a opção desejada.
    while (1) {
        menu();
        printf("Selecione uma opcao: ");
        scanf("%d", &opcao);
        if (opcao == 1) {
            novo_cliente(clientes, &total_clientes);
        } else if (opcao == 2) {
            apagar_cliente(clientes, &total_clientes);
        } else if (opcao == 3) {
            listar_clientes(clientes, total_clientes);
        } else if (opcao == 4) {
            debito(clientes, total_clientes);
        } else if (opcao == 5) {
            deposito(clientes, total_clientes);
        } else if (opcao == 6) {
            extrato(clientes, total_clientes);
        } else if (opcao == 7) {
            transferencia(clientes, total_clientes);
        } else if (opcao == 8) {
            livre(clientes, total_clientes);
        } else if (opcao == 9) {
            break;
        } else {
            printf("Erro, escolha novamente!\n");
        }
    }

    f = fopen("clientes", "wb");
    fwrite(clientes, sizeof(cliente), 100, f);
    fclose(f);

    f = fopen("total", "wb");
    fwrite(&total_clientes, sizeof(int), 1, f);
    fclose(f);

    return 0;
}