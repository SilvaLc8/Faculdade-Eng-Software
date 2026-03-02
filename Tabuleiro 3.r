#include "stdio.h"
#include "stdlib.h"
#include "ListaPecas.h"
#include "ListaJogadas.h"

#define PEAO    1
#define CAVALO  2
#define BISPO   3
#define TORRE   4
#define RAINHA  5
#define REI     6


typedef struct Posicao{
    int qtdBrancas;
    struct Peca *brancas;
    int qtdPretas;
    struct Peca *pretas;
    int jogVez;
    struct Peca *tab[8][8];
}Posicao;

void ResetCor(){
    printf("\033[0m");
}

void AjustaCor(int peca){
    switch(abs(peca)){
    case PEAO: printf("\033[0;36m");break;
    case CAVALO: printf("\033[1;33m");break;
    case BISPO: printf("\033[0;35m");break;
    case TORRE: printf("\033[0;32m");break;
    case RAINHA: printf("\033[0;34m");break;
    case REI: printf("\033[1;31m");break;
    }
}

void DesenhaTabuleiro(Posicao pos){
    int i,j;
    system("clear");

    printf("    +---+---+---+---+---+---+---+---+\n");
    for (i=7;i>=0;i--){
        printf("%d   |",i+1);
        for (j=0;j<8;j++){
            if (pos.tab[i][j]){ //se tem peça nessa casa
                AjustaCor(pos.tab[i][j]->codigo);
                if (pos.tab[i][j]->codigo>0)
                    printf(" %d",pos.tab[i][j]->codigo);
                else printf("%d",pos.tab[i][j]->codigo);
                ResetCor();
            }else printf("  ");//se não tem peça, deixa em vazio o printf
            printf(" |");
        }
        printf("\n    +---+---+---+---+---+---+---+---+\n");
    }
    printf("      1   2   3   4   5   6   7   8 \n");
}

void CalculaPeao(Posicao pos,int linha,int coluna,struct Jogada *lista){
    int peca = pos.tab[linha][coluna]->codigo;

    if (linha+peca>=0 && linha+peca<=7){//não está na primeira nem na última linha
    if((linha==1 && peca==1) || (linha==6 && peca==-1)){
      if (pos.tab[linha+2*peca][coluna]==NULL){
        InsereJogada(lista,linha,coluna,linha+2*peca,coluna);
        }
    }
        if (pos.tab[linha+peca][coluna]==NULL){ //pode avancar
            InsereJogada(lista,linha,coluna,linha+peca,coluna);
        }
        if (coluna>0 && pos.tab[linha+peca][coluna-1]!=NULL && pos.tab[linha+peca][coluna-1]->codigo*peca<0){ //verificar captura na esquerda
            InsereJogada(lista,linha,coluna,linha+peca,coluna-1);
            pos.tab[linha+peca][coluna-1]->ataques++;
        }
        if (coluna<7 && pos.tab[linha+peca][coluna+1]!=NULL && pos.tab[linha+peca][coluna+1]->codigo*peca<0){
            InsereJogada(lista,linha,coluna,linha+peca,coluna+1);
            pos.tab[linha+peca][coluna+1]->ataques++;
        }
    }
}

