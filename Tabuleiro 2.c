#include "stdio.h"
#include "stdlib.h"

// referente numero e pe�a
#define PEAO    1
#define CAVALO  2
#define BISPO   3
#define TORRE   4
#define RAINHA  5
#define REI     6

typedef struct Jogada{
    int deLinha,deColuna,paraLinha,paraColuna;
		struct Jogada *prox, *ant;
}Jogada;

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

struct Peca{
	int codigo;
	int linha, coluna;
	int ataques;
	struct Peca *prox, *ant;
};

struct Posicao{
	int qtdBrancos;
	struct Peca *brancas;
	int qtdPretas;
	struct Peca *pretas;
	int jogVez;
	struct Peca *tab[8][8];
};

struct Peca *CriaPeca(int codigo, int linha, int coluna){
  struct Peca *auxPeca = (struct Peca*) malloc (sizeof(struct Peca));
    auxPeca -> codigo = codigo;
    auxPeca -> linha  = linha;
    auxPeca -> coluna  = coluna;
	auxPeca -> ataques = 0;
	return auxPeca;
}

struct Peca *CriaLista(){
	  struct Peca*sentinela = (struct Peca*) malloc(sizeof(struct Peca));
	  sentinela->prox = sentinela;
	  sentinela->ant = sentinela;
	  return sentinela;
}

void InserePecas(struct Peca *lista, struct Peca *auxPeca){
	struct Peca* novo = auxPeca;
	novo->prox = lista->prox;
	novo->ant = lista;
	lista->prox->ant = novo;
	lista->prox = novo;
}
//roda
struct Jogada *CriaJogada (int deLinha, int deColuna, int paraLinha, int paraColuna){
	struct Jogada *sentinela = (struct Jogada*) malloc (sizeof(struct Jogada));
  sentinela -> deLinha = deLinha;
  sentinela -> deColuna = deColuna;
  sentinela -> paraLinha = paraLinha;
  sentinela -> paraColuna = paraColuna;
	sentinela -> prox = sentinela;
	sentinela -> ant = sentinela;
	return sentinela;
}

struct Jogada *CriaListaJogada(){
	struct Jogada *CriaListaJogada = (struct Jogada*) malloc (sizeof(struct Jogada));
	CriaListaJogada->prox = CriaListaJogada;
	CriaListaJogada->ant = CriaListaJogada;
	return CriaListaJogada;
}

void DesenhaTabuleiro(struct Posicao posAtual){
    int i,j;
    system("clear");

    printf("    +---+---+---+---+---+---+---+---+\n");
    for (i=7;i>=0;i--){
        printf("%d   |",i+1);
        for (j=0;j<8;j++){
            if(posAtual.tab[i][j]!=NULL){
              AjustaCor(posAtual.tab[i][j]->codigo);
              if (posAtual.tab[i][j]->codigo>=0)
                printf(" %d",posAtual.tab[i][j]->codigo);
              else printf("%d",posAtual.tab[i][j]->codigo);
            }else printf(" 0");
         ResetCor();
         printf(" |");
        }
        printf("\n    +---+---+---+---+---+---+---+---+\n");
    }
    printf("      1   2   3   4   5   6   7   8 \n");
}

int CalculaPeao(struct Posicao PosAtual,int linha,int coluna, struct Jogada *listaJogada){
    Jogada Jogada;
    int qtd = 0, peca = PosAtual.tab[linha][coluna]->codigo;

    if (linha+peca>=0 && linha+peca<=7){//n�o est� na primeira nem na �ltima linha
        if (PosAtual.tab[linha+peca][coluna]==NULL){//pode avancar
            listaJogada = CriaJogada(linha,coluna,linha+peca,coluna); qtd++;
        }
        if (coluna>0 && PosAtual.tab[linha+peca][coluna-1]->codigo*peca<0){ //verificar captura na esquerda
            listaJogada = CriaJogada(linha,coluna,linha+peca,coluna-1); qtd++;
						PosAtual.tab[linha+peca][coluna-1]->ataques+=1;
        }
        if (coluna<7 && PosAtual.tab[linha+peca][coluna+1]->codigo*peca<0){
            listaJogada = CriaJogada(linha,coluna,linha+peca,coluna+1); qtd++;
						PosAtual.tab[linha+peca][coluna+1]->ataques+=1;
        }
    }
    return qtd;
}

