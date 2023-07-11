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
    char modelo[50]; //Tem q ser de 4 a 30 caracteres
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

int buscaVeiculoPorPlaca(Veiculo veiculos[], int qtdVeiculos, char placa[]){

    for (int i = 0; i < qtdVeiculos; i++)
        if (strcmp(veiculos[i].placa, placa) == 0)
            return i;
    
    return -1;
    
}

int buscaLocacaoPorCliente(Cliente cliente, Locacao locacoes[], int qtdLocacoes){

    if (qtdLocacoes == 0)
        return -1;

    for (int i = 0; i < qtdLocacoes; i++)
        if (strcmp(cliente.cpf, locacoes[i].cpf) == 0)
            return i;
    
    return -1;
}

int buscaLocacaoPorVeiculo(Veiculo veiculo, Locacao locacoes[], int qtdLocacoes){

    if (qtdLocacoes == 0)
        return -1;

    for (int i = 0; i < qtdLocacoes; i++)
        if (strcmp(veiculo.placa, locacoes[i].placa) == 0)
            return i;
    
    return -1;
}

int buscaClientePorLocacao(Locacao locacao, Cliente clientes[], int qtdClientes){

    if (qtdClientes == 0)
        return -1;

    for (int i = 0; i < qtdClientes; i++)
        if (strcmp(locacao.cpf, clientes[i].cpf) == 0)
            return i;
    
    return -1;

}

bool placaCadastrada(Veiculo veiculos[], char placa[], int qtdVeiculos){

    for (int i = 0; i < qtdVeiculos; i++)
    {
        if (strcmp(veiculos[i].placa, placa) == 0)
        {
            return true;
        }
    }

    return false;
}

bool veiculoLocado(Veiculo veiculo, Locacao locacoes[], int qtdLocacoes){

    for (int i = 0; i < qtdLocacoes; i++)
        if (strcmp(veiculo.placa, locacoes[i].placa) == 0)
                return true;
   
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
        somador += (cpf[i] - '0')  * j;

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

    for (int i = 0, j = 11; i < 10; i++, j--)
        somador += (cpf[i] - '0') * j;

    somador = (somador * 10) % 11;

    if (somador == 10)
        somador = 0;

    if (somador != (cpf[10] - '0')) {
        printf("CPF inválido!\n");
        return false;
    }
            
    return true;
}

bool cpfExistente(Cliente clientes[], int qtdClientes, char cpf[]){

   if (buscaCPF(clientes, cpf, qtdClientes) >= 0)
   {
        printf("Cliente ja cadastrado!\n");
        return true;
   }

   return false;
}

//acabar
bool dataNascimentoValida(char dataNasc[]){

    return 1;
}

int clienteCadastrado(Cliente clientes[], int *qtdClientes){

    if (*qtdClientes == 30)
    {
        printf("Numero Maximo de clientes cadastrados\n");
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
        clientes[*qtdClientes] = c;
        *qtdClientes += 1; 
        return 1;
    }
    
    return 0;
}

void incluirClientes(Cliente clientes[], int *qtdClientes){

    if (clienteCadastrado(clientes, qtdClientes))
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

void removeCliente(Cliente clientes[], int *qtdClientes, int i){

    *qtdClientes -= 1;

    for (int j = i; j < *qtdClientes; j++) 
        clientes[j] = clientes[j + 1];
    
    printf("Cliente removido com sucesso!\n");
}

void excluirCliente(Cliente clientes[], Locacao locacoes[], char cpf[], int *qtdClientes, int *qtdLocacoes){
    
    int i = buscaCPF(clientes, cpf, *qtdClientes);
    if (i < 0)
        printf("CPF não Cadastrado\n");
    else if (!clienteEmLocacao(clientes[i], locacoes, *qtdLocacoes))
        removeCliente(clientes, qtdClientes, i);
    
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
        int tamanho = 50 - strlen(veiculos[i].modelo);
        char espacos[tamanho + 1];

        for (int j = 0; j < tamanho + 1; j++)
        {
            espacos[j] = ' ';
        }

        espacos[tamanho] = '\0';
        printf("%s %s %s %s\n", clientes[i].cpf, clientes[i].nome, espacos, clientes[i].dataNasc);
        int indiceLocacao = buscaLocacaoPorCliente(clientes[i], locacoes, qtdLocacoes);
        if (indiceLocacao > -1)
        {
            int indiceVeiculo = buscaVeiculo(locacoes[indiceLocacao], veiculos, qtdVeiculos);
            if (indiceVeiculo > -1)
            {
                printf("            Placa: %s\n", veiculos[indiceVeiculo].placa);
                printf("            TTipo: %c\n", veiculos[indiceVeiculo].tipo);
                printf("            Modelo: %s\n", veiculos[indiceVeiculo].modelo);
                printf("            Km: %d\n", veiculos[indiceVeiculo].Km);
                printf("            Data da Locacao: %s\n", locacoes[indiceLocacao].data);
            }
        }
    }

    printf("\n");
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

bool veiculoCadastrado(Veiculo veiculos[], int *qtdVeiculos){

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
        toUpper(v.placa);
    } while (!placaValida(v.placa));

    v.placa[strcspn(v.placa, "\n")] = 0;
    
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
        fgets(v.modelo, 50, stdin);
    } while (!modeloValido(v.modelo));

    toUpper(v.modelo);
    v.modelo[strcspn(v.modelo, "\n")] = 0;

    do
    {
        fflush(stdin);
        printf("Ano: ");
        scanf("%d", &v.anoFabricacao);
    } while (!anoValido(v.anoFabricacao));

    printf("Valor da locacao/dia: ");
    scanf("%f", &v.valorLocacao);

    printf("Quilometragem: ");
    scanf("%d", &v.Km);

    if (placaCadastrada(veiculos, v.placa, *qtdVeiculos))
    {
        printf("Erro: veiculo ja cadastrado\n");
        return false;
    }
        
    veiculos[*qtdVeiculos] = v;
    *qtdVeiculos += 1;
    return true;
}

