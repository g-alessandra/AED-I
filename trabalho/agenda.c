#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[10];
    int idade;
    int telefone;
}Dados;

typedef struct nodo{
    Dados dados;
    struct nodo *prox;
    struct nodo *anterior;
}Nodo;

typedef struct{
    int contador, encontrar, i, contadorOrdenada;
    char nomeProcurado[10];
    Nodo *inicio, *fim; //lista
    Nodo *inicioOrdenada, *fimOrdenada; //fila
    Nodo *percorrer, *aux, *aux2, *aux3, *fimOrdenadaCopia; //auxiliares
}Controle;


void incluir(Controle *pBuffer){ //insere no fim da lista
    Nodo *novoNodo;
    novoNodo = (Nodo *)malloc(sizeof(Nodo));
    novoNodo->prox = NULL;
    novoNodo->anterior = NULL;

    if(novoNodo == NULL){ //verifica se conseguiu alocar 
        printf("Erro!"); 
        exit(1); 
    }
    
    printf("Digite os dados do usuário que deseja adicionar:\nNome: ");
    getchar(); 
    scanf("%[^\n]", novoNodo->dados.nome); 
    printf("Idade: "); 
    getchar(); 
    scanf("%d", &novoNodo->dados.idade); 
    printf("Telefone: "); 
    getchar(); 
    scanf("%d", &novoNodo->dados.telefone);       

    if(pBuffer->inicio == NULL){    
        pBuffer->inicio = novoNodo;
        pBuffer->inicio->anterior = NULL;
    }
    else{ 
        novoNodo->anterior = pBuffer->fim;
        pBuffer->fim->prox = novoNodo;
    }
    
    pBuffer->fim = novoNodo;
    
    pBuffer->contador += 1; 
}


void apagar(Controle *pBuffer){//remove o usuario de acordo com o nome solicitado, informa caso nao encontre
    if(pBuffer->contador == 0){ 
        printf("    AGENDA VAZIA\n");
    }
    else{
        printf("Digite o nome do usuário que deseja apagar: ");
        getchar();
        scanf("%[^\n]", pBuffer->nomeProcurado); 

        pBuffer->encontrar = 0; //encontrar
        
        pBuffer->percorrer = pBuffer->inicio; 
    
        for(pBuffer->i = 0; pBuffer->i < pBuffer->contador; pBuffer->i+=1){            
            if(strcmp(pBuffer->percorrer->dados.nome, pBuffer->nomeProcurado) == 0){
                if(pBuffer->contador == 1){ //se eh o unico elemento
                    pBuffer->inicio = NULL;
                    pBuffer->fim = NULL;
                    free(pBuffer->percorrer);

                }
                else{
                    if(pBuffer->percorrer == pBuffer->inicio){ //se eh o primeiro
                        pBuffer->percorrer = pBuffer->percorrer->prox; 
                        pBuffer->percorrer->anterior = NULL;
                        
                        pBuffer->inicio = pBuffer->percorrer; 
                        free(pBuffer->percorrer);

                    }
                    else{
                        if(pBuffer->percorrer == pBuffer->fim){ //eh o ultimo
                            pBuffer->percorrer = pBuffer->percorrer->anterior;
                            pBuffer->percorrer->prox = NULL;
                            
                            pBuffer->fim = pBuffer->percorrer;
                            free(pBuffer->percorrer);

                        }
                        else{ //ta no meio
                            pBuffer->aux = pBuffer->percorrer->anterior; 
                            pBuffer->aux->prox = pBuffer->percorrer->prox; 
                            pBuffer->aux2 = pBuffer->percorrer->prox; 
                            pBuffer->aux2->anterior = pBuffer->percorrer->anterior;
                            free(pBuffer->percorrer);
                        }
                    }
                }

                pBuffer->encontrar = 1; 
                pBuffer->contador -= 1; 
                pBuffer->i = pBuffer->contador; //completa condição do for, sai do loop
            }
            else{
                 pBuffer->percorrer = pBuffer->percorrer->prox;             
            }
        }
        
        if(pBuffer->encontrar != 1){ 
            printf("Usuário não encontrado!\n");    
        }
    }
}