int CalculaCavalo(struct Posicao PosAtual, int linha, int coluna, struct Jogada *listaJogada){
	Jogada Jogada;
    int qtd=0, peca = PosAtual.tab[linha][coluna]->codigo;

    if (linha<6){ //duas linhas acima
        if (coluna<7){
          if(PosAtual.tab[linha+2][coluna+1] == NULL || PosAtual.tab[linha+2][coluna+1]->codigo*peca<=0){//direita
            listaJogada = CriaJogada(linha,coluna,linha+2,coluna+1); qtd++;
            if(PosAtual.tab[linha+2][coluna+1] != NULL)
						PosAtual.tab[linha+2][coluna+1]->ataques+=1;
          }
        }
    }
        if (coluna>0){
				 if(PosAtual.tab[linha+2][coluna-1] == NULL || PosAtual.tab[linha+2][coluna-1]->codigo*peca<=0){//esquerda
            listaJogada = CriaJogada(linha,coluna,linha+2,coluna-1); qtd++;
						if(PosAtual.tab[linha+2][coluna-1] != NULL)
						PosAtual.tab[linha+2][coluna-1]->ataques+=1;
				 	}
        }
    if (linha<7){//uma linha acima
        if (coluna<6){
					if (PosAtual.tab[linha+1][coluna+2] == NULL ||  PosAtual.tab[linha+1][coluna+2]->codigo*peca<=0){ //duas casas � direita
            listaJogada = CriaJogada(linha,coluna,linha+1,coluna+2); qtd++;
						if(PosAtual.tab[linha+1][coluna+2] != NULL)
						PosAtual.tab[linha+2][coluna+2]->ataques+=1;
					}
        }
		}
        if (coluna>1){
					 if(PosAtual.tab[linha+1][coluna-2] == NULL || PosAtual.tab[linha+1][coluna-2]->codigo*peca<=0){ //duas casas � esquerda
            listaJogada = CriaJogada(linha,coluna,linha+1,coluna-2); qtd++;
						if(PosAtual.tab[linha+1][coluna-2] != NULL)
						PosAtual.tab[linha+1][coluna-2]->ataques+=1;
					 }
        }
    if (linha>1){ //duas linhas abaixo
        if (coluna<7){
					if(PosAtual.tab[linha-2][coluna+1]== NULL || PosAtual.tab[linha-2][coluna+1]->codigo*peca<=0){ //direita
            listaJogada = CriaJogada(linha,coluna,linha-2,coluna+1); qtd++;
						if(PosAtual.tab[linha-2][coluna+1] != NULL)
						PosAtual.tab[linha-2][coluna+1]->ataques+=1;
					}
        }
    }
    if (coluna>0){
					if(PosAtual.tab[linha-2][coluna-1] == NULL || PosAtual.tab[linha-2][coluna-1]->codigo*peca<=0){ //esquerda
            listaJogada = CriaJogada(linha,coluna,linha-2,coluna-1); qtd++;
						if(PosAtual.tab[linha-2][coluna-1] != NULL)
						PosAtual.tab[linha-2][coluna-1]->ataques+=1;
					}
    }

    if (linha>0){//uma linha abaixo
        if (coluna<6){
					if (PosAtual.tab[linha-1][coluna+2] == NULL || PosAtual.tab[linha-1][coluna+2]->codigo*peca<=0){ //duas casas � direita
            listaJogada = CriaJogada(linha,coluna,linha-1,coluna+2); qtd++;
						if(PosAtual.tab[linha-1][coluna+2] != NULL)
						PosAtual.tab[linha-1][coluna+2]->ataques+=1;
					}
        }
    }
        if (coluna>1){
            if (PosAtual.tab[linha-1][coluna-2] == NULL || PosAtual.tab[linha-1][coluna-2]->codigo*peca<=0){ //duas casas � esquerda
            listaJogada = CriaJogada(linha,coluna,linha-1,coluna-2); qtd++;
            if(PosAtual.tab[linha-1][coluna+2] != NULL)
            PosAtual.tab[linha-1][coluna-2]->ataques+=1;
          }
        }
    return qtd;
}

