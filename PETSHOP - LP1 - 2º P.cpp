#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>


struct cadastro {
    char nome[100];
    double tel;
    char nome_animal[100];
    char servico[20];
    char animal[20];
    int porte_animal;
    float valor_servico; 
    struct cadastro *proximoPtr;
};			

typedef struct cadastro Cadastro;

void consumeNewline() {
        int c;
    while ((c = getchar()) != '\n' && c != EOF);
} //função para corrigir erros de pular linha

int contar_cadastros(Cadastro *cadastroPtr) {
    int contador = 0;
    while (cadastroPtr != NULL) {
        contador++;
        cadastroPtr = cadastroPtr->proximoPtr;
    }
    return contador;
} //função de contar os cadastros

char* formatar_numero_telefone(long long num) {
    char str[20];
    sprintf(str, "%lld", num);

    static char formatado[20];  
    formatado[0] = '(';
    formatado[1] = str[0];
    formatado[2] = str[1];
    formatado[3] = ')';
    formatado[4] = ' ';
    formatado[5] = str[2];
    formatado[6] = ' ';
    formatado[7] = str[3];
    formatado[8] = str[4];
    formatado[9] = str[5];
    formatado[10] = str[6];
    formatado[11] = '-';
    formatado[12] = str[7];
    formatado[13] = str[8];
    formatado[14] = str[9];
    formatado[15] = str[10];
    formatado[16] = '\0';

    return formatado;
} //função de formatar o numero de telefone do cadastro e printar (xx) x xxxx-xxxx

