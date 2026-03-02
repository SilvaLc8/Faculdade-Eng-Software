struct Jogada{
int deLinha,deColuna,paraLinha,paraColuna;
struct Jogada *prox,*ant;
};

struct Jogada *CriaListaJogada(){
    struct Jogada *lista = (struct Jogada*) malloc(sizeof(struct Jogada));
    lista->prox = lista->ant = lista;
    return lista;
}

struct Jogada *CriaJogada(int deLinha,int deColuna, int paraLinha, int paraColuna){
    struct Jogada *aux = (struct Jogada*) malloc(sizeof(struct Jogada));
    aux->deLinha = deLinha;
    aux->deColuna = deColuna;
    aux->paraLinha = paraLinha;
    aux->paraColuna = paraColuna;
    aux->prox = aux->ant = NULL;
    return aux;
}

void InsereJogada(struct Jogada *lista, int deLinha, int deColuna, int paraLinha, int paraColuna){
    struct Jogada *novo = CriaJogada(deLinha, deColuna, paraLinha, paraColuna);

    novo->prox = lista->prox;
    novo->ant = lista;
    lista->prox->ant = novo;
    lista->prox = novo;
}


void DestroiJogadas(struct Jogada *lista){
    struct Jogada *aux = lista;
    lista->ant->prox = NULL;
    while (aux!=NULL){
        lista = lista->prox;
        free(aux);
        aux = lista;
    }
}