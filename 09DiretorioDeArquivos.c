    //Renata Sendreti Broder 112347
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    typedef struct tipoNo{
        char nome[100];
        struct tipoNo *filho;
        struct tipoNo*irmao;
    }tipoNo;
     
    typedef struct TipoArvore{
        tipoNo *raiz;
    }tipoArvore;
     
    void inicializaArvore(tipoArvore *arvore){
        arvore->raiz = NULL;
    }
     
    void insereNo(tipoNo *raiz, tipoNo *novo, char *destino){
        if(!strcmp(raiz->nome, destino)){
            novo->irmao = raiz->filho;
            raiz->filho = novo;
            return;
        }
        tipoNo *i = raiz->filho;
        while(i != NULL){
            insereNo(i, novo, destino);
            i = i->irmao;
        }
    }
     
    void criarNo(tipoArvore *arvore, char *recente, char *destino){
        tipoNo *aux = malloc(sizeof(tipoNo));
        strcpy(aux->nome, recente);
        aux->filho = NULL;
        aux->irmao = NULL;
     
        if(arvore->raiz == NULL) arvore->raiz = aux;
        else insereNo(arvore->raiz, aux, destino);
    }
     
    void moverArquivo(tipoArvore *arvore, tipoNo *raiz, char *recente, char *destino){
        if(raiz->filho != NULL && !strcmp(raiz->filho->nome, recente)){
            tipoNo *mover = raiz->filho;
            raiz->filho = raiz->filho->irmao;
            insereNo(arvore->raiz, mover, destino);
            return;
        }
        if(raiz->irmao != NULL && !strcmp(raiz->irmao->nome, recente)){
            tipoNo *mover = raiz->irmao;
            raiz->irmao = raiz->irmao->irmao;
            insereNo(arvore->raiz, mover, destino);
            return;
        }
        tipoNo *i = raiz->filho;
        while(i != NULL){
            moverArquivo(arvore, i, recente, destino);
            i = i->irmao;
        }
    }
     
    void liberarMemoria(tipoNo *raiz){
        tipoNo *p = raiz->filho;
        while(p!=NULL){
            tipoNo *aux = p->irmao;
            liberarMemoria(p);
            p = aux;
        }
        free(raiz);
    }
     
    void removerArquivo(tipoNo *raiz, char *recente){
        if(raiz->filho != NULL && !strcmp(raiz->filho->nome, recente)){
            tipoNo *remover = raiz->filho;
            raiz->filho = raiz->filho->irmao;
            liberarMemoria(remover);
            return;
        }
        else if(raiz->irmao != NULL && !strcmp(raiz->irmao->nome, recente)){
            tipoNo *remover = raiz->irmao;
            raiz->irmao = raiz->irmao->irmao;
            liberarMemoria(remover);
            return;
        }
        tipoNo *i = raiz->filho;
        while(i != NULL){
            removerArquivo(i, recente);
            i = i->irmao;
        }
    }
     
     
    int imprimeArvore(tipoNo *raiz, char *aBusca){
        int ret;
        if(!strcmp(raiz->nome, aBusca)){
            printf("%s ", raiz->nome);
            return 1;
        }
        tipoNo *i = raiz->filho;
        while(i!=NULL){
            ret = imprimeArvore(i,aBusca);
            if(ret == 1){
                printf("%s ",raiz->nome);
                return 1;
            }
            i = i->irmao;
        }
        return 0;
    }
     
     
    void imprimePre(tipoNo *arv){
         tipoNo *p = arv->filho;
         printf("%s ",arv->nome);
         while(p!=NULL){
             imprimePre(p);
             p=p->irmao;
         }
    }
     
    int main(){
        tipoArvore arvore;
        inicializaArvore(&arvore);
     
        int i, N;
        char aBusca[1024];
        char stringOp[3];
        char recente[1024] = "\root";
        char destino[1024] = "\0";
     
        criarNo(&arvore, "\\root", destino);
     
        //printf("%s\n", arvore.raiz->nome);
        scanf("%d", &N);
        scanf("%s", aBusca);
        for(i=0; i<N; i++){
            scanf("%s", stringOp);
            scanf("%s", recente);
     
            if(stringOp[1] == 'a'){
                scanf("%s", destino);
                criarNo(&arvore, recente, destino);
            }
            else if(stringOp[1] == 'm'){
                scanf("%s", destino);
                moverArquivo(&arvore, arvore.raiz, recente, destino);
            }
            else if(stringOp[1] == 'r') removerArquivo(arvore.raiz, recente);
        }
     
        int a = imprimeArvore(arvore.raiz, aBusca);
        if(a == 0) printf("Arquivo nao encontrado!");
        //imprimePre(arvore.raiz);
        return 0;
    }