void CalculaCavalo(Posicao pos, int linha, int coluna, struct Jogada *lista){
    int peca = pos.tab[linha][coluna]->codigo;

    if (linha<6){ //duas linhas acima
        if (coluna<7 && (pos.tab[linha+2][coluna+1]==NULL || pos.tab[linha+2][coluna+1]->codigo*peca<0)){ //direita
            InsereJogada(lista,linha,coluna,linha+2,coluna+1);
            if (pos.tab[linha+2][coluna+1]!=NULL)
                pos.tab[linha+2][coluna+1]->ataques++;
        }
        if (coluna>0 && (pos.tab[linha+2][coluna-1]==NULL || pos.tab[linha+2][coluna-1]->codigo*peca<0)){ //esquerda
            InsereJogada(lista,linha,coluna,linha+2,coluna-1);
            if (pos.tab[linha+2][coluna-1]!=NULL)
                pos.tab[linha+2][coluna-1]->ataques++;
        }
    }
    if (linha<7){//uma linha acima
        if (coluna<6 && (pos.tab[linha+1][coluna+2]==NULL || pos.tab[linha+1][coluna+2]->codigo*peca<0)){ //duas casas à direita
            InsereJogada(lista,linha,coluna,linha+2,coluna-1);
            if (pos.tab[linha+1][coluna+2]!=NULL)
                pos.tab[linha+1][coluna+2]->ataques++;
        }
        if (coluna>1 && (pos.tab[linha+1][coluna-2]==NULL || pos.tab[linha+1][coluna-2]->codigo*peca<0)){ //duas casas à esquerda
            InsereJogada(lista,linha,coluna,linha+1,coluna-2);
            if (pos.tab[linha+1][coluna-2]!=NULL)
                pos.tab[linha+1][coluna-2]->ataques++;
        }
    }
    if (linha>1){ //duas linhas abaixo
        if (coluna<7 && (pos.tab[linha-2][coluna+1]==NULL || pos.tab[linha-2][coluna+1]->codigo*peca<0)){ //direita
            InsereJogada(lista,linha,coluna,linha-2,coluna+1);
            if (pos.tab[linha-2][coluna+1]!=NULL)
                pos.tab[linha-2][coluna+1]->ataques++;
        }
        if (coluna>0 && (pos.tab[linha-2][coluna-1]==NULL || pos.tab[linha-2][coluna-1]->codigo*peca<0)){ //esquerda
            InsereJogada(lista,linha,coluna,linha-2,coluna-1);
            if (pos.tab[linha-2][coluna-1]!=NULL)
                pos.tab[linha-2][coluna-1]->ataques++;
        }
    }
    if (linha>0){//uma linha abaixo
        if (coluna<6 && (pos.tab[linha-1][coluna+2]==NULL || pos.tab[linha-1][coluna+2]->codigo*peca<0)){ //duas casas à direita
            InsereJogada(lista,linha,coluna,linha-1,coluna+2);
            if (pos.tab[linha-1][coluna+2]!=NULL)
                pos.tab[linha-1][coluna+2]->ataques++;
        }
        if (coluna>1 && (pos.tab[linha-1][coluna-2]==NULL || pos.tab[linha-1][coluna-2]->codigo*peca<0)){ //duas casas à esquerd
            InsereJogada(lista,linha,coluna,linha-1,coluna-2);
            if (pos.tab[linha-1][coluna-2]!=NULL)
                pos.tab[linha-1][coluna-2]->ataques++;
        }
    }
}

void CalculaBispo(Posicao pos, int linha, int coluna, struct Jogada *lista){
    int peca = pos.tab[linha][coluna]->codigo;

    int k=0;

    do{//diagonal superior direita
        k++;
        if (linha+k<8 && coluna+k<8 && (pos.tab[linha+k][coluna+k]==NULL||pos.tab[linha+k][coluna+k]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha+k,coluna+k);
            if (pos.tab[linha+k][coluna+k]!=NULL)
                pos.tab[linha+k][coluna+k]->ataques++;
        }
    }while (linha+k<8 && coluna+k<8 && pos.tab[linha+k][coluna+k]==NULL);

    k=0;
    do{//diagonal superior esquerda
        k++;
        if (linha+k<8 && coluna-k>=0 && (pos.tab[linha+k][coluna-k]==NULL||pos.tab[linha+k][coluna-k]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha+k,coluna-k);
            if (pos.tab[linha+k][coluna-k]!=NULL)
                pos.tab[linha+k][coluna-k]->ataques++;
        }
    }while (linha+k<8 && coluna-k>=0 && pos.tab[linha+k][coluna-k]==NULL);

    k=0;
    do{//diagonal inferior direita
        k++;
        if (linha-k>=0 && coluna+k<8 && (pos.tab[linha-k][coluna+k]==NULL||pos.tab[linha-k][coluna+k]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha-k,coluna+k);
            if (pos.tab[linha-k][coluna+k]!=NULL)
                pos.tab[linha-k][coluna+k]->ataques++;
        }
    }while (linha-k>=0 && coluna+k<8 && pos.tab[linha-k][coluna+k]==NULL);

    k=0;
    do{//diagonal inferior direita
        k++;
        if (linha-k>=0 && coluna-k>=0 && (pos.tab[linha-k][coluna-k]==NULL||pos.tab[linha-k][coluna-k]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha-k,coluna-k);
            if (pos.tab[linha-k][coluna-k]!=NULL)
                pos.tab[linha-k][coluna-k]->ataques++;
        }
    }while (linha-k>=0 && coluna+k>=0 && pos.tab[linha-k][coluna-k]==NULL);
}

