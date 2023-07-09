#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct est_Clientes
{
    char nome[50];//Letras maiusculas
    char cpf[13]; //N podem existir dois clientes com msm cpf
    char dataNasc[10];//DDMMAAAA, tem q ter mais q 18 anos
    
}Cliente;

typedef struct est_Veiculos
{
    char placa[8]; //Formato XXX9999, n pode placa igual
    char tipo;
    char modelo[31]; //Tem q ser de 4 a 30 caracteres
    int anoFabricacao;
    float valorLocacao;
    int Km;

}Veiculo;

typedef struct est_Locacao
{
    char cpf[13];
    char placa[8];
    char cartao[18];
    char data[10];

}Locacao;

void toUpper(char c[]){

    for (int i = 0; c[i] != '\0'; i++)
        c[i] = toupper(c[i]); 
}

int buscaCPF(Cliente clientes[], char cpf[], int qtdClientes){

    if (qtdClientes == 0)
        return -1;

    for (int i = 0; i < qtdClientes; i++)
        if (strcmp(clientes[i].cpf, cpf) == 0)
            return i;
    
    return -1;
}

int buscaVeiculoDaLocacao(Locacao locacao, Veiculo veiculos[], int qtdVeiculos){

    for (int i = 0; i < qtdVeiculos; i++) 
        if (strcmp(locacao.placa, veiculos[i].placa) == 0)
            return i;
    
}

int buscaLocacao(Cliente cliente, Locacao locacoes[], int qtdLocacoes){

    if (qtdLocacoes == 0)
        return -1;

    for (int i = 0; i < qtdLocacoes; i++)
        if (strcmp(cliente.cpf, locacoes[i].cpf) == 0)
            return i;
    
    return -1;
}

//Funcoes para incluir cliente
int verificaCPF(char cpf[]){

    int somador = 0;

    //Verificando primeiro digito

    for (int i = 0, j = 10; i < 9; i++, j--)
        somador += (int)(cpf[i] - '0')  * j;

    somador = (somador * 10) % 11;

    if (somador == 10)
        somador = 0;

    if (somador != (int)(cpf[9] - 48))
        return 0;

    //Verificando segundo digito

    somador = 0;

    for (int i = 0, j = 11; i < 9; i++, j--)
        somador += (int)(cpf[i] - '0')  * j;

    somador += 4;

    somador = (somador * 10) % 11;

    if (somador == 10)
        somador = 0;

    if ((char)somador != (int)(cpf[10] - 48))
        return 0;    

    return 1;
}

int cpfExistente(Cliente clientes[], int qtdClientes, char cpf[]){

   if (buscaCPF(clientes, cpf, qtdClientes) >= 0)
   {
        printf("Cliente ja cadastrado!");
        return 1;
   }

   return 0;
}

//acabar
int dataNascimentoValida(char dataNasc[]){

    return 1;
}

int incluirCliente(Cliente clientes[], int *qtdClientes){

    if (*qtdClientes == 30)
    {
        printf("Numero Maximo de clientes cadastrados");
        return 0;
    }
        
    Cliente c;

    fflush(stdin);
    printf("Nome: ");
    fgets(c.nome, 50, stdin);
    c.nome[strcspn(c.nome, "\n")] = 0; //Remove o \n do fgets
    toUpper(c.nome);

    do
    {
        fflush(stdin);
        printf("CPF: ");
        fgets(c.cpf, 13, stdin);
    } while (verificaCPF(c.cpf));
    c.cpf[strcspn(c.cpf, "\n")] = 0;

    fflush(stdin);
    printf("Data de Nascimento: ");
    fgets(c.dataNasc, 10, stdin);
    c.dataNasc[strcspn(c.dataNasc, "\n")] = 0;

    if ( !cpfExistente(clientes, *qtdClientes, c.cpf) /*&& dataNascimentoValida(c.dataNasc)*/)
    {
        clientes[*qtdClientes++] = c;
        return 1;
    }
    
    return 0;
}

void incluirClientes(Cliente clientes[], int *qtdClientes){

    if (incluirCliente(clientes, qtdClientes))
        printf("Cliente cadastrado com sucesso!\n");
}

//Funcoes para excluir cliente
int clienteEmLocacao(Cliente cliente, Locacao locacoes[], int qtdLocacoes){
    
    for (int i = 0; i <= qtdLocacoes; i++)
        if (strcmp(cliente.cpf, locacoes[i].cpf) == 0)
        {
            printf("Cliente com Locacao ativa!\n");
            return 1;
        }

    return 0;
}

void excluirCliente(Cliente clientes[], int *qtdClientes, int i){

    for (int j = i; j < *qtdClientes; j++) 
        clientes[j] = clientes[j + 1];
    
    *qtdClientes--; 

    printf("Cliente removido com sucesso!\n");
}

void excluirCliente(Cliente clientes[], Locacao locacoes[], char cpf[], int *qtdClientes, int *qtdLocacoes){
    
    int i = buscaCPF(clientes, cpf, *qtdClientes);
    if (i < 0)
        printf("CPF não Cadastrado\n");
    else if (!clienteEmLocacao(clientes[i], locacoes, *qtdLocacoes))
        excluirCliente(clientes, qtdClientes, i);
    
}

