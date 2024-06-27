#include "struct.h"

// Função que retorna a posição de um cliente especifico.
int buscaCliente(long cnpj, cliente clientes[], int total);

// Função que verifica a existência do cliente.
int verificarCliente(long cnpj, cliente clientes[], int total);

// Função que verifica a senha do cliente.
int verificarSenha(int senha, cliente clientes[], int total, int posicao);

// Função que retorna o tipo de conta do cliente.
const char *obterTipo(int posicao, cliente clientes[]);

// Função para cadastrar um novo cliente.
void novo_cliente(cliente clientes[], int *total_clientes);

// Função para apagar um cliente.
void apagar_cliente(cliente clientes[], int *total_clientes);

// Função para listar todos os clientes.
void listar_clientes(cliente clientes[], int total_clientes);

// Função para debitar da conta do cliente.
void debito(cliente clientes[], int total_clientes);

// Função para depositar na conta do cliente.
void deposito(cliente clientes[], int total_clientes);

// Função que mostra o extrato do cliente.
void extrato(cliente clientes[], int total_clientes);

// Função que transfere dinheiro da conta de um cliente para outro cliente.
void transferencia(cliente clientes[], int total_clientes);

// Função sem função.
void livre(cliente clientes[], int total_clientes);

// Função que mostra o menu.
void menu();