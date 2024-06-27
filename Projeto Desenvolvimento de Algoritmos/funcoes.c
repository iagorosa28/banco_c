#include <stdio.h>
#include "struct.h"

int buscaCliente(long cnpj, cliente clientes[], int total) {

    // Percorrendo o array com o for para achar o cliente exato (com o CNPJ), assim podendo retornar a posição dele.
    for (int i = 0; i < total; i++) {
        if (clientes[i].cnpj == cnpj) {
            return i;
        }
    }
    return -1;

}

int verificarCliente(long cnpj, cliente clientes[], int total) {

    // Utilizando a função buscarCliente para retornar se o cliente existe ou não.
    int indice_cliente = buscaCliente(cnpj, clientes, total);

    if (indice_cliente >= 0) {
        printf("Cliente encontrado!\n");
        return 1;
    } else {
        printf("Cliente nao encontrado!\n");
        return 0;
    }

}

int verificarSenha(int senha, cliente clientes[], int total, int posicao) {

    // Recebendo a posição do cliente da função buscarCliente para verificar a senha.
    if (posicao >= 0) {
        if (clientes[posicao].senha == senha) {
            printf("Senha correta!\n");
            return 1;
        } else {
            printf("Senha incorreta!\n");
            return 0;
        }
    } else {
        printf("Cliente nao encontrado!\n");
        return 0;
    }

}

const char *obterTipo(int posicao, cliente clientes[]) {

    // Recebendo a posição do cliente da função buscarCliente para retornar o tipo da conta.
    return clientes[posicao].tipo_conta;

}

void novo_cliente(cliente clientes[], int *total_clientes) {

    long cnpj;
    printf("Digite o CNPJ para cadastrar uma conta (apenas numeros): ");
    scanf("%ld", &cnpj);

    // Utilizando a função verificarClientes para verificar se já existe um cliente com o CNPJ digitado.
    if (verificarCliente(cnpj, clientes, *total_clientes)) {
        printf("CNPJ ja existente! Cadastro interrompido.\n");
        return;
    }

    // Salvando as informações do cliente caso não exista um cliente com o mesmo CNPJ.
    clientes[*total_clientes].cnpj = cnpj;
    printf("Digite a razao social: ");
    scanf("%s", clientes[*total_clientes].nome);
    printf("Digite o tipo de conta: ");
    scanf("%s", clientes[*total_clientes].tipo_conta);

    // Loop que permite o usuário escolher apenas um dos dois tipos de conta.
    while (strcmp(clientes[*total_clientes].tipo_conta, "comum") != 0 &&
           strcmp(clientes[*total_clientes].tipo_conta, "plus") != 0) {
        printf("Escolha apenas entre comum ou plus: ");
        scanf("%s", clientes[*total_clientes].tipo_conta);
    }

    printf("Digite o saldo inicial: ");
    scanf("%f", &clientes[*total_clientes].valor_inicial);
    printf("Digite a senha: ");
    scanf("%d", &clientes[*total_clientes].senha);

    // Acrescentando +1 cliente no banco.
    (*total_clientes)++;

    printf("------------------------------\n");
    printf("Cliente cadastrado!\n");
    printf("------------------------------\n");

}

void apagar_cliente(cliente clientes[], int *total_clientes) {

    long cnpj;
    printf("Digite o CNPJ da conta que deseja apagar: ");
    scanf("%ld", &cnpj);

    // Guardando a posição (com o retorno da chamada da função buscarCliente) em uma variavel.
    int indice_cliente = buscaCliente(cnpj, clientes, *total_clientes);

    // Atualizando o cliente que deseja apagar com as informações dos clientes posteriores.
    if (indice_cliente >= 0) {
        for (int i = indice_cliente; i < (*total_clientes) - 1; i++) {
            clientes[i] = clientes[i + 1];
        }

        // Preenchendo o último elemento com 0.
        memset(&clientes[(*total_clientes) - 1], 0, sizeof(cliente));

        // Decrementando -1 cliente no banco.
        (*total_clientes)--;

        printf("------------------------------\n");
        printf("Cliente removido!\n");
        printf("------------------------------\n");
    } else {
        printf("Cliente nao encontrado!\n");
    }

    // * Um pouco de dúvidas sobre o "memset".

}