void criarPastaEArquivo(const char *nome_arquivo, Cadastro *cadastroPtr, int contagem_tosa, int contagem_banho, int contagem_tosa_banho, 
						int contagem_cachorro, int contagem_gato, int contagem_pequeno, int contagem_medio, int contagem_grande, float total_ganho, 
						float total_tosa,  float total_banho, float total_tosa_banho) {
    char caminho_pasta_petshop[200];
    char caminho_subpasta[200];
    char caminho_relatorio[200];
    char caminho_clientes[200];
    char caminho_recibo[200];

    // Caminho da pasta central "PETSHOP"
    sprintf(caminho_pasta_petshop, "PETSHOP");

    // Criação da pasta central "PETSHOP"
    if (CreateDirectoryA(caminho_pasta_petshop, NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
        printf("Pasta 'PETSHOP' criada com sucesso.\n");
    } else {
        printf("Falha ao criar a pasta 'PETSHOP'.\n");
        return;  // Return on failure
    }

    // Caminho para a subpasta dentro de "PETSHOP"
    sprintf(caminho_subpasta, "%s/%s", caminho_pasta_petshop, nome_arquivo);

    // Criação da subpasta dentro de "PETSHOP"
    if (CreateDirectoryA(caminho_subpasta, NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
        printf("Pasta '%s' criada com sucesso.\n", nome_arquivo);
    } else {
        printf("Falha ao criar a pasta '%s'.\n", nome_arquivo);
        return; 
    }

    // Caminhos para os arquivos dentro da subpasta
    sprintf(caminho_relatorio, "%s/relatorio.txt", caminho_subpasta);
    sprintf(caminho_clientes, "%s/clientes_cadastrados.txt", caminho_subpasta);
    sprintf(caminho_recibo, "%s/recibo.txt", caminho_subpasta);

    // Criação dos arquivos dentro da subpasta
    HANDLE arquivo_relatorio = CreateFileA(caminho_relatorio, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE arquivo_clientes = CreateFileA(caminho_clientes, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE arquivo_recibo = CreateFileA(caminho_recibo, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (arquivo_relatorio != INVALID_HANDLE_VALUE && arquivo_clientes != INVALID_HANDLE_VALUE && arquivo_recibo != INVALID_HANDLE_VALUE) {
        // Fechar os arquivos após a criação
        CloseHandle(arquivo_relatorio);
        CloseHandle(arquivo_clientes);
        CloseHandle(arquivo_recibo);

        printf("Subpasta e arquivos adicionados ao diretório.\n");

        // RECIBO
        FILE *arquivo_recibo = fopen(caminho_recibo, "w");

        if (arquivo_recibo != NULL) {
            fprintf(arquivo_recibo, "_______________________________________________________________________________________________\n");
            fprintf(arquivo_recibo, "\n                           RECIBO\n");
            fprintf(arquivo_recibo, "Total ganho: R$ %.2f\n", total_ganho);
            fprintf(arquivo_recibo, "\n");
            fprintf(arquivo_recibo, "Receita:\n");
            fprintf(arquivo_recibo, "- Tosa: R$ %.2f\n", total_tosa);
            fprintf(arquivo_recibo, "- Banho: R$ %.2f\n", total_banho);
            fprintf(arquivo_recibo, "- Banho e tosa: R$ %.2f\n", total_tosa_banho);
            fprintf(arquivo_recibo, "\n_______________________________________________________________________________________________\n");

            // Fechar o arquivo após a escrita
            fclose(arquivo_recibo);
        } else {
            printf("Falha ao adicionar subpasta e arquivos ao diretório.\n");
            return;  
        }

        // RELATÓRIO
        FILE *arquivo_relatorio = fopen(caminho_relatorio, "w");

        if (arquivo_relatorio != NULL) {
            int total = contar_cadastros(cadastroPtr);

            fprintf(arquivo_relatorio, "_______________________________________________________________________________________________\n");
            fprintf(arquivo_relatorio, "\n                             RELATÓRIO                             \n");
            fprintf(arquivo_relatorio, "Total de clientes atendidos: %d\n", total);
            fprintf(arquivo_relatorio, "\n");
            fprintf(arquivo_relatorio, "Serviços realizados:\n");
            fprintf(arquivo_relatorio, "- Tosa: %d\n", contagem_tosa);
            fprintf(arquivo_relatorio, "- Banho: %d\n", contagem_banho);
            fprintf(arquivo_relatorio, "- Banho e tosa: %d\n", contagem_tosa_banho);
            fprintf(arquivo_relatorio, "\n");
            fprintf(arquivo_relatorio, "Animais atendidos:\n");
            fprintf(arquivo_relatorio, "- Cachorros: %d\n", contagem_cachorro);
            fprintf(arquivo_relatorio, "- Gatos: %d\n", contagem_gato);
            fprintf(arquivo_relatorio, "\n");
            fprintf(arquivo_relatorio, "Portes atendidos:\n");
            fprintf(arquivo_relatorio, "- Pequeno: %d\n", contagem_pequeno);
            fprintf(arquivo_relatorio, "- Médio: %d\n", contagem_medio);
            fprintf(arquivo_relatorio, "- Grande: %d\n", contagem_grande);
            fprintf(arquivo_relatorio, "\n_______________________________________________________________________________________________\n");

            // Fechar o arquivo após a escrita
            fclose(arquivo_relatorio);
        } else {
            printf("Falha ao adicionar subpasta e arquivos ao diretório.\n");
            return;  
        }

        // CLIENTES CADASTRADOS
        FILE *arquivo_clientes = fopen(caminho_clientes, "w");

        if (arquivo_clientes != NULL) {
            fprintf(arquivo_clientes, "_______________________________________________________________________________________________\n");
            fprintf(arquivo_clientes, "\n                        CLIENTES CADASTRADOS                             \n");

            while (cadastroPtr != NULL) {
                char nomeUpper[100];
                strcpy(nomeUpper, cadastroPtr->nome);
                for (int i = 0; nomeUpper[i]; i++) {
                    nomeUpper[i] = toupper(nomeUpper[i]);
                }
                fprintf(arquivo_clientes, "\nNome do tutor: %s\n", nomeUpper);
                fprintf(arquivo_clientes, "Telefone: %s\n", formatar_numero_telefone(cadastroPtr->tel));
                fprintf(arquivo_clientes, "Nome do animal: %s\n", cadastroPtr->nome_animal);
                fprintf(arquivo_clientes, "Serviço realizado: %s\n", cadastroPtr->servico);
                fprintf(arquivo_clientes, "Animal: %s\n", cadastroPtr->animal);
                fprintf(arquivo_clientes, "Porte do animal: ");

                switch (cadastroPtr->porte_animal) {
                    case 1:
                        fprintf(arquivo_clientes, "Pequeno\n");
                        break;
                    case 2:
                        fprintf(arquivo_clientes, "Médio\n");
                        break;
                    case 3:
                        fprintf(arquivo_clientes, "Grande\n");
                        break;
                    default:
                        fprintf(arquivo_clientes, "Desconhecido\n");
                }
                fprintf(arquivo_clientes, "----------------------------------------------------------------------------------\n");

                cadastroPtr = cadastroPtr->proximoPtr;
            }

            fprintf(arquivo_clientes, "_______________________________________________________________________________________________\n");

            // Fechar o arquivo após a escrita
            fclose(arquivo_clientes);
        } else {
            printf("Falha ao adicionar subpasta e arquivos ao diretório.\n");
            return; 
        }
}
} // função de criar pasta e arquivo

void printa_cadastros(Cadastro *cadastroPtr) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n-------------------------------Clientes Cadastrados-------------------------------\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    while (cadastroPtr != NULL) {
        char nomeUpper[100];
        strcpy(nomeUpper, cadastroPtr->nome);
        for (int i = 0; nomeUpper[i]; i++) {
            nomeUpper[i] = toupper(nomeUpper[i]);
        }
        printf("\nNome do tutor: %s\n", nomeUpper);
        printf("Telefone: %s\n", formatar_numero_telefone(cadastroPtr->tel));
        printf("Nome do animal: %s\n", cadastroPtr->nome_animal);
        printf("Serviço realizado: %s\n", cadastroPtr->servico);
        printf("Animal: %s\n", cadastroPtr->animal);
        printf("Porte do animal: ");

        switch (cadastroPtr->porte_animal) {
            case 1:
                printf("Pequeno\n");
                break;
            case 2:
                printf("Médio\n");
                break;
            case 3:
                printf("Grande\n");
                break;
            default:
                printf("Desconhecido\n");
        }
        printf("Valor do serviço: %.2f\n", cadastroPtr->valor_servico);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("----------------------------------------------------------------------------------\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        cadastroPtr = cadastroPtr->proximoPtr;
    }
} //função de printar cadastros

void procura_cadastro(Cadastro *cadastroPtr, char *nome_cadastrado) {
    int encontrado = 0;
    while (cadastroPtr != NULL) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (stricmp(nome_cadastrado, cadastroPtr->nome)) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("\n-------------------------------Cliente Cadastrado-------------------------------\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            char nomeUpper[100];
            strcpy(nomeUpper, cadastroPtr->nome);
            for (int i = 0; nomeUpper[i]; i++) {
                nomeUpper[i] = toupper(nomeUpper[i]);
            }
            printf("Nome do tutor: %s\n", nomeUpper);
            printf("Telefone: %s\n", formatar_numero_telefone(cadastroPtr->tel));
            printf("Nome do animal: %s\n", cadastroPtr->nome_animal);
            printf("Serviço realizado: %s\n", cadastroPtr->servico);
            printf("Animal: %s\n", cadastroPtr->animal);
            printf("Porte do animal: ");

            switch (cadastroPtr->porte_animal) {
                case 1:
                    printf("Pequeno\n");
                    break;
                case 2:
                    printf("Médio\n");
                    break;
                case 3:
                    printf("Grande\n");
                    break;
                default:
                    printf("Desconhecido\n");
            }
            printf("Valor do serviço: %.2f\n", cadastroPtr->valor_servico);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("--------------------------------------------------------------------------------\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            encontrado = 1;
        }
        cadastroPtr = cadastroPtr->proximoPtr;
    }
    if (!encontrado) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("--------------------------------------------------------------------------------\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("Nenhum cliente encontrado com o nome '%s'\n", nome_cadastrado);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("--------------------------------------------------------------------------------\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
} //função de printar o cadastro encontrado

int stricmp(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower(*a) != tolower(*b)) return 0;
        a++;
        b++;
    }
    return (*a == 0 && *b == 0);
} //função de comparar string

void listarCadastros(Cadastro *primPtr) {
    if (primPtr != NULL) {
        printa_cadastros(primPtr);
    } else {
        printf("\nNenhum cadastro para mostrar\n");
    }
} //função de listar todos os cadastros

void pesquisarCadastro(Cadastro *primPtr) {
    char nome_pesquisa[100];
    printf("Digite o nome do tutor para pesquisar: ");

    consumeNewline();

    fgets(nome_pesquisa, sizeof(nome_pesquisa), stdin);
    nome_pesquisa[strlen(nome_pesquisa) - 1] = '\0';
    printf("\n");
    procura_cadastro(primPtr, nome_pesquisa);
} //função de pesquisar cadastro pelo nome do tutor

void gerarRelatorio(Cadastro *primPtr, int contagem_tosa, int contagem_banho, int contagem_tosa_banho, int contagem_cachorro, int contagem_gato, 
					int contagem_pequeno, int contagem_medio, int contagem_grande) {
    int total = contar_cadastros(primPtr);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n-------------------------------Relatório-------------------------------\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("Total de clientes atendidos: %d\n", total);
    printf("\n");
    printf("Serviços realizados:\n");
    printf("- Tosa: %d\n", contagem_tosa);
    printf("- Banho: %d\n", contagem_banho);
    printf("- Banho e tosa: %d\n", contagem_tosa_banho);
    printf("\n");
    printf("Animais atendidos:\n");
    printf("- Cachorros: %d\n", contagem_cachorro);
    printf("- Gatos: %d\n", contagem_gato);
    printf("\n");
    printf("Portes atendidos:\n");
    printf("- Pequeno: %d\n", contagem_pequeno);
    printf("- Médio: %d\n", contagem_medio);
    printf("- Grande: %d\n", contagem_grande);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("-----------------------------------------------------------------------\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
} //função de printar relatorio 

void gerarRecibo(float total_tosa, float total_banho, float total_tosa_banho, float total_ganho) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n-------------------------------Recibo-------------------------------\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("Total ganho: R$ %.2f\n", total_ganho);
    printf("\n");
    printf("Receita:\n");
    printf("- Tosa: R$ %.2f\n", total_tosa);
    printf("- Banho: R$ %.2f\n", total_banho);
    printf("- Banho e tosa: R$ %.2f\n", total_tosa_banho);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("--------------------------------------------------------------------\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
} // função de printar recibo

void menu(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\n_________Menu________\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("( 1 ) - Cadastrar cliente\n"
           "( 2 ) - Exibir clientes atendidos\n"
           "( 3 ) - Pesquisar cliente\n"
           "( 4 ) - Relatório\n"
           "( 5 ) - Recibo\n"
           "( 6 ) - Pesquisar informaçõs (salvas por data)\n"
           "( 7 ) - Salvar informações\n"
           "( 8 ) - Finalizar programa\n");
      SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);     
    printf("____________________\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

} //função de printar o menu

Cadastro* inserir(Cadastro *cadastroPtr, char nome_cadastro[100], double tel_cadastro, char nome_animal_cadastro[100], char servico_cadastro[20], 
					char animal_cadastro[20], int porte_animal_cadastro, float valor_servico_cadastro) {
    Cadastro *novoCadastro = (Cadastro *)malloc(sizeof(Cadastro));
    strcpy(novoCadastro->nome, nome_cadastro);
    novoCadastro->tel = tel_cadastro;
    strcpy(novoCadastro->nome_animal, nome_animal_cadastro);
    strcpy(novoCadastro->servico, servico_cadastro);
    strcpy(novoCadastro->animal, animal_cadastro);
    novoCadastro->porte_animal = porte_animal_cadastro;
    novoCadastro->valor_servico = valor_servico_cadastro; 
    novoCadastro->proximoPtr = cadastroPtr;
    return novoCadastro;
} //função de inserir um novo cadastro

float obterValorServico(int tipo_servico) {

    float valor_servico;
    printf("Informe o valor do serviço: ");
    scanf("%f", &valor_servico);
    consumeNewline();
    return valor_servico;
}

Cadastro* cadastrar(Cadastro *primPtr, int *contagem_tosa, int *contagem_banho, int *contagem_tosa_banho, int *contagem_cachorro, int *contagem_gato, 
					int *contagem_pequeno, int *contagem_medio, int *contagem_grande, float *total_ganho, float *total_tosa, float *total_banho, float *total_tosa_banho) {
    int cadastrarOutro;
    int animal_num = 0;

    do {
        char nome_scan[100];
        double tel_scan;
        int servico_num;
        char servico_scan[20];
        char porte_scan[20];
        int porte_animal_scan;
        char animal_scan[20];
        char nome_animal_scan[100];
        float valor_servico = 0;

        consumeNewline();

        printf("\n-----------------------------------------------------------------------------------\n");
        printf("\nNome do tutor: ");
        fgets(nome_scan, sizeof(nome_scan), stdin);
        nome_scan[strlen(nome_scan) - 1] = '\0';
        printf("Telefone do tutor: ");
        scanf("%lf", &tel_scan);
        consumeNewline();
        printf("Nome do animal: ");
        fgets(nome_animal_scan, sizeof(nome_animal_scan), stdin);
        nome_animal_scan[strlen(nome_animal_scan) - 1] = '\0';

        do {
            printf("\nServiços:\n");
            printf("1 - Tosa\n");
            printf("2 - Banho\n");
            printf("3 - Banho e Tosa\n");
            printf("Informe o serviço realizado: ");
            scanf("%d", &servico_num);
            consumeNewline();

            switch (servico_num) {
                case 1:
                    strcpy(servico_scan, "Tosa");
                    (*contagem_tosa)++;
                    break;
                case 2:
                    strcpy(servico_scan, "Banho");
                    (*contagem_banho)++;
                    break;
                case 3:
                    strcpy(servico_scan, "Banho e tosa");
                    (*contagem_tosa_banho)++;
                    break;
                default:
                    printf("\nOpção de serviço inválida. Digite uma das opções válidas.\n");
            }
        } while (servico_num < 1 || servico_num > 3);

        do {
            printf("\nAnimal:\n");
            printf("1 - Cachorro\n");
            printf("2 - Gato\n");
            printf("Informe qual o animal: ");
            scanf("%d", &animal_num);
            consumeNewline();

            switch (animal_num) {
                case 1:
                    strcpy(animal_scan, "Cachorro");
                    (*contagem_cachorro)++;
                    break;
                case 2:
                    strcpy(animal_scan, "Gato");
                    (*contagem_gato)++;
                    break;
                default:
                    printf("\nOpção de animal inválida. Digite uma das opções válidas.\n");
            }
        } while (animal_num < 1 || animal_num > 2);

        do {
            printf("\nPortes:\n");
            printf("1 - Pequeno\n");
            printf("2 - Médio\n");
            printf("3 - Grande\n");
            printf("Informe o porte do animal: ");
            scanf("%d", &porte_animal_scan);
            consumeNewline();

            switch (porte_animal_scan) {
                case 1:
                    strcpy(porte_scan, "Pequeno");
                    (*contagem_pequeno)++;
                    break;
                case 2:
                    strcpy(porte_scan, "Médio");
                    (*contagem_medio)++;
                    break;
                case 3:
                    strcpy(porte_scan, "Grande");
                    (*contagem_grande)++;
                    break;
                default:
                    printf("\nOpção de porte inválida. Digite uma das opções válidas.\n");
            }
        } while (porte_animal_scan < 1 || porte_animal_scan > 3);

        valor_servico = obterValorServico(servico_num);

        do {
            switch (servico_num) {
                case 1:
                    strcpy(servico_scan, "Tosa");
                    (*total_tosa) += valor_servico;
                    (*total_ganho) += valor_servico;
                    break;
                case 2:
                    strcpy(servico_scan, "Banho");
                    (*total_banho) += valor_servico;
                    (*total_ganho) += valor_servico;
                    break;
                case 3:
                    strcpy(servico_scan, "Banho e tosa");
                    (*total_tosa_banho) += valor_servico;
                    (*total_ganho) += valor_servico;
                    break;
                default:
                    printf("\nOpção de serviço inválida. Digite uma das opções válidas.\n");
            }
        } while (servico_num < 1 || servico_num > 3);

        primPtr = inserir(primPtr, nome_scan, tel_scan, nome_animal_scan, servico_scan, animal_scan, porte_animal_scan, valor_servico);

        // Pergunta se deseja realizar outro cadastro
        printf("\n1 - Sim\n");
        printf("2 - Não\n");
        printf("Deseja realizar outro cadastro?\n");
        scanf("%d", &cadastrarOutro);
		if (cadastrarOutro != 1 && cadastrarOutro != 2 ) {
			printf("\nOpção inválida!\n");
			printf("Voltando para o menu.....\n");
		}
    } while (cadastrarOutro == 1);

    return primPtr;
} //função de cadastrar

void imprimirConteudoArquivo(const char *nome_arquivo) {
    char caminho_relatorio[200];
    char caminho_clientes[200];
    char caminho_recibo[200];

    snprintf(caminho_relatorio, sizeof(caminho_relatorio), "PETSHOP/%s/relatorio.txt", nome_arquivo);
    snprintf(caminho_clientes, sizeof(caminho_clientes), "PETSHOP/%s/clientes_cadastrados.txt", nome_arquivo);
    snprintf(caminho_recibo, sizeof(caminho_recibo), "PETSHOP/%s/recibo.txt", nome_arquivo);
    int opcao;

    do {
        printf("\nO que deseja ver?\n");
        printf("1 - Relatorio\n");
        printf("2 - Recibo\n");
        printf("3 - Clientes Cadastrados (Diario)\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);

        if (opcao != 0) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("\n\nDescrição do dia %s", nome_arquivo);

            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            printf("\n\n");

            FILE *arquivo = NULL;

            switch (opcao) {
                case 1:
                    arquivo = fopen(caminho_relatorio, "r");
                    break;
                case 2:
                    arquivo = fopen(caminho_recibo, "r");
                    break;
                case 3:
                    arquivo = fopen(caminho_clientes, "r");
                    break;
                default:
                    printf("Opção inválida.\n");
                    return;
            }

            if (arquivo == NULL) {
                printf("Falha ao abrir o arquivo '%s'. Verifique se o arquivo existe na pasta 'PETSHOP/%s'.\n", nome_arquivo, nome_arquivo);
                return;
            }

            char linha[256]; // Ajuste o tamanho conforme necessário
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                printf("%s", linha);
            }

            printf("\n\n");
            fclose(arquivo);
        }

    } while (opcao != 0);
} //função de imprimir conteudo do arquivo

int main() {
    setlocale(LC_ALL, "Portuguese");
	int num;
    Cadastro *primPtr = NULL;
    int total = 0;
    int contagem_tosa = 0;
    int contagem_banho = 0;
    int contagem_tosa_banho = 0;
    int contagem_cachorro = 0;
    int contagem_gato = 0;
    int contagem_pequeno = 0;
    int contagem_medio = 0;
    int contagem_grande = 0;
    float total_tosa = 0;
    float total_banho = 0;
    float total_tosa_banho = 0;
    float total_ganho = 0;
	int resultado;
	char nome_pasta[100];
    char nome_arquivo[100];


    do {
        menu();
        printf("\nDigite o número correspondente ao que deseja fazer: ");
        scanf("%d", &num);

        switch (num) {
            case 1:
   				primPtr = cadastrar(primPtr, &contagem_tosa, &contagem_banho, &contagem_tosa_banho, &contagem_cachorro, &contagem_gato, 
				   &contagem_pequeno, &contagem_medio, &contagem_grande, &total_ganho, &total_tosa, &total_banho, &total_tosa_banho);
    			break;
            case 2:
                listarCadastros(primPtr);
                break;
            case 3:
                pesquisarCadastro(primPtr);
                break;
            case 4:
                gerarRelatorio(primPtr, contagem_tosa, contagem_banho, contagem_tosa_banho, contagem_cachorro, contagem_gato, contagem_pequeno, contagem_medio, contagem_grande);
                break;
            case 5:
    		gerarRecibo(total_tosa, total_banho, total_tosa_banho, total_ganho);
    		break;
			case 6:
				printf("Digite a data (dd-mm-yyyy) do arquivo para visualizar: ");
                scanf("%s", nome_arquivo);
                imprimirConteudoArquivo(nome_arquivo);
                break;
    		case 7:
                int scan_salvar;
                printf("\nDeseja salvar as informações de agora?"
                       "\n1- Sim"
                       "\n2- Não\n");
                scanf("%d", &scan_salvar);
                if (scan_salvar == 1) {
                    printf("Digite a data[dd-mm-yyyy]: ");
                    scanf("%s", nome_arquivo);

                   criarPastaEArquivo(nome_arquivo, primPtr, contagem_tosa, contagem_banho,
                        contagem_tosa_banho, contagem_cachorro, contagem_gato,
                        contagem_pequeno, contagem_medio, contagem_grande,
                        total_ganho, total_tosa, total_banho, total_tosa_banho);

                } else {
                    printf("As informações não foram salvas\n");
                } 
                break;
			case 8: //desaloca um bloco de memória ( memblock ) que foi alocado anteriormente
            		printf("Programa finalizado!\n");
                while (primPtr != NULL) {
                    Cadastro *temp = primPtr;
                    primPtr = primPtr->proximoPtr;
                    free(temp); }
                    break;
			default:
                printf("\nOpção inválida. Digite uma das opções válidas.\n");}

    } while (num != 8);

    return 0;
}
