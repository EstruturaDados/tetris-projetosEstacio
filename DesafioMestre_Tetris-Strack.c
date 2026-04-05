// Incluindo bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// --- Variável global
#define MAX 5 // tamanho máximo da fila
#define MAXP 3 // tamanho máximo da pilha

int proximoID = 0; // para ID's das novas peças

// --- Definindo a estrutura das peças
typedef struct {
	char peca[2];
	int id;
} Peca;

// --- Definindo a estrutura da fila de peças com início, fim e total de peças
typedef struct {
	Peca itens[MAX];
	int inicio;
	int fim;
	
} Fila;

// --- Definindo a estrutura da Pilha de peças máximo 3 peças.
typedef struct {
	Peca itens[MAXP];
	int topo;
} Pilha; 

//======================================== INICIALIZAÇÕES ========================================================

// --- Para inicializar a fila (definindo 'f' como ponteiro da estrutura Peca.
void inicioFila(Fila *f) {
	f-> inicio = 0;
	f-> fim = 0;
	
} 

// --- inicializar pilha
void inicioPilha(Pilha *p) {
	p->topo = -1;
}
//======================================== OPERAÇÕES BÁSICAS DE VERIFICAÇÃO =======================================
// --- Para verificar se a fila está cheia
int filaCheia(Fila *f){
	return (f->fim + 1) %  MAX == f->inicio;
}

// --- Para verificar se a fila está vazia
int filaVazia(Fila *f) {
	return f->inicio == f->fim;
	
}

// --- Para verificar se a pilha esta cheia
int pilhaCheia(Pilha *p) {
	return p->topo == MAXP - 1;
}

// --- Para verifcar se a pilha esta vazia
int pilhaVazia(Pilha *p) {
	return p->topo == -1;
}

// ======================================= PREENCHENDO FILA E PILHA NO INÍCIO =====================================
// --- função para preencher a fila no inicio
void preencherFila(Fila *f) {
	char tipos[] = {'T','O','L','I'};
		
	
	//for (int i = 0; i < MAX; i++) {
	for (int i = 0; i < MAX - 1; i++) {
		Peca p;
		
		p.peca[0] = tipos[i % 4];
		p.peca[1] = '\0';
		
		p.id = proximoID++;
		
		inserir(f, p);

	}
}

// --- função para preencher a pilha no inicio
void preencherPilha(Pilha *pl) {
	char tipos[] = {'T','O','L'};
		
	
	for (int i = 0; i < MAXP; i++) {
		Peca p;
		
		p.peca[0] = tipos[i % 3];
		p.peca[1] = '\0';
		
		p.id = proximoID++;
		
		push(pl, p);
		
	}
}
// ======================================= OPERAÇÕES COMO FILA  ====================================================

// --- função para inserir peças na fila
int inserir(Fila *f, Peca p) {
	if (filaCheia(f)) {
		printf("peça da pilha inserida na fila. Fila continua cheia.\n");
		return 0; // erro
	}

	f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
	
	return 1; // sucesso
}

// --- função para remover peças da fila
int remover(Fila *f, Peca *p) { 
	if(filaVazia(f)) {
		printf("Fila vazia, nao ha peça a remover!\n");
		return 0;
	}
	
	*p = f->itens[f->inicio];  // copia o elemento do início da fila para *p
	f->inicio = (f->inicio + 1) % MAX; // avança o início da fila (comportamento circular)
	
	return 1; // sucesso
    	
}

// --- função para atualizar a fila a cada ação (jogar, reservar)
void atualizaFila(Fila *f) {

	Peca nova; // 'nova' contém os dados da peça
	char tipos[] = {'T','O','I','L'};
					
	nova.peca[0] = tipos[proximoID % 4];
	nova.peca[1] = '\0';
	nova.id = proximoID++;
				
	inserir(f, nova);
	
}

// ======================================= OPERAÇÕES COMO PILHA  ==================================================

// --- função para inserir (push) peças na pilha
int push(Pilha *p, Peca nova) {
	if(pilhaCheia(p)) {
		printf("Pilha cheia, nao e possivel inserir!\n");
		return 0;
	}

	p->itens[++p->topo] = nova;
	return 1;
}

