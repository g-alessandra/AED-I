#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[10];
    int idade;
    int telefone;
}Pessoas;

Pessoas pessoas[10];

void incluir(void *pBuffer){ 
    if(*(int *)(pBuffer + (0)*(sizeof(int))) < 10){
        printf("Digite os dados do usuário que deseja adicionar:\nNome: "); 
        scanf("%s", pessoas[*(int *)(pBuffer + (0)*(sizeof(int)))].nome); 
        printf("Idade: "); 
        scanf("%d", &pessoas[*(int *)(pBuffer + (0)*(sizeof(int)))].idade); 
        printf("Telefone: "); 
        scanf("%d", &pessoas[*(int *)(pBuffer + (0)*(sizeof(int)))].telefone);
    
        *(int *)(pBuffer + (0)*(sizeof(int))) += 1;
    }
    else{
        printf("Não possui espaço suficiente!\n");
    }
}


void apagar(void *pBuffer){ 
    if(*(int *)(pBuffer + (0)*(sizeof(int))) != 0){

        *(int *)(pBuffer + (3)*sizeof(int)) = 0;

        printf("Digite o nome do usuario que deseja remover: ");
        scanf("%s", (char *)(pBuffer + (4)*sizeof(int))); 
        
        for(*(int *)(pBuffer + (1)*(sizeof(int))) = 0; *(int *)(pBuffer + (1)*(sizeof(int))) < *(int *)(pBuffer + (0)*(sizeof(int)));  *(int *)(pBuffer + (1)*(sizeof(int)))+=1){
            if(strcmp(pessoas[*(int *)(pBuffer + (1)*(sizeof(int)))].nome, (char *)(pBuffer + (4)*sizeof(int))) == 0){

                for(*(int *)(pBuffer + (2)*sizeof(int)) = *(int *)(pBuffer + (1)*(sizeof(int))) + 1; *(int *)(pBuffer + (2)*(sizeof(int))) < *(int *)(pBuffer + (0)*(sizeof(int))); *(int *)(pBuffer + (2)*sizeof(int)) += 1){
                    pessoas[*(int *)(pBuffer + (1)*(sizeof(int)))] = pessoas[*(int *)(pBuffer + (2)*sizeof(int))];
                    *(int *)(pBuffer + (1)*(sizeof(int))) += 1;
                } 
            
                pessoas[(*(int *)(pBuffer + (0)*sizeof(int))) - 1].nome[0] = '\0'; //zera os dados da última pessoa
                pessoas[(*(int *)(pBuffer + (0)*sizeof(int))) - 1].idade = 0;
                pessoas[(*(int *)(pBuffer + (0)*sizeof(int))) - 1].telefone = 0;
                
                *(int *)(pBuffer + (3)*sizeof(int)) = 1;
                *(int *)(pBuffer + (0)*sizeof(int)) -= 1;
            }
        }        
        
        if(*(int *)(pBuffer + (3)*sizeof(int)) == 0){
            printf("Usuário não encontrado!\n");    
        }
    }
    else{
        printf("Lista vazia!\n");
    }
}


void buscar(void *pBuffer){ 
    if(*(int *)(pBuffer + (0)*(sizeof(int))) != 0){
    
        *(int *)(pBuffer + (3)*sizeof(int)) = 0;
    
        printf("Digite o nome do usuário que deseja buscar: "); 
        scanf("%s", (char *)(pBuffer + (4)*sizeof(int)));  
    
        for(*(int *)(pBuffer + (1)*(sizeof(int))) = 0; *(int *)(pBuffer + (1)*(sizeof(int))) < *(int *)(pBuffer + (0)*(sizeof(int)));  *(int *)(pBuffer + (1)*(sizeof(int)))+=1){
            if(strcmp(pessoas[*(int *)(pBuffer + (1)*(sizeof(int)))].nome, (char *)(pBuffer + (4)*sizeof(int))) == 0){
                printf("Nome: ");
                for(*(int *)(pBuffer + (2)*sizeof(int)) = 0; pessoas[*(int *)(pBuffer + (1)*(sizeof(int)))].nome[*(int *)(pBuffer + (2)*(sizeof(int)))] != '\0';  *(int *)(pBuffer + (2)*(sizeof(int)))+=1){
                    printf("%c", pessoas[*(int *)(pBuffer + (1)*(sizeof(int)))].nome[*(int *)(pBuffer + (2)*sizeof(int))]);
                } 
                printf(" | Idade: %d ", pessoas[*(int *)(pBuffer + (1)*(sizeof(int)))].idade);  
                printf("| Telefone: %d\n", pessoas[*(int *)(pBuffer + (1)*(sizeof(int)))].telefone);         

                *(int *)(pBuffer + (3)*sizeof(int)) = 1;
            }
        }

        if(*(int *)(pBuffer + (3)*sizeof(int)) == 0){
            printf("Usuário não encontrado!\n");    
        }
    }
    else{
        printf("Lista vazia!\n");
    }
}


void listar(void *pBuffer){
    if(*(int *)(pBuffer + (0)*(sizeof(int))) != 0){
        
        for(*(int *)(pBuffer + (1)*(sizeof(int))) = 0; *(int *)(pBuffer + (1)*(sizeof(int))) < *(int *)(pBuffer + (0)*(sizeof(int)));  *(int *)(pBuffer + (1)*(sizeof(int)))+=1){
            printf("Nome: %s ", pessoas[*(int *)(pBuffer + (1)*(sizeof(int)))].nome);
            printf(" | Idade: %d ", pessoas[*(int *)(pBuffer + (1)*(sizeof(int)))].idade);  
            printf(" | Telefone: %d\n", pessoas[*(int *)(pBuffer + (1)*(sizeof(int)))].telefone);          
        }

    }
    else{
        printf("Lista vazia!\n");
    }
    
} 


int main(){
    void *pBuffer = NULL;
    pBuffer = (void *)malloc((4)*sizeof(int) + (10)*(sizeof(char))); //contador de pessoas, i, j, flag encontrar, nome(buscar/remover)     

    *(int *)(pBuffer + (0)*(sizeof(int))) = 0; 

    if(pBuffer == NULL){ //verifica se conseguiu alocar 
        printf("Erro!"); 
        exit(1); 
    }
    
    do{
        printf("Escolha uma opção:\n 1)Incluir\n 2)Apagar\n 3)Busar\n 4)Listar\n 5)Sair\n"); //menu

        switch(getchar()){
            case '1': 
                incluir(pBuffer);
                break;
            case '2':
                apagar(pBuffer);
                break;
            case '3':
                buscar(pBuffer);
                break;
            case '4':
                listar(pBuffer);
                break;    
            case '5':
                free(pBuffer);
                exit(1);
            default: 
                printf("Opção inexistente\n");
        }

    }while(getchar());
    
    exit(0);
}
