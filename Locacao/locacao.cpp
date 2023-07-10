#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct est_Clientes
{
    char nome[50];//Letras maiusculas
    char cpf[13]; //N podem existir dois clientes com msm cpf
    char dataNasc[10];//DDMMAAAA, tem q ter mais q 18 anos
    
}Cliente;

typedef struct est_Veiculos
{
    char placa[9]; //Formato XXX9999, n pode placa igual
    char tipo;
    char modelo[32]; //Tem q ser de 4 a 30 caracteres
    int anoFabricacao;
    float valorLocacao;
    int Km;

}Veiculo;

typedef struct est_Locacao
{
    char cpf[13];
    char placa[9];
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

int buscaVeiculo(Locacao locacao, Veiculo veiculos[], int qtdVeiculos){

    for (int i = 0; i < qtdVeiculos; i++) 
        if (strcmp(locacao.placa, veiculos[i].placa) == 0)
            return i;
    return -1;
}

int buscaLocacao(Cliente cliente, Locacao locacoes[], int qtdLocacoes){

    if (qtdLocacoes == 0)
        return -1;

    for (int i = 0; i < qtdLocacoes; i++)
        if (strcmp(cliente.cpf, locacoes[i].cpf) == 0)
            return i;
    
    return -1;
}

bool placaCadastrada(Veiculo veiculos[], char placa[], int qtdVeiculos){

    for (int i = 0; i < qtdVeiculos; i++)
    {
        if (strcmp(veiculos[i].placa, placa) == 0)
        {
            printf("Erro: veiculo ja cadastrado\n");
            return true;
        }
    }

    return false;
}

bool placaValida(char placa[]){

    if (strlen(placa) != 7 + 1) // + 1 por causa do '\n'
    {
        printf("Placa deve estar no formato XXX9999\n");
        return false;
    }
       
    
    for (int i = 0; i < 3; i++)
    {
        if (!isalpha(placa[i]))
        {
            printf("Placa deve estar no formato XXX9999\n");
            return false;
        } 
    }        
    
    for (int i = 3; i < 7; i++) 
    {
        if (!isdigit(placa[i]))
        {
            printf("Placa deve estar no formato XXX9999\n");
            return false;
        } 
    }      
    
    return true;
}

bool tipoValido(char tipo){

    switch (tipo)
    {
        case 'c':
        case 'C':
        case 'm':
        case 'M':
            return true;
        
        default:
            printf("Categoria deve ser C ou M\n");
            return false;
    }
}

bool modeloValido(char modelo[]){

    if (strlen(modelo) < 4 + 1 || strlen(modelo) > 30 + 1) //+1 por causa do '\n'
    {
        printf("Modelo deve ter de 4 a 30 caracteres\n");
        return false;
    }
    
    return true;
}

//acabar
bool anoValido(int ano){

    return true;
}

//Funcoes para incluir cliente
bool verificaCPF(char cpf[]){

    if (strlen(cpf) != 11 + 1)// +1 por causa do '\n'
        return false;
    
    int somador = 0;

    //Verificando primeiro digito

    for (int i = 0, j = 10; i < 9; i++, j--)
        somador += (int)(cpf[i] - '0')  * j;

    somador = (somador * 10) % 11;

    if (somador == 10)
        somador = 0;

    if (somador != (int)(cpf[9] - 48))
    {
        printf("CPF invalido!\n");
        return false;
    }

    //Verificando segundo digito

    somador = 0;

    for (int i = 0, j = 11; i < 9; i++, j--)
        somador += (int)(cpf[i] - '0')  * j;

    somador += 4;

    somador = (somador * 10) % 11;

    if (somador == 10)
        somador = 0;

    if ((char)somador != (int)(cpf[10] - 48))
    {
        printf("CPF invalido!\n");
        return false;
    }
            

    return true;
}

bool cpfExistente(Cliente clientes[], int qtdClientes, char cpf[]){

   if (buscaCPF(clientes, cpf, qtdClientes) >= 0)
   {
        printf("Cliente ja cadastrado!");
        return true;
   }

   return false;
}

//acabar
bool dataNascimentoValida(char dataNasc[]){

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
    } while (!verificaCPF(c.cpf));
    c.cpf[strcspn(c.cpf, "\n")] = 0;

    fflush(stdin);
    printf("Data de Nascimento: ");
    fgets(c.dataNasc, 10, stdin);
    c.dataNasc[strcspn(c.dataNasc, "\n")] = 0;

    if (!cpfExistente(clientes, *qtdClientes, c.cpf) /*&& dataNascimentoValida(c.dataNasc)*/)
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
            int indiceVeiculo = buscaVeiculo(locacoes[indiceLocacao], veiculos, qtdVeiculos);
            if (indiceVeiculo > -1)
            {
                printf("            Placa: %s\n", veiculos[indiceVeiculo].placa);
                printf("            TTipo: %c\n", veiculos[indiceVeiculo].tipo);
                printf("            Modelo: %s\n", veiculos[indiceVeiculo].modelo);
                printf("            Km: %d\n", veiculos[indiceVeiculo].Km);
                printf("            Data da Locacao: %s", locacoes[indiceLocacao].data);
            }
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

//Funcoes para incluir veiculos

bool incluirVeiculo(Veiculo veiculos[], int *qtdVeiculos){

    if (*qtdVeiculos == 30)
    {
        printf("Numero Maximo de veiculos Cadastrados\n");
        return false;
    }

    Veiculo v;

    do
    {
        fflush(stdin);
        printf("Placa (XXX9999): ");
        fgets(v.placa, 9, stdin);
    } while (!placaValida(v.placa));

    toUpper(v.placa);
    
    do
    {
        fflush(stdin);
        printf("Tipo: ");
        scanf("%c", &v.tipo);
    } while (!tipoValido(v.tipo));

    toupper(v.tipo);

    do
    {
        fflush(stdin);
        printf("Modelo: ");
        fgets(v.modelo, 32, stdin);
    } while (!modeloValido(v.modelo));

    toUpper(v.modelo);

    do
    {
        fflush(stdin);
        printf("Ano: ");
        scanf("%d", &v.anoFabricacao);
    } while (!anoValido(v.anoFabricacao));

    printf("Valor da locacao/dia: ");
    scanf("%f", &v.valorLocacao);

    printf("Quilometragem: ");
    scanf("%f", &v.Km);

    if (placaCadastrada(veiculos, v.placa, *qtdVeiculos))
        return false;
    
    veiculos[*qtdVeiculos] = v;
    *qtdVeiculos += 1;
    return true;
}

void incluirVeiculos(Veiculo veiculos[], int *qtdVeiculos){

    if (incluirVeiculo(veiculos, qtdVeiculos))
        printf("Veiculo cadastrado com sucesso\n");
    
}

//Menus
void menuVeiculos(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int *qtdClientes, int *qtdLocacoes, int *qtdVeiculos){

    printf("\n================\n");
    printf("Menu de Veiculos\n");
    printf("================\n");
    printf("  1 - Incluir\n");
    printf("  2 - Excluir\n");
    printf("  3 - Consultar\n");
    printf("  4 - Voltar\n");

    int opc;

    do
    {
        printf("Opcao: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            incluirVeiculos(veiculos, qtdVeiculos);
            break;

        case 2:
            //excluirVeiculos(clientes, locacoes, cpf, qtdClientes, qtdLocacoes);
            break;

        case 3:
            if (*qtdVeiculos == 0)
                printf("Sem Veiculos cadastrados\n");
            else            
                //consultarVeiculos(clientes, locacoes, veiculos, *qtdClientes, *qtdLocacoes, *qtdVeiculos);
            break;

        case 4:
            break;

        default:
            printf("Opcao Invalida\n");
            break;
        }
    } while (opc != 4);

}
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
                printf("Sem Clientes cadastrados\n");
            else            
                consultaCPF(clientes, locacoes, veiculos, *qtdClientes, *qtdLocacoes, *qtdVeiculos);
            break;

        case 4:
            if (*qtdClientes == 0)
                printf("Sem Clientes cadastrados\n");
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
                    menuVeiculos(clientes, locacoes, veiculos, qtdClientes, qtdLocacoes, qtdVeiculos);
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
