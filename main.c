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

            posicao_virgula = -1;
            for(contador = 0; linha[contador] != '\0'; contador++){
                if(linha[contador] == ','){
                    posicao_virgula = contador;
                    break;
                }
            }

            if(posicao_virgula != -1){
                for(contador = 0; contador < posicao_virgula && contador < 49; contador++){
                    usuario_correto[contador] = linha[contador];
                }
                usuario_correto[contador] = '\0';

                while(contador > 0 && usuario_correto[contador-1] == ' '){
                    usuario_correto[--contador] = '\0';
                }

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

        if(strstr(linha_cardapio, "=====") != NULL){
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

        if(strlen(linha_cardapio) == 0) continue;

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

        char linha_minusculo[200];
        for(contador = 0; linha_sem_preco[contador] != '\0'; contador++){
            if(linha_sem_preco[contador] >= 'A' && linha_sem_preco[contador] <= 'Z'){
                linha_minusculo[contador] = linha_sem_preco[contador] + 32;
            } else {
                linha_minusculo[contador] = linha_sem_preco[contador];
            }
        }
        linha_minusculo[contador] = '\0';

        bool busca_encontrada = false;

        if(strstr(linha_minusculo, termo_busca_minusculo) != NULL){
            busca_encontrada = true;
        }

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

    FILE *arquivo_geral = fopen("pedidos.txt", "a");
    if(arquivo_geral != NULL) {
        fprintf(arquivo_geral, "%s,%s,%d,%s,0\n", usuario_logado, alimento_pedido, quantidade_pedido, data_pedido);
        fclose(arquivo_geral);
    }

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
    if (strlen(usuario_logado) == 0) {
        printf("Nenhum usuario logado!\n");
        system("pause");
        return;
    }
    
    printf("\n=== EDITAR PEDIDO ===\n");
    
    char nome_arquivo[100];
    sprintf(nome_arquivo, "pedidos_%s.txt", usuario_logado);
    
    FILE *arquivo_pedidos = fopen(nome_arquivo, "r");
    if (arquivo_pedidos == NULL) {
        printf("Voce nao tem pedidos para editar!\n");
        system("pause");
        return;
    }
    
    printf("Seus pedidos atuais:\n");
    printf("====================\n");
    
    char linha_pedido[300];
    int numero_pedido = 1;
    int total_pedidos = 0;
    int i;
    char pedidos_guardados[20][300];
    
    while (fgets(linha_pedido, sizeof(linha_pedido), arquivo_pedidos) != NULL) {
        printf("%d. %s", numero_pedido, linha_pedido);
        strcpy(pedidos_guardados[total_pedidos], linha_pedido);
        numero_pedido++;
        total_pedidos++;
    }
    fclose(arquivo_pedidos);
    
    if (total_pedidos == 0) {
        printf("Nenhum pedido encontrado.\n");
        system("pause");
        return;
    }
    
    int pedido_editar;
    printf("\nDigite o numero do pedido que deseja editar (ou 0 para cancelar): ");
    scanf("%d", &pedido_editar);
    getchar();
    
    if (pedido_editar == 0) {
        printf("Operacao cancelada.\n");
        system("pause");
        return;
    }
    
    if (pedido_editar < 1 || pedido_editar > total_pedidos) {
        printf("Numero de pedido invalido!\n");
        system("pause");
        return;
    }
    
    printf("\n=== OPCOES DE EDICAO ===\n");
    printf("Pedido selecionado: %s", pedidos_guardados[pedido_editar-1]);
    printf("\nO que deseja fazer?\n");
    printf("1- Mudar quantidade do alimento\n");
    printf("2- Mudar alimento\n");
    printf("3- Adicionar novo alimento ao pedido\n");
    printf("4- Remover alimento do pedido\n");
    printf("5- Cancelar\n");
    printf("Escolha uma opcao: ");
    
    int opcao_edicao;
    scanf("%d", &opcao_edicao);
    getchar();
    
    switch(opcao_edicao) {
        case 1: {
            printf("\n=== MUDAR QUANTIDADE ===\n");
            printf("Pedido atual: %s", pedidos_guardados[pedido_editar-1]);
            
            int nova_quantidade;
            printf("Digite a nova quantidade: ");
            scanf("%d", &nova_quantidade);
            getchar();
            
            if (nova_quantidade <= 0) {
                printf("Quantidade invalida! Deve ser maior que zero.\n");
                system("pause");
                return;
            }
            
            char alimento[100], data[20], avaliacao[20];
            int quantidade_antiga;
            
            sscanf(pedidos_guardados[pedido_editar-1], "Alimento: %[^|] | Quantidade: %d | Data: %[^|] | Avaliacao: %[^\n]", 
                   alimento, &quantidade_antiga, data, avaliacao);
            
            alimento[strcspn(alimento, " ")] = '\0';
            
            sprintf(pedidos_guardados[pedido_editar-1], 
                    "Alimento: %s | Quantidade: %d | Data: %s | Avaliacao: %s\n", 
                    alimento, nova_quantidade, data, avaliacao);
            
            printf("Quantidade alterada de %d para %d!\n", quantidade_antiga, nova_quantidade);
            break;
        }
        
        case 2: {
            printf("\n=== MUDAR ALIMENTO ===\n");
            printf("Pedido atual: %s", pedidos_guardados[pedido_editar-1]);
            
            char novo_alimento[100];
            printf("Digite o novo alimento: ");
            fgets(novo_alimento, sizeof(novo_alimento), stdin);
            novo_alimento[strcspn(novo_alimento, "\n")] = 0;
            
            char alimento_antigo[100], data[20], avaliacao[20];
            int quantidade;
            
            sscanf(pedidos_guardados[pedido_editar-1], "Alimento: %[^|] | Quantidade: %d | Data: %[^|] | Avaliacao: %[^\n]", 
                   alimento_antigo, &quantidade, data, avaliacao);
            
            sprintf(pedidos_guardados[pedido_editar-1], 
                    "Alimento: %s | Quantidade: %d | Data: %s | Avaliacao: %s\n", 
                    novo_alimento, quantidade, data, avaliacao);
            
            printf("Alimento alterado de '%s' para '%s'!\n", alimento_antigo, novo_alimento);
            break;
        }
        
        case 3: {
            printf("\n=== ADICIONAR ALIMENTO ===\n");
            
            char novo_alimento[100];
            int nova_quantidade;
            char nova_data[20];
            
            printf("Digite o novo alimento: ");
            fgets(novo_alimento, sizeof(novo_alimento), stdin);
            novo_alimento[strcspn(novo_alimento, "\n")] = 0;
            
            printf("Digite a quantidade: ");
            scanf("%d", &nova_quantidade);
            getchar();
            
            printf("Digite a data (DD/MM/AAAA): ");
            fgets(nova_data, sizeof(nova_data), stdin);
            nova_data[strcspn(nova_data, "\n")] = 0;
            
            if (total_pedidos < 20) {
                sprintf(pedidos_guardados[total_pedidos], 
                        "Alimento: %s | Quantidade: %d | Data: %s | Avaliacao: Nao avaliado\n", 
                        novo_alimento, nova_quantidade, nova_data);
                total_pedidos++;
                printf("Novo alimento adicionado ao pedido!\n");
            } else {
                printf("Limite maximo de pedidos atingido!\n");
            }
            break;
        }
        
        case 4: {
            printf("\n=== REMOVER ALIMENTO ===\n");
            printf("Pedido que sera removido: %s", pedidos_guardados[pedido_editar-1]);
            
            char confirmacao;
            printf("Tem certeza que deseja remover este alimento? (s/n): ");
            scanf("%c", &confirmacao);
            getchar();
            
            if (confirmacao == 's' || confirmacao == 'S') {
                for (i = pedido_editar-1; i < total_pedidos-1; i++) {
                    strcpy(pedidos_guardados[i], pedidos_guardados[i+1]);
                }
                total_pedidos--;
                printf("Alimento removido do pedido!\n");
            } else {
                printf("Remocao cancelada.\n");
            }
            break;
        }
        
        case 5:
            printf("Edicao cancelada.\n");
            system("pause");
            return;
            
        default:
            printf("Opcao invalida!\n");
            system("pause");
            return;
    }
    
    FILE *arquivo_novo = fopen(nome_arquivo, "w");
    if (arquivo_novo != NULL) {
        for (i = 0; i < total_pedidos; i++) {
            fputs(pedidos_guardados[i], arquivo_novo);
        }
        fclose(arquivo_novo);
        printf("Alteracoes salvas com sucesso!\n");
    } else {
        printf("Erro ao salvar alteracoes!\n");
    }
    
    system("pause");
}

void excluir_pedido() {
    if (strlen(usuario_logado) == 0) {
        printf("Nenhum usuario logado!\n");
        system("pause");
        return;
    }
    
    printf("\n=== EXCLUIR PEDIDO ===\n");
    
    char nome_arquivo[100];
    sprintf(nome_arquivo, "pedidos_%s.txt", usuario_logado);
    
    FILE *arquivo_pedidos = fopen(nome_arquivo, "r");
    if (arquivo_pedidos == NULL) {
        printf("Voce nao tem pedidos para excluir!\n");
        system("pause");
        return;
    }
    
    printf("Seus pedidos atuais:\n");
    printf("====================\n");
    
    char linha_pedido[300];
    int numero_pedido = 1;
    int total_pedidos = 0;
    
    while (fgets(linha_pedido, sizeof(linha_pedido), arquivo_pedidos) != NULL) {
        printf("%d. %s", numero_pedido, linha_pedido);
        numero_pedido++;
        total_pedidos++;
    }
    fclose(arquivo_pedidos);
    
    if (total_pedidos == 0) {
        printf("Nenhum pedido encontrado.\n");
        system("pause");
        return;
    }
    
    int pedido_excluir;
    printf("\nDigite o numero do pedido que deseja excluir (ou 0 para cancelar): ");
    scanf("%d", &pedido_excluir);
    getchar();
    
    if (pedido_excluir == 0) {
        printf("Operacao cancelada.\n");
        system("pause");
        return;
    }
    
    if (pedido_excluir < 1 || pedido_excluir > total_pedidos) {
        printf("Numero de pedido invalido!\n");
        system("pause");
        return;
    }
    
    char confirmacao;
    printf("Tem certeza que deseja excluir o pedido %d? (s/n): ", pedido_excluir);
    scanf("%c", &confirmacao);
    getchar();
    
    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Exclusao cancelada.\n");
        system("pause");
        return;
    }
    
    arquivo_pedidos = fopen(nome_arquivo, "r");
    if (arquivo_pedidos == NULL) {
        printf("Erro ao abrir arquivo de pedidos!\n");
        system("pause");
        return;
    }
    
    char nome_arquivo_temp[100];
    sprintf(nome_arquivo_temp, "temp_%s.txt", usuario_logado);
    FILE *arquivo_temp = fopen(nome_arquivo_temp, "w");
    
    if (arquivo_temp == NULL) {
        printf("Erro ao criar arquivo temporario!\n");
        fclose(arquivo_pedidos);
        system("pause");
        return;
    }
    
    int pedido_atual = 1;
    while (fgets(linha_pedido, sizeof(linha_pedido), arquivo_pedidos) != NULL) {
        if (pedido_atual != pedido_excluir) {
            fputs(linha_pedido, arquivo_temp);
        } else {
            printf("Pedido %d excluido: %s", pedido_excluir, linha_pedido);
        }
        pedido_atual++;
    }
    
    fclose(arquivo_pedidos);
    fclose(arquivo_temp);
    
    remove(nome_arquivo);
    rename(nome_arquivo_temp, nome_arquivo);
    
    printf("Pedido excluido com sucesso!\n");
    system("pause");
}

