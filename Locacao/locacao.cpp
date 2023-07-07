#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct est_Clientes{
    char nome[50];//Letras maiusculas
    char cpf[13]; //N podem existir dois clientes com msm cpf
    char dataNasc[10];//DDMMAAAA, tem q ter mais q 18 anos
    }Cliente;

typedef struct est_Veiculos{
    char placa[8]; //Formato XXX9999, n pode placa igual
    char tipo;
    char modelo[31]; //Tem q ser de 4 a 30 caracteres
    int anoFabricacao;
    float valorLocacao;
    int Km;
}Veiculo;

//Funcoes para incluir cliente
int verificaCPF(char cpf[]){

    int somador = 0;

    for (int i = 0, j = 10; i < 11; i++, j--)
    {
        somador += cpf[i] *
    }


}
int cpfExistente(Cliente clientes[], int tamanho, Cliente c){

    for (int i = 0; i < tamanho; i++)
    {
        if (strcmp(clientes[i].cpf, c.cpf) == 0)
        {
            printf("\nCPF já cadastrado");
            return 0;
        }
    }
    return 1;
}

int dataNascimentoValida(char dataNasc[]){



}
int incluirCliente(Cliente clientes[], int tamanho){

    if (tamanho == 30)
        return 0;

    Cliente c;

    fflush(stdin);
    printf("Nome: ");
    fgets(c.nome, 50, stdin);

    do
    {
        flush(stdin);
        printf("\nCPF: ");
        fgets(c.cpf, 13, stdin);
    } while (verificaCPF(c.cpf));

    fflush(stdin);
    printf("\nData de Nascimento: ");
    fgets(c.dataNasc, 10, stdin);


    return (cpfExistente(clientes, tamanho, c) && dataNascimentoValida(c.dataNasc));
}

void incluirClientes(Cliente clientes[], int *tamanho){

    if (incluirCliente(clientes, *tamanho))
        printf("Cliente cadastrado com sucesso!");
    else
        printf("Numero Maximo de clientes atingido.");
}

void menuClientes(){

    printf("================\n");
    printf("Menu de Clientes\n");
    printf("================\n");
    printf("  1 - Incluir\n");
    printf("  2 - Excluir\n");
    printf("  3 - Consultar por CPF\n");
    printf("  4 - Consultar por Nome\n");
    printf("  5 - Voltar\n");

    int opc;

    do
    {
        printf("Opcao: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
           // incluirClientes();
            break;

        case 2:
            //excluirCliente();
            break;

        case 3:
            //consultaCPF();
            break;

        case 4:
            //consultaNome();
            break;

        case 5:
            break;

        default:
            printf("Opcao Invalida\n");
            break;
        }
    } while (opc != 5);

}
void imprimeMenu(){

    printf("===========================================\n");
    printf("Locadora de Veiculos - Menu Principal (1.0)\n");
    printf("===========================================\n");
    printf("  1 - Clientes\n");
    printf("  2 - Veiculos\n");
    printf("  3 - Locacoes\n");
    printf("  4 - Fim\n");

    int opc;

    do
    {
        printf("Opcao: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            menuClientes();
            break;

        case 2:
            //menuVeiculos();
            break;

        case 3:
           // menuLocacao();
            break;

        case 4:
            printf("Finalizando...");
            break;

        default:
            printf("Opcao Invalida\n");
            break;
        }
    } while (opc != 4);


}
int main(){

    imprimeMenu();
    return 0;
}