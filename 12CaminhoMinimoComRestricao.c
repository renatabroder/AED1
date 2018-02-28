    //Renata Sendreti Broder, 112347
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h>
    #define INF INT_MAX
     
    typedef struct tipoItem{
        int info;
        struct tipoItem *prox;
    }tipoItem;
     
    typedef struct tipoPilha{
        tipoItem *topo;
    }tipoPilha;
     
    void inicializaPilha(tipoPilha *pilha){
        pilha->topo = NULL;
     }
     
    void insereNaPilha(tipoPilha *pilha, int valor){
        tipoItem *aux = malloc(sizeof(tipoItem));
        aux->info = valor;
        aux->prox = pilha->topo;
        pilha->topo = aux;
    }
     
    int removeDaPilha(tipoPilha *pilha){
        int retorno = pilha->topo->info;
        //tipoItem *r = pilha->topo;
        pilha->topo = pilha->topo->prox;
        //free(r);
        return retorno;
    }
     
    typedef struct tipoVertice{
        int info;
        int peso;
        struct tipoVertice *prox;
    }tipoVertice;
     
    typedef struct tipoListaA{
        tipoVertice **adj;
        int tam;
    }tipoListaA;
     
    void inicializaLista(tipoListaA *lista, int N){
        int i;
        lista->adj = malloc(N*sizeof(tipoVertice*));
        for(i=0; i<N; i++) lista->adj[i] = NULL;
        lista->tam = N;
    }
     
    void insereAresta(tipoListaA *lista, int v1, int v2, int peso){
        tipoVertice *aux = malloc(sizeof(tipoVertice));
        aux->info = v2;
        aux->prox = NULL;
        aux->peso = peso;
     
        if(lista->adj[v1] == NULL) lista->adj[v1] = aux;
        else if(lista->adj[v1] != NULL){
            if(lista->adj[v1]->info > aux->info){
                aux->prox = lista->adj[v1];
                lista->adj[v1] = aux;
            }
            else{
                tipoVertice *percorre = lista->adj[v1];
                while(percorre->prox != NULL && percorre->prox->info < aux->info) percorre = percorre->prox;
                aux->prox = percorre->prox;
                percorre->prox = aux;
            }
        }
    }
     
    void ordenacaoTopologica(tipoListaA *lista, int v, int *visitados, tipoPilha *pilha){
        visitados[v] = 1;
     
        tipoVertice *L = lista->adj[v];
        while(L != NULL){
            if(visitados[L->info] == 0) ordenacaoTopologica(lista, L->info, visitados, pilha);
            L = L->prox;
        }
     
        insereNaPilha(pilha, v);
    }
     
    void relax(int u, int v, int peso, int *dist, int R){
        if(dist[v] > dist[u] + peso) dist[v] = dist[u] + peso;
    }
     
    void buscaMenorCaminho(tipoListaA *lista, int busca, int N, int R){
        int i;
        tipoPilha pilha;
        int *dist = malloc(N*sizeof(int));
        inicializaPilha(&pilha);
     
        int *visitados = malloc(N*sizeof(int));
        for(i=0; i<N; i++){
            visitados[i] = 0;
            dist[i] = INF;
        }
        dist[busca] = 0;
     
        for(i=busca; i<N; i++){
            if(visitados[i] == 0) ordenacaoTopologica(lista, i, visitados, &pilha);
        }
     
        tipoVertice *L;
     
        while(pilha.topo != NULL){
            int u = removeDaPilha(&pilha);
            L = lista->adj[u];
     
            if(dist[u] != INF){
                while(L!=NULL){
                    if(L->peso <= R) relax(u, L->info, L->peso, dist, R);
                    L = L->prox;
                }
            }
        }
     
        for(i=0; i<N; i++){
            if(dist[i] == INF) printf("INF ");
            else printf("%d ", dist[i]);
        }
        printf("\n");
    }
     
    int main(){
        int busca, R, N, M, P, i;
        scanf("%d", &busca);
        scanf("%d", &R);
        scanf("%d %d", &N, &M);
     
        tipoListaA lista;
        inicializaLista(&lista, N);
     
        int v1, v2;
     
        for(i=0; i<M; i++){
            scanf("%d %d %d", &v1, &v2, &P);
            insereAresta(&lista, v1, v2, P);
        }
     
        buscaMenorCaminho(&lista, busca, N, R);
     
        return 0;
    }