void buscar(Controle *pBuffer){//mostra os dados do usuario solicitado
    if(pBuffer->contador == 0){
        printf("    AGENDA VAZIA\n");
    }
    else{
        printf("Digite o nome do usuário que deseja buscar: "); 
        getchar();
        scanf("%[^\n]", pBuffer->nomeProcurado);

        pBuffer->encontrar = 0; 
    
        for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){ 
            if(strcmp(pBuffer->percorrer->dados.nome, pBuffer->nomeProcurado) == 0){
                printf("Nome: %s |  ", pBuffer->percorrer->dados.nome); 
                printf("Idade: %d | ", pBuffer->percorrer->dados.idade); 
                printf("Telefone: %d \n", pBuffer->percorrer->dados.telefone); 
                
                pBuffer->encontrar = 1;
            }
        }
        
        if(pBuffer->encontrar != 1){ 
            printf("Usuário não encontrado!\n");    
        }
    }
}


void imprimir(Controle *pBuffer){ 
    if(pBuffer->contador == 0){
        printf("    AGENDA VAZIA\n");
    }
    else{
        printf("    AGENDA\n");
        for(pBuffer->percorrer = pBuffer->inicioOrdenada; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){
            printf("Nome: %s |  ", pBuffer->percorrer->dados.nome); 
            printf("Idade: %d | ", pBuffer->percorrer->dados.idade); 
            printf("Telefone: %d \n", pBuffer->percorrer->dados.telefone); 
        }
    }
}


void ordenaI(Controle *pBuffer){
    for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){ 
        Nodo *novo;
        novo = (Nodo *)malloc(sizeof(Nodo));
        novo->prox = NULL;
        novo->prox = NULL;

        novo->dados = pBuffer->percorrer->dados;    

        if(pBuffer->inicioOrdenada == NULL){
            pBuffer->inicioOrdenada = novo;
            pBuffer->inicioOrdenada->anterior = NULL;
        }
        else{
            novo->anterior = pBuffer->fimOrdenada;
            pBuffer->fimOrdenada->prox = novo;
        }
    
        pBuffer->fimOrdenada = novo; //insere no fim da fila 
    }
}


void ordenaAlfabetica(Controle *pBuffer){
    for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){ 
        Nodo *novo;
        novo = (Nodo *)malloc(sizeof(Nodo));
        novo->anterior = NULL;
        novo->prox = NULL;

        if(novo == NULL){ //verifica se conseguiu alocar 
            printf("Erro!"); 
            exit(1); 
        }
    
        novo->dados = pBuffer->percorrer->dados;
        
        pBuffer->fimOrdenadaCopia = pBuffer->fimOrdenada;

        if(pBuffer->inicioOrdenada == NULL){//eh o primeiro a ser inserido
            pBuffer->inicioOrdenada = novo;
            pBuffer->fimOrdenada = novo;
        }
        else if((pBuffer->contadorOrdenada == 1) && (strcmp(novo->dados.nome, pBuffer->inicioOrdenada->dados.nome) < 0)){ //insere no inicio, so tem um elemento
            pBuffer->inicioOrdenada->anterior = novo;                                
            novo->prox = pBuffer->inicioOrdenada;                                   
            pBuffer->inicioOrdenada = novo;                                          
        }
        else if((pBuffer->contadorOrdenada >= 1) && (strcmp(novo->dados.nome, pBuffer->fimOrdenada->dados.nome) >= 0)){ //insere no fim
            novo->anterior = pBuffer->fimOrdenada;
            pBuffer->fimOrdenada->prox = novo;
            pBuffer->fimOrdenada = novo;  
        }
        else{
            for(pBuffer->i = pBuffer->contadorOrdenada; (pBuffer->i > 0) && (strcmp(novo->dados.nome, pBuffer->fimOrdenadaCopia->dados.nome) < 0 ); pBuffer->i -= 1){ 
                if(pBuffer->i == pBuffer->contadorOrdenada){ //novo sera o penultimo elemento
                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;        
                    pBuffer->aux2->prox = novo;                                 
                    novo->anterior = pBuffer->aux2;                             
                    pBuffer->fimOrdenadaCopia->anterior = novo;                                     
                    novo->prox = pBuffer->fimOrdenadaCopia;                     
                    pBuffer->fimOrdenada = pBuffer->fimOrdenadaCopia;            
                }
                else if(pBuffer->i == 1){ //novo sera o primeiro elemento
                    pBuffer->aux2 = novo->prox;                                 
                    pBuffer->aux2->anterior = novo->anterior;                                       
                    novo->prox->anterior = pBuffer->aux2->anterior;
                    novo->anterior->prox = pBuffer->aux2;
                    novo->anterior->anterior = novo;
                    novo->prox = pBuffer->aux2->anterior;
                    novo->anterior = NULL;
                    pBuffer->inicioOrdenada = novo;                             
                }
                else{ //novo fica em qualquer lugar entre o segundo e o penultimo elemento
                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;
                    pBuffer->aux2->prox = novo;                    
                    novo->anterior = pBuffer->aux2;                    
                    pBuffer->aux2 = novo->prox;
                    pBuffer->aux2->anterior = pBuffer->fimOrdenadaCopia;                    
                    pBuffer->fimOrdenadaCopia->prox = pBuffer->aux2;
                    pBuffer->fimOrdenadaCopia->anterior = novo; 
                    novo->prox = pBuffer->fimOrdenadaCopia;
                }
                pBuffer->fimOrdenadaCopia = novo->anterior;
            }
        }
        
        pBuffer->contadorOrdenada += 1;    
    }  
}