void incluirVeiculos(Veiculo veiculos[], int *qtdVeiculos){

    if (veiculoCadastrado(veiculos, qtdVeiculos))
        printf("Veiculo cadastrado com sucesso\n");
    
}

//Funcoes para excluir veiculos

void removeVeiculo(Veiculo veiculos[], int *qtdVeiculos, int i){
    
    *qtdVeiculos -= 1; 

    for (int j = i; j < *qtdVeiculos; j++) 
        veiculos[j] = veiculos[j + 1];

    printf("Veiculo removido com sucesso!\n");

}

void excluiVeiculo(Locacao locacoes[], Veiculo veiculos[], int *qtdLocacoes, int *qtdVeiculos, char placa[]){

    int i = buscaVeiculoPorPlaca(veiculos, *qtdVeiculos, placa);

    if(i == -1)
        printf("Placa nao cadastrada");
    else if (veiculoLocado(veiculos[i], locacoes, *qtdLocacoes))
        printf("Veiculo em Locacao");
    else
        removeVeiculo(veiculos, qtdVeiculos, i);

}

//Funcoes para consultar o veiculo

void ordenaVeiculos(Veiculo veiculos[], int qtdVeiculos){

    Veiculo temp;

    for (int i = 0; i < qtdVeiculos; i++) {
        int minIndex = i;

        for (int j = i + 1; j < qtdVeiculos; j++) {
            if (strcmp(veiculos[j].placa, veiculos[minIndex].placa) < 0) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            temp = veiculos[i];
            veiculos[i] = veiculos[minIndex];
            veiculos[minIndex] = temp;
        }
    }
}

void listarVeiculos(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int qtdClientes, int qtdLocacoes, int qtdVeiculos){

    printf("----------------------------------------------------------------\n");
    printf("  Placa   Tipo Modelo                          Locacao  Km atual\n");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < qtdVeiculos; i++)
    {
        int tamanho = 31 - strlen(veiculos[i].modelo);
        char espacos[tamanho + 1];

        for (int j = 0; j < tamanho + 1; j++)
        {
            espacos[j] = ' ';
        }

        espacos[tamanho] = '\0';
        
        printf(" %s   %c   %s  %s  %.2f  %d\n", veiculos[i].placa, veiculos[i].tipo, veiculos[i].modelo, espacos, veiculos[i].valorLocacao, veiculos[i].Km);

        if (veiculoLocado(veiculos[i], locacoes, qtdLocacoes))
        {
            int indiceLocacao = buscaLocacaoPorVeiculo(veiculos[i], locacoes, qtdLocacoes);
            int indiceCliente = buscaClientePorLocacao(locacoes[indiceLocacao], clientes, qtdClientes);
            printf("               CPF: %s\n", clientes[indiceCliente].cpf);
            printf("               Nome: %s\n", clientes[indiceCliente].nome);
            printf("               Dt nascimento: %s\n", clientes[indiceCliente].dataNasc);
            printf("               Data da Locacao%s\n", locacoes[indiceLocacao].data);
        }
    }
    printf("\n");
}