void listar_clientes(cliente clientes[], int total_clientes) {

    printf("\n");
    printf("Clientes:\n");

    // Usando o for para listar todos os clientes e as informações deles.
    for (int i = 0; i < total_clientes; i++) {
        printf("------------------------------\n");
        printf("Cliente %d:\n", i + 1);
        printf("Razao Social: %s\n", clientes[i].nome);
        printf("CNPJ: %ld\n", clientes[i].cnpj);
        printf("Tipo de conta: %s\n", clientes[i].tipo_conta);
        printf("Saldo da conta: %.2f\n", clientes[i].valor_inicial);
        printf("Senha: %d\n", clientes[i].senha);
        printf("------------------------------\n");
    }

    printf("\n");

}

void debito(cliente clientes[], int total_clientes) {

    long cnpj;
    int senha;
    printf("Digite o CNPJ: ");
    scanf("%ld", &cnpj);
    printf("Digite a senha: ");
    scanf("%d", &senha);

    int posicao_cliente = buscaCliente(cnpj, clientes, total_clientes);

    // Verificando a existência do cliente com o CNPJ.
    if (verificarCliente(cnpj, clientes, total_clientes)) {

        // Verificando se a senha está correta.
        if (verificarSenha(senha, clientes, total_clientes, posicao_cliente)) {

            // Confirmando o tipo de conta do cliente.
            const char *tipo_conta = obterTipo(posicao_cliente, clientes);

            float valor_debito;
            printf("Digite o valor do debito: ");
            scanf("%f", &valor_debito);

            // Se o cliente for comum, fazer a operação com base nas suas restrições.
            if (strcmp(tipo_conta, "comum") == 0) {

                // Verificando se o valor vai exceder o limite da conta.
                if (clientes[posicao_cliente].valor_inicial - valor_debito >= -1000) {

                    // Aplicando a taxa e atualizando o valor na conta.
                    float taxa = valor_debito * 0.05;
                    clientes[posicao_cliente].valor_inicial -= (valor_debito + taxa);

                    printf("------------------------------\n");
                    printf("Debito realizado!\n");
                    printf("Valor debitado: %.2f\n", valor_debito);
                    printf("Taxa aplicada: %.2f\n", taxa);
                    printf("Saldo atual: %.2f\n", clientes[posicao_cliente].valor_inicial);
                    printf("------------------------------\n");

                    // Adicionando a operação no extrato do cliente.
                    sprintf(clientes[posicao_cliente].operacoes[clientes[posicao_cliente].total_operacoes],
                            "Debito: %.2f, Taxa: %.2f", valor_debito, taxa);
                    clientes[posicao_cliente].total_operacoes++;

                } else {
                    printf("Limite de debito excedido para conta comum!\n");
                }

                // Se o cliente for plus, fazer a operação com base nas suas restrições.
            } else if (strcmp(tipo_conta, "plus") == 0) {

                // Verificando se o valor vai exceder o limite da conta.
                if (clientes[posicao_cliente].valor_inicial - valor_debito >= -5000) {

                    // Aplicando a taxa e atualizando o valor na conta.
                    float taxa = valor_debito * 0.03;
                    clientes[posicao_cliente].valor_inicial -= (valor_debito + taxa);

                    printf("------------------------------\n");
                    printf("Debito realizado!\n");
                    printf("Valor debitado: %.2f\n", valor_debito);
                    printf("Taxa aplicada: %.2f\n", taxa);
                    printf("Saldo atual: %.2f\n", clientes[posicao_cliente].valor_inicial);
                    printf("------------------------------\n");

                    // Adicionando a operação no extrato do cliente.
                    sprintf(clientes[posicao_cliente].operacoes[clientes[posicao_cliente].total_operacoes],
                            "Debito: %.2f, Taxa: %.2f", valor_debito, taxa);
                    clientes[posicao_cliente].total_operacoes++;

                } else {
                    printf("Limite de debito excedido para conta plus!\n");
                }

            } else {
                printf("Tipo de conta invalido!\n");
            }

        } else {
            printf("Senha incorreta!\n");
        }

    } else {
        printf("Cliente nao encontrado!\n");
    }

}