void ordenaAlfabeticaDecrescente(Controle *pBuffer){
    for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){
        Nodo *novo;
        novo = (Nodo *)malloc(sizeof(Nodo));
        novo->anterior = NULL;
        novo->prox = NULL;

        if(novo == NULL){ //verifica se conseguiu alocar 
            printf("Erro!"); 
            exit(1); 
        }
    
        novo->dados = pBuffer->percorrer->dados; 
        
        pBuffer->fimOrdenadaCopia = pBuffer->fimOrdenada;
        
        if(pBuffer->inicioOrdenada == NULL){//eh o primeiro a ser inserido
            pBuffer->inicioOrdenada = novo;
            pBuffer->fimOrdenada = novo;
        }
        else if((pBuffer->contadorOrdenada == 1) && (strcmp(novo->dados.nome, pBuffer->inicioOrdenada->dados.nome) > 0)){ //insere no inicio, so tem um elemento
            pBuffer->inicioOrdenada->anterior = novo;                                
            novo->prox = pBuffer->inicioOrdenada;                                   
            pBuffer->inicioOrdenada = novo;                                         
        }
        else if((pBuffer->contadorOrdenada >= 1) && (strcmp(novo->dados.nome, pBuffer->fimOrdenada->dados.nome) <= 0)){ //insere no fim
            novo->anterior = pBuffer->fimOrdenada;
            pBuffer->fimOrdenada->prox = novo;
            pBuffer->fimOrdenada = novo;  
        }
        else{
            for(pBuffer->i = pBuffer->contadorOrdenada; (pBuffer->i > 0) && (strcmp(novo->dados.nome, pBuffer->fimOrdenadaCopia->dados.nome) > 0 ); pBuffer->i -= 1){ 
                if(pBuffer->i == pBuffer->contadorOrdenada){ //novo sera o penultimo elemento
                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;        
                    pBuffer->aux2->prox = novo;                                                    
                    novo->anterior = pBuffer->aux2;                                               
                    pBuffer->fimOrdenadaCopia->anterior = novo;                
                    novo->prox = pBuffer->fimOrdenadaCopia;                    
                    pBuffer->fimOrdenada = pBuffer->fimOrdenadaCopia;            
                }
                else if(pBuffer->i == 1){ //novo sera o primeiro elemento
                    pBuffer->aux2 = novo->prox;                                 
                    pBuffer->aux2->anterior = novo->anterior;                                      
                    novo->prox->anterior = pBuffer->aux2->anterior;
                    novo->anterior->prox = pBuffer->aux2;
                    novo->anterior->anterior = novo;
                    novo->prox = pBuffer->aux2->anterior;
                    novo->anterior = NULL;                    
                    pBuffer->inicioOrdenada = novo;                             
                }
                else{ //novo fica em qualquer lugar entre o primeiro e o penultimo elemento
                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;
                    pBuffer->aux2->prox = novo;                    
                    novo->anterior = pBuffer->aux2; 
                    pBuffer->aux2 = novo->prox;
                    pBuffer->aux2->anterior = pBuffer->fimOrdenadaCopia;
                    pBuffer->fimOrdenadaCopia->prox = pBuffer->aux2;
                    pBuffer->fimOrdenadaCopia->anterior = novo; 
                    novo->prox = pBuffer->fimOrdenadaCopia;
                }
                pBuffer->fimOrdenadaCopia = novo->anterior;
            }
        }
        
        pBuffer->contadorOrdenada += 1;    
    }  
}