//funcoes para locar veiculo
bool verificaErrosLocacao(Cliente clientes[], Locacao locacoes[], Locacao l, Veiculo veiculos[], int qtdClientes, int qtdLocacoes, int qtdVeiculos){

    int indiceCliente = buscaCPF(clientes, l.cpf, qtdClientes);
    int indiceVeiculo = buscaVeiculoPorPlaca(veiculos, qtdVeiculos, l.placa);

    if (indiceCliente < 0)
    {
        printf("ERRO: Cliente nao encontrado\n");
        return false;
    }
    else if (buscaLocacaoPorCliente(clientes[indiceCliente], locacoes, qtdLocacoes) > -1)
    {
        printf("ERRO: Cliente ja tem uma locacao\n");
        return false;
    }
    else if (indiceVeiculo < 0)
    {
        printf("ERRO: Veiculo nao encontrado\n");
        return false;
    }
    else if (buscaLocacaoPorVeiculo(veiculos[indiceVeiculo], locacoes, qtdLocacoes) > -1)
    {
        printf("ERRO: Veiculo ja esta alugado\n");
        return false;
    }
    
    return true;
}

bool incluirLocacao(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int *qtdClientes, int *qtdLocacoes, int *qtdVeiculos){

    Locacao l;

    do
    {
        fflush(stdin);
        printf("CPF: ");
        fgets(l.cpf, 13, stdin);

    } while (!verificaCPF(l.cpf));

    l.cpf[strcspn(l.cpf, "\n")] = 0;

    do
    {
        fflush(stdin);
        printf("Placa (XXX9999): ");
        fgets(l.placa, 13, stdin);
        toUpper(l.placa);

    } while (!placaValida(l.placa));

    l.placa[strcspn(l.placa, "\n")] = 0;

 //   do
   // {
        fflush(stdin);
        printf("Numero CC: ");
        fgets(l.cartao, 13, stdin);

   // } while (!cartaoValido(l.cartao));

    l.cartao[strcspn(l.cartao, "\n")] = 0;

    //l.data = data atual do pc

    if (verificaErrosLocacao(clientes, locacoes, l, veiculos, *qtdClientes, *qtdLocacoes, *qtdVeiculos))
    {
        locacoes[*qtdLocacoes] = l;
        *qtdLocacoes += 1;
        return true;
    }
    else    
        return false;
}

void locarVeiculo(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int *qtdClientes, int *qtdLocacoes, int *qtdVeiculos){

    printf("\n--------------------\n");
    printf("Locacao de Veiculo\n");
    printf("--------------------\n");
    
    if (incluirLocacao(clientes, locacoes, veiculos, qtdClientes, qtdLocacoes, qtdVeiculos))
        printf("Locacao realizada com sucesso!\n");
    
}

//funcoes para devolver veiculo

void lerDados(char cpf[], char dataDevolucao[], int *km){

    do
    {
        fflush(stdin);
        printf("CPF: ");
        fgets(cpf, 13, stdin);

    } while (!verificaCPF(cpf));

    cpf[strcspn(cpf, "\n")] = 0;

    fflush(stdin);
    printf("Data de devolucao (DDMMAAAA): ");
    fgets(dataDevolucao, 13, stdin);

    dataDevolucao[strcspn(dataDevolucao, "\n")] = 0;

    printf("Quilometragem: ");
    scanf("%d", km);
}

bool verificaErrosDevolucao(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int qtdClientes, int qtdLocacoes, int qtdVeiculos, int km, char cpf[], char dataDevolucao[]){

    int indiceCliente = buscaCPF(clientes, cpf, qtdClientes);

    if (indiceCliente < 0)
    {
        printf("ERRO: Cliente nao encontrado\n");
        return false;
    }
    else if (buscaLocacaoPorCliente(clientes[indiceCliente], locacoes, qtdLocacoes) < 0)
    {
        printf("ERRO: Cliente nao possui locacao\n");
        return false;
    }
    /*else if (data invalida)
    {
        printf("ERRO: Data da devolucao deve ser menor ou igual a hoje e maior ou igual a data da locacao\n");
        return false;
    }*/
    else 
    {
        int indiceLocacao = buscaLocacaoPorCliente(clientes[indiceCliente], locacoes, qtdLocacoes);
        int indiceVeiculo = buscaVeiculoPorPlaca(veiculos, qtdVeiculos, locacoes[indiceLocacao].placa);

        if (km < veiculos[indiceVeiculo].Km)
        {
            printf("ERRO: Quilometragem deve ser maior ou igual a quilometragem da locacao\n");
            return false;
        }

        return true;
    }
}

