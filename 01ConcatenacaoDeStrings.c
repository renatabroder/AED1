    #include <stdio.h>
    #include <stdlib.h>
     
    int contarCaracteres(char * string, int X, int Y){
        int i, qtd=0;
        for(i=0; i<(X+Y); i++){
            if(string[i]=='\0') return qtd;
            qtd++;
        }
        return -1;
    }
     
    char * concatenarCaracteres(char * stringX, char * stringY, int X, int Y, int *qtdZ){
        int i, qtdCaracteresX, qtdCaracteresY, qtdTotal;
     
        qtdCaracteresX = contarCaracteres(stringX, X, Y);
        qtdCaracteresY = contarCaracteres(stringY, X, Y);
        qtdTotal = qtdCaracteresX+qtdCaracteresY;
        *qtdZ = qtdTotal;
     
        //printf("%d\n", qtdTotal);
     
        char * stringZ;
        stringZ = malloc((qtdTotal+1)*sizeof(char));
     
        for(i=0; i<(qtdCaracteresX+1); i++){
            stringZ[i] = stringX[i];
        }
        for(i=0; i<(qtdCaracteresY+1); i++){
            stringZ[i+qtdCaracteresX] = stringY[i];
        }
     
        //printf("%s", stringZ); //stringZ esta sendo construida
     
        return stringZ;
    }
     
    int contaQuantidade(char * string, char C, int qtdZ){
        int i, qtdC=0;
     
        for(i=0; i<qtdZ; i++){
            if(string[i] == C) qtdC++;
        }
     
        return qtdC;
    }
     
    int main()
    {
        int X, Y;
        char C;
        int qtdZ;
     
        scanf("%d %d %c", &X, &Y, &C);
        char *stringX, *stringY;
        stringX = malloc((X+1)*sizeof(char));
        stringY = malloc((Y+1)*sizeof(char));
     
        scanf("%s %s", stringX, stringY);
     
        char *stringZ;
        stringZ = concatenarCaracteres(stringX, stringY, X, Y, &qtdZ); //tá concatenando.
     
        int qtdC;
        qtdC = contaQuantidade(stringZ, C, qtdZ);
     
        printf("%s\n", stringZ);
        printf("%d\n", qtdZ);
        printf("%d\n", qtdC);
     
        return 0;
    }