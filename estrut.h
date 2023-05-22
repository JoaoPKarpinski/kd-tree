#ifndef _ESTRH_
#define _ESTRH_

typedef struct _no{
    void * item;
    struct _no * esq;
    struct _no * dir;
    int nivel;
}tno;

typedef struct _coord{
    //inserir informacoes da implementação específica
    int x;
    int y;
}coord;

typedef struct _arv{
    tno * raiz;
    int (*compara)(int a, int b);
}tarv;

void abb_construir(tarv * parv, int (*compara)(int a, int b));
void abb_inserir(tarv * parv, void *pitem);

#endif 
