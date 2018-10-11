/*
  Trabalho Avaliativo - Estrutura de dados 1 - UFPR
  Equipe: Diego Lemos e Jean de Jesus
  Projeto Calculadora de matrizes
*/

// Includes com as bibliotecas necessárias
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

// Método que inicializa a lista
void inicializa_lista(ListaLinear **N)
  {
   *N = NULL;
  }

// Método que aloca memória para o lista
ListaLinear *Cria_lista()
{
  ListaLinear *matriz ;
  matriz = (ListaLinear*) malloc(sizeof(ListaLinear));
  if(!matriz)
  {
    printf("Problema de alocação!");
    exit(0);
  }
  return matriz ;
}

void menuop();

void insere_inicio_lista(ListaLinear **N, Matriz info);

float **aloca_linhas(int);

void aloca_coluna(int **matriz, int lin, int col);

void imprime_matriz (float **matriz, int lin, int co,char nome[]);

Matriz busca_lista(ListaLinear *N, char nome[]);

Matriz Transposta (ListaLinear **li , float **N, int l, int c, char nome[]);

void operacao (ListaLinear **li,ListaLinear *l, char op);

void imprimir_diagonal(float **matriz, int lin, int col, char nome[]);

int remover(ListaLinear *N);

void Cria_Matriz(ListaLinear **l);

//Função main
int main ()
{    // declaração de variaveis do main
     Matriz info;
     ListaLinear *Lista,*Lista2, Lista3,Lista4;
     char nome[20];
     char nome1[20];
     inicializa_lista(&Lista);
     int menu;
     Lista2 = Lista;
     do
     {
         menuop();// apenas mostrar as opções
         setbuf(stdin,NULL);
         scanf("%d", &menu);

        switch(menu)
        {
              case 1:
                Cria_Matriz(&Lista);
              break;
              case 2 :
                printf("Entre com o nome da matriz que deseja transpor: ");
                setbuf(stdin,NULL);
                scanf("%s", nome);
                Lista3.MD = busca_lista(Lista,nome);
                if(Lista3.MD.totalL != NULL){
                  Transposta(&Lista,Lista->MD.M, Lista->MD.totalL, Lista->MD.totalC,nome);
                }

              break;
              case 3 :
                operacao(&Lista,Lista, '+');
              break;
              case 4:
                operacao(&Lista,Lista, '-');
              break;
              case 5:
                operacao(&Lista,Lista, '/');
              break;
              case 6:
                operacao(&Lista,Lista, '*');
              break;
              case 7:
                printf("Entre com o nome da matriz que imprimir a diagonal principal: ");
                setbuf(stdin,NULL);
                scanf("%s", nome);
                Lista4.MD= busca_lista(Lista,nome);
                if(Lista4.MD.totalL != NULL){
                  imprimir_diagonal(Lista4.MD.M, Lista4.MD.totalL, Lista4.MD.totalC, Lista4.MD.nome_matriz);
                }
              break;
              case 8 :
                /* Trecho comentado com a versão antiga do código onde houve correção
                printf("Entre com nome da lista que deseja imprimir: ");
                setbuf(stdin,NULL);
                scanf("%s",nome);
                busca_lista(Lista, nome);
                */
                printf("Entre com nome da lista que deseja imprimir: ");
                setbuf(stdin,NULL);
                scanf("%s",nome);
                Lista3.MD= busca_lista(Lista,nome);
              break;
              case 9:
               remover(Lista);
              break;
              case 10:
               printf("\nEncerrando...\n");
               exit(0);
              break;
              default:
                printf("\nOpcão Inválida!!!\n\n");
              break;
         }
    }while(menu != 10);
    return 1;
 }
// Função para mostrar o menu
 void menuop(){
   printf("\n1.  Declarar uma matriz: ");
   printf("\n2.  Transpor uma matriz: ");
   printf("\n3.  Somar duas matrizes: ");
   printf("\n4.  Subtrair duas matrizes: ");
   printf("\n5.  Dividir uma matriz por outra: ");
   printf("\n6.  Multiplicar uma matriz por outra: ");
   printf("\n7.  Imprimir a Diagonal Principal: ");
   printf("\n8.  Imprimir matriz: ");
   printf("\n9.  Destruir uma matriz: ");
   printf("\n10. Sair do Programa: ");
   printf("\nDIGITE A OPÇÃO : ");
}

