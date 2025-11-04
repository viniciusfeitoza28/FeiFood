#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void menu();
void menu_aposlogin();
void cadastro();
void cadastrar_novo();
void login();
void mostrar_cardapio();
void buscar_alimento();

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
	        printf("4- cadastrar pedido\n5- avaliar pedido\n6- ver cardapio\n7- Sair\n");
	        printf("Escolha uma opcao: ");
	        
	        scanf("%d", &opcao);
	        
	        switch(opcao){
	            case 1:
	                cadastrar_novo();
	                break;
	            case 2:
	                buscar_alimento();
	                break;
	//          case 3:
	//              historico();
	//              break;
	//          case 4:
	//              pedidos();
	//              break;
	//          case 5:
	//              avaliacao();
	//              break;
	            case 6:
	                mostrar_cardapio();
	                break;
	            case 7:
	                printf("Saindo...\n");
	                return;
	            default:
	                printf("Digite uma opcao valida!\n");
	                break;
	        }
	    }while (opcao != 7);
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



void buscar_alimento(){
    char busca[100];
    char linha[200];
    bool encontrou = false;
    
    printf("Digite a comida que deseja achar: ");
    scanf("%99s", busca);
    getchar(); // Limpa o buffer do input
    
    FILE *cardapio = fopen("cardapio.txt", "r");
    if(cardapio == NULL){
        printf("Erro ao abrir o cardapio!\n");
        system("pause");
        menu_aposlogin();
        return;
    }
    
    printf("\nResultados da busca por '%s':\n", busca);
    printf("============================\n");
    
    while(fgets(linha, sizeof(linha), cardapio) != NULL){
        linha[strcspn(linha, "\n")] = 0;
        
        if(strstr(linha, "=====") != NULL || strstr(linha, "CARDAPIO") != NULL || 
           strstr(linha, "comidas") != NULL || strlen(linha) == 0){
            continue;
        }
        if(strstr(linha, busca) != NULL){
            printf("%s\n", linha);
            encontrou = true;
        }
    }
    
    fclose(cardapio);
    
    if(!encontrou){
        printf("Nenhum alimento encontrado com '%s'\n", busca);
    }
    
    printf("\n");
    system("pause");
    menu_aposlogin();
}

void cadastra_pedido(){
	
	
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

int main(){
    menu();
    return 0;
}