void CalculaTorre(Posicao pos, int linha, int coluna, struct Jogada *lista){
    int peca=pos.tab[linha][coluna]->codigo;

    int k=0;

    do{//coluna acima
        k++;
        if (linha+k<8 && (pos.tab[linha+k][coluna]==NULL||pos.tab[linha+k][coluna]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha+k,coluna);
            if (pos.tab[linha+k][coluna]!=NULL)
                pos.tab[linha+k][coluna]->ataques++;
        }
    }while(linha+k<8 && pos.tab[linha+k][coluna]==NULL);

    k=0;
    do{//coluna abaixo
        k++;
        if (linha-k>=0 && (pos.tab[linha-k][coluna]==NULL||pos.tab[linha-k][coluna]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha-k,coluna);
            if (pos.tab[linha-k][coluna]!=NULL)
                pos.tab[linha-k][coluna]->ataques++;
        }
    }while(linha-k>=0 && pos.tab[linha-k][coluna]==NULL);

    k=0;
    do{//linha direita
        k++;
        if (coluna+k<8 && (pos.tab[linha][coluna+k]==NULL||pos.tab[linha][coluna+k]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha,coluna+k);
            if (pos.tab[linha][coluna+k]!=NULL)
                pos.tab[linha][coluna+k]->ataques++;
        }
    }while(coluna+k<8 && pos.tab[linha][coluna+k]==NULL);

    k=0;
    do{//linha esquerda
        k++;
        if (coluna-k>=0 && (pos.tab[linha][coluna-k]==NULL||pos.tab[linha][coluna-k]->codigo*peca<0)){
            InsereJogada(lista,linha,coluna,linha,coluna-k);
            if (pos.tab[linha][coluna-k]!=NULL)
                pos.tab[linha][coluna-k]->ataques++;
        }
    }while(coluna-k>=0 && pos.tab[linha][coluna-k]==NULL);
}

void CalculaRei(Posicao pos, int linha, int coluna,struct Jogada *lista){
    int peca=pos.tab[linha][coluna]->codigo;

    if (linha<7){//linha de cima
        if (pos.tab[linha+1][coluna]==NULL||pos.tab[linha+1][coluna]->codigo*peca<0){//mesma coluna
            InsereJogada(lista,linha,coluna,linha+1,coluna);
            if (pos.tab[linha+1][coluna]!=NULL)
                pos.tab[linha+1][coluna]->ataques++;
        }
        if (coluna<7 && (pos.tab[linha+1][coluna+1]==NULL||pos.tab[linha+1][coluna+1]->codigo*peca<0)){//superior direita
            InsereJogada(lista,linha,coluna,linha+1,coluna+1);
            if (pos.tab[linha+1][coluna+1]!=NULL)
                pos.tab[linha+1][coluna+1]->ataques++;
        }
        if (coluna>0 && (pos.tab[linha+1][coluna-1]==NULL||pos.tab[linha+1][coluna-1]->codigo*peca<0)){//superior esquerda
            InsereJogada(lista,linha,coluna,linha+1,coluna-1);
            if (pos.tab[linha+1][coluna-1]!=NULL)
                pos.tab[linha+1][coluna-1]->ataques++;
        }
    }

    if (linha>0){//linha de baixo
        if (pos.tab[linha-1][coluna]==NULL||pos.tab[linha-1][coluna]->codigo*peca<0){//mesma coluna
            InsereJogada(lista,linha,coluna,linha-1,coluna);
            if (pos.tab[linha-1][coluna]!=NULL)
                pos.tab[linha-1][coluna]->ataques++;
        }
        if (coluna<7 && (pos.tab[linha-1][coluna+1]==NULL||pos.tab[linha-1][coluna+1]->codigo*peca<0)){//inferior direita
            InsereJogada(lista,linha,coluna,linha-1,coluna+1);
            if (pos.tab[linha-1][coluna+1]!=NULL)
                pos.tab[linha-1][coluna+1]->ataques++;
        }
        if (coluna>0 && (pos.tab[linha-1][coluna-1]==NULL||pos.tab[linha-1][coluna-1]->codigo*peca<0)){//inferior esquerda
            InsereJogada(lista,linha,coluna,linha-1,coluna-1);
            if (pos.tab[linha-1][coluna-1]!=NULL)
                pos.tab[linha-1][coluna-1]->ataques++;
        }
    }

    if (coluna<7 && (pos.tab[linha][coluna+1]==NULL||pos.tab[linha][coluna+1]->codigo*peca<0)){ //mesma linha, casa da direita
        InsereJogada(lista,linha,coluna,linha+1,coluna);
            if (pos.tab[linha][coluna+1]!=NULL)
                pos.tab[linha][coluna+1]->ataques++;
    }

    if (coluna>0 && (pos.tab[linha][coluna-1]==NULL||pos.tab[linha][coluna-1]->codigo*peca<0)){ //mesma linha, casa da esquerda
        InsereJogada(lista,linha,coluna,linha,coluna-1);
            if (pos.tab[linha][coluna-1]!=NULL)
                pos.tab[linha][coluna-1]->ataques++;
    }
}

