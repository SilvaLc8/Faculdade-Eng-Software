#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//1 - Uma fun��o IniciaTabuleiro (int tab[8][8]) que receba um tabuleiro e coloque as pe�as na posi��o inicial, de acordo com as explica��es acima.

void IniciaTabuleiro (int tab[8][8]){
  tab[0][0]=4;
  tab[0][1]=2;
  tab[0][2]=3;
  tab[0][3]=5;
  tab[0][4]=6;
  tab[0][5]=3;
  tab[0][6]=2;
  tab[0][7]=4;
  tab[1][0]=1;
  tab[1][1]=1;
  tab[1][2]=1;
  tab[1][3]=1;
  tab[1][4]=1;
  tab[1][5]=1;
  tab[1][6]=1;
  tab[1][7]=1;
  tab[2][0]=0;
  tab[2][1]=0;
  tab[2][2]=0;
  tab[2][3]=0;
  tab[2][4]=0;
  tab[2][5]=0;
  tab[2][6]=0;
  tab[2][7]=0;
  tab[3][0]=0;
  tab[3][1]=0;
  tab[3][2]=0;
  tab[3][3]=0;
  tab[3][4]=0;
  tab[3][5]=0;
  tab[3][6]=0;
  tab[3][7]=0;
  tab[4][0]=0;
  tab[4][1]=0;
  tab[4][2]=0;
  tab[4][3]=0;
  tab[4][4]=0;
  tab[4][5]=0;
  tab[4][6]=0;
  tab[4][7]=0;
  tab[5][0]=0;
  tab[5][1]=0;
  tab[5][2]=0;
  tab[5][3]=0;
  tab[5][4]=0;
  tab[5][5]=0;
  tab[5][6]=0;
  tab[5][7]=0;
  tab[6][0]=-1;
  tab[6][1]=-1;
  tab[6][2]=-1;
  tab[6][3]=-1;
  tab[6][4]=-1;
  tab[6][5]=-1;
  tab[6][6]=-1;
  tab[6][7]=-1;
  tab[7][0]=-4;
  tab[7][1]=-2;
  tab[7][2]=-3;
  tab[7][3]=-5;
  tab[7][4]=-6;
  tab[7][5]=-3;
  tab[7][6]=-2;
  tab[7][7]=-4;
}
/*2 - Uma fun��o que mostre o tabuleiro na tela, de forma �semelhante� � figura acima (mostrando os c�digos no lugar das pe�as). Pode ser utilizado o sistema de coordenadas da matriz (linhas e colunas entre 0 e 7).*/

int PrintTab (int tab[8][8]) {
	for(int lin=0;lin<8;lin++){
		for(int col=0;col<8;col++){
      printf("\t");
		  printf("%d ",tab[lin][col]);
		}
    printf("\n");
	}
}

int moverPeca (int Tab[8][8], int linOri, int colOri, int linDes, int colDes){
  Tab[linDes][colDes] = Tab[linOri][colOri];
  Tab[linOri][colOri] = 0;
  return 0;
}

struct jogada {
  int linhaDE;
	int colunaDE;
	int linhaPARA;
	int colunaPARA;
};

int MovPeao(int Tab[8][8], int LinhaDe, int ColunaDe){
	int mov, MovL, MovC;
  printf("Possibilidade de jogadas:\n");
  if(Tab[LinhaDe][ColunaDe]==1){//1
    printf("[%d][%d] ?\n",LinhaDe+1,ColunaDe);
    if(LinhaDe==1){
      printf("[%d][%d] ?\n",LinhaDe+2,ColunaDe);
	  }
    if(Tab[LinhaDe+1][ColunaDe+1]!=0 && ColunaDe<7){
      printf("[%d][%d] ?\n",LinhaDe+1,ColunaDe+1);
    }
    if(Tab[LinhaDe+1][ColunaDe-1]!=0 && ColunaDe>0){
      printf("[%d][%d] ?\n",LinhaDe+1,ColunaDe-1);
    }
  }
  else{//-1
    printf("[%d][%d] ?\n",LinhaDe-1,ColunaDe);
    if(LinhaDe==6){
      printf("[%d][%d] ?\n",LinhaDe-2,ColunaDe);
	  }
    if(Tab[LinhaDe-1][ColunaDe+1]!=0 && ColunaDe<7){
      printf("[%d][%d] ?\n",LinhaDe-1,ColunaDe+1);
    }
    if(Tab[LinhaDe-1][ColunaDe-1]!=0 && ColunaDe>0){
      printf("[%d][%d] ?\n",LinhaDe-1,ColunaDe-1);
    }
  }
  scanf("%d %d",&MovL, &MovC);
  moverPeca(Tab, LinhaDe, ColunaDe, MovL, MovC);
  return 0;
}


