struct Peca{
int codigo;
int linha,coluna;
int ataques;
struct Peca *prox,*ant;
};

struct Peca *CriaListaPeca(){
    struct Peca *lista = (struct Peca*) malloc(sizeof(struct Peca));
    lista->prox = lista->ant = lista;
    return lista;
}

struct Peca *CriaPeca(int codigo,int linha, int coluna){
    struct Peca *aux = (struct Peca*) malloc(sizeof(struct Peca));
    aux->codigo = codigo;
    aux->linha = linha;
    aux->coluna = coluna;
    aux->ataques = 0;
    aux->prox = aux->ant = NULL;
    return aux;
}

struct Peca *InserePeca(struct Peca *lista, int codigo, int linha, int coluna){
    struct Peca *novo = CriaPeca(codigo,linha,coluna);

    novo->prox = lista->prox;
    novo->ant = lista;
    lista->prox->ant = novo;
    lista->prox = novo;

    return novo;
}

void RemovePeca(struct Peca *ponteiro){
    ponteiro->prox->ant = ponteiro->ant;
    ponteiro->ant->prox = ponteiro->prox;
    free(ponteiro);
}

void DestroiPecas(struct Peca *lista){
    struct Peca *aux = lista;
    lista->ant->prox = NULL;
    while (aux!=NULL){
        lista = lista->prox;
        free(aux);
        aux = lista;
    }
}

void ZeraAtaques(struct Peca *lista){
    struct Peca *aux = lista->prox;
    while (aux!=lista){
        aux->ataques = 0;
        aux = aux->prox;
    }
}