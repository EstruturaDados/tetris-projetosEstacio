// Incluindo bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>


// --- Variável global

#define MAX 5 // tamanho máximo do vetor

int proximoID = 0; // para ID's de peças novas

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

// --- Para inicializar a fila (definindo 'f' como ponteiro da estrutura Peca.

void inicioFila(Fila *f) {
	f-> inicio = 0;
	f-> fim = 0;
	f-> total = 0;
} 

// --- Função para preencher a fila no inicio
void preencherFila(Fila *f) {
	char tipos[] = {'T','O','L','I'};
		static int proximoID = 0;
	
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

// --- função para mostrar fila 

void mostrarFila(Fila *f) {
	if(filaVazia(f)) {
		printf("Fila vazia, nada para mostrar\n");
		return;
	}
	
	printf("----------------------------------------\n");
	printf("       PECAS NA FILA ATUAL\n");
	printf("----------------------------------------\n");
	
	printf("Fila: ");
	for (int i = 0, idx = f->inicio; 
	i < f->total; i++, idx = (idx + 1) % MAX ) {
		printf("[%s, %d] ", f->itens[idx].peca, f->itens[idx].id);
		
	}
	printf("\n");
}

// --- Declaração e exibição da fila

int main() {
	Fila f; // f variável tipo fila armazenada na memória.
	inicioFila(&f); // Inicializa a fila
	
	preencherFila(&f);
	
	int opcao; // número de opção do menu;
	Peca p;
		
	do {
		// --- mostra a fila
		mostrarFila(&f);
		 
		printf("\n----------------------------------------\n");
		printf("        MOVIMENTAR FILA     \n");
		printf("----------------------------------------");
		printf("\n1 - Remover\n2 - Inserir\n0 - Sair\n");
		printf("----------------------------------------\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
		
		getchar(); // limpa Enter
		
		switch (opcao) {
			
			case 1:
				remover(&f, &p);
				printf("\nRemovido: [%s %d]\n", p.peca, p.id);
				break;
			
			case 2:
				printf("Escolha a peca (I, O, L, T): ");
				scanf(" %c", &p.peca[0]);
				p.peca[1] = '\0';
				
				p.id = proximoID++;
				
				inserir(&f, p);
				break;
			
			case 0:
				printf("Saindo...");
				break;
			default:
				printf("Opcao invalida..");		
		}	
	}while (opcao != 0);
	
	return 0;
	
}	