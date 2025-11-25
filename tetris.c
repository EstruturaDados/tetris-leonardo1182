#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// Estrutura da peça
typedef struct {
    char tipo[5]; // Ex: "I", "O", "T", "L", "J"
    int id;       // Identificador numérico único
} Peca;

// ----------- FILA CIRCULAR -----------
typedef struct {
    Peca itens[MAX_FILA];
    int inicio, fim, quantidade;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// Inserir no final da fila
int inserirFila(Fila *f, Peca p) {
    if (f->quantidade == MAX_FILA)
        return 0; // Fila cheia

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->quantidade++;
    return 1;
}

// Remover da frente da fila
int removerFila(Fila *f, Peca *p) {
    if (f->quantidade == 0)
        return 0; // Fila vazia

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->quantidade--;
    return 1;
}

// ----------- PILHA -----------
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int push(Pilha *p, Peca x) {
    if (p->topo == MAX_PILHA - 1)
        return 0; // Pilha cheia

    p->itens[++p->topo] = x;
    return 1;
}

int pop(Pilha *p, Peca *x) {
    if (p->topo == -1)
        return 0; // Pilha vazia

    *x = p->itens[p->topo--];
    return 1;
}

//função gerar peças automaticamente
Peca GerarPeca(){
    Peca nova;
    char tipos[][5] = {"I", "O", "T", "L", "J"};
    int totalTipos = 5;

    //escolhe tipo aleatorio
    int t = rand() % totalTipos;
    strcpy(nova.tipo, tipos[t]);

    //gera id aletorio
    nova.id = rand() % 90 + 10;

    return nova;
}


// Jogar peça = remover da fila
void jogarPeca(Fila *fila, Pilha *pilha) {
    Peca p;
    if (removerFila(fila, &p)){
        printf("\nPeça jogada: %s (ID %d)\n", p.tipo, p.id);
        //gera nova peça automaticamente
        Peca nova = GerarPeca();
        inserirFila(fila, nova);
    }else{
        printf("\nA fila está vazia!\n");}

        printf("\n------ Estado Atual ------");


   
    printf("\nFila de peças (%d itens):\n", fila->quantidade);
    int idx = fila->inicio;
    for (int i = 0; i < fila->quantidade; i++) {
        printf("[%s | ID %d] ", fila->itens[i].tipo, fila->itens[i].id);
        idx = (idx + 1) % MAX_FILA;
    }

    printf("\n\nPilha de reserva (%d itens):\n", pilha->topo + 1);
    for (int i = pilha->topo; i >= 0; i--) {
        printf("[%s | ID %d]\n", pilha->itens[i].tipo, pilha->itens[i].id);
    }
    
    printf("---------------------------\n");

}

// Reservar peça = tirar da fila e colocar na pilha
void reservarPeca(Fila *fila, Pilha *pilha) {
    Peca p;
    if (!removerFila(fila, &p)) {
        printf("\nNão há peças na fila para reservar.\n");
        return;
    }

    if (!push(pilha, p)) {
        printf("\nA pilha de reserva está cheia! Não foi possível reservar.\n");
        inserirFila(fila, p); // devolve peça à fila
        return;
    }

    printf("\nPeça %s (ID %d) reservada.\n", p.tipo, p.id);

    //gera nova peça automaticamente
    Peca nova = GerarPeca();
    inserirFila(fila, nova);
    printf("Nova peça gerada a inserida: %s (ID %d)\n", nova.tipo, nova.id);
}

// Usar peça reservada = pop da pilha
void usarReservada(Pilha *pilha) {
    Peca p;
    if (pop(pilha, &p))
        printf("\nPeça reservada usada: %s (ID %d)\n", p.tipo, p.id);
    else
        printf("\nNenhuma peça reservada para usar.\n");
}

// Exibir estado atual
void exibirEstado(Fila *fila, Pilha *pilha) {
    printf("\n------ Estado Atual ------");

    printf("\nFila de peças (%d itens):\n", fila->quantidade);
    int idx = fila->inicio;
    for (int i = 0; i < fila->quantidade; i++) {
        printf("[%s | ID %d] ", fila->itens[idx].tipo, fila->itens[idx].id);
        idx = (idx + 1) % MAX_FILA;
    }

    printf("\n\nPilha de reserva (%d itens):\n", pilha->topo + 1);
    for (int i = pilha->topo; i >= 0; i--) {
        printf("[%s | ID %d]\n", pilha->itens[i].tipo, pilha->itens[i].id);
    }

    printf("---------------------------\n");
}

// ----------- MAIN -----------

int main() {
    srand(time(NULL));


    Fila fila;//instaciando fila
    Pilha pilha;//instaciando pilha

    //iniciciando pilha e fila
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Inicializa fila com 5 peças
    GerarPeca();

    for (int i = 0; i < 5; i++)
        inserirFila(&fila, GerarPeca());

    exibirEstado(&fila, &pilha);

    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Exibir estado atual\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: jogarPeca(&fila, &pilha); break;
            case 2: reservarPeca(&fila, &pilha); break;
            case 3: usarReservada(&pilha); break;
            case 4: exibirEstado(&fila, &pilha); break;
            case 0: printf("\nEncerrando...\n"); break;
            default: printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
