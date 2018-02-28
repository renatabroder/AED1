    //Renata Sendreti Broder, 112347
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    typedef struct tipoNo{
        char nome[17];
        int indice;
        struct tipoNo *prox;
    }tipoNo;
     
    typedef struct tipoLista{
        tipoNo *inicio, *fim;
        int qtd;
    }tipoLista;
     
    void inicializaLista(tipoLista *lista){
        lista->qtd = 0;
        lista->inicio = NULL;
        lista->fim = NULL;
    }
     
    int insereVertice(tipoLista *lista, char *pessoa){
        tipoNo *aux = malloc(sizeof(tipoNo));
        strcpy(aux->nome, pessoa);
        aux->prox = NULL;
     
        if(lista->inicio == NULL){
            lista->inicio = aux;
            lista->fim = aux;
        }
        else{
            lista->fim->prox = aux;
            lista->fim = aux;
        }
        lista->fim->indice = lista->qtd;
        lista->qtd++;
     
        return lista->fim->indice;
    }
     
    int verificaVertice(tipoLista *lista, char *pessoa){
        int indice;
        if(lista->inicio == NULL) indice = insereVertice(lista, pessoa);
        else{
            tipoNo *percorre = lista->inicio;
            while(percorre != NULL){
                if(!strcmp(percorre->nome, pessoa)) return percorre->indice;
                percorre = percorre->prox;
            }
            indice = insereVertice(lista, pessoa);
        }
        return indice;
    }
     
    int main(){
        int N, M, i, j, i1, i2;
        tipoLista lista;
        inicializaLista(&lista);
     
        char pessoa[17], pessoa1[17], pessoa2[17];
        scanf("%s", pessoa);
        scanf("%d %d", &N, &M);
     
        int matriz[N][N];
        for(i=0; i<N; i++){
            for(j=0; j<N; j++){
                matriz[i][j] = 0;
            }
        }
     
        for(i=0; i<M; i++){
            scanf("%s %s", pessoa1, pessoa2);
            i1 = verificaVertice(&lista, pessoa1);
            i2 = verificaVertice(&lista, pessoa2);
            matriz[i1][i2] = 1;
            matriz[i2][i1] = 1;
        }
     
        int p = verificaVertice(&lista, pessoa);
        int amigosSegrau[N-1];
        int qtd = 0;
     
        for(i=0; i<N; i++){
            if(i != p && matriz[p][i] == 1){
                for(j=0; j<N; j++){
                    if(j != p && matriz[i][j] == 1){
                        if(p != j && matriz[p][j] == 0){
                            amigosSegrau[qtd] = j;
                            qtd++;
                        }
                    }
                }
            }
        }
     
        int cont = 0;
        for(i=0; i<qtd; i++){
            for(j=(i+1); j<qtd; j++){
                if(amigosSegrau[i] == amigosSegrau[j]) amigosSegrau[j] = 'a';
            }
        }
     
        for(i=0; i<qtd; i++){
            if(amigosSegrau[i] != 'a') cont++;
        }
     
        printf("%d\n", cont);
     
        return 0;
    }