//inicia o tabuleiro, colocando as peças e criando as listas
struct Posicao IniciaTabuleiro(){
    struct Posicao pos;
    pos.qtdBrancas = pos.qtdPretas = 16;
    pos.jogVez = 1;
    pos.brancas = CriaListaPeca();
    pos.pretas = CriaListaPeca();

    int i,j;
    for (i=2;i<6;i++)
        for (j=0;j<8;j++)
            pos.tab[i][j] = NULL;

    for (j=0;j<8;j++){
        pos.tab[1][j] = InserePeca(pos.brancas,PEAO,1,j);
        pos.tab[6][j] = InserePeca(pos.pretas,-PEAO,6,j);
    }

    pos.tab[0][0] = InserePeca(pos.brancas,TORRE,0,0);
    pos.tab[0][7] = InserePeca(pos.brancas,TORRE,0,7);

    pos.tab[7][0] = InserePeca(pos.pretas,-TORRE,7,0);
    pos.tab[7][7] = InserePeca(pos.pretas,-TORRE,7,7);

    pos.tab[0][1] = InserePeca(pos.brancas,CAVALO,0,1);
    pos.tab[0][6] = InserePeca(pos.brancas,CAVALO,0,6);

    pos.tab[7][1] = InserePeca(pos.pretas,-CAVALO,7,1);
    pos.tab[7][6] = InserePeca(pos.pretas,-CAVALO,7,6);

    pos.tab[0][2] = InserePeca(pos.brancas,BISPO,0,2);
    pos.tab[0][5] = InserePeca(pos.brancas,BISPO,0,5);

    pos.tab[7][2] = InserePeca(pos.pretas,-BISPO,7,2);
    pos.tab[7][5] = InserePeca(pos.pretas,-BISPO,7,5);

    pos.tab[0][3] = InserePeca(pos.brancas,RAINHA,0,3);
    pos.tab[7][3] = InserePeca(pos.pretas,-RAINHA,7,3);

    pos.tab[0][4] = InserePeca(pos.brancas,REI,0,4);
    pos.tab[7][4] = InserePeca(pos.pretas,-REI,7,4);

    return pos;
}

struct Posicao CopiaTabuleiro(){
    struct Posicao copiapos;
    copiapos.qtdBrancas = copiapos.qtdPretas = 16;
    copiapos.jogVez = 1;
    copiapos.brancas = CriaListaPeca();
    copiapos.pretas = CriaListaPeca();

    int i,j;
    for (i=2;i<6;i++)
        for (j=0;j<8;j++)
            copiapos.tab[i][j] = NULL;

    for (j=0;j<8;j++){
        copiapos.tab[1][j] = InserePeca(copiapos.brancas,PEAO,1,j);
        copiapos.tab[6][j] = InserePeca(copiapos.pretas,-PEAO,6,j);
    }

    copiapos.tab[0][0] = InserePeca(copiapos.brancas,TORRE,0,0);
    copiapos.tab[0][7] = InserePeca(copiapos.brancas,TORRE,0,7);

    copiapos.tab[7][0] = InserePeca(copiapos.pretas,-TORRE,7,0);
    copiapos.tab[7][7] = InserePeca(copiapos.pretas,-TORRE,7,7);

    copiapos.tab[0][1] = InserePeca(copiapos.brancas,CAVALO,0,1);
    copiapos.tab[0][6] = InserePeca(copiapos.brancas,CAVALO,0,6);

    copiapos.tab[7][1] = InserePeca(copiapos.pretas,-CAVALO,7,1);
    copiapos.tab[7][6] = InserePeca(copiapos.pretas,-CAVALO,7,6);

    copiapos.tab[0][2] = InserePeca(copiapos.brancas,BISPO,0,2);
    copiapos.tab[0][5] = InserePeca(copiapos.brancas,BISPO,0,5);

    copiapos.tab[7][2] = InserePeca(copiapos.pretas,-BISPO,7,2);
    copiapos.tab[7][5] = InserePeca(copiapos.pretas,-BISPO,7,5);

    copiapos.tab[0][3] = InserePeca(copiapos.brancas,RAINHA,0,3);
    copiapos.tab[7][3] = InserePeca(copiapos.pretas,-RAINHA,7,3);

