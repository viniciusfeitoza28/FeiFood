#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>


void menu();
void menu_aposlogin();
void cadastro();
void cadastrar_novo();
void login();
void mostrar_cardapio();
void buscar_alimento();
void salvar_historico_busca();
void historico_buscas();

char nome_input[50];
char senha_input[50];

char usuario_logado[50];

void menu(){
    printf("Bem Vindo ao FeiFood!\n\n\n");
    printf("1- Cadastro\n2- Login\n3- exit\n");
    printf("Escolha uma opcao: ");
    
    int x;
    scanf("%d", &x);
    getchar(); 
    
    switch(x){
        case 1: 
            cadastro();
            break;
        case 2: 
            login();
            break;
        case 3:
            exit(0);
        default: 
            printf("Escolha uma opcao valida\n");
            menu(); 
            break;
    }
}



void menu_aposlogin(){
    int opcao;
    
    do {
        printf("\n=====BEM VINDO AO FEI FOOD=====\n\nOque deseja fazer?\n\n");
        printf("1- cadastrar novo usuario\n2- buscar por alimento\n3- ver historico de pedidos\n");
        printf("4- cadastrar pedido\n5- avaliar pedido\n6- ver cardapio\78- Sair\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        switch(opcao){
            case 1:
                cadastrar_novo();
                break;
            case 2:
                buscar_alimento();
                break;
             case 3:
                historico_buscas();
                break;
            // case 4:
            //     pedidos();
            //     break;
            // case 5:
            //     avaliacao();
            //     break;
            case 6:
                mostrar_cardapio();
                break;
            case 7: // Mudei para 8
                printf("Saindo...\n");
                return;
            default:
                printf("Digite uma opcao valida!\n");
                break;
        }
    } while (opcao != 8);
}