int CalculaBispo(struct Posicao PosAtual, int linha, int coluna, struct Jogada *listaJogada){
    Jogada Jogada;
    int qtd = 0, peca = PosAtual.tab[linha][coluna]->codigo;

    int k=0;

    do{//diagonal superior direita
        k++;
        if (linha+k<8 && coluna+k<8){
					if (PosAtual.tab[linha+k][coluna+k] == NULL || PosAtual.tab[linha+k][coluna+k]->codigo*peca<0){
          listaJogada = CriaJogada (linha,coluna,linha+k,coluna+k); qtd++;
						if (PosAtual.tab[linha+k][coluna+k] != NULL)
						PosAtual.tab[linha+k][coluna+k]->ataques+=1;
					}
        }
    }while (linha+k<8 && coluna+k<8 && PosAtual.tab[linha+k][coluna+k]==0);

    k=0;
    do{//diagonal superior esquerda
        k++;
        if (linha+k<8 && coluna-k>=0){
          if (PosAtual.tab[linha+k][coluna-k] == NULL || PosAtual.tab[linha+k][coluna-k]->codigo*peca<0){
          listaJogada = CriaJogada(linha,coluna,linha+k,coluna-k); qtd++;
            if (PosAtual.tab[linha+k][coluna-k] != NULL)
						PosAtual.tab[linha+k][coluna-k]->ataques+=1;
          }
        }
    }while (linha+k<8 && coluna-k>=0 && PosAtual.tab[linha+k][coluna-k]==0);

    k=0;
    do{//diagonal inferior direita
        k++;
        if (linha-k>=0 && coluna+k<8){
          if (PosAtual.tab[linha-k][coluna+k] == NULL || PosAtual.tab[linha-k][coluna+k]->codigo*peca<0){
            listaJogada = CriaJogada(linha,coluna,linha-k,coluna+k); qtd++;
            if(PosAtual.tab[linha-k][coluna+k] != NULL)
            PosAtual.tab[linha-k][coluna+k]->ataques+=1;
        }
      }
    }while (linha-k>=0 && coluna+k<8 && PosAtual.tab[linha-k][coluna+k]==0);

    k=0;
    do{//diagonal inferior direita
        k++;
        if (linha-k>=0 && coluna-k>=0){
           if(PosAtual.tab[linha-k][coluna-k] == NULL|| PosAtual.tab[linha-k][coluna-k]->codigo*peca<0){
            listaJogada = CriaJogada(linha,coluna,linha-k,coluna-k); qtd++;
              if(PosAtual.tab[linha-k][coluna-k] != NULL)
              PosAtual.tab[linha-k][coluna-k]->ataques+=1;
        }
      }
    }while (linha-k>=0 && coluna+k>=0 && PosAtual.tab[linha-k][coluna-k]==0);
    	return qtd;

}

int CalculaTorre(struct Posicao PosAtual, int linha, int coluna, struct Jogada *listaJogada){
    Jogada Jogada;
    int qtd = 0, peca = PosAtual.tab[linha][coluna]->codigo;

    int k=0;

    do{//coluna acima
        k++;
        if (linha+k<8){
					if(PosAtual.tab[linha+k][coluna] == NULL || PosAtual.tab[linha+k][coluna]->codigo*peca<0){
            listaJogada = CriaJogada(linha,coluna,linha+k,coluna); qtd++;
						if(PosAtual.tab[linha+k][coluna] == NULL)
						PosAtual.tab[linha+k][coluna]->ataques+=1;
					}
        }
    }while(linha+k<8 && PosAtual.tab[linha+k][coluna]==0);

    k=0;
    do{//coluna abaixo
        k++;
        if (linha-k>=0){
					if(PosAtual.tab[linha-k][coluna] == NULL || PosAtual.tab[linha-k][coluna]->codigo*peca<0){
            listaJogada = CriaJogada(linha,coluna,linha-k,coluna); qtd++;
						if(PosAtual.tab[linha-k][coluna] == NULL)
						PosAtual.tab[linha-k][coluna]->ataques+=1;
					}
        }
    }while(linha-k>=0 && PosAtual.tab[linha-k][coluna]==0);

    k=0;
    do{//linha direita
        k++;
        if (coluna+k<8){
				 if(PosAtual.tab[linha][coluna+k] == NULL || PosAtual.tab[linha][coluna+k]->codigo*peca<0){
            listaJogada = CriaJogada(linha,coluna,linha,coluna+k); qtd++;
						if(PosAtual.tab[linha][coluna+k] == NULL)
						PosAtual.tab[linha][coluna+k]->ataques+=1;
				 	}
        }
    }while(coluna+k<8 && PosAtual.tab[linha][coluna+k]==0);

    k=0;
    do{//linha esquerda
        k++;
        if (coluna-k>=0){
					if(PosAtual.tab[linha][coluna-k] == NULL || PosAtual.tab[linha][coluna-k]->codigo*peca<=0){
            listaJogada = CriaJogada(linha,coluna,linha,coluna-k); qtd++;
						if(PosAtual.tab[linha][coluna-k] == NULL)
						PosAtual.tab[linha][coluna-k]->ataques+=1;
					}
        }
    }while(coluna-k>=0 && PosAtual.tab[linha][coluna-k]==0);

  return qtd;
}

