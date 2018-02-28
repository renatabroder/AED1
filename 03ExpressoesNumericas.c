        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #define TAM 10
     
        typedef struct item{
            int algarismo;
        }item;
     
        typedef struct pilhaRPN{
            item *itens;
            int topo;
        }pilhaRPN;
     
        void inicializaPilhaRPN(pilhaRPN *pilha){
            pilha->topo=-1;
        }
     
     
     
        typedef struct pilhaParenteses{
            char carac[TAM/2];
            int topo;
        }pilhaParenteses;
     
        void inicializaPilhaParenteses(pilhaParenteses *pilha){
            pilha->topo=-1;
        }
        int pilhaParentesesVazia(pilhaParenteses *pilha){
            if(pilha->topo < 0) return 1;
            return 0;
        }
        void empilhaParenteses(pilhaParenteses *pilha, char i){
            //printf("entrou empilha 1\n");
            pilha->topo++;
            pilha->carac[pilha->topo] = i;
        }
        void desempilhaParenteses(pilhaParenteses *pilha){
            //printf("entrou desempilha\n");
            pilha->topo--;
        }
     
     
        int verificaValidade(char *expressao){
            int i;
            int len = strlen(expressao);
            pilhaParenteses pilha;
            inicializaPilhaParenteses(&pilha);
     
            for(i=0; i<len; i++){
                if(expressao[i] == '(' || expressao[i]==')'){
                    if(expressao[i]==')' && pilhaParentesesVazia(&pilha)){ //primeiro parenteses é ')'
                        printf("Unbalanced parentesis\n");
                        return 0;
                    }
                    else if(pilhaParentesesVazia(&pilha)) empilhaParenteses(&pilha, expressao[i]);
                    else if(!pilhaParentesesVazia(&pilha)){
                        if(expressao[i]==pilha.carac[pilha.topo])empilhaParenteses(&pilha, expressao[i]);
                        else desempilhaParenteses(&pilha);
                    }
                }
                if(expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*' || expressao[i] == '/'){
                    //printf("entrou verifica operador\n");
                    if(expressao[i-1] == '(' && expressao[i+1]==')'){
                        printf("Invalid expression\n");
                        return 0;
                    }
                    if(expressao[i-1] == expressao[i+1] && (expressao[i-1] == '(' || expressao[i-1] == ')')){
                        printf("Invalid expression\n");
                        return 0;
                    }
                    if(expressao[i+1] == '+' || expressao[i+1] == '-' || expressao[i+1] == '*' || expressao[i+1] == '/'){
                        printf("Invalid expression\n");
                        return 0;
                    }
                }
            }
            if(pilha.topo != -1){ //ou seje, tem parenteses sobrando
                printf("Unbalanced parentesis\n");
                return 0;
            }
     
            return 1;
        }
     
     
        /*int converteRPN(char *expressao){
        }*/
     
        int main(){
            char expressao[TAM];
            scanf("%s", expressao);
     
            if(verificaValidade(expressao)) //converteRPN(expressao);
     
            return 0;
        }