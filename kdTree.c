#include <stdio.h>
#include <stdlib.h>
#include "estrut.h"

int compara(int a, int b){
    return a < b;
}

coord* constr(int x, int y){
    coord* cordenada = (coord*)malloc(sizeof(coord));
    cordenada->x = x;
    cordenada->y = y;

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



void remover(tno** pPno){
    tno* aux;
    if(*pPno != NULL){
        if((*pPno)->dir == NULL && (*pPno)->esq == NULL){
            free((*pPno)->item);
            free(*pPno);
            *pPno = NULL;
        } else if((*pPno)->dir == NULL && (*pPno)->esq != NULL){
            aux = *pPno;
            free((*pPno)->item);
            *pPno = (*pPno)->esq;
            free(aux);
        } else if((*pPno)->esq == NULL && (*pPno)->dir != NULL){
            aux = *pPno;
            free((*pPno)->item);
            *pPno = (*pPno)->dir;
            free(aux);
        } else {
            tno* suc = (*pPno)->dir;
            tno** psuc = &(*pPno)->dir;
            while(suc->esq != NULL){
                psuc = &suc->esq;
                suc = suc->esq;
            }
            free((*pPno)->item);
            (*pPno)->item = suc->item;
            *psuc = suc->dir;
            free(suc); 
        }
    }
}

int main(){
    tarv arv;
    abb_construir(&arv, compara);

    abb_inserir(&arv, constr(40, 45)); //raiz

    abb_inserir(&arv, constr(15, 70)); //esq

    abb_inserir(&arv, constr(70, 10)); //dir

    abb_inserir(&arv, (constr(69, 50))); //dir
    
    abb_inserir(&arv, (constr(55, 80))); //esq
    
    abb_inserir(&arv, (constr(69, 120))); //dir

    tno** raiz = &arv.raiz; 

    remover(raiz);

    printf("%d - x\n", ((coord*)arv.raiz->dir->item)->x);

    return 0;
}