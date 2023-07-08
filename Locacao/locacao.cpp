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

}Locacao;

void toUpper(char c[]){

    for (int i = 0; c[i] != '\n'; i++)
        c[i] = toupper(c[i]); 
}

int buscaCPF(Cliente clientes[], char cpf[], int qtdClientes){

    for (int i = 0; i <= qtdClientes; i++)
        if (strcmp(clientes[i].cpf, cpf) == 0)
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
    toUpper(c.nome);

    do
    {
        fflush(stdin);
        printf("CPF: ");
        fgets(c.cpf, 13, stdin);
    } while (verificaCPF(c.cpf));

    fflush(stdin);
    printf("Data de Nascimento: ");
    fgets(c.dataNasc, 10, stdin);

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
            printf("Cliente com Locacao ativa!");
            return 1;
        }

    return 0;
}

void excluirCliente(Cliente clientes[], int *qtdClientes, int i){

    for (int j = i; j <= *qtdClientes; j++) 
        clientes[j] = clientes[j + 1];
    
    *qtdClientes--; 

    printf("Cliente removido com sucesso!");
}

void excluirCliente(Cliente clientes[], Locacao locacoes[], char cpf[], int *qtdClientes, int *qtdLocacoes){
    
    int i = buscaCPF(clientes, cpf, *qtdClientes);
    if (i < 0 && !clienteEmLocacao(clientes[i], locacoes, *qtdLocacoes))
        printf("CPF não Cadastrado");
    else
        excluirCliente(clientes, qtdClientes, i);
}

//Menus
void menuClientes(Cliente clientes[], Locacao locacoes[], int *qtdClientes, int *qtdLocacoes){

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
            incluirClientes(clientes, qtdClientes);
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
void imprimeMenu(Cliente clientes[], Veiculo veiculos[], Locacao locacoes[], int *qtdClientes, int *qtdVeiculos, int *qtdLocacoes){
    
    int opc;
    int flag;

    do
    {   
        printf("===========================================\n");
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
                    menuClientes(clientes, locacoes, qtdClientes, qtdLocacoes);
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
