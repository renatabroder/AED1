    //Renata Sendreti Broder, 112347
     
    #include <stdio.h>
    #include <stdlib.h>
     
    typedef struct tipoNo{
        int info;
        struct tipoNo *esq;
        struct tipoNo *dir;
    }tipoNo;
     
    typedef struct tipoArvore{
        tipoNo *raiz;
    }tipoArvore;
     
    void inicializaArvore(tipoArvore *arvore){
        arvore->raiz = NULL;
    }
     
    void insereNovoNo(tipoNo *raiz, tipoNo *novoNo){
        if(novoNo->info >= raiz->info){
            if(raiz->dir != NULL) insereNovoNo(raiz->dir, novoNo);
            else raiz->dir = novoNo;
        }
        else if(novoNo->info < raiz->info){
            if(raiz->esq != NULL) insereNovoNo(raiz->esq, novoNo);
            else raiz->esq = novoNo;
        }
    }
     
    void criaNo(tipoArvore *arvore, int num){
        tipoNo *aux;
        aux = malloc(sizeof(tipoNo));
        aux->info = num;
        aux->dir = NULL;
        aux->esq = NULL;
     
        if(arvore->raiz == NULL){
            arvore->raiz = aux;
        }
        else{
            insereNovoNo(arvore->raiz, aux);
        }
    }
     
    void imprimePreOrdem(tipoNo *no){
        if(no == NULL) return;
        printf("%d ", no->info);
        imprimePreOrdem(no->esq);
        imprimePreOrdem(no->dir);
    }
     
    void imprimeEmOrdem(tipoNo *no){
        if(no == NULL) return;
        imprimeEmOrdem(no->esq);
        printf("%d ", no->info);
        imprimeEmOrdem(no->dir);
    }
     
    void imprimePosOrdem(tipoNo *no){
        if(no == NULL) return;
        imprimePosOrdem(no->esq);
        imprimePosOrdem(no->dir);
        printf("%d ", no->info);
    }
     
    void imprimeSequencia(tipoNo *no, int numero){
        printf("%d ", no->info);
        if(no->info == numero) return;
        else if(numero > no->info) imprimeSequencia(no->dir, numero);
        else if(numero < no->info) imprimeSequencia(no->esq, numero);
    }
     
    int retornaAltura(tipoNo *no) {
        int e, d;
        if (no == NULL) return -1;
        e = retornaAltura(no->esq);
        d = retornaAltura(no->dir);
        if (e > d) return e+1;
        else return d+1;
    }
     
    int main(){
    int N, i, numero, altura, verific=-1;
    tipoArvore arvore;
    inicializaArvore(&arvore);
     
    scanf("%d %d", &N, &numero);
    int sequencia[N];
     
    for(i=0; i<N; i++){
        scanf("%d", &sequencia[i]);
        criaNo(&arvore, sequencia[i]);
        if(sequencia[i] == numero) verific++;
    }
     
    imprimePreOrdem(arvore.raiz);
    printf("\n");
    imprimeEmOrdem(arvore.raiz);
    printf("\n");
    imprimePosOrdem(arvore.raiz);
    printf("\n");
    if(verific == -1) printf("%d", verific);
    else imprimeSequencia(arvore.raiz, numero);
    printf("\n");
     
    altura = retornaAltura(arvore.raiz);
    printf("%d", altura);
     
    return 0;
    }