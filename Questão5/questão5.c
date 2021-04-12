#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[30];
    int idade;
    int altura;
}Pessoas;

int num_pessoas = 0;

void *adicionar(Pessoas *pessoas){ 
    if(num_pessoas != 0){
        pessoas = (Pessoas *)realloc(pessoas, sizeof(Pessoas)*(num_pessoas + 1)); 
    }    
    else{
        pessoas = (Pessoas *)malloc(sizeof(Pessoas)); 
    }
    
    printf("\nDigite os dados da pessoa que deseja adicionar:\nNome: "); 
    getchar();
    scanf("%[^\n]", pessoas[num_pessoas].nome); 

    printf("Idade: ");
    scanf("%d", &pessoas[num_pessoas].idade); 

    printf("Altura: "); 
    scanf("%d", &pessoas[num_pessoas].altura);

    num_pessoas++;
    return pessoas;
}


void listar(Pessoas *pessoas){
    if(num_pessoas > 0){
        for(int i = 0; i < num_pessoas; i++){
            printf("Nome: %s |", pessoas[i].nome);
            printf("Idade: %d |", pessoas[i].idade);
            printf("Altura: %d\n", pessoas[i].altura);
        }
    }
    else{
        printf("Lista vazia!\n");
    }
    
} 


int main(){

    Pessoas *pessoas = NULL;

    do{
        printf("Deseja adicionar mais dados?\n <S> Sim      <N> Não \n"); //menu

        switch(getchar()){
            case 'S': 
                pessoas = adicionar(pessoas);
                break;
            case 'N':
                printf("\n");
                listar(pessoas);
                free(pessoas);
                exit(1);
            default:
                printf("Opção inexistente!\n");
        }
        printf("\n");
        
    }while(getchar());
    
    exit(0);
}