void ordenaIdade(Controle *pBuffer){
    for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){
        Nodo *novo;
        novo = (Nodo *)malloc(sizeof(Nodo));
        novo->anterior = NULL;
        novo->prox = NULL;

        if(novo == NULL){ //verifica se conseguiu alocar 
            printf("Erro!"); 
            exit(1); 
        }
    
        novo->dados = pBuffer->percorrer->dados;  

        pBuffer->fimOrdenadaCopia = pBuffer->fimOrdenada;

        if(pBuffer->inicioOrdenada == NULL){//eh o primeiro a ser inserido
            pBuffer->inicioOrdenada = novo;
            pBuffer->fimOrdenada = novo;
        }
        else if((pBuffer->contadorOrdenada == 1) && (novo->dados.idade < pBuffer->inicioOrdenada->dados.idade)){ //insere no inicio, so tem um elemento
            pBuffer->inicioOrdenada->anterior = novo;                                
            novo->prox = pBuffer->inicioOrdenada;                                   
            pBuffer->inicioOrdenada = novo;                                         
        }
        else if((pBuffer->contadorOrdenada >= 1) && (novo->dados.idade >= pBuffer->fimOrdenada->dados.idade)){ //insere no fim
            novo->anterior = pBuffer->fimOrdenada;
            pBuffer->fimOrdenada->prox = novo;
            pBuffer->fimOrdenada = novo;  
        }
        else{
            for(pBuffer->i = pBuffer->contadorOrdenada; (pBuffer->i > 0) && (novo->dados.idade < pBuffer->fimOrdenadaCopia->dados.idade); pBuffer->i -= 1){ 
                if(pBuffer->i == pBuffer->contadorOrdenada){ //novo sera o penultimo elemento
                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;        
                    pBuffer->aux2->prox = novo;                                 
                    novo->anterior = pBuffer->aux2;                             
                    pBuffer->fimOrdenadaCopia->anterior = novo;                                     
                    novo->prox = pBuffer->fimOrdenadaCopia;                     
                    pBuffer->fimOrdenada = pBuffer->fimOrdenadaCopia;           
                }
                else if(pBuffer->i == 1){ //novo sera o primeiro elemento
                    pBuffer->aux2 = novo->prox;                                 
                    pBuffer->aux2->anterior = novo->anterior;                                       
                    novo->prox->anterior = pBuffer->aux2->anterior;
                    novo->anterior->prox = pBuffer->aux2;
                    novo->anterior->anterior = novo;
                    novo->prox = pBuffer->aux2->anterior;
                    novo->anterior = NULL;
                    pBuffer->inicioOrdenada = novo;                             
                }
                else{ //novo fica em qualquer lugar entre o primeiro e o penultimo
                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;
                    pBuffer->aux2->prox = novo;                    
                    novo->anterior = pBuffer->aux2;                    
                    pBuffer->aux2 = novo->prox;
                    pBuffer->aux2->anterior = pBuffer->fimOrdenadaCopia;                    
                    pBuffer->fimOrdenadaCopia->prox = pBuffer->aux2;
                    pBuffer->fimOrdenadaCopia->anterior = novo;                     
                    novo->prox = pBuffer->fimOrdenadaCopia;
                }
                pBuffer->fimOrdenadaCopia = novo->anterior;
            }
        }
        
        pBuffer->contadorOrdenada += 1;    
    }  
}


