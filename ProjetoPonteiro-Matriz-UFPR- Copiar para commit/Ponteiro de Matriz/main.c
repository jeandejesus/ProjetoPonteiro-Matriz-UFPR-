#include <stdio.h>
#include <stdlib.h>
typedef struct MB
{
    char nome_matriz[20];
    float **M;
    int totalL, totalC; //dimensão da matriz
}Matriz;

typedef struct Lista_Encadeada
{
     Matriz MD;
     struct Lista_Encadeada *prox;
}ListaLinear;

void inicializa_lista(ListaLinear **N)//inicializa a lista
  {
   *N = NULL;
  }

ListaLinear * Cria_lista(int lin) //aloca memória para o lista
{
  ListaLinear **matriz ;
matriz = (ListaLinear **) malloc(lin * sizeof(ListaLinear *));
       if(!matriz)
       {
       printf("Problema de alocação");
       exit(0);
     }
  return matriz ;
}

void menuop();

void insere_lista(ListaLinear **N, int dado);

int **aloca_linhas(int);

void aloca_coluna( int**,int,int);

void le_dados (int **matriz, int lin, int col);

void imprime_matriz (int **matriz, int lin, int col);

void Cria_Matriz();

void main ( )
{
     ListaLinear **Lista;
     int menu;
         do{

            menuop();// apenas mostrar as opções

         scanf("%d", &menu);

        switch(menu)
        {
              case 1:
                    Cria_Matriz();

                break;
              case 9 :
                 //imprime_matriz (int **matriz, int lin, int col)
             break;

                default:
                     printf("\nOpcao Invalida!!!");
         }
    }while(menu != 10);
 return 0;
 }

  menuop(){

         printf("\n1. Declarar uma matriz: ");
         printf("\n2. Transpor uma matriz: ");
         printf("\n3. Somar duas matrizes: ");
         printf("\n4. Subtrair duas matrizes: ");
         printf("\n6.. Dividir uma matriz por outra: ");
         printf("\n7. Multiplicar uma matriz por outra: ");
         printf("\n8. Imprimir a Diagonal Principal: ");
         printf("\n9. Imprimir uma matriz: ");
         printf("\n10 Sair do Programa: ");
         printf("\nDIGITE A OPÇÃO : ");

  }


void Cria_Matriz(){

          Matriz info;
          char linha[80]; /* linha de caracteres com os dados */
          char coluna[80]; /* linha de caracteres com os dados */
          int lin=0, col=0; /* número de linhas e colunas */
          int **matriz; /* ponteiro para os ponteiros de cada uma das linhas */
                puts("Entre com o nome da Matriz");
                scanf("%s", &info.nome_matriz);// inserir nome para a matriz na Struc
                    do{
                        puts("Qual o numero de linhas?");
                        scanf("%s",&linha);
                        lin = atoi(linha);
                        info.totalL = lin; //inserir total de linhas

                        } while (lin<=0);
                    aloca_linhas(lin);// alocar linhas na memória
                    do
                    {
                      puts("Qual o numero de de coluna");
                        scanf("%s",&coluna);
                        col = atoi(coluna);
                        info.totalC = col; // inserir o  total de colunas ;

                    }while (col<=0);
            matriz = Cria_lista(lin);
            aloca_coluna(matriz,lin,col);// alocar espaço para ela na memoria no endereço da matriz;
 int i, j;
 puts("Entre com os dados");
    for (i=0; i<lin; i++)
     {
            printf("Entre com a linha %d\n", i);
        for (j=0; j<col; j++)
             {
             printf("Elemento %d %d\n", i, j);
             scanf("%d", *(matriz +i) +j);
             }
     }
     imprime_matriz (matriz, lin, col);

}

  int **aloca_linhas(int lin)
    {
         int **m;
         m = (int **) malloc (lin * sizeof(int *));

         if (!m)
        {
             puts("Nao há espaço para alocar memória");
             exit(1);
         }else
         printf("Alocando espaço para armazenar os ponteiros para as linhas.\n");


 return m;
    }



void aloca_coluna(int **matriz, int lin, int col)
{
     Cria_lista(lin);
    for (int i=0; i<lin; i++)
 {
        *(matriz +i) = (int *) malloc(col * sizeof (int));
 if (! *(matriz+i) ){
        printf("Não há espaço para alocar a linha %d", i);
        exit(1);
 }
 }
}

void imprime_matriz (int **matriz, int lin, int col)
{
     int i, j;
     for (i=0; i<lin; i++)
     {
         for (j=0; j<col; j++)
         {
         printf("%7d ", *(*(matriz +i) +j));
         }
     printf("\n");
     }
}
