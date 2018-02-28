    //Renata Sendreti Broder, 112347
    #include <stdio.h>
    #include <stdlib.h>
     
    typedef struct tipoCliente{
        int id;
        int tempo;
        struct tipoCliente *prox;
    }tipoCliente;
     
    typedef struct tipoFila{
        int id;
        int tempo;
        tipoCliente *inicio;
        tipoCliente *fim;
    }tipoFila;
     
    void inicializaFila(tipoFila *atendentes, int A){
        int i;
        for(i=0; i<A; i++){
            atendentes[i].id = i+1;
            atendentes[i].tempo = 0;
            atendentes[i].inicio = NULL;
            atendentes[i].fim = NULL;
        }
    }
     
    int filaVazia(tipoFila *atendentes, int i){
        if(atendentes[i].inicio==NULL)return 1;
        return 0;
    }
     
    int proximaFila(tipoFila *atendentes, int A){
        int i;
        int menor = atendentes[0].tempo;
        int indice = 0;
     
        for(i=1; i<A; i++){
            if(atendentes[i].tempo<menor){
                menor = atendentes[i].tempo;
                indice = i;
            }
        }
        return indice;
    }
     
    int atendePrimeiros(tipoFila *atendentes, int i, tipoCliente novoCliente){
        if(filaVazia(atendentes, i)){
            atendentes[i].inicio = malloc(sizeof(tipoCliente));
            (*atendentes[i].inicio) = novoCliente;
            atendentes[i].tempo += novoCliente.tempo;
            atendentes[i].fim = atendentes[i].inicio;
            atendentes[i].inicio->prox=NULL;
        }
        return 0;
    }
     
    int atendeProximos(tipoFila *atendentes, int A, tipoCliente novoCliente){
        int i;
        i = proximaFila(atendentes, A);
     
        atendentes[i].fim->prox = malloc(sizeof(tipoCliente));
        (*atendentes[i].fim->prox) = novoCliente;
        atendentes[i].tempo += novoCliente.tempo;
        atendentes[i].fim = atendentes[i].fim->prox;
        atendentes[i].fim->prox = NULL;
     
        return 0;
    }
     
    void imprimeFilas(tipoFila *atendentes, int A){
        int i;
        tipoCliente *remove;
        for(i=0; i<A; i++){
            printf("%d :", atendentes[i].id);
            while(atendentes[i].inicio != NULL){
                printf(" %d", atendentes[i].inicio->id);
                remove = atendentes[i].inicio;
                atendentes[i].inicio = atendentes[i].inicio->prox;
                free(remove);
            }
            printf("\n");
        }
    }
     
    int main(){
        int N, A, i;
        scanf("%d %d", &N, &A);
        tipoFila atendentes[A];
        inicializaFila(atendentes, A);
     
        tipoCliente novoCliente;
        for(i=0; i<A;i++){
            if(i==N) break;
            novoCliente.id = i+1;
            scanf("%d", &novoCliente.tempo);
            atendePrimeiros(atendentes, i, novoCliente);
        }
     
        for(i=i; i<N; i++){
            novoCliente.id = i+1;
            scanf("%d", &novoCliente.tempo);
            atendeProximos(atendentes, A, novoCliente);
        }
     
        imprimeFilas(atendentes, A);
     
        return 0;
    }