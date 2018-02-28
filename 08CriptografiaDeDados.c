    //Renata Sendreti Broder, 112347
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    typedef struct tipoNo{
        int freq;
        char letra;
        struct tipoNo *esq, *dir;
    }tipoNo;
     
    typedef struct tipoArvore{
        tipoNo *raiz;
    }tipoArvore;
     
    void inicializaArvore(tipoArvore *arvore){
        arvore->raiz = NULL;
    }
     
    void insereNovoNo(tipoNo *raiz, tipoNo *novoNo){
        if(novoNo->freq >= raiz->freq){
            if(raiz->dir != NULL) insereNovoNo(raiz->dir, novoNo);
            else raiz->dir = novoNo;
        }
        else if(novoNo->freq < raiz->freq){
            if(raiz->esq != NULL) insereNovoNo(raiz->esq, novoNo);
            else raiz->esq = novoNo;
        }
    }
     
    void criaNo(tipoArvore *arvore, tipoNo novoNo){
        tipoNo *aux;
        aux = malloc(sizeof(tipoNo));
        *aux = novoNo;
        aux->dir = NULL;
        aux->esq = NULL;
     
        if(arvore->raiz == NULL){
            arvore->raiz = aux;
        }
        else{
            insereNovoNo(arvore->raiz, aux);
        }
    }
     
    tipoNo* removerNo(tipoNo*no){
        tipoNo *novo = NULL;
        tipoNo *aux = no;
     
        if(no->esq == NULL && no->dir == NULL) return novo;//sem filhos
        else if(no->esq != NULL && no->dir == NULL) return no->esq; //soh tem filho da esq
        else if(no->esq == NULL && no->dir != NULL) return no->dir; //soh tem filho da dir
        else if(no->esq != NULL && no->dir != NULL){ //tem os dois filhos
            aux = aux->dir;
            while(aux->esq != NULL && aux->esq->esq != NULL) aux = aux->esq; //novo->esq é o novo real;
            if(aux->esq == NULL){
                novo = aux;
                novo->esq = no->esq;
                return novo;
            }
            novo = aux->esq;
            if(novo->dir == NULL && novo->esq== NULL) aux->esq = NULL;
            else if(novo->dir != NULL) aux->esq = novo->dir;
            novo->dir = no->dir;
            novo->esq = no->esq;
            free(no);
            return novo;
        }
    }
     
    void buscaRemocao(tipoArvore *arvore, int freqLetra, char letra){
        tipoNo *remover, *ant;
        remover = arvore->raiz;
     
        while(remover != NULL){
            if(letra == remover->letra){
                if(remover == arvore->raiz){
                    arvore->raiz = removerNo(remover);
                    return;
                }
                else if(ant->dir == remover){
                    ant->dir = removerNo(remover);
                    return;
                }
                else{
                    ant->esq = removerNo(remover);
                    return;
                }
            }
            ant = remover;
            if(freqLetra < remover->freq && letra != remover->letra) remover = remover->esq;
            else if(freqLetra >= remover->freq && letra != remover->letra) remover = remover->dir;
        }
    }
     
    void imprimeEmOrdem(tipoNo *no){
        if(no == NULL) return;
        imprimeEmOrdem(no->esq);
        printf("%c", no->letra);
        imprimeEmOrdem(no->dir);
    }
     
    int main(){
     
        tipoArvore arvore;
        inicializaArvore(&arvore);
     
        char string[1025];
        char letra1, letra2, auxLetra;
        int freqLetra1, freqLetra2;
        int i, cont[26];
     
        scanf("%c %c", &letra1, &letra2);
        scanf("%s", string);
     
        tipoNo novoNo;
     
        for(i=0; i<26; i++) cont[i] = 0;
        for(i=0; i<strlen(string); i++){
            if (string[i]>=65 && string[i]<=90) cont[string[i]-65]++;
        }
        for(i=0; i<26; i++){
            if (cont[i]>0){
                char c = i+65;
                novoNo.letra = c;
                novoNo.freq = cont[i];
                criaNo(&arvore, novoNo);
                if(novoNo.letra == letra1) freqLetra1 = novoNo.freq;
                if(novoNo.letra == letra2) freqLetra2 = novoNo.freq;
            }
        }
     
        buscaRemocao(&arvore, freqLetra1, letra1);
        buscaRemocao(&arvore, freqLetra2, letra2);
     
        imprimeEmOrdem(arvore.raiz);
     
        return 0;
    }