#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

ListaLinear *Cria_lista() //aloca memória para o lista
{
  ListaLinear *matriz ;
    matriz = (ListaLinear*) malloc(sizeof(ListaLinear));
       if(!matriz)
       {
       printf("Problema de alocação");
       exit(0);
     }
  return matriz ;
}

void menuop();

void insere_inicio_lista(ListaLinear **N, Matriz info);

float **aloca_linhas(int);

void aloca_coluna(int **matriz, int lin, int col);

void le_dados (int **matriz, int lin, int col);

void imprime_matriz (float **matriz, int lin, int col);

Matriz busca_lista(ListaLinear *N, char nome[]);

Matriz Transposta (ListaLinear **li , float **N, int l, int c, char nome[]);

void Cria_Matriz(ListaLinear **l);

int main ()
{
     Matriz info;
     ListaLinear *Lista;
     char nome[20];
     inicializa_lista(&Lista);
     int menu;
         do{

            menuop();// apenas mostrar as opções

         scanf("%d", &menu);

        switch(menu)
        {
              case 1:
              Cria_Matriz(&Lista);
              break;
              case 2 :
                printf("Entre com o nome da matriz que deseja transpor");
                setbuf(stdin,NULL);
                scanf("%s", nome);
                Lista->MD = busca_lista(Lista,nome);
                Transposta(&Lista,Lista->MD.M, Lista->MD.totalL, Lista->MD.totalC,nome);
              break;
              case 9 :
                printf("Entre com nome da lista que deseja procurar");
                setbuf(stdin,NULL);
                scanf("%s",nome);
                busca_lista(Lista, nome);
              break;

                default:
                  printf("\nOpcao Invalida!!!");
         }
    }while(menu != 10);
    return 1;
 }

 void menuop(){

         printf("\n1. Declarar uma matriz: ");
         printf("\n2. Transpor uma matriz: ");
         printf("\n3. Somar duas matrizes: ");
         printf("\n4. Subtrair duas matrizes: ");
         printf("\n6.. Dividir uma matriz por outra: ");
         printf("\n7. Multiplicar uma matriz por outra: ");
         printf("\n8. Imprimir a Diagonal Principal: ");
         printf("\n9. Busca matriz: ");
         printf("\n10 Sair do Programa: ");
         printf("\nDIGITE A OPÇÃO : ");

  }


void Cria_Matriz(ListaLinear **l){

          Matriz info;
          char linha[80]; /* linha de caracteres com os dados */
          char coluna[80]; /* linha de caracteres com os dados */
          int lin=0, col=0; /* número de linhas e colunas */
          float **matriz; /* ponteiro para os ponteiros de cada uma das linhas */
                puts("Entre com o nome da Matriz");
                setbuf(stdin,NULL);
                scanf("%s", info.nome_matriz);// inserir nome para a matriz na Struc
                    do{
                        puts("Qual o numero de linhas?");
                        setbuf(stdin,NULL);

                        scanf("%s",linha);
                        lin = atoi(linha);
                        info.totalL = lin; //inserir total de linhas

                        } while (lin<=0);
                    matriz = aloca_linhas(lin);// alocar linhas na memória
                    do
                    {
                      puts("Qual o numero de de coluna");
                        setbuf(stdin,NULL);
                        scanf("%s",coluna);
                        col = atoi(coluna);
                        info.totalC = col; // inserir o  total de colunas ;

                    }while (col<=0);
                    aloca_coluna(matriz,lin,col);// alocar espaço para ela na memoria no endereço da matriz;

            int i, j;
                 puts("Entre com os dados");
                    for (i=0; i<lin; i++)
                     {
                            printf("Entre com a linha %d\n", i);
                        for (j=0; j<col; j++)
                             {
                             printf("Elemento %d %d\n", i, j);
                             scanf("%f", *(matriz +i) +j);
                             }
                     }
            info.M=matriz;

            insere_inicio_lista(l,info);
            imprime_matriz(matriz,lin,col);
}

float **aloca_linhas(int lin)
    {
      float **m;
      m = (int **) malloc (lin * sizeof(float));

     if (!m)
      {             puts("Nao há espaço para alocar memória");
             exit(1);
         }else
         printf("Alocando espaço para armazenar os ponteiros para as linhas.\n");

         return m;
    }



void aloca_coluna(int **matriz, int lin, int col)
{
    for (int i=0; i<lin; i++)
 {
    *(matriz +i) = (float *) malloc(col * sizeof (float));

 if (! *(matriz+i) ){
        printf("Não há espaço para alocar a linha %d", i);
        exit(1);
 }else
         printf("Alocando espaço para armazenar os ponteiros para as coluna.\n");

 }
}

void imprime_matriz (float **matriz, int lin, int col)
{
     int i, j;
     for (i=0; i<lin; i++)
     {
         for (j=0; j<col; j++)
         {
         printf("%.2f ", *(*(matriz +i) +j));
         }
     printf("\n");
     }
     return 0;
}

void insere_inicio_lista(ListaLinear **N, Matriz mat)
    {
         ListaLinear *novo;
         novo = Cria_lista();
         strcpy(novo->MD.nome_matriz,mat.nome_matriz);
         novo->MD.totalC = mat.totalC;
         novo->MD.totalL = mat.totalL;
         novo->MD.M = mat.M;
         novo->prox = *N;
         *N = novo;
    }

Matriz busca_lista(ListaLinear *N, char nome[]){
    ListaLinear *aux;

    if(N == NULL)
    {
        printf("lista vazia busca ");

    }
    else
    {
        aux = N;
        while( aux != NULL)
        {
           if(strcmp(aux->MD.nome_matriz,nome)== 0){
               break;
            }
           else
                aux = aux->prox;
        }
        if (aux != NULL){
          imprime_matriz(aux->MD.M, aux->MD.totalL, aux->MD.totalC);


        }
            return aux->MD;
    }


}

Matriz Transposta (ListaLinear **li , float **N, int l, int c, char nome[])
{
  Matriz info,MT;
  ListaLinear *aux;
  char linha[80]; /* linha de caracteres com os dados */
  char coluna[80]; /* linha de caracteres com os dados */
  int lin=0, col=0; /* número de linhas e colunas */
  float **matriz; /* ponteiro para os ponteiros de cada uma das linhas */

                puts("Entre com o nome para Matriz Transposta");
                setbuf(stdin,NULL);
                scanf("%s", info.nome_matriz);// inserir nome para a matriz na Struc

                do{
                        lin = c;
                        info.totalL = lin; //inserir total de linhas

                        } while (lin<=0);
                    matriz = aloca_linhas(lin);// alocar linhas na memória
                    do
                    {

                        col = l;
                        info.totalC = col; // inserir o  total de colunas ;

                    }while (col<=0);
                    aloca_coluna(matriz,lin,col);// alocar espaço para ela na memoria no endereço da matriz

                 for (int i=0; i<lin; i++)
                     {
                        for (int j=0; j<col; j++)
                             {
                              matriz[i][j] = N[j][i];
                             }
                     }
            info.M=matriz;
            insere_inicio_lista(li,info);
            imprime_matriz(matriz,lin,col);

}