int MovTorre(int Tab[8][8], int LinhaDe, int ColunaDe){
	int mov,i=0;
	  if(LinhaDe==0){
      printf("Possibilidade de jogadas:\n");
      while(Tab[LinhaDe+1][ColunaDe]!=0 || Tab[LinhaDe][ColunaDe+1]!=0){
          printf("[%d][%d]\n",LinhaDe+i, ColunaDe+i);
          i++;
      }
      scanf("%d",&mov);
   		moverPeca(Tab, LinhaDe, ColunaDe, mov, ColunaDe);
	  }
    /*
    if(LinhaDe==7){
      while(Tab[LinhaDe+1][ColunaDe+1]!=0 || Tab[LinhaDe+1][ColunaDe-1]!=0)
	  	printf("Deseja mover para a linha 2 ou para a linha 3?\n"); //mudar aqui
		  scanf("%d",&mov);
   		moverPeca(Tab, LinhaDe, ColunaDe, mov, ColunaDe);
	  }*/
}
/*
int MovCavalo(int Tab[8][8], int LinhaDe, int ColunaDe){
	int mov;
	  if(LinhaDe==1){
      /////vetor struct jogada
	  	printf("Deseja mover para a linha 2 ou para a linha 3?\n"); //mudar aqui
		  scanf("%d",&mov);
   		moverPeca(Tab, LinhaDe, ColunaDe, mov, ColunaDe);
	  }
}

int MovBispo(int Tab[8][8], int LinhaDe, int ColunaDe){
	int mov;
	  if(LinhaDe==1){
      /////vetor struct jogada
	  	printf("Deseja mover para a linha 2 ou para a linha 3?\n"); //mudar aqui
		  scanf("%d",&mov);
   		moverPeca(Tab, LinhaDe, ColunaDe, mov, ColunaDe);
	  }
}

int MovRainha(int Tab[8][8], int LinhaDe, int ColunaDe){
	int mov;
	  if(LinhaDe==1){
      /////vetor struct jogada
	  	printf("Deseja mover para a linha 2 ou para a linha 3?\n"); //mudar aqui
		  scanf("%d",&mov);
   		moverPeca(Tab, LinhaDe, ColunaDe, mov, ColunaDe);
	  }
}

int MovRei(int Tab[8][8], int LinhaDe, int ColunaDe){
	int mov;
	  if(LinhaDe==1){
      /////vetor struct jogada
	  	printf("Deseja mover para a linha 2 ou para a linha 3?\n"); //mudar aqui
		  scanf("%d",&mov);
   		moverPeca(Tab, LinhaDe, ColunaDe, mov, ColunaDe);
	  }
}
*/
int main() {
	setlocale(LC_ALL,"");

	int Tab[8][8];
  struct jogada movimento;
  int Movimento;
  IniciaTabuleiro(Tab);

  while(1){
    PrintTab(Tab);
  //3.1- Pergunta ao usuario qual pe�a ele deseja mover por meio da linha e da coluna em que a pe�a est� localizada.
    printf("Qual pe�a deseja mover: (ex: linha 1, coluna 3)");
    scanf("%d %d", &movimento.linhaDE, &movimento.colunaDE);

  //3.2- Analisa se a posi��o possui alguma pe�a ou se existe. Caso aconte�a, pede ao usu�rio que informe uma nova pe�a.
    // pe�o:
    if (Tab[movimento.linhaDE][movimento.colunaDE] == 1 || Tab[movimento.linhaDE][movimento.colunaDE] == -1) {
    MovPeao(Tab, movimento.linhaDE,movimento.colunaDE);
  }

	  // torre:
    if (Tab[movimento.linhaDE][movimento.colunaDE] == 4 || Tab[movimento.linhaDE][movimento.colunaDE] == -4) {
    MovTorre(Tab, movimento.linhaDE,movimento.colunaDE);
  }
/*
	  // cavalo:
    if (Tab[movimento.linhaDE][movimento.colunaDE] == 2 || Tab[movimento.linhaDE][movimento.colunaDE] == -2){
    MovCavalo(Tab, movimento.linhaDE,movimento.colunaDE);
  }

	  // bispo:
    if (Tab[movimento.linhaDE][movimento.colunaDE] == 3 || Tab[movimento.linhaDE][movimento.colunaDE] == -3){
    MovBispo(Tab, movimento.linhaDE,movimento.colunaDE);
  }

	  // rainha:
    if (Tab[movimento.linhaDE][movimento.colunaDE] == 5 || Tab[movimento.linhaDE][movimento.colunaDE] == -5){
    MovRainha(Tab, movimento.linhaDE,movimento.colunaDE);
  }

	  // rei:
    if (Tab[movimento.linhaDE][movimento.colunaDE] == 6 || Tab[movimento.linhaDE][movimento.colunaDE] == -6) {
    MovRei(Tab, movimento.linhaDE,movimento.colunaDE);
  }
*/
	/* O programa deve permitir a captura de pe�as, retirando a pe�a capturada da posi��o em que estava e colocando ali a pe�a que fez a captura. O programa encerra quando um rei for capturado e deve informar quem foi o jogador vencedor. A captura s� pode ser feita por uma pe�a do jogador advers�rio, nunca por outra pe�a do mesmo jogador.*/

  }
  return 0;
}