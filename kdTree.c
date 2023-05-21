#include <stdio.h>
#include <stdlib.h>
#include "estrut.h"

int compara(int a, int b){
    return a < b;
}

coord constr(int x, int y){
    coord cordenada;
    cordenada.x = x;
    cordenada.y = y;

    return cordenada;
}


void abb_construir(tarv * parv, int (*compara)(int a, int b)){
    parv->raiz = NULL;
    parv->compara = compara;
}



void abb_inserir(tarv * parv, void *pitem){
    tno ** ppno;
    tno * pno;
    ppno = &(parv->raiz);
    pno = *ppno;
    int nivel = 1;

    while(pno != NULL){
        if(pno->nivel % 2 > 0){
                            /* 10     20 */
            if (parv->compara(((coord*)pno->item)->x,((coord*)pitem)->x)){ /* direita*/
                ppno = &(pno->dir);
                pno = *ppno;
                nivel++;
            }else{                              /* esquerda*/
                ppno = &(pno->esq);
                pno = *ppno;
                nivel++;
            }
        } else {
            if (parv->compara(((coord*)pno->item)->y,((coord*)pitem)->y)){ /* direita*/
                ppno = &(pno->dir);
                pno = *ppno;
                nivel++;
            }else{                              /* esquerda*/
                ppno = &(pno->esq);
                pno = *ppno;
                nivel++;
            }
        }
    }
    if ((*ppno) == NULL){
        (*ppno) = malloc(sizeof(tno));
        (*ppno)->item = pitem;
        (*ppno)->nivel = nivel;
        (*ppno)->esq = NULL;
        (*ppno)->dir = NULL;
    }
}



int main(){
    tarv arv;
    abb_construir(&arv, compara);

    coord c1 = constr(40, 45);

    abb_inserir(&arv, &c1);


    coord c2 = constr(15, 70);

    abb_inserir(&arv, &c2);


    coord c3 = constr(70, 10);

    abb_inserir(&arv, &c3);


    coord c4 = constr(69, 50);

    abb_inserir(&arv, &c4);

    printf("%d - x\n", ((coord*)arv.raiz->dir->dir->item)->x);

    return 0;
}