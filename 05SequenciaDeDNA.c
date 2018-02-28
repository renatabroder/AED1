    //Renata Sendreti Broder, 112347
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    typedef struct tipoBase{
        char base;
        struct tipoBase *prox;
        struct tipoBase *ant;
    }tipoBase;
     
    typedef struct tipoLista{
        tipoBase *inicio;
        tipoBase *fim;
    }tipoLista;
     
    void inicializaLista(tipoLista *lista){
        lista->inicio = NULL;
        lista->fim = NULL;
    }
     
    int listaVazia(tipoLista *lista){
        if(lista->inicio == NULL) return 1;
        return 0;
    }
     
    int insereBase(tipoLista *lista, char novaBase){
        tipoBase *aux = malloc(sizeof(tipoBase));
        aux->base = novaBase;
     
        if(listaVazia(lista)){
            lista->inicio = aux;
            lista->fim = lista->inicio;
            lista->inicio->prox = NULL;
            lista->inicio->ant = NULL;
            return 1;
        }
        else if(lista->fim->prox == NULL){
            aux->ant = lista->fim;
            lista->fim->prox = aux;
            lista->fim = aux;
            aux->prox = NULL;
            return 1;
        }
        return 0;
    }
     
    int removerSeq(tipoLista *lista, tipoBase *inicio, tipoBase *fim, int tamSub){
        int i;
        tipoBase *remove1, *remove2;
        remove1 = inicio;
        remove2 = inicio;
     
        //fim = fim->prox;
     
        /*if(fim != NULL) fim->ant = inicio->ant;
        else lista->fim = inicio->ant;
        if(inicio != lista->inicio) inicio->ant->prox = fim;
        else lista->inicio = fim;*/
        if(inicio->ant == NULL){
            lista->inicio = fim;
            fim->ant = NULL;
        }
     
        else if(fim == NULL){
            lista->fim = inicio->ant;
            lista->fim->prox = NULL;
        }
     
        else{
            inicio->ant->prox = fim;
            fim->ant = inicio->ant;
        }
     
        for(i=0; i<tamSub; i++){
            remove2 = remove2->prox;
            free(remove1);
            remove1 = remove2;
        }
        return 0;
    }
     
    int compararSub(tipoLista *lista, char *sub, int tamSub){
        int i, qtd=0, cont;
        tipoBase *compara, *baseSub, *recomp;
        compara = lista->inicio;
     
        while(compara!=NULL){
            if(compara->base != sub[0]){
                compara = compara->prox;
            }
            else{
                baseSub = compara->prox;
                cont = 1;
                for(i=1; i<tamSub; i++){
                    if(baseSub != NULL && baseSub->base == sub[i]){
                        cont++;
                        baseSub = baseSub->prox;
                    }
                    else{
                        break;
                    }
                }
                if(cont == tamSub){
                    qtd++;
                    removerSeq(lista, compara, baseSub, tamSub);
                    compara = baseSub;
                }
                else compara = compara->prox;
            }
        }
        return qtd;
    }
     
    tipoBase removeTudo(tipoLista *lista){
        tipoBase *remove, imprime;
        remove = lista->inicio;
        imprime = (*lista->inicio);
        lista->inicio = lista->inicio->prox;
        free(remove);
        remove = lista->inicio;
     
        return imprime;
     
    }
     
    void imprimirLista(tipoLista *lista, int qtd){
        tipoBase imprime;
        printf("%d\n", qtd);
        while(lista->inicio!=NULL){
            imprime = removeTudo(lista);
            printf("%c", imprime.base);
        }
        lista->fim = NULL;
    }
     
     
    int main(){
        int i, tamSt, tamSub, qtd;
        char string[1024];
        char sub[1024];
        char base;
     
        scanf("%s", string);
        tamSt = strlen(string);
     
        tipoLista lista;
        inicializaLista(&lista);
     
        for(i=0; i<tamSt; i++){
            base = string[i];
            insereBase(&lista, base);
        }
     
        scanf("%s", sub);
        tamSub = strlen(sub);
     
        qtd = compararSub(&lista, sub, tamSub);
        imprimirLista(&lista, qtd);
     
        return 0;
    }