// --- função para remover (pop) peça da pilha (simulação de uso no jogo)
int pop(Pilha *p, Peca *remover) {
	if(pilhaVazia(p)) {
		printf("Pilha vazia, nao ha peca para remover!\n");
		return 0;
	}
	
	*remover = p->itens[p->topo]; // Remove o primeiro elemento da fila e avança o índice
	p->topo--;
    return 1;

}
//=================================================== FILA E PILHA
// --- função para mostrar fila 
void mostrarFilaPilha(Fila *f, Pilha *pl) {
	if(filaVazia(f)) {
		printf("Fila: [ ] [ ] [ ] [ ] [ ] \n");

	} else {
		printf("\n----------------------------------------------------------\n");
		printf("              PECAS ATUAIS NA FILA E PILHA");
		printf("\n----------------------------------------------------------\n");
	
		printf("Fila:  ");

		int idx = f->inicio;
		while (idx != f->fim) {  // PARA no fim, não MAX
    		printf("[%s, %d] ", f->itens[idx].peca, f->itens[idx].id);
    		idx = (idx + 1) % MAX; // avança circularmente
		}
	    	
			printf("\n"); // quebra de linha entre fila e pilha
	
	}
	if(pilhaVazia(pl)) {
		printf("Pilha : [    ] [    ] [    ]\n");
	} else {
		printf("Pilha: ");
		
		for (int i = pl->topo; i >= 0; i--) {
    	printf("[%s, %d] ", pl->itens[i].peca, pl->itens[i].id);

		}

		printf("\n");
			
	}
			
}
// --- função principal Declaração, manipulação e exibição da fila
int main() {
	Fila f; // f vari�vel tipo fila armazenada na memória.
	Pilha pl;
	
	inicioFila(&f); // Inicializa a fila
	inicioPilha(&pl);
	
	preencherFila(&f);
	preencherPilha(&pl);
		
		
	int opcao; // número de opção do menu;
	Peca p;
	
		do {
		// mostrar fila no inicio somente após o proximoID 8 (5 fila e 3 pilha)	não executa	
		if (proximoID <= 8) {
			mostrarFilaPilha(&f, &pl);
		}
				 
		printf("\n----------------------------------------------------------\n");
		printf("        MOVIMENTAR FILA     ");
		printf("\n----------------------------------------------------------");
		printf("\n1 - Jogar Peca da frente da fila");
		printf("\n2 - Enviar peca da fila para reserva (Pilha)");
		printf("\n3 - Usar Peca da reserva(pilha)");
		printf("\n4 - Trocar peca da frente da fila com o topo da pilha");
		printf("\n5 - Trocar as 3 primeiras pecas da fila com as 3 da pilha");
		printf("\n0 - Sair...");
		printf("\n----------------------------------------------------------\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
		
		getchar(); // limpa Enter
		
		switch (opcao) {
			
			case 1:
				printf("Jogar Peca\n");
				remover(&f, &p);
				printf("Removido: [%s %d]\n", p.peca, p.id);
				
				// --- gera nova peça automaticamente
				atualizaFila(&f);
				
				break;
			
			case 2: {
				if (filaVazia(&f)) {
					printf("\nFila vazia!\n");
					break;
				}
				
				Peca topo;
				pop(&pl, &topo);
				
				Peca frente;
				remover(&f, &frente);
				printf("remover: [%c, %d]\n", topo.peca[0], topo.id);

				if (pilhaCheia(&pl)) {
					Peca topo;
					pop(&pl, &topo);

					push(&pl, frente);
					inserir(&f, topo);

				} else {
					push(&pl, frente);
				}

				atualizaFila(&f);
				break;
			}

			case 3: {
				
				if(pilhaVazia(&pl)) {
					printf("\nNao ha peca na reservada\n");
					break;
				}
					Peca removida;
					pop(&pl, &removida);
					atualizaFila(&f);

					remover(&f, &p); // tira da reserva
					inserir(&f, removida); // coloca na fila	

					break;
								
			}
			
			case 4: {
				if (filaVazia(&f) || pilhaVazia(&pl)) {
						printf("\nNao ha elementos suficientes\n");
						break;
					}

					Peca frente, topo;

					remover(&f, &frente);
					pop(&pl, &topo);

					inserir(&f, topo);
					push(&pl, frente);

					break;
			}

			case 5: {

					// removendo as três primeiras peças da fila
					Peca fila3[3];

					for (int i = 0; i < 3; i++) {
    					remover(&f, &fila3[i]);
					}	

					// removendo as três peças da pilha
					Peca pilha3[3];

					for (int i = 0; i < 3; i++) {
    					pop(&pl, &pilha3[i]);
					}

					// colocando da pilha as peças na fila
					for (int i = 2; i >= 0; i--) {
    					inserir(&f, pilha3[i]);
					}

					// colocando da fila as peças na pilha
					for (int i = 0; i < 3; i++) {
    					push(&pl, fila3[i]);
					}
					

				break;	
			}	
				
			case 0:
				printf("Saindo...");
				break;
			default:
				printf("Opcao invalida..");		
		}
	 
	}while (opcao != 0);
	
	return 0;
	
}	
