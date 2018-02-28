    #include <stdio.h>
    #include <stdlib.h>
     
    typedef struct tipoMonomio{
        int C;
        int E;
    }tipoMonomio;
     
    typedef struct tipoPolinomio{
        tipoMonomio *polinomio;
        int tamMax;
        int ultimo;
    }tipoPolinomio;
     
    int inicializaPolinomio(tipoPolinomio *lista, int N){
        lista->tamMax = N;
        lista->ultimo = 0;
        lista->polinomio = malloc(N*sizeof(tipoMonomio));
        if(lista->polinomio == NULL) return -1;
        return 0;
    }
     
    void inserePrimeiro(tipoPolinomio *lista, tipoMonomio novoMonomio){
        lista->polinomio[lista->ultimo] = novoMonomio;
        lista->ultimo++;
    }
     
    void remover(tipoPolinomio *lista, int i){
        int aux, ultimo=lista->ultimo;
        for(aux=i; aux<(ultimo-1); aux++){
            lista->polinomio[aux] = lista->polinomio[aux+1];
        }
        lista->ultimo--;
    }
     
    int verificaParticularidades(tipoPolinomio *lista, tipoMonomio novoMonomio){
        int i, j, ultimo = lista->ultimo;
     
        for(i=0; i<ultimo; i++){
            if(novoMonomio.E == lista->polinomio[i].E){
                lista->polinomio[i].C += novoMonomio.C; //podia liberar alguma memoria aqui
                if(lista->polinomio[i].C == 0) remover(lista, i);
                return 1;
            }
            else if(novoMonomio.E > lista->polinomio[i].E){
                for(j=ultimo; j>i; j--){
                    lista->polinomio[j]=lista->polinomio[j-1];
                }
                lista->polinomio[i]=novoMonomio;
                lista->ultimo++;
                i=ultimo; //se é maior que algum da esquerda, não precisa voltar a checar com os outros
                return 2;
            }
        }
        return 0;
    }
     
    void inserir(tipoPolinomio *lista, tipoMonomio novoMonomio){
        int verifica;
        verifica = verificaParticularidades(lista, novoMonomio);
        if(verifica == 0){
            lista->polinomio[lista->ultimo] = novoMonomio;
            lista->ultimo++;
        }
    }
     
    int main (){
        int N, i, C, E;
        scanf("%d", &N);
     
        tipoPolinomio lista;
        int inic;
        inic = inicializaPolinomio(&lista, N);
     
        tipoMonomio novoMonomio;
        scanf("%d %d", &novoMonomio.C, &novoMonomio.E);
        inserePrimeiro(&lista, novoMonomio);
     
        for(i=1; i<N; i++){
            scanf("%d %d", &novoMonomio.C, &novoMonomio.E);
            inserir(&lista, novoMonomio);
        }
     
        if(lista.polinomio[0].C == 0) printf("nulo\n0\n");
        else{
            for(i=0; i<lista.ultimo; i++){
                printf("%d %d ", lista.polinomio[i].C, lista.polinomio[i].E);
            }
            printf("\n%d\n", lista.ultimo);
        }
     
        return 0;
    }