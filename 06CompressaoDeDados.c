    //Renata Sendreti Broder, 112347
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    typedef struct tipoItem{
        char letra;
        int qtd;
        struct tipoItem *ant;
        struct tipoItem *prox;
    } tipoItem;
     
    typedef struct tipoLista{
        tipoItem *inicio;
        tipoItem *fim;
        int tam;
    }tipoLista;
     
    void inicializaLista(tipoLista *lista){
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tam = 0;
    }
     
    void insereNovoItem(tipoLista *lista, tipoItem novoItem){
        tipoItem *aux = malloc(sizeof(tipoItem));
        *aux = novoItem;
     
        if(lista->inicio == NULL){
            lista->inicio = aux;
            lista->fim = aux;
            aux->ant = NULL;
            aux->prox = NULL;
        }
        else{
            aux->ant = lista->fim;
            lista->fim->prox = aux;
            lista->fim = aux;
            aux->prox = NULL;
        }
        lista->tam++;
    }
     
    void lerString(tipoLista *lista, char *string, int tamStr){
        int i, j=0;
        int qtd;
        tipoItem novoItem;
     
        for(i=0; i<tamStr; i++){
            novoItem.letra = string[i];
            qtd = 1;
            for(j=(j+1); j<tamStr; j++){
                if(string[i] == string[j]){
                    qtd++;
                }
                else break;
            }
            novoItem.qtd = qtd;
            insereNovoItem(lista, novoItem);
            i=(j-1);
        }
    }
     
    void removeCompressao(tipoLista *lista, tipoItem *percorre){
        tipoItem *remove;
        int maior;
     
        if(percorre == lista->inicio && percorre->prox->qtd != 1){
            remove = lista->inicio;
            lista->inicio = lista->inicio->prox;
            lista->inicio->qtd++;
            lista->inicio->ant = NULL;
            lista->tam--;
            //free(remove);
        }
        else if(percorre == lista->fim && percorre->ant->qtd != 1){
            remove = lista->fim;
            lista->fim = lista->fim->ant;
            lista->fim->qtd++;
            lista->fim->prox = NULL;
            lista->tam--;
            //free(remove);
        }
        else if(percorre->ant != NULL && percorre->prox != NULL){
            if(percorre->ant->qtd != 1 && percorre->prox->qtd != 1){
                remove = percorre;
                maior = percorre->ant->qtd;
                if(maior < percorre->prox->qtd) percorre->prox->qtd++;
                else percorre->ant->qtd++;
                percorre->ant->prox = percorre->prox;
                percorre->prox->ant = percorre->ant;
                lista->tam--;
                }
            //free(remove);
        }
    }
     
    void compressao(tipoLista *lista){
        tipoItem *percorre;
        percorre = lista->inicio;
     
        while(percorre != NULL){
            if(percorre->qtd == 1){
                removeCompressao(lista, percorre);
                percorre=percorre->prox;
            }
            else percorre=percorre->prox;
        }
    }
     
    void imprimir(tipoLista *lista){
        tipoItem *percorre;
        percorre = lista->inicio;
     
        printf("%d\n", lista->tam*2);
        while(percorre!= NULL){
            printf("%d%c", percorre->qtd, percorre->letra);
            percorre = percorre->prox;
        }
     
        printf("\n");
        return;
     
    }
     
    tipoItem removeTudo(tipoLista *lista){
        tipoItem *remove, imprime;
        remove = lista->inicio;
        imprime = (*lista->inicio);
        lista->inicio = lista->inicio->prox;
        free(remove);
        remove = lista->inicio;
     
        return imprime;
    }
     
    void imprimirRemoverLista(tipoLista *lista){
        tipoItem imprime;
     
        printf("%d\n", lista->tam*2);
        while(lista->inicio!=NULL){
            imprime = removeTudo(lista);
            printf("%d%c", imprime.qtd, imprime.letra);
        }
        lista->fim = NULL;
    }
     
    int main(){
        tipoLista lista;
        inicializaLista(&lista);
     
        char string[1023];
        scanf("%s", string);
        int tamStr = strlen(string);
     
        lerString(&lista, string, tamStr);
        imprimir(&lista);
        compressao(&lista);
     
        imprimirRemoverLista(&lista);
     
        return 0;
    }