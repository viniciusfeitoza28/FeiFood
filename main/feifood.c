#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cadastro(char nome[], char senha[]);
void login();

//parte de cadastro
void cadastro(char nome[], char senha[]){
	
	printf("Digite seu nome:");
	scanf("%s" , nome);
	
	printf("Digite sua senha:");
	scanf("%s" , senha);
	
}


// void login(){
	
// 	boolean valido = true;
	
// 	arquivo = fopen("C:\\Users\\vini2\\OneDrive\\Área de Trabalho\\usuarios.txt", "r");
	
// 	if(arquivo == NULL){
// 		printf("Erro! nenhum usuario cadastrado");
// 		return;
// 	}
	
	
	// while(fscanf(arquivo, "%s, %s",nome_arquivo, senha_arquivo))
	
	
	
// }



int main(){
	
	
	
	//menu inicial
	printf("Bem Vindo ao FeiFood!\n\n\n");

    char nome[50];
    char senha[50];
	
	int x;
	
	printf("1- Cadastro\n2- Login");
	
	scanf("%d", &x);
	
	switch(x){
 		case 1: cadastro(nome, senha);

            cadastro(nome, senha);

            FILE *usuarios = fopen("C:\\Users\\vini2\\OneDrive\\Área de Trabalho\\usuarios.txt", "a");
            if (usuarios == NULL) {
                printf("Erro ao abrir arquivo!\n");
                system("pause");
                return 1;
            }

            fprintf(usuarios, "%s, %s\n", nome, senha);
            fclose(usuarios);

            printf("Cadastro realizado com sucesso!\n");
            printf("Seu cadastro:\n");
            printf("Nome: %s\n", nome);
            printf("Senha: %s\n", senha);
            break;

 		case 2: login();
 			break;
 		
 		case 3:
 			return 1;
 			break;
 	
 		default: printf("escolha uma opcao valida");
 			break;
}

	//////////////////////////////////////////
	system("pause");

	return 0;
}