void deposito(cliente clientes[], int total_clientes) {

    long cnpj;
    printf("Digite o CNPJ que deseja depositar: ");
    scanf("%ld", &cnpj);

    int posicao_cliente = buscaCliente(cnpj, clientes, total_clientes);

    // Verificando a existência do cliente com o CNPJ.
    if (verificarCliente(cnpj, clientes, total_clientes)) {

        // Depositando o valor na conta do cliente.
        float valor_deposito;
        printf("Digite o valor do deposito: ");
        scanf("%f", &valor_deposito);
        clientes[posicao_cliente].valor_inicial += valor_deposito;

        printf("------------------------------\n");
        printf("Deposito realizado!\n");
        printf("Valor depositado: %.2f\n", valor_deposito);
        printf("Saldo atual: %.2f\n", clientes[posicao_cliente].valor_inicial);
        printf("------------------------------\n");

        // Adicionando a operação no extrato do cliente.
        sprintf(clientes[posicao_cliente].operacoes[clientes[posicao_cliente].total_operacoes], "Deposito: %.2f",
                valor_deposito);
        clientes[posicao_cliente].total_operacoes++;

    } else {
        printf("Cliente nao encontrado!\n");
    }

}

void extrato(cliente clientes[], int total_clientes) {

    long cnpj;
    int senha;
    printf("Digite o CNPJ: ");
    scanf("%ld", &cnpj);
    printf("Digite a senha: ");
    scanf("%d", &senha);

    int posicao_cliente = buscaCliente(cnpj, clientes, total_clientes);

    // Verificando a existência do cliente com o CNPJ.
    if (verificarCliente(cnpj, clientes, total_clientes)) {

        // Verificando se a senha está correta.
        if (verificarSenha(senha, clientes, total_clientes, posicao_cliente)) {

            printf("\n");
            printf("Extrato do cliente: %s\n", clientes[posicao_cliente].nome);
            printf("------------------------------\n");

            // Exibindo as operações do extrato do cliente.
            for (int i = 0; i < clientes[posicao_cliente].total_operacoes; i++) {
                printf("%s\n", clientes[posicao_cliente].operacoes[i]);
            }
            printf("------------------------------\n");

            printf("\n");

        } else {
            printf("Senha incorreta!\n");
        }

    } else {
        printf("Cliente não encontrado.\n");
    }

    // * Não consegui colocar as datas e os horarios das operações a tempo... (no extrato).

}

