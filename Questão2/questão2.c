#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

char *add_name(char *string){ 
    printf("Digite o nome que deseja adicionar: "); 
    getchar(); 
    char *s = (char*)malloc(sizeof(char) * 100); 
    scanf("%[^\n]", s);

    if (string == NULL){ //verifica se string ja possui algum conteudo
        string = (char *) malloc(sizeof(char) * (strlen(s) + 2));
        strcpy(string, s); 
    }
    else{
        string = (char *) realloc(string, (strlen(string) + strlen(s) + 2)); 
        strcat(string, s); 
    }

    strcat(string, "|");
         
    if(string == NULL){ //verifica se consegui alocar a memoria
        printf("Erro!"); 
        exit(1);
    }

    free(s);
    return string;
}

char *remove_name(char *string){
    if (string != NULL){
        printf("Digite o nome que deseja remover: "); 
        getchar();
        char *r = (char*)malloc(sizeof(char) * 100); 
        scanf("%[^\n]", r); 

        int encontrar = 0;//flag

        char *guarda = NULL; //string que vai guardar todos os nomes, exceto o removido 
        char *s = NULL; //usada para comparar com o nome a ser removido, armazena token temporariamente
        s = strtok(string, "|");
        while(s != NULL){
            if(strcmp (s, r) != 0){ //verifica se o token eh o nome a ser removido
                if (guarda == NULL){
                    guarda = (char *) malloc(sizeof(char) * (strlen(s) + 2)); 
                    strcpy(guarda,s);
                }
                else{                
                    guarda = (char *) realloc(guarda, (strlen(guarda) + strlen(s) + 2)); 
                    strcat(guarda,s);
                }
                strcat(guarda,"|");
            }
            else{
                encontrar = 1;
            }
   	        s = strtok(NULL, "|");
        }
        
        if(encontrar != 1){
            printf("Nome não encontrado!\n");               
        }

        if (guarda != NULL){
            string = (char *) realloc(string, sizeof(char) * (strlen(guarda) + 1));
            strcpy(string, guarda); //copia guarda para string
        }
        else{
      	    string = (char *) realloc(string, sizeof(char)*0);
        }        
        free(s);    
        free(guarda);
        free(r);
    }

    else{
        printf("Lista vazia!\n");               
    }
	return string;
}
 

void show(char *string){ 
    if(string != NULL){
        while (*string){
            if(*string != '|'){
	            putchar(*string);
	        }
	        else{
	            putchar('\n');
	        }
            string++;
        }
    }
    else{
        printf("Lista vazia!\n");
    }     
}


 
int main(){
    
    char *string = NULL;

    do{
        printf("Escolha uma opção:\n 1)Adicionar\n 2)Remover\n 3)Listar\n 4)Sair\n"); //menu

        switch(getchar()){
            case '1': 
                string = add_name(string);
                break;
            case '2':
                string = remove_name(string);
                break;
            case '3':
                show(string);
                break;
            case '4':
                free(string); 
                exit(1);
            default: 
                printf("Opção inexistente\n");
        }
    }while(getchar());
    exit(0);
}