    copiapos.tab[0][4] = InserePeca(copiapos.brancas,REI,0,4);
    copiapos.tab[7][4] = InserePeca(copiapos.pretas,-REI,7,4);

    return copiapos;
}

void CalculaJogadas(Posicao pos,int linha, int coluna, struct Jogada *lista){
    int peca = pos.tab[linha][coluna]->codigo;
    switch (abs(peca)){
    case PEAO:   CalculaPeao(pos,linha,coluna,lista);break;//peoes
    case CAVALO: CalculaCavalo(pos,linha,coluna,lista);break;//cavalos
    case BISPO:  CalculaBispo(pos,linha,coluna,lista);break;//bispos
    case TORRE:  CalculaTorre(pos,linha,coluna,lista);break;//torres
    case RAINHA: CalculaBispo(pos,linha,coluna,lista);
                 CalculaTorre(pos,linha,coluna,lista);break;
    case REI:    CalculaRei(pos,linha,coluna,lista);break;//rei
    }
}

struct Jogada *CalculaMovimentosPossiveis(Posicao pos){
    struct Jogada *jogadas = CriaListaJogada();
    struct Peca *aux;

    ZeraAtaques(pos.brancas);
    ZeraAtaques(pos.pretas);

    if (pos.jogVez==1){
        aux = pos.brancas->prox;
        while (aux!=pos.brancas){
            CalculaJogadas(pos,aux->linha,aux->coluna,jogadas);
            aux=aux->prox;
        }
    }else{
        aux = pos.pretas->prox;
        while (aux!=pos.pretas){
            CalculaJogadas(pos,aux->linha,aux->coluna,jogadas);
            aux=aux->prox;
        }
    }
    return jogadas;
}

struct Jogada *EscolheJogada(struct Jogada *jogadas){
    int Linha, Coluna;
    struct Jogada *jog=NULL;
    do{
        printf("Digite a linha e a coluna em que a peca sera colocada");
        scanf("%d %d",&Linha,&Coluna);
        Linha--;Coluna--;//na matriz a contagem começa com 0

        jog = jogadas->prox;
        while (jog!=jogadas&&(jog->deLinha!=deLinha||jog->deColuna!=deColuna||jog->paraLinha!=paraLinha||jog->paraColuna!=paraColuna)){
            jog = jog->prox;
        }
    }while (jog==jogadas);
    return jog;
}

int ExecutaJogada(Posicao *pos,struct Jogada jog){
    int resp=0;
    if ((pos->tab[jog.deLinha][jog.deColuna]->codigo==PEAO && jog.paraLinha==7) || (pos->tab[jog.deLinha][jog.deColuna]->codigo==-PEAO && jog.paraLinha == 0)){
		pos->tab[jog.deLinha][jog.deColuna]->codigo *= RAINHA;    	
	}
    struct Peca *peca = pos->tab[jog.deLinha][jog.deColuna];

    pos->tab[jog.deLinha][jog.deColuna] = NULL; //retira a peça do ligar

    if (pos->tab[jog.paraLinha][jog.paraColuna]!=NULL){ //a peça fará uma captura
        if (abs(pos->tab[jog.paraLinha][jog.paraColuna]->codigo)==REI) //rei capturado
            resp=1;

        RemovePeca(pos->tab[jog.paraLinha][jog.paraColuna]); //retira a peça que foi capturada da sua lista
        if (pos->jogVez==1)
            pos->qtdPretas--; //capturou peça preta
        else pos->qtdBrancas--;//capturou peça branca
    }
    pos->tab[jog.paraLinha][jog.paraColuna] = peca;
    peca->linha = jog.paraLinha;
    peca->coluna = jog.paraColuna;

    pos->jogVez = -pos->jogVez;

    return resp;
}

int main(){
    int vencedor=0;

    struct Posicao posAux = IniciaTabuleiro();
    struct Jogada *jogadasPossiveis=NULL,*jogadaEscolhida=NULL;

    while (vencedor==0){
        DesenhaTabuleiro(posAux);
        jogadasPossiveis = CalculaMovimentosPossiveis(posAux);
        jogadaEscolhida = EscolheJogada(jogadasPossiveis);
        vencedor = ExecutaJogada(&posAux,*jogadaEscolhida);
        DestroiJogadas(jogadasPossiveis);
    }
    if (posAux.jogVez==-1){ //a função ExecutaJogada já trocou o jogador da vez
        printf("Brancas venceram!");
    }else printf("Pretas venceram!");

    DestroiPecas(posAux.brancas);
    DestroiPecas(posAux.pretas);
}