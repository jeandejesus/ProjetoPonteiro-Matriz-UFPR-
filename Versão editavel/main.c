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

 menuop();
int **aloca_linhas(int);

void aloca_coluna(int**,int,int);


void main ( )
{
     Matriz info;
     int **matriz; /* ponteiro para os ponteiros de cada uma das linhas */
     int lin=0, col=0; /* número de linhas e colunas */
     int i, j,menu;
     char linha[80]; /* linha de caracteres com os dados */
     char coluna[80]; /* linha de caracteres com os dados */
     char nome;
     struct info;
     int *temp;

         do{

            menuop();// apenas mostrar as opções

         scanf("%d", &menu);

        switch(menu)
        {
              case 1:
                  do
                    {

                        puts("Entre com o nome da Matriz");
                        scanf("%s", &info.nome_matriz);// inserir nome para a matriz na Struc

                        puts("Qual o numero de linhas?");
                        scanf("%s",&linha);
                        lin = atoi(linha);
                        info.totalL = lin; //inserir total de linhas

                        } while (lin<=0 && col <=0);
                        aloca_linhas(lin);// alocar linhas na memória

                    do
                    {
                      puts("Qual o numero de de coluna");
                        scanf("%s",&coluna);
                        col = atoi(coluna);
                        info.totalC = col; // inserir o  total de colunas ;

                    }while (col<=0);

                    aloca_coluna(matriz,lin,col);// alocar espaço para ela na memoria no endereço da matriz;

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
     int i;
     for (i=0; i<lin; i++)
     {
        *(matriz +i) = (int *) malloc(col * sizeof (int));

    }

    if (! *(matriz+i) )
    {
     printf("Não há espaço para alocar a linha %d", i);
     exit(1);
    }else printf("Numero de colunas = %d\n", col);

}
