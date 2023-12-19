#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define esquerdinha \
  'l'  // → rotacionar 90º para a esquerda (sentido anti-horário).
#define direitinha 'r'  // r → rotacionar 90º para a direita (sentido horário).
#define frentinha 'w'   // → caminhar para frente. (anda uma casa)
#define corridinha 'j'  // → corridinha para frente. (anda duas casas)
#define correr 'R'      // → correr para frente. (anda três casas)
#define corridona 's'  // → correr ao máximo para frente. (anda quatro casas)
#define sensor 'c'     // → ativar sensor de paredes próximas.
#define distancia_euclides 'd'  // → ativar sensor de proximidade do objetivo.

int doAction(char c) {
  printf("%c\n", c);
  fflush(stdin);

  int ans;
  scanf("%d", &ans);
  fflush(stdout);

  return ans;
}

typedef struct {
  int p;
  int s;
} pair;

typedef pair Item;

typedef struct {

  bool paredes[4];  // paredes[0] - cima | paredes[1] - esquerda | paredes[2] -
                    // baixo | parede[3] - direita
  int dir;

  bool visitado;

  pair pai;

} mapa;

#define MAX_ROW 300
#define MAX_COL 300

pair directions[] = {
    (pair){-1, 0},  // pra cima
    (pair){0, 1},   // pra esquerda
    (pair){1, 0},   // pra baixo
    (pair){0, -1},  // pra direita
};

pair locomover(mapa grid[][MAX_COL], pair originCell, int direcaoRato) {
  int x = originCell.p, y = originCell.s;
  pair destinyCell;

  destinyCell.p = x + directions[direcaoRato].p;
  destinyCell.s = y + directions[direcaoRato].s;

  grid[destinyCell.p][destinyCell.s].pai = originCell;
  grid[destinyCell.p][destinyCell.s].visitado = true;
  grid[destinyCell.p][destinyCell.s].dir = direcaoRato;

  return destinyCell;
}

void setWall(mapa grid[][MAX_COL], pair coord, int direction) {
  int x = coord.p, y = coord.s;
  grid[x][y].paredes[direction] = true;
}

//////////////////////////////////////////////////////// Queue
////////////////////////////////////////////////////////////////////////////////////////////

typedef struct registro node;

struct registro {
  pair info;
  node *prox;
};

// tipo head
typedef struct cabeca head;

struct cabeca {
  int num_itens;
  node *prox;
  node *ultimo;
};

head *criar_lista();
node *criar_no(pair);

int queueVazia(head *);
int queueTamanho(head *);

node *queuePrimeiro(head *);
node *queueUltimo(head *);

void enfileira(head *, pair);  // insere_fim
pair desenfileira(head *);     // remove_inicio .. busca_inicio .. remove_no

head *criar_queue() {
  head *le = malloc(sizeof(head));
  le->num_itens = 0;
  le->prox = NULL;
  le->ultimo = NULL;
  return le;
}

node *criar_no(pair x) {
  node *no = malloc(sizeof(node));
  no->prox = NULL;
  no->info = x;
  return no;
}

int queueVazia(head *p) { return (p->prox == NULL); }

int queueTamanho(head *lista) { return lista->num_itens; }

node *queuePrimeiro(head *lista) { return lista->prox; }

node *queueUltimo(head *lista) { return lista->ultimo; }

void enfileira(head *lista, pair x) {
  node *novo = criar_no(x);
  if (novo) {
    novo->prox = NULL;

    // cabeca != node
    if (!queueVazia(lista))
      lista->ultimo->prox = novo;
    else
      lista->prox = novo;

    lista->ultimo = novo;
    lista->num_itens++;
  }
}

pair desenfileira(head *lista) {
  node *lixo = queuePrimeiro(lista);
  lista->prox = lista->prox->prox;

  // cabeca != node
  if (lixo == lista->ultimo) lista->ultimo = NULL;
  lista->num_itens--;

  pair x = lixo->info;
  free(lixo);
  return x;
}

//////////////////////////////////////////////////////// Stack
////////////////////////////////////////////////////////////////////////////////////////////

int stackVazia(head *);
int stackTamanho(head *);

node *stackPrimeiro(head *);
node *stackUltimo(head *);

pair stackEspia(head *);

void empilha(head *, pair);  // insere_inicio
pair desempilha(head *);     // remove_inicio

head *criar_stack() {
  head *le = malloc(sizeof(head));
  le->num_itens = 0;
  le->prox = NULL;
  le->ultimo = NULL;
  return le;
}

int stackVazia(head *p) { return (p->prox == NULL); }

int stackTamanho(head *lista) { return lista->num_itens; }

node *stackTopo(head *lista) { return lista->prox; }

node *stackUltimo(head *lista) { return lista->ultimo; }

pair stackEspia(head *p) { return (p->prox->info); }

void empilha(head *lista, pair x) {
  node *novo = criar_no(x);
  if (novo) {
    if (stackVazia(lista)) lista->ultimo = novo;

    novo->prox = lista->prox;
    lista->prox = novo;

    lista->num_itens++;
  }
}

pair desempilha(head *lista) {
  node *topo = lista->prox;
  lista->prox = topo->prox;

  if (topo == lista->ultimo) lista->ultimo = NULL;
  lista->num_itens--;

  pair x = topo->info;
  free(topo);
return x;
}

#define igualPair(A,B) {A.p == B.p && A.s == B.s}

pair noPath(mapa grid[][MAX_COL], pair destinCell, head *stack) {

    doAction(esquerdinha);
    doAction(esquerdinha);
    doAction(frentinha);

    pair originCell = desempilha(stack);
    int sonDirCell = grid[originCell.p][originCell.s].dir;
    sonDirCell = dirCell + 2 % 4;


    while(originCell.p == destinCell.p && originCell.s == destinCell.s){
        originCell = desempilha(stack);
        int dirCell = grid[originCell.p][originCell.s].dir;
        dirCell = dirCell + 2 % 4;
        if(sonDirCell == dirCell)
            doAction(frentinha);
        else if(dirCell == 1)
            doAction(esquerdinha);
        else if(dirCell == 3)
            doAction(direitinha)
        else
            doAction()
}