int CalculaRei(struct Posicao PosAtual, int linha, int coluna,struct Jogada *listaJogada){
    int qtd = 0, peca = PosAtual.tab[linha][coluna]->codigo;
    Jogada Jogada;
    if (linha<7){//linha de cima
        if (PosAtual.tab[linha+1][coluna] == NULL || PosAtual.tab[linha+1][coluna]->codigo*peca<0){//mesma coluna
          	listaJogada = CriaJogada(linha,coluna,linha+1,coluna); qtd++;
						if (PosAtual.tab[linha+1][coluna]== NULL)
						PosAtual.tab[linha+1][coluna]->ataques+=1;
        }
    }
        if (coluna<7){
					if(PosAtual.tab[linha+1][coluna+1] == NULL || PosAtual.tab[linha+1][coluna+1]->codigo*peca<0){//superior direita
            listaJogada = CriaJogada(linha,coluna,linha+1,coluna+1); qtd++;
            if(PosAtual.tab[linha+1][coluna+1] != NULL)
            PosAtual.tab[linha+1][coluna+1]->ataques+=1;
          }
        }
        if (coluna>0){
          if(PosAtual.tab[linha+1][coluna-1] == NULL || PosAtual.tab[linha+1][coluna-1]->codigo*peca<0){//superior esquerda
            listaJogada = CriaJogada(linha,coluna,linha+1,coluna-1); qtd++;
            if(PosAtual.tab[linha+1][coluna-1] != NULL)
            PosAtual.tab[linha+1][coluna-1]->ataques+=1;
          }
        }

    if (linha>0){//linha de baixo
        if (PosAtual.tab[linha-1][coluna] == NULL || PosAtual.tab[linha-1][coluna]->codigo*peca<0){//mesma coluna
            listaJogada = CriaJogada(linha,coluna,linha-1,coluna); qtd++;
            if (PosAtual.tab[linha-1][coluna] != NULL)
            PosAtual.tab[linha-1][coluna]->ataques+=1;
        }
    }
        if (coluna<7){
				 if(PosAtual.tab[linha-1][coluna+1] == NULL || PosAtual.tab[linha-1][coluna+1]->codigo*peca<0){//inferior direita
           listaJogada = CriaJogada(linha,coluna,linha-1,coluna+1); qtd++;
           if(PosAtual.tab[linha-1][coluna+1]!=NULL)
           PosAtual.tab[linha-1][coluna+1]->ataques+=1;
          }
        }
        if (coluna>0){
          if(PosAtual.tab[linha-1][coluna-1] == NULL || PosAtual.tab[linha-1][coluna-1]->codigo*peca<0){//inferior esquerda
            listaJogada = CriaJogada(linha,coluna,linha-1,coluna-1); qtd++;
            if(PosAtual.tab[linha-1][coluna-1] != NULL)
            PosAtual.tab[linha-1][coluna-1]->ataques+=1;
          }
        }
    if (coluna<7){
     if (PosAtual.tab[linha][coluna+1] == NULL || PosAtual.tab[linha][coluna+1]->codigo*peca<0){ //mesma linha, casa da direita
        listaJogada = CriaJogada(linha,coluna,linha,coluna+1); qtd++;
        if (PosAtual.tab[linha][coluna+1] != NULL)
        PosAtual.tab[linha][coluna+1]->ataques+=1;
      }
    }

    if (coluna>0){
       if(PosAtual.tab[linha][coluna-1] == NULL || PosAtual.tab[linha][coluna-1]->codigo*peca<0){ //mesma linha, casa da esquerda
       listaJogada = CriaJogada(linha,coluna,linha,coluna-1); qtd++;
       if(PosAtual.tab[linha][coluna-1] != NULL)
       PosAtual.tab[linha][coluna-1]->ataques+=1;
      }
    }
    return qtd;
}

