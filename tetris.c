// Código nível novato

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

int opcao;

// Struct da peça
typedef struct {
    char nome;
    int id;
} Peca;

// Struct da fila
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// Protótipos
void exibirMenu();
Peca jogarPeca(Fila *f);
void inserirPeca(Fila *f, Peca p);
void mostrarPecas(Fila *f);
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
Peca gerarPeca(int id);

int main() {
    srand(time(NULL));
    Fila f;
    int proximoId = 0;
    inicializarFila(&f);
    // Preenche a fila inicial com 5 peças
    for(int i = 0; i < MAX; i++) {
        inserirPeca(&f, gerarPeca(proximoId));
        proximoId++;
    }
    do {
        mostrarPecas(&f);
        exibirMenu();
        switch(opcao) {
            case 1: {
                Peca removida = jogarPeca(&f);
                if(removida.id != -1) {
                    printf("Peça jogada: [%c %d]\n", removida.nome, removida.id);
                }
                mostrarPecas(&f);
                break;
            }
            case 2: {
                if(filaCheia(&f)) {
                    printf("Número máximo de peças atingido! Você deve jogar uma peça antes.\n");
                } else {
                    Peca nova = gerarPeca(proximoId);
                    inserirPeca(&f, nova);
                    printf("Peça adicionada: [%c %d]\n", nova.nome, nova.id);
                    proximoId++;
                }
                mostrarPecas(&f);
                break;
            }
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while(opcao != 0);
    return 0;
}

// Menu
void exibirMenu() {
    printf("\nOpções:\n");
    printf("1 - Jogar peça\n");
    printf("2 - Inserir nova peça\n");
    printf("0 - Sair\n");
    printf("Digite sua escolha: ");
    scanf("%d", &opcao);
}

// Remove peça da fila
Peca jogarPeca(Fila *f) {
    Peca vazio = {'X', -1};
    if(filaVazia(f)) {
        printf("Não há peças para serem jogadas! Você deve adicionar alguma antes.");
        return vazio;
    }
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return p;
}

// Insere peça na fila
void inserirPeca(Fila *f, Peca p) {
    if(filaCheia(f)) {
        printf("Número máximo de peças atingido! Você deve jogar uma peça antes.");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

// Mostra a fila
void mostrarPecas(Fila *f) {
    printf("\nFila de peças:\n");
    for(int i = 0, idx = f->inicio;
        i < f->total;
        i++, idx = (idx + 1) % MAX) {
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Verifica se fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Gera peça aleatória
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}