// Função para declaração e inicialização de uma matriz
void Cria_Matriz(ListaLinear **l)
{
   Matriz info;
   char linha[80]; /* linha de caracteres com os dados */
   char coluna[80]; /* linha de caracteres com os dados */
   int lin=0, col=0; /* número de linhas e colunas */
   float **matriz; /* ponteiro para os ponteiros de cada uma das linhas */
   puts("Entre com o nome da Matriz:");
   setbuf(stdin,NULL);
   scanf("%s", info.nome_matriz);// inserir nome para a matriz na Struc
     do
     {
        puts("Digite o número de linhas:");
        setbuf(stdin,NULL);
        scanf("%s",linha);
        lin = atoi(linha);
        info.totalL = lin; //inserir total de linhas
     } while (lin<=0);

   matriz = aloca_linhas(lin);// alocar linhas na memória

   do
   {
      puts("Digite o número de colunas:");
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
      printf("Entre com dados para a linha %d\n", i);
      for (j=0; j<col; j++)
      {
        printf("Elemento %d %d: \n", i, j);
        setbuf(stdin,NULL);
        scanf("%f", *(matriz +i) +j);
      }
   }

  info.M=matriz;
  insere_inicio_lista(l,info);
  imprime_matriz(matriz,lin,col,info.nome_matriz);
}

// Função para alocação de linhas da matriz
float **aloca_linhas(int lin)
{
    float **m;
    m = (int **) malloc (lin * sizeof(float));

     if (!m)
      {
        puts("Não há espaço para alocar memória! ");
        exit(1);
      } else
         printf("Alocando espaço para armazenar os ponteiros para as linhas!\n");
         return m;
}

// Função para alocação de linhas da matriz
void aloca_coluna(int **matriz, int lin, int col)
{
    for (int i=0; i<lin; i++)
    {
        *(matriz +i) = (float *) malloc(col * sizeof (float));

       if (! *(matriz+i) )
       {
          printf("Não há espaço para alocar a linha %d !", i);
          exit(1);
       }
    }
    if (*(matriz+1)) {
      printf("Colunas alocadas! \n" );
    }
}

// Função que imprime uma matriz
void imprime_matriz (float **matriz, int lin, int col,char nome[])
{
     int i, j;
     printf("\n----MATRIZ %s ------\n\n",nome);
     for (i=0; i<lin; i++)
     {
         for (j=0; j<col; j++)
         {
           printf("[  %.2f  ] ", *(*(matriz +i) +j));
         }
         printf("\n");
     }
     printf("\n");
}

// Função que insere uma matriz no início da lista
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
// Função para buscar matriz dentro da lista
Matriz busca_lista(ListaLinear *N, char nome[])
{

  ListaLinear *aux,*aux1;
  aux1= N;
  //Se a lista não foi inicializada
  if(N == NULL)
  {
    printf("Lista está vazia!\n");
  }
    else
    {
      aux = N;
      while( aux != NULL)
      {
        if(strcmp(aux->MD.nome_matriz,nome)== 0){
          break;
        } else
           aux = aux->prox;
      }

      if (aux != NULL){
          imprime_matriz(aux->MD.M, aux->MD.totalL, aux->MD.totalC, aux->MD.nome_matriz);
          return aux->MD;
      }else {
        printf("Matriz não encontrada !\n");
      }

    }
}

// Função que calcula a transposta de uma matriz
Matriz Transposta (ListaLinear **li , float **N, int l, int c, char nome[])
{
  Matriz info,MT;
  ListaLinear *aux;
  char linha[80]; /* linha de caracteres com os dados */
  char coluna[80]; /* linha de caracteres com os dados */
  int lin=0, col=0; /* número de linhas e colunas */
  float **matriz; /* ponteiro para os ponteiros de cada uma das linhas */

  puts("Entre com o nome para Matriz Transposta: ");
  setbuf(stdin,NULL);
  scanf("%s", info.nome_matriz);// inserir nome para a matriz na Struc

    do
    {
      lin = c;
      info.totalL = lin; //inserir total de linhas
    } while (lin<=0);
    // Alocando linhas na memória para a matriz resposta
    matriz = aloca_linhas(lin);
        do
        {
          col = l;
          info.totalC = col; // inserir o  total de colunas ;
        }while (col<=0);
        // Alocando colunas espaço para ela na memoria no endereço da matriz
        aloca_coluna(matriz,lin,col);

        for (int i=0; i<lin; i++)
        {
           for (int j=0; j<col; j++)
           {
              matriz[i][j] = N[j][i];
           }
        }

        info.M=matriz;
        insere_inicio_lista(li,info);
        imprime_matriz(matriz,lin,col,info.nome_matriz);
}

