// Incluindo bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>


// --- Variável global
#define MAX 5 // tamanho máximo do vetor
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
	int total; 
} Fila;

// --- Definindo a estrutura da Pilha de peças máximo 3 peças.
typedef struct {
	Peca itens[MAX];
	int topo;
} Pilha; 

// --- Protótipo(s) necessários em função do acréscimo de funções (Fila, Pilha)
void inserir(Fila *f, Peca p);
//========================================FILA
// --- Para inicializar a fila (definindo 'f' como ponteiro da estrutura Peca.
void inicioFila(Fila *f) {
	f-> inicio = 0;
	f-> fim = 0;
	f-> total = 0;
} 

// --- Função para preencher a fila no inicio
void preencherFila(Fila *f) {
	char tipos[] = {'T','O','L','I'};
		
	
	for (int i = 0; i < MAX; i++) {
		Peca p;
		
		p.peca[0] = tipos[i % 4];
		p.peca[1] = '\0';
		
		p.id = proximoID++;
		
		inserir(f, p);
	}
}

// --- Para verificar se a fila está cheia
int filaCheia(Fila *f){
	return f-> total == MAX;
}

// --- Para verificar se a fila está vazia
int filaVazia(Fila *f) {
	return f-> total == 0;
}

//========================================PILHA
// --- Inicializar pilha
void inicioPilha(Pilha *p) {
	p->topo = -1;
}

// --- Para verificar se a pilha esta cheia
int pilhaCheia(Pilha *p) {
	return p->topo == MAX - 1;
}

// --- Para verifcar se a pilha esta vazia
int pilhaVazia(Pilha *p) {
	return p->topo == -1;
}

//========================================== Funções FILA
// --- Função para inserir peças na fila
void inserir(Fila *f, Peca p) {
	if (filaCheia(f)) {
		printf("Fila cheia, nao foi possível inserir peca!\n");
		return;
	}
	
	f->itens[f->fim] = p;
	f->fim = (f->fim + 1) % MAX; // Aplica a lógica circular (anda uma casa,
	f->total++;				     // se passar do tamanho da fila, retorna ao inicio.)
	
	
}

// --- Função para remover peças da fila
void remover(Fila *f, Peca *p) {
	if(filaVazia(f)) {
		printf("Fila vazia, nao ha peça a remover!\n");
		return;
	}
	
	*p = f->itens[f->inicio]; // Coloca o primeiro item na variável p
	f->inicio = (f->inicio + 1) % MAX;
	f->total--;
}

// --- Função para atualizar a fila a cada ação (jogar, reservar)
void atualizaFila(Fila *f) {

	Peca nova;
	char tipos[] = {'T','O','I','L'};
					
	nova.peca[0] = tipos[proximoID % 4];
	nova.peca[1] = '\0';
	nova.id = proximoID++;
				
	inserir(f, nova);
	
}
//========================================== Funções PILHA
// --- função para inserir (push) peças na pilha
void push(Pilha *p, Peca nova) {
	if(pilhaCheia(p)) {
		printf("Pilha cheia, nao e possivel inserir!\n");
		return;
	}
	
	p->topo++; // cria um espaço
	p->itens[p->topo] = nova; // coloca a nova peça no topo.
}

// --- funçao para remover (pop) peça da pilha (simulação de uso no jogo)
void pop(Pilha *p, Peca *remover) {
	if(pilhaVazia(p)) {
		printf("Pilha vazia, nao ha peca para remover!\n");
		return;
	}
	
	*remover = p->itens[p->topo];
	p->topo--;
}

//=================================================== FILA E PILHA
// --- função para mostrar fila 
void mostrarFilaPilha(Fila *f, Pilha *pl) {
	if(filaVazia(f)) {
		printf("Fila: [ ] [ ] [ ] [ ] [ ]\n");
		return;
		
	} else {
		printf("----------------------------------------\n");
		printf("    PECAS ATUAIS NA FILA E PILHA\n");
		printf("----------------------------------------\n");
	
		printf("Fila:   ");
		for (int i = 0, idx = f->inicio; 
		i < f->total; i++, idx = (idx + 1) % MAX ) {
			printf("[%s, %d] ", f->itens[idx].peca, f->itens[idx].id);
		}
	}
		
	printf("\n"); // quebra de linha entre fila e pilha
	
	if(pilhaVazia(pl)) {
		printf("Pilha : [    ] [    ] [    ] [    ] [    ]\n");
	} else {
		printf("Pilha: ");
		
		for (int i = pl->topo; i >=0; i--) {
			printf("[%s, %d] ", pl->itens[i].peca, pl->itens[i].id);
	}
	
		
	}
	
}

// --- Função principal Declaração, manipulação e exibição da fila
int main() {
	Fila f; // f variável tipo fila armazenada na memória.
	Pilha pl;
	
	inicioFila(&f); // Inicializa a fila
	inicioPilha(&pl);
	
	preencherFila(&f);
		
	//mostrarFilaPilha(&f, &pl);
	
	int opcao; // número de opção do menu;
	Peca p;
	
		
	do {
		// --- mostra a fila
		//mostrarFila(&f);
		mostrarFilaPilha(&f, &pl);
		 
		printf("\n----------------------------------------\n");
		printf("        MOVIMENTAR FILA     \n");
		printf("----------------------------------------");
		printf("\n1 - Jogar Peca\n2 - Reservar Peca \n3 -");
		printf(" Usar Peca Reservada\n0 - Sair\n");
		printf("----------------------------------------\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
		
		getchar(); // limpa Enter
		
		switch (opcao) {
			
			case 1:
				//printf("Jogar Peca\n");
				remover(&f, &p);
				printf("Removido: [%s %d]\n", p.peca, p.id);
				
				// --- gera nova peça automaticamente
				atualizaFila(&f);
								
				break;
			
			case 2:
				if (!filaVazia(&f) && !pilhaCheia(&pl)) {
					Peca reserva;
					
					remover(&f, &reserva); // tira da fila
					push(&pl, reserva); // coloca na pilha
					atualizaFila(&f);
										
				} else {
					printf("\nNao foi possivel reservar!");
				} 
				break;
			
			case 3: {
				
				if(pilhaVazia(&pl)) {
					printf("\nNao ha peca na reservada\n");
					break;
				}
					Peca removida;
					pop(&pl, &removida);
					atualizaFila(&f);
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