//Funcoes para Listagem de Clientes
void ordenarClientesPorCPF(Cliente clientes[], int qtdClientes){

    Cliente temp;

    for (int i = 0; i < qtdClientes; i++) {
        int minIndex = i;

        for (int j = i + 1; j < qtdClientes; j++) {
            if (strcmp(clientes[j].cpf, clientes[minIndex].cpf) < 0) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            temp = clientes[i];
            clientes[i] = clientes[minIndex];
            clientes[minIndex] = temp;
        }
    }
}

void ordenarClientesPorNome(Cliente clientes[], int qtdClientes){

    Cliente temp;

    for (int i = 0; i < qtdClientes; i++) {
        int minIndex = i;

        for (int j = i + 1; j < qtdClientes; j++) {
            if (strcmp(clientes[j].nome, clientes[minIndex].nome) < 0) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            temp = clientes[i];
            clientes[i] = clientes[minIndex];
            clientes[minIndex] = temp;
        }
    }
}
void listarClientes(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int qtdClientes, int qtdLocacoes, int qtdVeiculos){

    printf("----------------------------------------------------------------------------\n");
    printf("CPF         Nome                                               Dt nascimento\n");
    printf("----------------------------------------------------------------------------\n");

    for (int i = 0; i < qtdClientes; i++)
    {
        printf("%s %s\t%s", clientes[i].cpf, clientes[i].nome, clientes[i].dataNasc);
        int indiceLocacao = buscaLocacao(clientes[i], locacoes, qtdLocacoes);
        if (indiceLocacao > -1)
        {
            int indiceVeiculo = buscaVeiculoDaLocacao(locacoes[indiceLocacao], veiculos, qtdVeiculos);
            printf("            Placa: %s\n", veiculos[indiceVeiculo].placa);
            printf("            TTipo: %c\n", veiculos[indiceVeiculo].tipo);
            printf("            Modelo: %s\n", veiculos[indiceVeiculo].modelo);
            printf("            Km: %d\n", veiculos[indiceVeiculo].Km);
            printf("            Data da Locacao: %s", locacoes[indiceLocacao].data);
        }
    }
}

void consultaCPF(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int qtdClientes, int qtdLocacoes, int qtdVeiculos){

    ordenarClientesPorCPF(clientes, qtdClientes);
    listarClientes(clientes, locacoes, veiculos, qtdClientes, qtdLocacoes, qtdVeiculos);
}

void consultaNome(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int qtdClientes, int qtdLocacoes, int qtdVeiculos){

    ordenarClientesPorNome(clientes, qtdClientes);
    listarClientes(clientes, locacoes, veiculos, qtdClientes, qtdLocacoes, qtdVeiculos);
}

//Menus
void menuClientes(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int *qtdClientes, int *qtdLocacoes, int *qtdVeiculos){

    printf("\n================\n");
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
            incluirClientes(clientes, qtdClientes);
            break;

        case 2:
            char cpf[13];
            printf("Digite o CPF do cliente: ");
            fflush(stdin);
            fgets(cpf, 13, stdin);
            excluirCliente(clientes, locacoes, cpf, qtdClientes, qtdLocacoes);
            break;

        case 3:
            if (*qtdClientes == 0)
                printf("Sem Clientes cadastrados");
            else            
                consultaCPF(clientes, locacoes, veiculos, *qtdClientes, *qtdLocacoes, *qtdVeiculos);
            break;

        case 4:
            if (*qtdClientes == 0)
                printf("Sem Clientes cadastrados");
            else            
                consultaNome(clientes, locacoes, veiculos, *qtdClientes, *qtdLocacoes, *qtdVeiculos);
            break;

        case 5:
            break;

        default:
            printf("Opcao Invalida\n");
            break;
        }
    } while (opc != 5);

}
void imprimeMenu(Cliente clientes[], Veiculo veiculos[], Locacao locacoes[], int *qtdClientes, int *qtdVeiculos, int *qtdLocacoes){
    
    int opc;
    int flag;

    do
    {   
        printf("\n===========================================\n");
        printf("Locadora de Veiculos - Menu Principal (1.0)\n");
        printf("===========================================\n");
        printf("  1 - Clientes\n");
        printf("  2 - Veiculos\n");
        printf("  3 - Locacoes\n");
        printf("  4 - Fim\n");

        do
        {
            flag = 0;

            printf("Opcao: ");
            scanf("%d", &opc);

            switch (opc)
            {
                case 1:
                    menuClientes(clientes, locacoes, veiculos, qtdClientes, qtdLocacoes, qtdVeiculos);
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
                    flag = 1;
                    break;
            }
        } while (flag);   
    } while (opc != 4);

}
int main(){

    Cliente clientes[50];
    Veiculo veiculos[50];
    Locacao locacoes[50];

    int qtdClientes = 0, qtdVeiculos = 0, qtdLocacoes = 0;

    imprimeMenu(clientes, veiculos, locacoes, &qtdClientes, &qtdVeiculos, &qtdLocacoes);

    return 0;
}