void removeLocacao(Cliente cliente, Locacao locacoes[], int *qtdLocacoes, int indiceLocacao ){
    
    *qtdLocacoes -= 1; 

    for (int i = indiceLocacao ; i < *qtdLocacoes; i++) 
        locacoes[i] = locacoes[i + 1];
   
}

float calculaPreco(Locacao locacoes[], Veiculo veiculos[], int qtdVeiculos, int indiceLocacao, int km){

    float preco;
    int indiceVeiculo = buscaVeiculoPorPlaca(veiculos, qtdVeiculos, locacoes[indiceLocacao].placa);

    preco = (/*(dataLocacao - dataDevolucao) * */ veiculos[indiceVeiculo].valorLocacao)
            + (km - veiculos[indiceVeiculo].Km); 

    veiculos[indiceVeiculo].Km = km;

    return preco;
}

bool veiculoDevolvido(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int *qtdClientes, int *qtdLocacoes, int *qtdVeiculos){

    char cpf[13];
    char dataDevolucao[10];
    int km;

    lerDados(cpf, dataDevolucao, &km);

    if(verificaErrosDevolucao(clientes, locacoes, veiculos, *qtdClientes, *qtdLocacoes, *qtdVeiculos, km, cpf, dataDevolucao))
    {
        int i = buscaCPF(clientes, cpf, *qtdClientes);
        int j = buscaLocacaoPorCliente(clientes[i], locacoes, *qtdLocacoes);
        float preco = calculaPreco(locacoes, veiculos, *qtdVeiculos, j, km);

        removeLocacao(clientes[i], locacoes, qtdLocacoes, i);
        
        printf("Devolucao realizada com sucesso. Valor a pagar R$%.2f", preco);
        return true;
    }
    else 
        return false;
}

void devolverVeiculo(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int *qtdClientes, int *qtdLocacoes, int *qtdVeiculos){

    printf("\n--------------------\n");
    printf("Devolucao de Veiculo\n");
    printf("--------------------\n");

    if (veiculoDevolvido(clientes, locacoes, veiculos, qtdClientes, qtdLocacoes, qtdVeiculos))
    {
        //calculaPreco
    }
        

}

//funcoes para listar Locacao

void listarLocacao(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int qtdClientes, int qtdLocacoes, int qtdVeiculos){

    printf("\n----------------------------------------------------------------------------\n");
    printf("CPF         Nome                                               Dt nascimento\n");
    printf("----------------------------------------------------------------------------\n");

    ordenarClientesPorCPF(clientes, qtdClientes);

    for (int i = 0; i < qtdClientes; i++)
    {
        int indiceLocacao = buscaLocacaoPorCliente(clientes[i], locacoes, qtdLocacoes);

        if (indiceLocacao > -1)
        {
            int tamanho = 48 - strlen(clientes[i].nome);
            char espacos[tamanho + 1];

            for (int j = 0; j < tamanho + 1; j++)
                espacos[j] = ' ';
        
            printf("%s %s %s %s\n", clientes[i].cpf, clientes[i].nome, espacos, clientes[i].dataNasc);

            int indiceVeiculo = buscaVeiculoPorPlaca(veiculos, qtdVeiculos, locacoes[indiceLocacao].placa);

            printf("            Placa: %s\n", veiculos[indiceLocacao].placa);
            printf("            Tipo: %c\n", veiculos[indiceLocacao].tipo);
            printf("            Modelo: %s\n", veiculos[indiceLocacao].modelo);
            printf("            Quilometragem: %d\n", veiculos[indiceLocacao].Km);
            //printf("Placa: %s", locacoes[indiceLocacao].data);
        }
    }
    
    printf("----------------------------------------------------------------------------\n");
}

