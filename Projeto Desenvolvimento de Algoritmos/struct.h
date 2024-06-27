// Definindo o máximo de clientes e o máximo de operações por clientes (para controle do código).
#define MAX_CLIENTES 100
#define MAX_OPERACOES 100

// Struct com as váriaveis mais importantes a serem guardadas.
typedef struct {
    char nome[50];
    long cnpj;
    char tipo_conta[50];
    float valor_inicial;
    int senha;
    char operacoes[MAX_OPERACOES][100];
    int total_operacoes;
} cliente;