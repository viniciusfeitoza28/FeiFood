#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void menu();
void menu_apos_login();
void cadastro();
void cadastrar_novo_usuario();
void login();
void mostrar_cardapio();
void buscar_alimento();
void salvar_pedido(const char *alimento, int quantidade, const char *data);
void historico_pedidos();
void cadastrar_pedido();
void editar_pedido();
void excluir_pedido();
void avaliar_pedido();
void salvar_historico_busca(const char *busca);
void listar_historico_buscas();

char nome_input[50];
char senha_input[50];
char usuario_logado[50];

void menu(){
    printf("Bem Vindo ao FeiFood!\n\n\n");
    printf("1- Cadastro\n2- Login\n3- Sair\n");
    printf("Escolha uma opcao: ");
    
    int opcao;
    scanf("%d", &opcao);
    getchar(); 
    
    switch(opcao){
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

void menu_apos_login(){
    int opcao;
    
    do {
        printf("\n===== BEM VINDO AO FEI FOOD =====\n\nO que deseja fazer?\n\n");
        printf("1- Cadastrar novo usuario\n");
        printf("2- Buscar por alimento\n");
        printf("3- Ver historico de pedidos\n");
        printf("4- Cadastrar pedido\n");
        printf("5- Editar pedido\n");
        printf("6- Excluir pedido\n");
        printf("7- Avaliar pedido\n");
        printf("8- Ver cardapio\n");
        printf("9- Historico de buscas\n");
        printf("10- Sair\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        int limpar_buffer;
        while ((limpar_buffer = getchar()) != '\n' && limpar_buffer != EOF);
        
        switch(opcao){
            case 1:
                cadastrar_novo_usuario();
                break;
            case 2:
                buscar_alimento();
                break;
            case 3:
                historico_pedidos();
                break;
            case 4:
                cadastrar_pedido();
                break;
            case 5:
                editar_pedido();
                break;
            case 6:
                excluir_pedido();
                break;
            case 7:
                avaliar_pedido();
                break;
            case 8:
                mostrar_cardapio();
                break;
            case 9:
                listar_historico_buscas();
                break;
            case 10:
                printf("Saindo...\n");
                return;
            default:
                printf("Digite uma opcao valida!\n");
                break;
        }
    } while (opcao != 10);
}

void cadastro(){
    printf("Digite seu nome: ");
    fgets(nome_input, sizeof(nome_input), stdin);
    nome_input[strcspn(nome_input, "\n")] = 0;
    
    printf("Digite sua senha: ");
    fgets(senha_input, sizeof(senha_input), stdin);
    senha_input[strcspn(senha_input, "\n")] = 0;
    
    FILE *arquivo_usuarios = fopen("usuarios.txt", "a");
    if (arquivo_usuarios == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    fprintf(arquivo_usuarios, "%s, %s\n", nome_input, senha_input);
    fclose(arquivo_usuarios);
    
    printf("Cadastro realizado com sucesso!\n");
    printf("Seu cadastro:\n");
    printf("Nome: %s\n", nome_input);
    printf("Senha: %s\n", senha_input);
    printf("\n\n\n\n");
    
    menu();
}

void cadastrar_novo_usuario(){
    printf("Digite seu nome: ");
    fgets(nome_input, sizeof(nome_input), stdin);
    nome_input[strcspn(nome_input, "\n")] = 0;
    
    printf("Digite sua senha: ");
    fgets(senha_input, sizeof(senha_input), stdin);
    senha_input[strcspn(senha_input, "\n")] = 0;
    
    FILE *arquivo_usuarios = fopen("usuarios.txt", "a");
    if (arquivo_usuarios == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fprintf(arquivo_usuarios, "%s, %s\n", nome_input, senha_input);
    fclose(arquivo_usuarios);

    printf("Cadastro realizado com sucesso!\n");
    printf("Seu cadastro:\n");
    printf("Nome: %s\n", nome_input);
    printf("Senha: %s\n", senha_input);
    printf("\n\n\n\n");
    
    menu_apos_login();
}

void login(){
    char usuario_correto[50];
    char senha_correta[50];
    char usuario_input[50];
    char senha_input_login[50];
    bool login_valido = false;
    int contador, posicao_virgula, contador_j, contador_k;
    
    printf("===== LOGIN =====\n");
    printf("Usuario: ");
    scanf("%49s", usuario_input);
    printf("Senha: ");
    scanf("%49s", senha_input_login);
    getchar();
    
    FILE *arquivo_usuarios = fopen("usuarios.txt", "r");
    
    if(arquivo_usuarios != NULL){
        char linha[100];
        while(fgets(linha, sizeof(linha), arquivo_usuarios) != NULL){
            linha[strcspn(linha, "\n")] = 0;
            
            // Encontra a virgula manualmente
            posicao_virgula = -1;
            for(contador = 0; linha[contador] != '\0'; contador++){
                if(linha[contador] == ','){
                    posicao_virgula = contador;
                    break;
                }
            }
            
            if(posicao_virgula != -1){
                // Copia usuario (ate a virgula)
                for(contador = 0; contador < posicao_virgula && contador < 49; contador++){
                    usuario_correto[contador] = linha[contador];
                }
                usuario_correto[contador] = '\0';
                
                // Remove espacos do final do usuario
                while(contador > 0 && usuario_correto[contador-1] == ' '){
                    usuario_correto[--contador] = '\0';
                }
                
                // Copia senha (depois da virgula, pulando espacos)
                contador_j = posicao_virgula + 1;
                while(linha[contador_j] == ' ') contador_j++;
                
                contador_k = 0;
                while(linha[contador_j] != '\0' && contador_k < 49){
                    senha_correta[contador_k++] = linha[contador_j++];
                }
                senha_correta[contador_k] = '\0';
                
                if(strcmp(usuario_input, usuario_correto) == 0 && strcmp(senha_input_login, senha_correta) == 0){
                    login_valido = true;
                    strcpy(usuario_logado, usuario_input);
                    break;
                }
            }
        }
        fclose(arquivo_usuarios);
    }
    
    if(login_valido){
        printf("Login efetuado com sucesso!\n\n");
        menu_apos_login();
    } else {
        printf("Usuario ou senha incorretos!\n");
        system("pause");
        menu();
    }
}

void mostrar_cardapio(){
    FILE *arquivo_cardapio = fopen("cardapio.txt", "r");
    
    if(arquivo_cardapio == NULL){
        printf("Nao foi possivel abrir o arquivo.\n");
        system("pause");
        menu_apos_login();
        return;
    }
    
    char item_cardapio[1000];
    printf("Comidas em nosso cardapio:\n\n");
    
    while(fgets(item_cardapio, 1000, arquivo_cardapio) != NULL){
        printf("%s", item_cardapio);
    }

    printf("\n");
    system("pause");
}

void salvar_historico_busca(const char *busca) {
    if (strlen(usuario_logado) == 0) return;
    
    char nome_arquivo[100];
    sprintf(nome_arquivo, "historico_%s.txt", usuario_logado);
    
    FILE *arquivo_historico = fopen(nome_arquivo, "a");
    if (arquivo_historico != NULL) {
        fprintf(arquivo_historico, "%s\n", busca);
        fclose(arquivo_historico);
    }
}

void listar_historico_buscas() {
    if (strlen(usuario_logado) == 0) {
        printf("Nenhum usuario logado!\n");
        system("pause");
        return;
    }
    
    char nome_arquivo[100];
    sprintf(nome_arquivo, "historico_%s.txt", usuario_logado);
    
    FILE *arquivo_historico = fopen(nome_arquivo, "r");
    if (arquivo_historico == NULL) {
        printf("Voce ainda nao fez nenhuma busca!\n");
        system("pause");
        return;
    }
    
    printf("\n===== HISTORICO DE BUSCAS =====\n");
    printf("Usuario: %s\n\n", usuario_logado);
    
    char linha_busca[200];
    int contador_busca = 1;
    
    while (fgets(linha_busca, sizeof(linha_busca), arquivo_historico) != NULL) {
        printf("%d. %s", contador_busca, linha_busca);
        contador_busca++;
    }
    
    fclose(arquivo_historico);
    
    if (contador_busca == 1) {
        printf("Nenhuma busca encontrada no historico.\n");
    }
    
    printf("\n");
    system("pause");
}

void buscar_alimento(){
    char termo_busca[100];
    char linha_cardapio[200];
    char categoria_atual[100] = "";
    bool alimento_encontrado = false;
    int contador;
    
    printf("Digite a comida que deseja achar: ");
    fgets(termo_busca, sizeof(termo_busca), stdin);
    termo_busca[strcspn(termo_busca, "\n")] = 0;
    
    // Salva no histórico de buscas
    salvar_historico_busca(termo_busca);
    
    FILE *arquivo_cardapio = fopen("cardapio.txt", "r");
    if(arquivo_cardapio == NULL){
        printf("Erro ao abrir o cardapio!\n");
        system("pause");
        menu_apos_login();
        return;
    }
    
    printf("\nResultados da busca por '%s':\n", termo_busca);
    printf("============================\n");
    
    // Converte busca para minusculo
    char termo_busca_minusculo[100];
    for(contador = 0; termo_busca[contador] != '\0'; contador++){
        if(termo_busca[contador] >= 'A' && termo_busca[contador] <= 'Z'){
            termo_busca_minusculo[contador] = termo_busca[contador] + 32;
        } else {
            termo_busca_minusculo[contador] = termo_busca[contador];
        }
    }
    termo_busca_minusculo[contador] = '\0';
    
    while(fgets(linha_cardapio, sizeof(linha_cardapio), arquivo_cardapio) != NULL){
        linha_cardapio[strcspn(linha_cardapio, "\n")] = 0;
        
        // Verifica se é uma linha de categoria
        if(strstr(linha_cardapio, "=====") != NULL){
            // Extrai nome da categoria
            int comeco = 0;
            while(linha_cardapio[comeco] == '=') comeco++;
            
            int fim = comeco;
            while(linha_cardapio[fim] != '\0' && linha_cardapio[fim] != '=') fim++;
            
            int tamanho_categoria = fim - comeco;
            if(tamanho_categoria > 0 && tamanho_categoria < 100){
                for(contador = 0; contador < tamanho_categoria; contador++){
                    categoria_atual[contador] = linha_cardapio[comeco + contador];
                }
                categoria_atual[tamanho_categoria] = '\0';
            }
            continue;
        }
        
        // Pula linhas vazias
        if(strlen(linha_cardapio) == 0) continue;
        
        // Cria versao da linha sem preco
        char linha_sem_preco[200];
        int posicao_pipe = -1;
        for(contador = 0; linha_cardapio[contador] != '\0'; contador++){
            if(linha_cardapio[contador] == '|'){
                posicao_pipe = contador;
                break;
            }
        }
        
        if(posicao_pipe != -1){
            for(contador = 0; contador < posicao_pipe && contador < 199; contador++){
                linha_sem_preco[contador] = linha_cardapio[contador];
            }
            linha_sem_preco[posicao_pipe] = '\0';
        } else {
            strcpy(linha_sem_preco, linha_cardapio);
        }
        
        // Converte linha para minusculo
        char linha_minusculo[200];
        for(contador = 0; linha_sem_preco[contador] != '\0'; contador++){
            if(linha_sem_preco[contador] >= 'A' && linha_sem_preco[contador] <= 'Z'){
                linha_minusculo[contador] = linha_sem_preco[contador] + 32;
            } else {
                linha_minusculo[contador] = linha_sem_preco[contador];
            }
        }
        linha_minusculo[contador] = '\0';
        
        // Busca
        bool busca_encontrada = false;
        
        // Busca exata
        if(strstr(linha_minusculo, termo_busca_minusculo) != NULL){
            busca_encontrada = true;
        }
        
        // Busca por sinonimos
        if(!busca_encontrada){
            if((strstr(termo_busca_minusculo, "burguer") != NULL || 
                strstr(termo_busca_minusculo, "hamburguer") != NULL || 
                strstr(termo_busca_minusculo, "xburguer") != NULL) && 
                strstr(linha_minusculo, "burger") != NULL){
                busca_encontrada = true;
            }
            else if(strstr(termo_busca_minusculo, "refri") != NULL && 
                    strstr(linha_minusculo, "refrigerante") != NULL){
                busca_encontrada = true;
            }
        }
        
        if(busca_encontrada){
            printf("Categoria: %s\n", categoria_atual);
            printf("Alimento: %s\n", linha_cardapio);
            printf("------------------------\n");
            alimento_encontrado = true;
        }
    }
    
    fclose(arquivo_cardapio);
    
    if(!alimento_encontrado){
        printf("Nenhum alimento encontrado com '%s'\n", termo_busca);
    }
    
    printf("\n");
    system("pause");
}

void salvar_pedido(const char *alimento, int quantidade, const char *data) {
    if (strlen(usuario_logado) == 0) {
        printf("Erro: Nenhum usuario logado!\n");
        return;
    }
    
    char nome_arquivo[100];
    sprintf(nome_arquivo, "pedidos_%s.txt", usuario_logado);
    
    FILE *arquivo_pedidos = fopen(nome_arquivo, "a");
    if (arquivo_pedidos != NULL) {
        fprintf(arquivo_pedidos, "Alimento: %s | Quantidade: %d | Data: %s | Avaliacao: Nao avaliado\n", 
                alimento, quantidade, data);
        fclose(arquivo_pedidos);
        printf("Pedido salvo no historico!\n");
    } else {
        printf("Erro ao salvar pedido no historico!\n");
    }
}

void cadastrar_pedido() {
    char alimento_pedido[100];
    char data_pedido[20];
    int quantidade_pedido;
    
    printf("\n===== CADASTRAR PEDIDO =====\n");
    
    printf("Digite o alimento: ");
    fgets(alimento_pedido, sizeof(alimento_pedido), stdin);
    alimento_pedido[strcspn(alimento_pedido, "\n")] = 0;
    
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade_pedido);
    getchar();
    
    printf("Digite a data (DD/MM/AAAA): ");
    fgets(data_pedido, sizeof(data_pedido), stdin);
    data_pedido[strcspn(data_pedido, "\n")] = 0;
    
    // Salva no arquivo geral de pedidos
    FILE *arquivo_geral = fopen("pedidos.txt", "a");
    if(arquivo_geral != NULL) {
        fprintf(arquivo_geral, "%s,%s,%d,%s,0\n", usuario_logado, alimento_pedido, quantidade_pedido, data_pedido);
        fclose(arquivo_geral);
    }
    
    // Salva no histórico do usuário
    salvar_pedido(alimento_pedido, quantidade_pedido, data_pedido);
    
    system("pause");
}

void historico_pedidos() {
    if (strlen(usuario_logado) == 0) {
        printf("Nenhum usuario logado!\n");
        system("pause");
        return;
    }
    
    char nome_arquivo[100];
    sprintf(nome_arquivo, "pedidos_%s.txt", usuario_logado);
    
    FILE *arquivo_pedidos = fopen(nome_arquivo, "r");
    if (arquivo_pedidos == NULL) {
        printf("Voce ainda nao fez nenhum pedido!\n");
        system("pause");
        return;
    }
    
    printf("\n===== HISTORICO DE PEDIDOS =====\n");
    printf("Usuario: %s\n\n", usuario_logado);
    
    char linha_pedido[200];
    int contador_pedido = 1;
    
    while (fgets(linha_pedido, sizeof(linha_pedido), arquivo_pedidos) != NULL) {
        printf("%d. %s", contador_pedido, linha_pedido);
        contador_pedido++;
    }
    
    fclose(arquivo_pedidos);
    
    if (contador_pedido == 1) {
        printf("Nenhum pedido encontrado no historico.\n");
    }
    
    printf("\n");
    system("pause");
}

void editar_pedido() {
    printf("\n=== EDITAR PEDIDO ===\n");
    printf("Funcionalidade em desenvolvimento...\n");
    printf("Aqui sera possivel editar pedidos existentes.\n");
    system("pause");
}

void excluir_pedido() {
    printf("\n=== EXCLUIR PEDIDO ===\n");
    printf("Funcionalidade em desenvolvimento...\n");
    printf("Aqui sera possivel excluir pedidos.\n");
    system("pause");
}

void avaliar_pedido() {
    int numero_pedido;
    int estrelas;
    
    printf("\n=== AVALIAR PEDIDO ===\n");
    
    // Primeiro mostra os pedidos
    historico_pedidos();
    
    printf("Digite o numero do pedido que deseja avaliar: ");
    scanf("%d", &numero_pedido);
    getchar();
    
    printf("Digite a avaliacao (0-5 estrelas): ");
    scanf("%d", &estrelas);
    getchar();
    
    if (estrelas < 0 || estrelas > 5) {
        printf("Avaliacao invalida! Use valores de 0 a 5.\n");
    } else {
        printf("Pedido %d avaliado com %d estrelas!\n", numero_pedido, estrelas);
    }
    
    system("pause");
}

int main(){
    menu();
    return 0;
}
