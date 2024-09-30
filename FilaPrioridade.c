#include <stdio.h>
#include <stdlib.h>
typedef struct no{
	struct no *proximo;
	int dado;	
}No;
void entrar_fila(No **inicio, int x){
	No *aux, *novo = malloc(sizeof(No));
	if(novo){
		novo->proximo = NULL; 
		novo->dado = x;
		if(*inicio == NULL){
			*inicio = novo; 
		}
		else{ 
			aux = *inicio;
			while(aux->proximo){
				aux = aux->proximo;
			}
			aux->proximo = novo;
		}
	}
	else{
		printf("Erro ao alocar memoria...\n");
	}
}
void entrar_fila_Prioridade(No **inicio, int x){
	No *aux, *novo = malloc(sizeof(No));
	if(novo){
		novo->proximo = NULL; 
		novo->dado = x;
		if(*inicio == NULL){
			*inicio = novo; 
		}
		else{ 
			if(x > 59){
				if( (*inicio)->dado < 60){
					novo->proximo = *inicio;
					*inicio = novo;
				}
				else{
					aux = *inicio;
					while(aux->proximo->dado > 59 && aux->proximo){
						aux = aux->proximo;
					}
					novo->proximo = aux->proximo;
					aux->proximo = novo;

				}	
			}
			else{ 
				aux = *inicio;
				while(aux->proximo){
					aux = aux->proximo;
				}
				aux->proximo = novo;
			}
		}
	}
	else{
		printf("Erro ao alocar memoria...\n");
	}
}
void remover_fila(No **inicio){
	if(*inicio){
		No* remover = *inicio;
		*inicio = remover->proximo;
		printf("O elemento %d foi removido!\n", remover->dado);
		free(remover); 
	}	
	else{
		printf("Sem elementos\n");
	}
}
void imprimir(No **inicio){
	No *aux = *inicio;
	printf("LISTA: ");
	while(aux){
		printf("%d ", aux->dado);
		aux = aux->proximo;
	}
}
int main(){
	int opcao, x;
	No *topo = NULL;
	do{
		printf("\n\tDigite:\n\t0 Para sair\n\t1 Para Inserir\n\t2 Para Remover\n\t3 Para Imprimir\n");
		scanf("%d", &opcao);
		switch(opcao){
			case 0:
				printf("Encerrando Programa...");
				break;
			case 1: 
				printf("Digite um valor: ");
				scanf("%d", &x);
				entrar_fila_Prioridade(&topo, x);
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
	}while(opcao != 0);
 return 0;
}