void cadastro(){
    printf("Digite seu nome: ");
    fgets(nome_input, sizeof(nome_input), stdin);
    nome_input[strcspn(nome_input, "\n")] = 0;
    
    printf("Digite sua senha: ");
    fgets(senha_input, sizeof(senha_input), stdin);
    senha_input[strcspn(senha_input, "\n")] = 0;
    
    FILE *usuarios = fopen("usuarios.txt", "a");
    if (usuarios == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    fprintf(usuarios, "%s, %s\n", nome_input, senha_input);
    fclose(usuarios);
    
    printf("Cadastro realizado com sucesso!\n");
    printf("Seu cadastro:\n");
    printf("Nome: %s\n", nome_input);
    printf("Senha: %s\n", senha_input);
    printf("\n\n\n\n");
    
    menu();
}

void cadastrar_novo(){
    printf("Digite seu nome: ");
    fgets(nome_input, sizeof(nome_input), stdin);
    nome_input[strcspn(nome_input, "\n")] = 0;
    
    printf("Digite sua senha: ");
    fgets(senha_input, sizeof(senha_input), stdin);
    senha_input[strcspn(senha_input, "\n")] = 0;
    
    FILE *usuarios = fopen("usuarios.txt", "a");
    if (usuarios == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fprintf(usuarios, "%s, %s\n", nome_input, senha_input);
    fclose(usuarios);

    printf("Cadastro realizado com sucesso!\n");
    printf("Seu cadastro:\n");
    printf("Nome: %s\n", nome_input);
    printf("Senha: %s\n", senha_input);
    printf("\n\n\n\n");
    
    menu_aposlogin();
}

void login(){
    char usuario_correto[50];
    char senha_correta[50];
    char usuario_input[50];
    char senha_input[50];
    bool valido = false;
    
    printf("=====LOGIN=====\n");
    printf("Usuario: ");
    scanf("%49s", usuario_input);
    printf("Senha: ");
    scanf("%49s", senha_input);
    getchar(); // limpa o buffer do input
    
    FILE *usuarios = fopen("usuarios.txt", "r");
    
    if(usuarios != NULL){
        char linha[100];
        while(fgets(linha, sizeof(linha), usuarios) != NULL){
            linha[strcspn(linha, "\n")] = 0;
            char *virgula = strchr(linha, ',');
            if(virgula != NULL){
                *virgula = '\0'; 
                strcpy(usuario_correto, linha);
                char *senha_ptr = virgula + 2; 
                if(*senha_ptr == ' ') senha_ptr++; 
                strcpy(senha_correta, senha_ptr);
                int i = strlen(usuario_correto) - 1;
                while(i >= 0 && usuario_correto[i] == ' '){
                    usuario_correto[i] = '\0';
                    i--;
                }
                if(strcmp(usuario_input, usuario_correto) == 0 && strcmp(senha_input, senha_correta) == 0){
                    valido = true;
                    strcpy(usuario_logado, usuario_input); // AQUI: Salva o usuário logado
                    break;
                }
            }
        }
        fclose(usuarios);
    }
    
    if(valido){
        printf("Login efetuado com sucesso!\n\n");
        menu_aposlogin();
    } else {
        printf("Usuario ou senha incorretos!\n");
        system("pause");
        menu();
    }
}

void mostrar_cardapio(){
    FILE *cardapio = fopen("cardapio.txt", "r");
    
    if(cardapio == NULL){
        printf("nao foi possivel abrir o arquivo.\n");
        system("pause");
        menu_aposlogin();
        return;
    }
    
    char itens[1000];
    printf("comidas em nosso cardapio:\n\n");
    
    while(fgets(itens, 1000, cardapio) != NULL){
        printf("%s", itens);
    }

    printf("\n");
    
    menu_aposlogin();
}

void cadastrar_pedido() {
    char alimento[100];
    char data[20];
    int quantidade;
    
    printf("\n===== CADASTRAR PEDIDO =====\n");
    
    printf("Digite o alimento: ");
    fgets(alimento, sizeof(alimento), stdin);
    alimento[strcspn(alimento, "\n")] = 0;
    
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);
    getchar();
    
    printf("Digite a data (DD/MM/AAAA): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = 0;
    
    FILE *file = fopen("pedidos.txt", "a");
    if(file != NULL) {
        fprintf(file, "%s,%s,%d,%s,0\n", usuario_logado, alimento, quantidade, data);
        fclose(file);
        printf("Pedido salvo!\n");
    } else {
        printf("Erro ao salvar pedido!\n");
    }
    
    system("pause");
}

void salvar_historico_busca(const char *busca_realizada) {
    // Cria o nome do arquivo baseado no usuário logado
    char filename[100];
    snprintf(filename, sizeof(filename), "historico_%s.txt", usuario_logado);
    
    FILE *historico = fopen(filename, "a");
    if (historico != NULL) {
        fprintf(historico, "%s - %s\n", usuario_logado, busca_realizada);
        fclose(historico);
    }
}


void buscar_alimento(){
    char busca[100];
    char linha[200];
    char categoria[100] = "";
    bool encontrou = false;
    int i;
    
    printf("Digite a comida que deseja achar: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = 0;
    
    // SALVA A BUSCA NO HISTÓRICO (mesmo se não encontrar nada)
    salvar_historico_busca(busca);
    
    FILE *cardapio = fopen("cardapio.txt", "r");
    if(cardapio == NULL){
        printf("Erro ao abrir o cardapio!\n");
        system("pause");
        menu_aposlogin();
        return;
    }
    
    printf("\nResultados da busca por '%s':\n", busca);
    printf("============================\n");
    
    // Converte busca para minúsculo
    char busca_lower[100];
    strcpy(busca_lower, busca);
    for(i = 0; busca_lower[i]; i++) busca_lower[i] = tolower(busca_lower[i]);
    
    while(fgets(linha, sizeof(linha), cardapio) != NULL){
        linha[strcspn(linha, "\n")] = 0;
        
        // Verifica se é uma linha de categoria
        if(strstr(linha, "=====") != NULL){
            char temp[100];
            strcpy(temp, linha);
            char *start = temp;
            while(*start == '=') start++;
            char *end = strstr(start, "=====");
            if(end != NULL) *end = '\0';
            strcpy(categoria, start);
            continue;
        }
        
        // Pula linhas vazias
        if(strlen(linha) == 0) continue;
        
        // Cria uma versão limpa da linha (sem preço e caracteres especiais)
        char linha_limpa[200];
        char linha_lower[200];
        strcpy(linha_limpa, linha);
        strcpy(linha_lower, linha);
        
        // Remove o preço e caracteres especiais
        char *pipe_pos = strchr(linha_limpa, '|');
        if(pipe_pos != NULL) {
            *pipe_pos = '\0'; // Corta a linha no |
        }
        
        // Converte para minúsculo
        for(i = 0; linha_lower[i]; i++) linha_lower[i] = tolower(linha_lower[i]);
        for(i = 0; linha_limpa[i]; i++) linha_limpa[i] = tolower(linha_limpa[i]);
        
        // Remove espaços extras e caracteres especiais da linha limpa
        char linha_final[200];
        int k = 0;
        for(i = 0; linha_limpa[i]; i++) {
            if(isalnum(linha_limpa[i]) || linha_limpa[i] == ' ' || linha_limpa[i] == '-') {
                linha_final[k++] = linha_limpa[i];
            }
        }
        linha_final[k] = '\0';
        
        // Diferentes estratégias de busca
        bool achou = false;
        
        // 1. Busca exata no nome completo
        if(strstr(linha_lower, busca_lower) != NULL) {
            achou = true;
        }
        // 2. Busca por palavras individuais
        else {
            char *palavras_busca[10];
            int num_palavras = 0;
            char busca_temp[100];
            strcpy(busca_temp, busca_lower);
            
            // Divide a busca em palavras
            char *token = strtok(busca_temp, " -");
            while(token != NULL && num_palavras < 10) {
                palavras_busca[num_palavras++] = token;
                token = strtok(NULL, " -");
            }
            
            // Verifica se todas as palavras estão presentes
            int palavras_encontradas = 0;
            for(i = 0; i < num_palavras; i++) {
                if(strstr(linha_final, palavras_busca[i]) != NULL) {
                    palavras_encontradas++;
                }
            }
            
            // Se encontrou pelo menos uma palavra, considera como resultado
            if(palavras_encontradas > 0) {
                achou = true;
            }
        }
        
        // 3. Busca por sinônimos/atalhos
        if(!achou) {
            // Mapeamento de atalhos comuns
            if((strstr(busca_lower, "burguer") || strstr(busca_lower, "hamburguer") || strstr(busca_lower, "xburguer")) && 
               strstr(linha_final, "burger")) {
                achou = true;
            }
            else if(strstr(busca_lower, "refri") && strstr(linha_final, "refrigerante")) {
                achou = true;
            }
            else if(strstr(busca_lower, "strogonoff") && strstr(linha_final, "strogonoff")) {
                achou = true;
            }
            else if(strstr(busca_lower, "parmegiana") && strstr(linha_final, "parmegiana")) {
                achou = true;
            }
        }
        
        if(achou){
            printf("Categoria: %s\n", categoria);
            printf("Alimento: %s\n", linha);
            printf("------------------------\n");
            encontrou = true;
        }
    }
    
    fclose(cardapio);
    
    if(!encontrou){
        printf("Nenhum alimento encontrado com '%s'\n", busca);
        printf("\nSugestoes de busca:\n");
        printf("- X-Burger, X-Bacon, X-Frango\n");
        printf("- Strogonoff, Feijoada, Parmegiana\n");
        printf("- Batata, Refrigerante, Suco\n");
        printf("- Pudim, Mousse, Brownie\n");
    }
    
    printf("\n");
    system("pause");
    menu_aposlogin();
}


void historico_buscas() {
    if (strlen(usuario_logado) == 0) {
        printf("Nenhum usuario logado!\n");
        system("pause");
        return;
    }
    
    char filename[100];
    snprintf(filename, sizeof(filename), "historico_%s.txt", usuario_logado);
    
    FILE *historico = fopen(filename, "r");
    if (historico == NULL) {
        printf("Voce ainda nao fez nenhuma busca!\n");
        system("pause");
        return;
    }
    
    printf("\n===== HISTORICO DE BUSCAS =====\n");
    printf("Usuario: %s\n\n", usuario_logado);
    
    char linha[200];
    int contador = 1;
    
    while (fgets(linha, sizeof(linha), historico) != NULL) {
        printf("%d. %s", contador, linha);
        contador++;
    }
    
    fclose(historico);
    
    if (contador == 1) {
        printf("Nenhuma busca encontrada no historico.\n");
    }
    
    printf("\n");
    system("pause");
}

int main(){
    menu();
    return 0;
}