struct Posicao IniciaTabuleiro(){
  	struct Posicao auxPos;
    auxPos.qtdBrancos=16;
    auxPos.qtdPretas=16;
    auxPos.jogVez=1;
    struct Peca *auxPeca;
    auxPos.brancas = CriaLista();
		auxPos.pretas = CriaLista();

		for (int i=2;i<=5;i++){
			for(int j=0;j<8;j++){
				auxPos.tab[i][j] = NULL;
			}
		}
    // PEAO
		for (int i=0;i<8;i++){
				auxPeca = CriaPeca(PEAO, 1, i);
				InserePecas(auxPos.brancas, auxPeca);
				auxPos.tab[1][i] = auxPeca;

				auxPeca = CriaPeca(-PEAO, 6, i);
				InserePecas(auxPos.pretas, auxPeca);
				auxPos.tab[6][i] = auxPeca;
		}
    // TORRE
		auxPeca = CriaPeca(TORRE, 0, 0);
		InserePecas(auxPos.brancas, auxPeca);
		auxPos.tab[0][0] = auxPeca;
    auxPeca = CriaPeca(TORRE, 0, 7);
		InserePecas(auxPos.brancas, auxPeca);
		auxPos.tab[0][7] = auxPeca;

    auxPeca = CriaPeca(-TORRE, 7, 7);
		InserePecas(auxPos.pretas, auxPeca);
		auxPos.tab[7][7] = auxPeca;
    auxPeca = CriaPeca(-TORRE, 7, 0);
		InserePecas(auxPos.pretas, auxPeca);
		auxPos.tab[7][0] = auxPeca;

	//	CAVALO
    auxPeca = CriaPeca(CAVALO, 0, 1);
		InserePecas(auxPos.brancas, auxPeca);
		auxPos.tab[0][1] = auxPeca;
    auxPeca = CriaPeca(CAVALO, 0, 6);
		InserePecas(auxPos.brancas, auxPeca);
		auxPos.tab[0][6] = auxPeca;


    auxPeca = CriaPeca(-CAVALO, 7, 1);
		InserePecas(auxPos.pretas, auxPeca);
		auxPos.tab[7][1] = auxPeca;
    auxPeca = CriaPeca(-CAVALO, 7, 6);
		InserePecas(auxPos.pretas, auxPeca);
		auxPos.tab[7][6] = auxPeca;

    //BISPO
    auxPeca = CriaPeca(BISPO, 0, 2);
		InserePecas(auxPos.brancas, auxPeca);
		auxPos.tab[0][2] = auxPeca;
    auxPeca = CriaPeca(BISPO, 0, 5);
		InserePecas(auxPos.brancas, auxPeca);
		auxPos.tab[0][5] = auxPeca;

    auxPeca = CriaPeca(-BISPO, 7, 2);
		InserePecas(auxPos.pretas, auxPeca);
		auxPos.tab[7][2] = auxPeca;
    auxPeca = CriaPeca(-BISPO, 7, 5);
		InserePecas(auxPos.pretas, auxPeca);
		auxPos.tab[7][5] = auxPeca;

    //RAINHA
    auxPeca = CriaPeca(RAINHA, 0, 3);
		InserePecas(auxPos.brancas, auxPeca);
		auxPos.tab[0][3] = auxPeca;

    auxPeca = CriaPeca(-RAINHA, 7, 3);
		InserePecas(auxPos.pretas, auxPeca);
		auxPos.tab[7][3] = auxPeca;

    //REI
    auxPeca = CriaPeca(REI, 0, 4);
		InserePecas(auxPos.brancas, auxPeca);
		auxPos.tab[0][4] = auxPeca;

    auxPeca = CriaPeca(-REI, 7, 4);
		InserePecas(auxPos.pretas, auxPeca);
		auxPos.tab[7][4] = auxPeca;

    return auxPos;
}

