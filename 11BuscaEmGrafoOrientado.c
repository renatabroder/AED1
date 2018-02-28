    //Renata Sendreti Broder, 112347
     
    #include <stdio.h>
    #include <stdlib.h>
     
    typedef struct tipoVertice{
        int info;
        struct tipoVertice *prox;
    }tipoVertice;
     
    typedef struct tipoListaA{
        tipoVertice **adj;
        int tam;
    }tipoListaA;
     
    typedef struct tipoFila{
        tipoVertice *inicio, *fim;
    }tipoFila;
     
    void inicializaLista(tipoListaA *lista, int N){
        int i;
        lista->adj = malloc(N*sizeof(tipoVertice*));
        for(i=0; i<N; i++) lista->adj[i] = NULL;
        lista->tam = N;
    }
     
    void insereAresta(tipoListaA *lista, int v1, int v2){
        tipoVertice *aux = malloc(sizeof(tipoVertice));
        aux->info = v2;
        aux->prox = NULL;
     
        if(lista->adj[v1] == NULL) lista->adj[v1] = aux;
        else if(lista->adj[v1] != NULL){
            tipoVertice *percorre = lista->adj[v1];
            if(percorre->prox != NULL){
                while(percorre->prox != NULL && percorre->prox->info < aux->info) percorre = percorre->prox;
                aux->prox = percorre->prox;
                percorre->prox = aux;
            }
            if(percorre->prox == NULL){
                if(percorre->info > aux->info){
                    aux->prox = lista->adj[v1];
                    lista->adj[v1] = aux;
                }
                else{
                while(percorre->prox != NULL && percorre->prox->info < aux->info) percorre = percorre->prox;
                aux->prox = percorre->prox;
                percorre->prox = aux;
                }
            }
        }
    }
     
    void inicializaFila(tipoFila *fila){
        fila->inicio = NULL;
        fila->fim = NULL;
     }
     
    void insereNaFila(tipoFila *fila, int valor){
        tipoVertice *aux = malloc(sizeof(tipoVertice));
        aux->info = valor;
        aux->prox = NULL;
     
        if(fila->inicio == NULL) fila->inicio = aux;
        else fila->fim->prox = aux;
        fila->fim = aux;
    }
     
    int removeDaFila(tipoFila *fila){
        int retorno = fila->inicio->info;
        tipoVertice *r = fila->inicio;
        fila->inicio = fila->inicio->prox;
        free(r);
        return retorno;
    }
     
    void inicializaBuscaEmLargura(tipoListaA *lista, int busca){
        int *visitados = malloc(lista->tam * sizeof(int));
        int i;
        for(i=0; i<lista->tam; i++) visitados[i] = 0;
        visitados[busca] = 1;
     
        tipoFila fila;
        inicializaFila(&fila);
     
        insereNaFila(&fila, busca);
        tipoVertice *p;
        int valor;
        while(fila.inicio != NULL){
            valor = removeDaFila(&fila);
            printf("%d ", valor);
     
            p = lista->adj[valor];
            while(p != NULL){
                if(!visitados[p->info]){
                    visitados[p->info]= 1;
                    insereNaFila(&fila, p->info);
                }
                p = p->prox;
            }
        }
        printf("\n");
    }
     
    void buscaEmProfundidade(tipoListaA *lista, int busca, int *visitados){
        visitados[busca] = 1;
        printf("%d ", busca);
     
        tipoVertice *p = lista->adj[busca];
        while(p != NULL){
            if(!visitados[p->info]) buscaEmProfundidade(lista, p->info, visitados);
            p = p->prox;
        }
    }
     
    void inicializaBuscaEmProfundidade(tipoListaA *lista, int busca){
        int *visitados = malloc(lista->tam * sizeof(int));
        int i;
        for(i=0; i<lista->tam; i++) visitados[i] = 0;
     
        buscaEmProfundidade(lista, busca, visitados);
        printf("\n");
    }
     
    int main(){
        int busca, N, M, i;
        scanf("%d", &busca);
        scanf("%d %d", &N, &M);
     
        tipoListaA lista;
        inicializaLista(&lista, N);
     
        int v1, v2;
     
        for(i=0; i<M; i++){
            scanf("%d %d", &v1, &v2);
            insereAresta(&lista, v1, v2);
        }
     
        inicializaBuscaEmLargura(&lista, busca);
        inicializaBuscaEmProfundidade(&lista, busca);
     
    return 0;
    }