void transferencia(cliente clientes[], int total_clientes) {

    long cnpj_origem;
    int senha;
    long cnpj_destino;
    float taxa = 0;
    printf("Digite o CNPJ de origem: ");
    scanf("%ld", &cnpj_origem);
    printf("Digite a senha da conta origem: ");
    scanf("%d", &senha);
    printf("Digite o CNPJ de destino: ");
    scanf("%ld", &cnpj_destino);

    int posicao_cliente_origem = buscaCliente(cnpj_origem, clientes, total_clientes);
    int posicao_cliente_destino = buscaCliente(cnpj_destino, clientes, total_clientes);

    // Verificando a existência do cliente de origem com o CNPJ.
    if (verificarCliente(cnpj_origem, clientes, total_clientes)) {

        // Verificando se a senha da conta de origem está correta.
        if (verificarSenha(senha, clientes, total_clientes, posicao_cliente_origem)) {

            // Verificando a existência do cliente de destino com o CNPJ.
            if (verificarCliente(cnpj_destino, clientes, total_clientes)) {

                float valor_transferencia;
                printf("Digite o valor da transferencia: ");
                scanf("%f", &valor_transferencia);

                // Verificando o saldo da conta de origem.
                if (clientes[posicao_cliente_origem].valor_inicial >= valor_transferencia) {

                    // Realizando o débito na conta de origem de cliente comum.
                    if (strcmp(clientes[posicao_cliente_origem].tipo_conta, "comum") == 0) {
                        if (clientes[posicao_cliente_origem].valor_inicial - valor_transferencia >= -1000) {
                            taxa = valor_transferencia * 0.05;
                            clientes[posicao_cliente_origem].valor_inicial -= (valor_transferencia + taxa);
                        } else {
                            printf("Limite de debito excedido para conta comum!\n");
                            return;
                        }

                        // Realizando o débito na conta de origem de cliente plus.
                    } else if (strcmp(clientes[posicao_cliente_origem].tipo_conta, "plus") == 0) {
                        if (clientes[posicao_cliente_origem].valor_inicial - valor_transferencia >= -5000) {
                            taxa = valor_transferencia * 0.03;
                            clientes[posicao_cliente_origem].valor_inicial -= (valor_transferencia + taxa);
                        } else {
                            printf("Limite de debito excedido para conta plus!\n");
                            return;
                        }

                    } else {
                        printf("Tipo de conta invalido!\n");
                        return;
                    }

                    // Realizando o depósito na conta de destino.
                    clientes[posicao_cliente_destino].valor_inicial += valor_transferencia;

                    printf("------------------------------\n");
                    printf("Transferencia realizada!\n");
                    printf("Valor transferido: %.2f\n", valor_transferencia);
                    printf("Saldo atual da conta de origem: %.2f\n", clientes[posicao_cliente_origem].valor_inicial);
                    printf("Saldo atual da conta de destino: %.2f\n", clientes[posicao_cliente_destino].valor_inicial);
                    printf("------------------------------\n");

                    // Adicionando a operação no extrato do cliente origem.
                    sprintf(clientes[posicao_cliente_origem].operacoes[clientes[posicao_cliente_origem].total_operacoes],
                            "Transferencia realizada: %.2f, Taxa: %.2f", valor_transferencia, taxa);
                    clientes[posicao_cliente_origem].total_operacoes++;

                    // Adicionando a operação no extrato do cliente destino.
                    sprintf(clientes[posicao_cliente_destino].operacoes[clientes[posicao_cliente_destino].total_operacoes],
                            "Transferencia recebida: %.2f", valor_transferencia);
                    clientes[posicao_cliente_destino].total_operacoes++;

                } else {
                    printf("Saldo insuficiente na conta de origem!\n");
                }

            } else {
                printf("Cliente destino nao encontrado!\n");
            }

        } else {
            printf("Senha da conta origem incorreta!\n");
        }

    } else {
        printf("Cliente origem nao encontrado!\n");
    }

}

void livre(cliente clientes[], int total_clientes) {

    printf("------------------------------\n");
    printf("Cantinho para chorar por um ponto a mais (ler os comentarios no código).");
    printf("------------------------------\n");

    // * A operação livre passou a ser o listar_clientes, como o Prof. Leonardo disse.

}

void menu() {

    // Mostrando o menu.
    printf("1. Novo cliente\n");
    printf("2. Apaga cliente\n");
    printf("3. Listar clientes\n");
    printf("4. Debito\n");
    printf("5. Deposito\n");
    printf("6. Extrato\n");
    printf("7. Transferencia entre contas\n");
    printf("8. Operecao livre\n");
    printf("9. Sair\n");

}