// Função que exclui uma matriz da lista
int remover(ListaLinear *N)
{   ListaLinear *m1;
    char nome[60];
    char nome2[60];
    //lista vazia
    if(N == NULL){
      printf("\nLista vazia. Não há o que remover! \n");
      return 0;
    }else
     {
      printf("\nEntre com o nome que deseja remover: ");
      setbuf(stdin,NULL);
      scanf("%s",nome);
      ListaLinear *ant = NULL;
      ListaLinear *aux = N;
      while(aux != NULL)
      {
         strcpy(nome2, aux->MD.nome_matriz);
         if(strcmp(nome, nome2) == 0)
             break;

         ant = aux;
         aux = aux->prox;
      }

     //se ant for null entao o elemento a ser removido é o primeiro ... esse caso precisa de tratamento especial
     if(ant == NULL){
         N = N->prox;
         printf("\n\tNome removido com sucesso!\n\n");
         free(aux);

     }
     //aux for diferente de NULL entao o while parou antes do fim da lista (Logo existe elemento com nome igual ao fornecido)
     else if(aux != NULL){
         ant = aux->prox; //ant agora aponta para o elemento que sucede aux
         printf("\n\tNome removido com sucesso!\n\n");
         free(aux);
     }

     return 1;
    }
}

// Função que realiza as quatro operações aritméticas entre as matrizes(+,-x,/)
void operacao (ListaLinear **li, ListaLinear *l,char op)
{
    Matriz info;
    ListaLinear m1,m2, *aux,*x1,*x2;
    char str[10];
    char linha[80]; /* linha de caracteres com os dados */
    char coluna[80]; /* linha de caracteres com os dados */
    int lin=0, col=0; /* número de linhas e colunas */
    float **matriz; /* ponteiro para os ponteiros de cada uma das linhas */
    char nome[20], nome1[20];
    char ope = op;
    float tot=0;

    // Verifica qual é a operação e preenche a string a ser utilizada nas impressões
    if (op == '+') {
      strcpy(str,"soma");
    } else if(op == '-') {
      strcpy(str,"subtração");
    } else if(op == '*'){
      strcpy(str,"multiplicação");
    } else if(op == '/'){
      strcpy(str,"divisão");
    }

    printf("Entre com o nome da matriz a: ");
    setbuf(stdin,NULL);
    scanf("%s", nome);

    // m1 recebe o resultado da busca da primeira matriz
    m1.MD= busca_lista(l,nome);
    printf("Entre com o nome da matriz b: ");
    setbuf(stdin,NULL);
    scanf("%s", nome1);
    // m2 recebe o resultado da busca da primeira matriz
    m2.MD = busca_lista(l,nome1);
    printf("Entre com nome para a matriz resultante da %s: ", str);
    setbuf(stdin,NULL);
    scanf("%s",info.nome_matriz );
    // se operação for de soma ou subtração
    if(op == '+' || op =='-'){
      if( (m2.MD.totalL == m1.MD.totalL) && (m2.MD.totalC == m1.MD.totalC)) // verifica se o tamanho das matrizes são iguais
      {
          do
          {
            lin = m2.MD.totalL;
            info.totalL = lin; //inserir total de linhas

          } while (lin<=0);

            matriz = aloca_linhas(lin);// alocar linhas na memória para a matriz resposta

              do
              {
                col = m2.MD.totalC;
                info.totalC = col; // inserir o  total de colunas ;
              }while (col<=0);

              aloca_coluna(matriz,lin,col);// alocar colunas na memória para a matriz resposta

              // Realiza os calculos e atribui os valores a suas respectivas posições
              for (int i=0; i<lin; i++)
              {
                  for (int j=0; j<col; j++)
                  { // Se for soma
                     if (op == '+') {
                       matriz[i][j] = *(*(m1.MD.M +i) +j) + *(*(m2.MD.M +i) +j);
                       // Se for subtração
                     } else if (op == '-'){
                       matriz[i][j] = *(*(m1.MD.M +i) +j) - *(*(m2.MD.M +i) +j);
                     }
                  }
              }
              // Insere a matriz resposta na lista e imprime os resultados
              info.M=matriz;
              insere_inicio_lista(li,info);
              printf("\n\tResultado da %s entre %s e %s \n\n",str,m1.MD.nome_matriz,m2.MD.nome_matriz);
              imprime_matriz(m1.MD.M,lin,col,m1.MD.nome_matriz );
              imprime_matriz(m2.MD.M,lin,col,m2.MD.nome_matriz );
              imprime_matriz(matriz,lin,col,info.nome_matriz );
      } else {
        printf("As matrizes não possuem o mesmo tamanho!\n");
      }// Se a operação for multiplicação
    } else if(op == '*')
      { // Verifica se atende a condicão colunas da matriz 1 = linhas da matriz 2
        if(m1.MD.totalC == m2.MD.totalL)
        {
          do
          {
              lin = m1.MD.totalL;
              info.totalL = lin; //inserir total de linhas

          } while (lin<=0);

            matriz = aloca_linhas(lin);// alocando linhas na memória para a matriz resposta

              do
              {
                col = m2.MD.totalC;
                info.totalC = col; // inserir o  total de colunas ;
              }while (col<=0);

              aloca_coluna(matriz,lin,col);// alocando colunas na memória para a matriz resposta

              // Realizando os cálculos e atribuindo o resultado as suas respectivas posições
              for (int i=0; i<lin; i++)
              {
                  for (int j=0; j<col; j++)
                  {
                    matriz[i][j] = tot;
                    for (int k=0; k<lin; k++)
                    {
                     tot+= ( *(*(m1.MD.M +i) +k) ) * (*(*(m2.MD.M +k) +j) );
                    }
                    matriz[i][j] = tot;
                    tot=0;
                  }
              }

              // Inserindo a matriz na lista e imprimindos os resultados
              info.M=matriz;
              insere_inicio_lista(li,info);
              printf("\n\tResultado da %s entre %s e %s \n\n",str,m1.MD.nome_matriz,m2.MD.nome_matriz);
              imprime_matriz(m1.MD.M,lin,col,m1.MD.nome_matriz );
              imprime_matriz(m2.MD.M,lin,col,m2.MD.nome_matriz );
              imprime_matriz(matriz,lin,col,info.nome_matriz );

      }else {
        printf("Não é possível realizar a multiplicação, pois a matriz 1  deve possuir a quantidade de colunas igual a quantidade de linhas da matriz 2\n");
      } // Se a operação for uma divisão
    }else if (op == '/'){
      int valida = 0; // Variavel utilizada para controle e validação da divisão (0=false, 1=true)
          if((m2.MD.totalL == m1.MD.totalL) && (m2.MD.totalC == m1.MD.totalC)) // verifica se os tamanhos das matrizes são iguais
          {   do
            {
                lin = m2.MD.totalL;
                info.totalL = lin; //inserir total de linhas

            } while (lin<=0);

              matriz = aloca_linhas(lin);// alocando linhas para a matriz resposta

                do
                {
                  col = m2.MD.totalC;
                  info.totalC = col; // inserir o  total de colunas ;
                }while (col<=0);

                aloca_coluna(matriz,lin,col);// alocando colunas para a matriz resposta

                // Calculando a divisão e atribuindo os resultados as suas respectivas posições
                for (int i=0; i<lin; i++)
                {
                    for (int j=0; j<col; j++)
                    {
                        if(*(*(m2.MD.M +i) +j) == 0){
                          valida =0;
                          goto fim;
                        } else{
                          matriz[i][j] = *(*(m1.MD.M +i) +j) / *(*(m2.MD.M +i) +j);
                          valida =1;
                        }
                    }
                }

                fim:
                // Se valida = 1 é porque a divisão foi realizada
                if(valida ==1 ){
                    info.M=matriz;
                    insere_inicio_lista(li,info);
                    printf("\n\tResultado da %s entre %s e %s \n\n",str,m1.MD.nome_matriz,m2.MD.nome_matriz);
                    imprime_matriz(m1.MD.M,lin,col,m1.MD.nome_matriz );
                    imprime_matriz(m2.MD.M,lin,col,m2.MD.nome_matriz );
                    imprime_matriz(matriz,lin,col,info.nome_matriz );
                } else if(valida ==0 ){
                    printf("\nA matriz 2 não pode possuir nenhum elemento igual a 0!\n");
                }
          } else {
            printf("As matrizes não possuem o mesmo tamanho\n");
          }
    }
}
//Função que imprime a diagonal de uma matriz
void imprimir_diagonal(float **matriz, int lin, int col, char nome[])
{
     int i, j;
     char nome_mat[60];
     strcpy(nome_mat,nome);
     printf("\nDiagonal Principal da matriz %s\n",nome_mat);
     for (i=0; i<lin; i++)
     {
         for (j=0; j<col; j++)
         { // Imprime somente se posição i == posição j
           if(i==j){
           printf(" %.2f  ", *(*(matriz +i) +j));

           }
         }
     }
     printf("\n\n");
}
