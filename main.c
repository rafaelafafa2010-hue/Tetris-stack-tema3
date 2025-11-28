#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct {
    char nome[20];
} Peca;

typedef struct {
    int inicio;
    int fim;
    int qtd;
    Peca itens[MAX];
} Fila;

typedef struct {
    int topo;
    Peca itens[MAX];
} Pilha;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

int filaVazia(Fila *f) {
    return f->qtd == 0;
}

int filaCheia(Fila *f) {
    return f->qtd == MAX;
}

void enfileirar(Fila *f, Peca peca) {
    if (filaCheia(f)) {
        printf("Fila cheia! Nao e possivel adicionar peca futura.\n");
        return;
    }
    f->itens[f->fim] = peca;
    f->fim = (f->fim + 1) % MAX;
    f->qtd++;
}

Peca desenfileirar(Fila *f) {
    Peca p = {"NULA"};
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return p;
    }
    p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->qtd--;
    return p;
}

void mostrarFila(Fila *f) {
    printf("\n--- Pecas Futuras (FILA) ---\n");
    if (filaVazia(f)) {
        printf("Vazia.\n");
        return;
    }
    int i = f->inicio;
    for (int count = 0; count < f->qtd; count++) {
        printf("%s ", f->itens[i].nome);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

void push(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Nao e possivel reservar mais pecas.\n");
        return;
    }
    p->itens[++p->topo] = peca;
}

Peca pop(Pilha *p) {
    Peca peca = {"NULA"};
    if (pilhaVazia(p)) {
        printf("Pilha vazia!\n");
        return peca;
    }
    return p->itens[p->topo--];
}

void mostrarPilha(Pilha *p) {
    printf("\n--- Pecas Reservadas (PILHA) ---\n");
    if (pilhaVazia(p)) {
        printf("Vazia.\n");
        return;
    }
    for (int i = p->topo; i >= 0; i--) {
        printf("%s ", p->itens[i].nome);
    }
    printf("\n");
}

int main() {
    Fila futuras;
    Pilha reserva;

    inicializarFila(&futuras);
    inicializarPilha(&reserva);

    int opc;
    Peca peca;
    Peca retirada;

    do {
        printf("\n====== TETRIS STACK ======\n");
        printf("1 - Adicionar peca na FILA (futuras)\n");
        printf("2 - Pegar proxima peca (remover FILA)\n");
        printf("3 - Reservar peca (colocar na PILHA)\n");
        printf("4 - Recuperar peca reservada (remover PILHA)\n");
        printf("5 - Mostrar FILA\n");
        printf("6 - Mostrar PILHA\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1:
                printf("Nome da peca: ");
                fgets(peca.nome, 20, stdin);
                peca.nome[strcspn(peca.nome, "\n")] = 0;
                enfileirar(&futuras, peca);
                break;

            case 2:
                retirada = desenfileirar(&futuras);
                printf("Peca retirada: %s\n", retirada.nome);
                break;

            case 3:
                printf("Nome da peca a reservar: ");
                fgets(peca.nome, 20, stdin);
                peca.nome[strcspn(peca.nome, "\n")] = 0;
                push(&reserva, peca);
                break;

            case 4:
                retirada = pop(&reserva);
                printf("Peca recuperada: %s\n", retirada.nome);
                break;

            case 5:
                mostrarFila(&futuras);
                break;

            case 6:
                mostrarPilha(&reserva);
                break;

            case 0:
                printf("Sistema encerrado.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opc != 0);

    return 0;
}
