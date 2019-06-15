/*
Nome:Jonathan Santos Silva
RA: 759052
Curso: Engenharia de Computação
**/
#include <stdio.h>
#include <stdlib.h>

typedef struct pessoa Pessoa;
struct pessoa
{
    int posicao;
    Pessoa *prox;
};

Pessoa *inicio = NULL;
Pessoa *fim;

//Protótipos
void insereLista(int x);
void removeLista(Pessoa *p);
int imprimeLista();
int resolveJosephus(int n, int m);

int main()
{
    int nroexecs;
    scanf("%d", &nroexecs);
    int *n = (int*)malloc(nroexecs * sizeof(int));
    int *p = (int*)malloc(nroexecs * sizeof(int));

    for (int i = 0; i < nroexecs; i++)
    {
        scanf("%d", &n[i]);
        scanf("%d", &p[i]);
    }

    for (int i = 0; i < nroexecs; i++)
    {
        printf("Usando n=%d, m=%d, resultado=%d\n", n[i], p[i], resolveJosephus(n[i], p[i]));
    }

    return 0;
}


int resolveJosephus(int n, int m)
{
    inicio = NULL;
    for (int i = 1; i <= n; i++) // Inicializa a lista circular com n elementos.
        insereLista(i);
    Pessoa *matador = inicio;
    Pessoa *morto = inicio;
    Pessoa *aux;
    while (matador != matador->prox)
    {
        if (m == 1)
        {
            morto = matador->prox;
            removeLista(matador); // no caso 1, como a funçao remove, já remove Pessoa->prox, entramos em um caso "padrão".
            matador = morto->prox;
        }
        else
        {
            for (int i = 1; i < m; i++)
            { // Caso onde salto é maior que 1
                matador = matador->prox;
                morto = matador->prox;
            }
            if (aux == matador)
            { //Caso em que matador comete suicídio. (CASO INVáLIDO)
                matador = matador->prox;
                morto = matador->prox;
            }
            removeLista(matador);
            aux = matador;
            matador = morto->prox;
        }
    }
    return matador->posicao;

}
/*
@brief - remover o elemento p→prox, ou seja, o elemento imediatamente depois de p.
param   {Pessoa *p} "Pessoa" imediatamente antes da que vai ser removida
 */
void removeLista(Pessoa *p)
{
    Pessoa *aux;
    aux = p->prox;
    p->prox = aux->prox;
    if (aux == inicio)
        inicio = aux->prox;
    free(aux);
}

/*
@brief - x é o elemento a ser inserido. O elemento é inserido no final da lista circular, onde o último elemento da lista deve
sempre aponta para o primeiro elemento dela.
@param {x}  conteudo que será inserido na estrutura
 */
void insereLista(int x)
{
    Pessoa *newnode = (Pessoa *)malloc(sizeof(Pessoa));
    newnode->posicao = x;
    if (inicio == NULL)
    { // Se inicio igual a null, insere no começo da lista
        inicio = newnode;
        newnode->prox = inicio;
        fim = inicio->prox;
    }
    fim->prox = newnode;
    newnode->prox = inicio;
    fim = fim->prox;
}
/*
imprimir todos os elementos
presentes na lista naquele momento, começando por aquele apontado por inicio.
 */
int imprimeLista()
{
    Pessoa *aux = inicio;
    do
    {
        return(printf("%d \n", aux->posicao));
        aux = aux->prox;
    } while (aux != inicio);
}
