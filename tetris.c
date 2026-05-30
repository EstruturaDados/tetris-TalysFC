// Código nível aventureiro

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5
#define maximo 3

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

// Struct da pilha
typedef struct {
    Peca itens[maximo];
    int topo;
} Pilha;

// Protótipos
void exibirMenu();

Peca jogarPeca(Fila *f);
void inserirPeca(Fila *f, Peca p);
void mostrarPecas(Fila *f);

void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
Peca gerarPeca(int id);

void inicializarPilha(Pilha *pi);
int pilhaCheia(Pilha *pi);
int pilhaVazia(Pilha *pi);
void inserirPilha(Pilha *pi, Fila *f);
void removerPilha(Pilha *pi);
void mostrarPilha(Pilha *pi);


int main() {
    srand((unsigned int)time(NULL));
    Fila f;
    Pilha pi;
    int proximoId = 0;
    inicializarFila(&f);
    inicializarPilha(&pi);
    // Preenche a fila inicial com 5 peças
    for(int i = 0; i < MAX; i++) {
        inserirPeca(&f, gerarPeca(proximoId));
        proximoId++;
    }
    printf("\n-- Bem vindo ao jogo Tetris Stack! --\n");
    do {
        mostrarPecas(&f);
        mostrarPilha(&pi);
        exibirMenu();
        switch(opcao) {
            case 1: {
                Peca removida = jogarPeca(&f);
                if(removida.id != -1){
                    printf("Peça jogada: [%c %d]\n", removida.nome, removida.id);
                    inserirPeca(&f, gerarPeca(proximoId));
                    proximoId++;
                }
                break;
            }
            case 2: {
                if(!pilhaCheia(&pi)) {
                    inserirPilha(&pi, &f);
                    inserirPeca(&f, gerarPeca(proximoId));
                    proximoId++;
                }
                break;
            }
            case 3: {
                removerPilha(&pi);
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
    printf("2 - Reservar peça\n");
    printf("3 - Jogar peça reservada\n");
    printf("0 - Sair\n");
    printf("Digite sua escolha: ");
    scanf("%d", &opcao);
}

// Remove peça da fila
Peca jogarPeca(Fila *f) {
    Peca vazio = {'X', -1};
    if(filaVazia(f)) {
        printf("Não há peças para serem jogadas! Você deve adicionar alguma antes. \n");
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
        printf("Número máximo de peças atingido! Você deve jogar uma peça antes. \n");
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

// Inicializa a pilha
void inicializarPilha(Pilha *pi){
    pi->topo = -1;
}

// Verifica se a pilha está cheia
int pilhaCheia(Pilha *pi){
    return pi->topo == maximo - 1;
}

// Verifica se a pilha está vazia
int pilhaVazia(Pilha *pi){
    return pi->topo == -1;
}

// Reserva peça da fila na pilha
void inserirPilha(Pilha *pi, Fila *f){
    if(pilhaCheia(pi)){
        printf("Pilha cheia! Retire uma peça. \n");
        return;
    }
    Peca p = jogarPeca(f);
    printf("Peça reservada: [%c %d]\n", p.nome, p.id);
    pi->topo++;
    pi->itens[pi->topo] = p;
}

// Remove a peça da pilha
void removerPilha(Pilha *pi){
    if(pilhaVazia(pi)){
        printf("Pilha vazia! Reserve uma peça antes. \n");
        return;
    }
    Peca p = pi->itens[pi->topo];
    pi->topo--;
    printf("Peça usada: [%c %d]\n", p.nome, p.id);
}

//Mostra todas as peças da pilha
void mostrarPilha(Pilha *pi){
    if(pilhaVazia(pi)){
        printf("Pilha vazia! Não há peças reservadas para mostrar. \n");
        return;
    }
    printf("Topo -> Base \n");
    for (int i = pi->topo; i >= 0; i--){
        printf("[%c %d] ", pi->itens[i].nome, pi->itens[i].id);
    }
}