void ordenaIdadeDecrecente(Controle *pBuffer){
    for(pBuffer->percorrer = pBuffer->inicio; pBuffer->percorrer != NULL; pBuffer->percorrer = pBuffer->percorrer->prox){
        Nodo *novo;
        novo = (Nodo *)malloc(sizeof(Nodo));
        novo->anterior = NULL;
        novo->prox = NULL;

        if(novo == NULL){ //verifica se conseguiu alocar 
            printf("Erro!"); 
            exit(1); 
        }
    
        novo->dados = pBuffer->percorrer->dados; 
        
        pBuffer->fimOrdenadaCopia = pBuffer->fimOrdenada;

        if(pBuffer->inicioOrdenada == NULL){//eh o primeiro a ser inserido
            pBuffer->inicioOrdenada = novo;
            pBuffer->fimOrdenada = novo;
        }        
        else if((pBuffer->contadorOrdenada == 1) && (novo->dados.idade > pBuffer->inicioOrdenada->dados.idade)){ //insere no inicio, so tem um elemento
            pBuffer->inicioOrdenada->anterior = novo;                                
            novo->prox = pBuffer->inicioOrdenada;                                   
            pBuffer->inicioOrdenada = novo;                                          
        }
        else if((pBuffer->contadorOrdenada >= 1) && (novo->dados.idade <= pBuffer->fimOrdenada->dados.idade)){ //insere no fim
            novo->anterior = pBuffer->fimOrdenada;
            pBuffer->fimOrdenada->prox = novo;
            pBuffer->fimOrdenada = novo;  
        }
        else{ 
            for(pBuffer->i = pBuffer->contadorOrdenada; (pBuffer->i > 0) && (novo->dados.idade > pBuffer->fimOrdenadaCopia->dados.idade); pBuffer->i -= 1){ 
                if(pBuffer->i == pBuffer->contadorOrdenada){ //novo sera o penultimo elemento
                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;        
                    pBuffer->aux2->prox = novo;                                 
                    novo->anterior = pBuffer->aux2;                             
                    pBuffer->fimOrdenadaCopia->anterior = novo;                                     
                    novo->prox = pBuffer->fimOrdenadaCopia;                     
                    pBuffer->fimOrdenada = pBuffer->fimOrdenadaCopia;           
                }
                else if(pBuffer->i == 1){ //novo sera o primeiro elemento
                    pBuffer->aux2 = novo->prox;                                 
                    pBuffer->aux2->anterior = novo->anterior;               
                    novo->prox->anterior = pBuffer->aux2->anterior;
                    novo->anterior->prox = pBuffer->aux2;
                    novo->anterior->anterior = novo;
                    novo->prox = pBuffer->aux2->anterior;
                    novo->anterior = NULL;
                    pBuffer->inicioOrdenada = novo;                             
                }
                else{ //novo fica em qualquer lugar entre o primeiro e o penultimo elemento
                    pBuffer->aux2 = pBuffer->fimOrdenadaCopia->anterior;
                    pBuffer->aux2->prox = novo;
                    novo->anterior = pBuffer->aux2;                  
                    pBuffer->aux2 = novo->prox;
                    pBuffer->aux2->anterior = pBuffer->fimOrdenadaCopia;                    
                    pBuffer->fimOrdenadaCopia->prox = pBuffer->aux2;
                    pBuffer->fimOrdenadaCopia->anterior = novo;                     
                    novo->prox = pBuffer->fimOrdenadaCopia;
                }
                pBuffer->fimOrdenadaCopia = novo->anterior;
            }
        }
        
        pBuffer->contadorOrdenada += 1;    
    }      
}


int main(){
    Controle *pBuffer;
    pBuffer = malloc(sizeof(Controle));

    if(pBuffer == NULL){ //verifica se conseguiu alocar 
        printf("Erro!"); 
        exit(1); 
    }

    pBuffer->contador = 0;
    pBuffer->contadorOrdenada = 0;
    pBuffer->inicio = NULL;
    pBuffer->fim = NULL;
    pBuffer->inicioOrdenada = NULL;
    pBuffer->fimOrdenada = NULL;
    
    do{
        pBuffer->percorrer = NULL;
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
            
            case '4': //escolha do metodo de ordenação, gera a fila e mostra os dados da agenda 
                pBuffer->inicioOrdenada = NULL;
                pBuffer->fimOrdenada = NULL;
                pBuffer->contadorOrdenada = 0;  
                
                printf("Escolha o parâmetro de ordenação desejado:\n"); 
                printf(" 1)Ordenação por ordem de inserção\n 2)Ordenação por ordem alfabética crescente\n 3)Ordenação por ordem alfabética decrescente\n 4)Ordenação por idade crescente\n 5)Ordenação por idade decrescente\n");
                scanf("%d", &pBuffer->i);
                
                switch (pBuffer->i){
                    case 1:
                        ordenaI(pBuffer);
                        break;
                    case 2:
                        ordenaAlfabetica(pBuffer);
                        break;
                    case 3:
                        ordenaAlfabeticaDecrescente(pBuffer);
                        break;
                    case 4:
                        ordenaIdade(pBuffer);
                        break;
                    case 5:
                        ordenaIdadeDecrecente(pBuffer);
                        break;
                }

                imprimir(pBuffer);
                
                pBuffer->aux = pBuffer->inicioOrdenada;
                while(pBuffer->aux != NULL){ //limpa a fila
                    pBuffer->aux3 = pBuffer->aux;
                    pBuffer->aux = pBuffer->aux->prox;
                    free(pBuffer->aux3);
                }
                break;    
            
            case '5':
                pBuffer->aux = pBuffer->inicio;
                while(pBuffer->aux != NULL){ //limpa lista
                    pBuffer->aux2 = pBuffer->aux;
                    pBuffer->aux = pBuffer->aux->prox;
                    free(pBuffer->aux2);
                }
                free(pBuffer);                
                exit(1);
            
            default: 
                printf("Opção inexistente\n");
        }

    }while(getchar());

    exit(0);
}