void avaliar_pedido() {
    if (strlen(usuario_logado) == 0) {
        printf("Nenhum usuario logado!\n");
        system("pause");
        return;
    }

    printf("\n=== AVALIAR PEDIDO ===\n");

    char nome_arquivo[100];
    sprintf(nome_arquivo, "pedidos_%s.txt", usuario_logado);
    
    FILE *arquivo_pedidos = fopen(nome_arquivo, "r");
    if (arquivo_pedidos == NULL) {
        printf("Voce nao tem pedidos para avaliar!\n");
        system("pause");
        return;
    }
    
    printf("Seus pedidos:\n");
    printf("=============\n");
    
    char linha_pedido[300];
    int numero_pedido = 1;
    int total_pedidos = 0;
    int i;
    char pedidos_guardados[20][300];
    
    while (fgets(linha_pedido, sizeof(linha_pedido), arquivo_pedidos) != NULL) {
        printf("%d. %s", numero_pedido, linha_pedido);
        strcpy(pedidos_guardados[total_pedidos], linha_pedido);
        numero_pedido++;
        total_pedidos++;
    }
    fclose(arquivo_pedidos);
    
    if (total_pedidos == 0) {
        printf("Nenhum pedido encontrado.\n");
        system("pause");
        return;
    }

    int pedido_avaliar;
    printf("\nDigite o numero do pedido que deseja avaliar: ");
    scanf("%d", &pedido_avaliar);
    getchar();

    if (pedido_avaliar < 1 || pedido_avaliar > total_pedidos) {
        printf("Numero de pedido invalido!\n");
        system("pause");
        return;
    }
    
    int estrelas;
    printf("Digite a avaliacao (0-5 estrelas): ");
    scanf("%d", &estrelas);
    getchar();

    if (estrelas < 0 || estrelas > 5) {
        printf("Avaliacao invalida! Use valores de 0 a 5.\n");
        system("pause");
        return;
    }
    
    char alimento[100], data[20], avaliacao_antiga[20];
    int quantidade;
    
    sscanf(pedidos_guardados[pedido_avaliar-1], "Alimento: %[^|] | Quantidade: %d | Data: %[^|] | Avaliacao: %[^\n]", 
           alimento, &quantidade, data, avaliacao_antiga);
    
    alimento[strcspn(alimento, " ")] = '\0';
    
    char nova_avaliacao[20];
    if (estrelas == 0) {
        strcpy(nova_avaliacao, "0 estrela");
    } else if (estrelas == 1) {
        strcpy(nova_avaliacao, "1 estrela");
    } else {
        sprintf(nova_avaliacao, "%d estrelas", estrelas);
    }
    
    sprintf(pedidos_guardados[pedido_avaliar-1], 
            "Alimento: %s | Quantidade: %d | Data: %s | Avaliacao: %s\n", 
            alimento, quantidade, data, nova_avaliacao);
    
    FILE *arquivo_novo = fopen(nome_arquivo, "w");
    if (arquivo_novo != NULL) {
        for (i = 0; i < total_pedidos; i++) {
            fputs(pedidos_guardados[i], arquivo_novo);
        }
        fclose(arquivo_novo);
        printf("Pedido %d avaliado com %s!\n", pedido_avaliar, nova_avaliacao);
    } else {
        printf("Erro ao salvar avaliacao!\n");
    }

    system("pause");
}

int main(){
    menu();
    return 0;
}
