#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
        int valor;
    int prioridade;
    struct Node* proximo;
} Node;

typedef struct {

    Node* frente;
} FilaPrioridade;

FilaPrioridade* criarFilaPrioridade() {
            FilaPrioridade* fila = (FilaPrioridade*)malloc(sizeof(FilaPrioridade));
    if (!fila) {
            perror("Erro ao alocar memória para a fila de prioridades");
        exit(EXIT_FAILURE);
    }
    fila->frente = NULL;
    return fila;
}

void enfileirar(FilaPrioridade* fila, int valor, int prioridade) {

        Node* novoNo = (Node*)malloc(sizeof(Node));
    if (!novoNo) {
        perror("Erro ao alocar memória para o nó");
        exit(EXIT_FAILURE);
    }
    novoNo->valor = valor;
    novoNo->prioridade = prioridade;
        novoNo->proximo = NULL;

    if (fila->frente == NULL || prioridade > fila->frente->prioridade) {
        novoNo->proximo = fila->frente;

        fila->frente = novoNo;

    } else {
        Node* atual = fila->frente;
        while (atual->proximo != NULL && prioridade <= atual->proximo->prioridade) {
            atual = atual->proximo;
        }
        novoNo->proximo = atual->proximo;
        atual->proximo = novoNo;
    }
}

int desenfileirar(FilaPrioridade* fila) {
    if (fila->frente == NULL) {
        printf("Erro: A fila de prioridades está vazia.\n");
        exit(EXIT_FAILURE);
    }

    Node* temp = fila->frente;
    int valor = temp->valor;
    fila->frente = fila->frente->proximo;

    free(temp);
    return valor;
}

int estaVazia(FilaPrioridade* fila) {
    return fila->frente == NULL;
}

void destruirFilaPrioridade(FilaPrioridade* fila) {
        while (!estaVazia(fila)) {
            desenfileirar(fila);
    }
    free(fila);
}


int main() {
        FilaPrioridade* filaPrioridade = criarFilaPrioridade();

    enfileirar(filaPrioridade, 12, 2);
    enfileirar(filaPrioridade, 24, 1);
    enfileirar(filaPrioridade, 30, 3);
    enfileirar(filaPrioridade, 190, 4);
    enfileirar(filaPrioridade, 380, 5);

    while (!estaVazia(filaPrioridade)) {
        printf("%d ", desenfileirar(filaPrioridade));
    }

    destruirFilaPrioridade(filaPrioridade);



    return 0;

}