//Menus
void menuLocacao(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int *qtdClientes, int *qtdLocacoes, int *qtdVeiculos){

    int opc;

    do
    {

        printf("\n================\n");
        printf("Menu de Locacao\n");
        printf("================\n");
        printf("  1 - Locar\n");
        printf("  2 - Devolver\n");
        printf("  3 - Consultar\n");
        printf("  4 - Voltar\n");

        bool flag;

        do
        {
            flag = false;

            printf("Opcao: ");
            scanf("%d", &opc);

            switch (opc)
            {
                case 1:
                    if (*qtdVeiculos == 0 && *qtdClientes == 0)
                        printf("Sem veiculos e clientes cadastrados!");
                    else if (*qtdClientes == 0)
                        printf("Sem clientes cadastrados!");
                    else if (*qtdVeiculos == 0)
                        printf("Sem veiculos cadastrados!");
                    else         
                        locarVeiculo(clientes, locacoes, veiculos, qtdClientes, qtdLocacoes, qtdVeiculos);
                    break;

                case 2:
                    if (*qtdLocacoes == 0)
                        printf("Sem veiculos Locados");
                    else
                        devolverVeiculo(clientes, locacoes, veiculos, qtdClientes, qtdLocacoes, qtdVeiculos);
                    break;        

                case 3:
                    if (*qtdLocacoes == 0)
                        printf("Sem Veiculos locados!\n");
                    else            
                        listarLocacao(clientes, locacoes, veiculos, *qtdClientes, *qtdLocacoes, *qtdVeiculos);
                    break;

                case 4:
                    break;

                default:
                    flag = true;
                    printf("Opcao Invalida\n");
                    break;
            
            }
        } while (flag);   
        
    } while (opc != 4);
}

void menuVeiculos(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int *qtdClientes, int *qtdLocacoes, int *qtdVeiculos){
    
    int opc;

     do
    {
        printf("\n================\n");
        printf("Menu de Veiculos\n");
        printf("================\n");
        printf("  1 - Incluir\n");
        printf("  2 - Excluir\n");
        printf("  3 - Consultar\n");
        printf("  4 - Voltar\n");

        bool flag;

        do
        {
            flag = false;
            printf("Opcao: ");
            scanf("%d", &opc);

            switch (opc)
            {
                case 1:
                    incluirVeiculos(veiculos, qtdVeiculos);
                    break;

                case 2:

                    if (*qtdVeiculos == 0)
                        printf("Sem veiculos cadastrados!");
                    else
                    {
                        char placa[9];
                        bool loop;

                        do
                        {
                            loop = false;
                            fflush(stdin);
                            printf("Placa: ");
                            fgets(placa, 9, stdin);

                            if (!placaValida(placa))
                                loop = true;
                            
                        } while (loop);
                        
                        toUpper(placa);
                        placa[strcspn(placa, "\n")] = 0;
                        excluiVeiculo(locacoes, veiculos, qtdLocacoes, qtdVeiculos, placa);
                    }
                    
                    break;

                case 3:
                    if (*qtdVeiculos == 0)
                        printf("Sem Veiculos cadastrados");
                    else            
                        listarVeiculos(clientes, locacoes, veiculos, *qtdClientes, *qtdLocacoes, *qtdVeiculos);
                    break;

                case 4:
                    break;

                default:
                    flag = true;
                    printf("Opcao Invalida\n");
                    break;
            }

        } while (flag);
    
    } while (opc != 4);
}

void menuClientes(Cliente clientes[], Locacao locacoes[], Veiculo veiculos[], int *qtdClientes, int *qtdLocacoes, int *qtdVeiculos){

   int opc;  
    
    do
    {
    
        printf("\n================\n");
        printf("Menu de Clientes\n");
        printf("================\n");
        printf("  1 - Incluir\n");
        printf("  2 - Excluir\n");
        printf("  3 - Consultar por CPF\n");
        printf("  4 - Consultar por Nome\n");
        printf("  5 - Voltar\n");

        bool flag;

        do
        {
            flag = false;
            printf("Opcao: ");
            scanf("%d", &opc);

            switch (opc)
            {
                case 1:
                    incluirClientes(clientes, qtdClientes);
                    break;

                case 2:
                    if (*qtdClientes == 0)
                        printf("Sem clientes cadastrados!");
                    else
                    {
                        char cpf[13];
                        bool loop;

                        do
                        {
                            printf("Digite o CPF do cliente: ");
                            fflush(stdin);
                            fgets(cpf, 13, stdin);
                            loop = verificaCPF(cpf);
                            
                        } while (!loop);

                        cpf[strcspn(cpf, "\n")] = 0;
                        excluirCliente(clientes, locacoes, cpf, qtdClientes, qtdLocacoes);
                    }
                    
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
                    flag = true;
                    break;
            }

        } while (flag);
           
    } while (opc != 5);
}

void imprimeMenu(Cliente clientes[], Veiculo veiculos[], Locacao locacoes[], int *qtdClientes, int *qtdVeiculos, int *qtdLocacoes){
    
    int opc;
    bool flag;

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
            flag = false;

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
                    menuLocacao(clientes, locacoes, veiculos, qtdClientes, qtdLocacoes, qtdVeiculos);
                    break;

                case 4:
                    printf("Finalizando...");
                    break;

                default:
                    printf("Opcao Invalida\n");
                    flag = true;
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
