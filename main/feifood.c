#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>





void menu();
void cadastro();
void login();
void mostrar_cardapio();

char nome_input[50];
char senha_input[50];


void menu(){
    // Menu inicial
    printf("Bem Vindo ao FeiFood!\n\n\n");
    
    printf("1- Cadastro\n2- Login\n3- cardapio\n4- exit\n");
    printf("Escolha uma opcao: ");
    
    int x;
    scanf("%d", &x);
    
    switch(x){
        case 1: 
            cadastro();
            break;
            
        case 2: 
            login();
            break;
            
        case 3:
            mostrar_cardapio();
        
        case 4:
        	exit(0);
        default: 
            printf("Escolha uma opcao valida\n");
            menu(); 
            break;
    }
}

//parte de cadastro
void cadastro(){
    printf("Digite seu nome: ");
    scanf("%s", nome_input);
    
    printf("Digite sua senha: ");
    scanf("%s", senha_input);
    
    FILE *usuarios = fopen("usuarios.txt", "a");
    if (usuarios == NULL) {
        printf("Erro ao abrir arquivo!\n");
        system("pause");
        return;
    }

    fprintf(usuarios, "%s, %s\n", nome_input, senha_input);
    fclose(usuarios);

    printf("Cadastro realizado com sucesso!\n");
    printf("Seu cadastro:\n");
    printf("Nome: %s\n", nome_input);
    printf("Senha: %s\n", senha_input);
    
    menu();
}


void login(){
	
	char usuario_correto[50];
	char senha_correta[50];
	char usuario_input[50];
	char senha_input[50];
	bool valido = false;
	
	
	printf("=====LOGIN=====\n");
    printf("Usuario: ");
    scanf("%s", usuario_input);
    printf("Senha: ");
    scanf("%s", senha_input);
    
	
	FILE *usuarios = fopen("usuarios.txt", "r");
    
	
	if(usuarios != NULL){
        while(fscanf(usuarios, "%50[^,], %50s", usuario_correto, senha_correta) == 2){
            if(strcmp(usuario_input, usuario_correto) == 0 && strcmp(senha_input, senha_correta) == 0){
                valido = true;
                break;
            }
        }
        fclose(usuarios);
    }
    
    if(valido){
        printf("Login efetuado com sucesso!\n");
        //cardapio lista busca historico e avaliação
    } else {
        printf("Usuario ou senha incorretos!\n");
    }
}

void mostrar_cardapio(){
    // pra mostrar o cardapio
    FILE *cardapio = fopen("cardapio.txt", "r");
    
    if(cardapio == NULL){
        printf("nao foi possivel abrir o arquivo.\n");
        //voltar pra HUD depois do login;
        return;
    }
    
    char itens[1000];
    printf("comidas em nosso cardapio:\n\n");
    
    while(fgets(itens, 1000, cardapio) != NULL){
        printf("%s", itens);
    }

    fclose(cardapio);	
    
    menu();
}

int main(){

	
	menu();
	system("pause");
	return 0;
}