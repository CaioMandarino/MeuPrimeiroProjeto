#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct endereco {
    char estado[3];
    char cidade[40];
    char bairro[40];
    char rua[40];
    int cep;    
} Endereco;

typedef struct nasc {
    int rg;
    int cpf;
    int idade; 
} Nascimento;

typedef struct cadastro {
    char nome[40];
    int telefone;
    Nascimento dados1;
    Endereco dados2;
} Cadastro;

typedef struct no {
    struct no *proximo;
    Cadastro dados; 
} No;

void cabeca(void) {
    system("cls");
    printf("---------Cadastro---------\n\n");    
}

void ler_cadastro(Cadastro *dados) {
    printf("Nome: \n");
    getchar(); 
    fgets(dados->nome, sizeof(dados->nome), stdin);
    dados->nome[strcspn(dados->nome, "\n")] = 0; 

    printf("Telefone: \n");
    scanf("%d", &dados->telefone);

    cabeca();
    printf("RG: \n");
    scanf("%d", &dados->dados1.rg);
    printf("CPF: \n");
    scanf("%d", &dados->dados1.cpf);
    printf("Idade: \n");  
    scanf("%d", &dados->dados1.idade);  
    cabeca();
    getchar(); 
    printf("Estado [UF]: \n");
    fgets(dados->dados2.estado, sizeof(dados->dados2.estado), stdin);
    dados->dados2.estado[strcspn(dados->dados2.estado, "\n")] = 0; 

    printf("Cidade: \n");
    fgets(dados->dados2.cidade, sizeof(dados->dados2.cidade), stdin);
    dados->dados2.cidade[strcspn(dados->dados2.cidade, "\n")] = 0; 

    printf("Bairro: \n");
    fgets(dados->dados2.bairro, sizeof(dados->dados2.bairro), stdin);
    dados->dados2.bairro[strcspn(dados->dados2.bairro, "\n")] = 0; 

    printf("Rua: \n");
    fgets(dados->dados2.rua, sizeof(dados->dados2.rua), stdin);
    dados->dados2.rua[strcspn(dados->dados2.rua, "\n")] = 0; 

    printf("CEP: \n");
    scanf("%d", &dados->dados2.cep);
}

void entrar_fila_Prioridade(No **inicio, Cadastro dados) {
    No *aux, *novo = malloc(sizeof(No));
    if (novo) {
        novo->proximo = NULL;
        novo->dados = dados; 

        if (*inicio == NULL) {
            *inicio = novo; 
        } else { 
            if (dados.dados1.idade < 60) { 
                if ((*inicio)->dados.dados1.idade >= 60) {
                    novo->proximo = *inicio;
                    *inicio = novo;
                } else {
                    aux = *inicio;
                    while (aux->proximo && aux->proximo->dados.dados1.idade < 60) {
                        aux = aux->proximo;
                    }
                    novo->proximo = aux->proximo;
                    aux->proximo = novo;
                }
            } else { 
                aux = *inicio;
                while (aux->proximo) {
                    aux = aux->proximo;
                }
                aux->proximo = novo;
            }
        }
    } else {
        printf("Erro ao alocar memoria...\n");
    }
}

void remover_fila(No **inicio) {
    if (*inicio) {
        No* remover = *inicio;
        *inicio = remover->proximo;
        printf("O elemento %s foi removido!\n", remover->dados.nome);
        free(remover); 
    } else {
        printf("Sem elementos\n");
    }
}

void imprimir(No **inicio) {
    No *aux = *inicio;
    printf("LISTA: \n");
    while (aux) {
        printf("Nome: %s, Telefone: %d, Idade: %d\n", aux->dados.nome, aux->dados.telefone, aux->dados.dados1.idade);  
        aux = aux->proximo;
    }
}

int main() {
    int opcao;
    No *topo = NULL;
    Cadastro dados;
	FILE *arq;
	char usuario[30], senha[30], conferir[30];
	char nomeParaArq[54];
	char resp;
	int registro, tamanho;
	do {		
		printf("Vc ja esta registrado? [1] para Sim e [2] para Nao: ");
		scanf("%d", &registro);
		switch(registro){
			case 1 :
				printf("Qual seu usuario: ");
				scanf("%s", usuario);
				getchar();
				strcat(usuario, ".bin");
				arq = fopen(usuario, "rb");
				if (arq == NULL){
					printf("\nUsuario nao encontrado\n");
					break;
				}
				printf("Qual sua senha: ");
				fgets(senha, 30, stdin);
				fread(&conferir, sizeof(conferir), 30, arq);
				
					if (strcmp(conferir, senha) == 0){
						printf("Login realizado com sucesso!\n");
						do {
							printf("\n\n\tDigite:\n\t0 Para sair\n\t1 Para Inserir\n\t2 Para Remover\n\t3 Para Imprimir\n");
							scanf("%d", &opcao);
							switch(opcao) {
								case 0:
									printf("Encerrando Programa...");
									break;
								case 1: 
									ler_cadastro(&dados);
									entrar_fila_Prioridade(&topo, dados);
									break;
								case 2: 
									remover_fila(&topo);
									break;
								case 3:
									imprimir(&topo);
									break;
								default:
									printf("Opcao invalida!\n");
							}
						} while (opcao != 0);
					}
					else {
						printf("\nErro senha incorreta\n");
					}
					fclose(arq);	
				
				break;	
			case 2 :
				printf("Escolha um nome de usuario: ");
				scanf("%s", usuario);
				getchar();
				printf("Escolha uma senha: ");
				fgets(senha, 30, stdin);
				strcat(usuario, ".bin");
				arq = fopen(usuario, "wb");
				if (arq == NULL){
					printf("Erro ao abrir o arquivo");
					return 1;
				}
				tamanho = strlen(senha);
				fwrite(senha, sizeof(char), tamanho, arq);
				fclose(arq);
				break;
			default :
				printf("Digite um valor que seja 1 ou 2\n");
		}
		printf("Quer fechar o programa? [S] / [N]");
		scanf(" %c", &resp);
	} while (resp == 'N');
    
    return 0;
}

