#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

void *incluir(void *pBuffer){   
    pBuffer = (void *)realloc(pBuffer, sizeof(int)*1 + (sizeof(char)*10 + sizeof(int)*2) * (*((int*)(pBuffer)) + 1));

    printf("Digite os dados do usuário que deseja adicionar:\nNome: "); 
    getchar(); 
    scanf("%[^\n]", (char *)(pBuffer + sizeof(int) + (sizeof(char)*10 + sizeof(int)*2) * (*((int*)(pBuffer))))); //avança num usuarios
    printf("Idade: "); 
    getchar(); 
    scanf("%d", (int *)(pBuffer + sizeof(int)*1 + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * (*((int*)(pBuffer))))); //avança num usuarios + nome 
    printf("Telefone: "); 
    getchar(); 
    scanf("%d", (int *)(pBuffer + sizeof(int)*2 + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * (*((int*)(pBuffer)))));   //avança num usuarios + nome + idade       
    
    *(int*)(pBuffer) += 1; 
    return pBuffer;
}

void *apagar(void *pBuffer){
    if(*(int*)(pBuffer) > 0){
        char *nome = (char*)malloc(sizeof(char) * 10); 
        printf("Digite o nome do usuario que deseja remover: ");
        getchar();
        scanf("%[^\n]", nome);

        int *encontrar = (int*)malloc(sizeof(int)); //flag
        *encontrar = 0;

        for(int p_contador = 0; p_contador < *(int*)(pBuffer); p_contador++){

            if(strcmp((char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int)*2) * p_contador), nome) == 0){       
                
                if ((p_contador) != *(int*)(pBuffer)){             
                    for(int contador_aux = (p_contador + 1); contador_aux < *(int *)(pBuffer); contador_aux++){ //puxa tudo que tem depois do usuario a ser removido para uma posição antes
                        strcpy((char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int)*2) * (p_contador)), (char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int)*2) * contador_aux)); 
                        *(int *)(pBuffer + sizeof(int) + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * (p_contador))=*(int *)(pBuffer + sizeof(int) + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * contador_aux); 
                        *(int *)(pBuffer + sizeof(int) + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * (p_contador))=*(int *)(pBuffer + sizeof(int)*2 + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * contador_aux); 
                        p_contador++;
                   }
                }
                
                pBuffer = (void *)realloc(pBuffer, sizeof(int)*1+ (sizeof(char)*10 + sizeof(int)*2) * (*((int*)(pBuffer)) - 1));    
                *encontrar = 1;
                *(int*)(pBuffer) -= 1; //reduz o total de usuarios

            }

        }

        if(*encontrar == 0){
            printf("Usuário não encontrado!\n");    
        }

        free(nome);
        free(encontrar);     
    }
    else{
        printf("Lista vazia!\n");
    }
    return pBuffer;

}


void buscar(void *pBuffer){
    char *nome = (char*)malloc(sizeof(char) * 10); 
    printf("Digite o nome do usuário que deseja buscar: "); 
    getchar();
    scanf("%[^\n]", nome);

    int *encontrar = (int*)malloc(sizeof(int)); //flag
    *encontrar = 0;
    
    for(int p_contador = 0; p_contador < *(int*)(pBuffer); p_contador++){
       
        if(strcmp((char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int)*2) * p_contador), nome) == 0){
            printf("Nome: %s |  ", (char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int)*2) * p_contador)); 
            printf("Idade: %d | ", *(int *)(pBuffer + sizeof(int) + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * p_contador)); 
            printf("Telefone: %d \n", *(int *)(pBuffer + sizeof(int)*2 + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * p_contador)); 
            *encontrar = 1;
        }

    }

    if(*encontrar != 1){
        printf("Usuário não encontrado!\n");    
    }

    free(nome);
    free(encontrar); 
}


void listar(void *pBuffer){ 
    if(*(int*)(pBuffer) == 0){
        printf("    AGENDA VAZIA\n");
    }
    else{
        printf("    AGENDA\n");
        for(int p_contador = 0; p_contador < *(int*)(pBuffer); p_contador++){
            printf("Nome: %s |  ", (char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int)*2) * p_contador)); 
            printf("Idade: %d | ", *(int *)(pBuffer + sizeof(int) + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * p_contador)); 
            printf("Telefone: %d \n", *(int *)(pBuffer + sizeof(int)*2 + sizeof(char)*10  + (sizeof(char) * 10 + sizeof(int)*2) * p_contador)); 
        }
    }
}


int main(){
    
    void *pBuffer = malloc(sizeof(int));

    if(pBuffer == NULL){ //verifica se conseguiu alocar 
        printf("Erro!"); 
        exit(1); 
    }

    *(int*)pBuffer = 0;

    do{
        printf("Escolha uma opção:\n 1)Incluir\n 2)Apagar\n 3)Busar\n 4)Listar\n 5)Sair\n"); //menu

        switch(getchar()){
            case '1': 
                pBuffer = incluir(pBuffer);
                break;
            case '2':
                pBuffer = apagar(pBuffer);
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