void EscolhePeca(struct Posicao PosAtual,int *linha, int *coluna){
    do{
        printf("Digite a linha e a coluna da peca a ser movida:\n");
				printf("linha:");
        scanf("%d",linha);
				printf("coluna:");
        scanf("%d",coluna); //l� valores de 1 a 8
        (*linha)--; //converte para valores de 0 a 7
        (*coluna)--;
        if (PosAtual.tab[*linha][*coluna]==0){
            printf("Nao tem peca nessa casa!!!\n");
        }
    }while (PosAtual.tab[*linha][*coluna]==0);
}

struct Jogada *CalculaMovimentosPossiveis(struct Posicao PosAtual){
    struct Jogada *listaJogada = CriaListaJogada();
    struct Peca *auxBrancas = PosAtual.brancas;
		struct Peca *auxPretas = PosAtual.pretas;
		while(auxBrancas != PosAtual.brancas){
			auxBrancas->ataques = 0;
			auxBrancas = auxBrancas->prox;
			/* listaJogada = PosAtual.brancas -> */
		}
		while(auxPretas != PosAtual.pretas){
			auxPretas->ataques = 0;
			auxPretas = auxPretas->prox;
		}

    return listaJogada;
};

int CalculaJogadas(struct Posicao PosAtual,int linha, int coluna, struct Jogada *listaJogada){
    int aux, peca = PosAtual.tab[linha][coluna]->codigo;
    switch (abs(peca)){
    case PEAO:   return CalculaPeao(PosAtual, linha, coluna, listaJogada);break;//peoes
    case CAVALO: return CalculaCavalo(PosAtual,linha, coluna, listaJogada);break;//cavalos
    case BISPO:  return CalculaBispo(PosAtual,linha, coluna,listaJogada);break;//bispos
    case TORRE:  return CalculaTorre(PosAtual, linha, coluna,listaJogada);break;//torres
    case RAINHA: aux = CalculaBispo(PosAtual, linha, coluna,listaJogada);
                 aux += CalculaTorre(PosAtual, linha, coluna, listaJogada); //rainha
                 return aux;
                 break;
    case REI:    return CalculaRei(PosAtual, linha, coluna, listaJogada);break;//rei
    }
}

int EscolheJogada(int qtd, Jogada jogs[]){
    int i,j,op;
    do{
        for (i=0;i<qtd;i++){
            printf("Jogada %2d: mover para linha %d coluna %d |",i+1,jogs[i].paraLinha+1,jogs[i].paraColuna+1);
            if ( (i+1) % 3 == 0)
                printf("\n");
        }
        printf("\nJogada:");
        scanf("%d",&op);
    }while (op<1 || op>qtd);
    return op;
}

int ExecutaJogada(int tab[8][8],Jogada jog){
    int resp=0, peca = tab[jog.deLinha][jog.deColuna];

    tab[jog.deLinha][jog.deColuna] = 0; //tira a pe�a

    if (abs(tab[jog.paraLinha][jog.paraColuna])==REI) //verifica se o rei advers�rio ser� capturado
        resp = peca; //resp indica quem ser� vencedor

    tab[jog.paraLinha][jog.paraColuna] = peca; //coloca a pe�a na nova posi��o

    return resp;
}

void RemovePeca(struct Peca *CriaLista, int x, int y){
    struct elemento *aux = CriaLista->prox;
    while (aux!=CriaLista && (aux->x!=x || aux->y!=y)){
        aux = aux->prox;
    }
    if (aux!=CriaLista){
        aux->prox->ant = aux->ant;
        aux->ant->prox = aux->prox;
        free(aux);
    }
}//removerPeca

int main() {
   	int tab[8][8];
  	int vencedor=0,linha,coluna,escolha;
  	int qtdJogadas;
    Jogada jogadas[30];
    struct Posicao posAtual;
		posAtual = IniciaTabuleiro();

    DesenhaTabuleiro(posAtual);

    while (vencedor==0){
        DesenhaTabuleiro(posAtual);
        EscolhePeca(posAtual, &linha,&coluna);

        qtdJogadas = CalculaJogadas(posAtual,linha,coluna,jogadas);
        if (qtdJogadas>0){
            escolha = EscolheJogada(qtdJogadas,jogadas);
            vencedor = ExecutaJogada(tab,jogadas[escolha-1]);
        }else printf("Nao ha jogadas disponiveis!");
    }

		void RemovePeca(struct Peca CriaLista, x, y);

    if (vencedor>0){
        printf("Brancas venceram!");
    }else printf("Pretas venceram!");

}
