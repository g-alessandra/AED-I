#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Nodo{ 
    int conteudo;
    struct Nodo *esq, *dir;
}Nodo;

int Altura(Nodo* raiz){ 
    int iEsq, iDir;
    if (raiz == NULL){ 
        return 0;
    }
    
    iEsq = Altura(raiz->esq);  
    iDir = Altura(raiz->dir); 
    
    if(iEsq > iDir){  
        return iEsq + 1;
    }
    else{
        return iDir + 1;
    }
}

int FB (Nodo* raiz){ 
    if(raiz == NULL){ 
        return 0;
    }
    return Altura(raiz->esq) -Altura(raiz->dir);
}

void RSE(Nodo **raizP){ 
    Nodo *pAux;
    pAux = (*raizP)->dir;
    (*raizP)->dir = pAux->esq;
    pAux->esq = (*raizP);
    (*raizP) = pAux;
}

void RSD(Nodo **raizP){ 
    Nodo *pAux;
    pAux = (*raizP)->esq;
    (*raizP)->esq = pAux->dir;
    pAux->dir = (*raizP);
    (*raizP) = pAux;
}

int BalancearEsquerda(Nodo **raizP){
    int fbe = FB ((*raizP)->esq);
    if ( fbe > 0 ){
        RSD(raizP);
        return 1;
    }
    else if (fbe < 0 ){ //Rotação Dupla Direita
        RSE( &((*raizP)->esq));
        RSD( raizP ); 
        return 1;
    }
    return 0;
}

int BalancearDireita(Nodo **raizP){
    int fbd = FB( (*raizP)->dir);
    if ( fbd < 0 ){
        RSE (raizP); 
        return 1;
    }
    else if (fbd > 0 ){ //Rotação Dupla Esquerda
    RSD( &((*raizP)->dir) );
    RSE( raizP );
        return 1;
    }
    return 0;
}

int Balanceamento(Nodo **raizP){ 
    int fb = FB(*raizP); 
    if ( fb > 1){
        return BalancearEsquerda(raizP);
    }
    else if (fb < -1 ){
        return BalancearDireita(raizP);
    }
    else{
        return 0;
    }
}

int insere(Nodo **raizP, int infoNodo){
    if (*raizP == NULL){ //insere o primeiro nodo
        *raizP = (Nodo*)malloc(sizeof(Nodo));
        (*raizP)->conteudo = infoNodo;
        (*raizP)->esq = NULL;
        (*raizP)->dir = NULL;
        return 1;
    }
    else if ( (*raizP)->conteudo > infoNodo){ //insere esq
        if ( insere(&(*raizP)->esq,infoNodo)){
            if (Balanceamento(raizP)){
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    else if ( (*raizP)->conteudo < infoNodo){ //insere dir
        if ( insere(&(*raizP)->dir,infoNodo) ){
            if (Balanceamento(raizP)){
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            return 0;
        }
    }
    else{ //ja existe um nodo com esse valor
        return 0; 
    }
}

void imprime(Nodo *raiz){ 
    if(raiz != NULL){
        printf("%d(", raiz->conteudo);
        imprime(raiz->esq);
        imprime(raiz->dir);
        printf(")");   
    }
}

void limpa(Nodo *raiz){ 
    if(raiz != NULL){
        limpa(raiz->esq);
        limpa(raiz->dir);
        free(raiz);
    }
}

int menor(Nodo *atual){ 
    Nodo *n = atual;
    Nodo *n2 = atual->esq;
    while (n2 != NULL){
        n = n2;
        n2 = n2->esq;
    }
    return n->conteudo;
}

int remover(Nodo **raizP, int infoNodo){  
    Nodo *removido = NULL;
    if(*raizP == NULL){ 
        printf("Não encontrado!\n");
        return 0;
    }
    
    if((*raizP)->conteudo > infoNodo){ 
        if(remover(&(*raizP)->esq,infoNodo) == 1){
            Balanceamento(raizP);
        }
    }
    if((*raizP)->conteudo < infoNodo){
        if(remover(&(*raizP)->dir,infoNodo) == 1){
            Balanceamento(raizP);
        }   
    }

    if((*raizP)->conteudo == infoNodo){ 
        if((*raizP)->esq == NULL || (*raizP)->dir == NULL){//tem 0 ou 1 filho
            removido = *raizP;
            if((*raizP)->esq != NULL){   
                (*raizP) =(*raizP)->esq;
            }
            else{
                (*raizP) = (*raizP)->dir;
            }
            free(removido);
        }
        else{//tem 2 filhos
            (*raizP)->conteudo = menor((*raizP)->dir); 
            remover(&(*raizP)->dir, (*raizP)->conteudo); 
            Balanceamento(raizP);
        }
        return 1;
    }

}

void caso1(Nodo *raiz){
    printf("____________________Caso 1____________________\n");

    int numNodo, infoNodo;
    srand(time(0));

    printf("Informe quantos nodos deseja adicionar: "); 
    scanf("%d", &numNodo);
        
    for(int i = 0; i < numNodo; i++){
        infoNodo = rand()%1000;
        insere(&raiz, infoNodo);
    }

    imprime(raiz);

    if(raiz == NULL){
        printf("Arvore Vazia! \n");
    }
    else if(FB(raiz) >= -1 && FB(raiz)<=1){
        printf("\nEh Arvore AVL \n\n");
    }
    else{
        printf("\nNao eh arvore AVL \n\n");
    }

    limpa(raiz);    
}

void caso2(Nodo *raiz){ 
    printf("____________________Caso 2____________________\n");  
    raiz = NULL;                                                
    printf("Inserindo 15 - Caso 1");                            
    insere(&raiz, 20);                                          
    insere(&raiz, 4);
    printf("\nArvore antes de inserir: ");
    imprime(raiz);
    insere(&raiz, 15);
    printf("\nArvore depois de inserir: ");
    imprime(raiz);
    limpa(raiz);
    printf("\n\n");

    raiz = NULL;
    printf("Inserindo 15 - Caso 2");
    insere(&raiz, 20);
    insere(&raiz, 4);
    insere(&raiz, 26);
    insere(&raiz, 9);
    insere(&raiz, 3);
    printf("\nArvore antes de inserir: ");
    imprime(raiz);
    insere(&raiz, 15);
    printf("\nArvore depois de inserir: ");
    imprime(raiz);
    limpa(raiz);
    printf("\n\n");

    raiz = NULL;
    printf("Inserindo 15 - Caso 3");
    insere(&raiz, 20);
    insere(&raiz, 4);
    insere(&raiz, 26);
    insere(&raiz, 9);
    insere(&raiz, 3);
    insere(&raiz, 21);
    insere(&raiz, 30);
    insere(&raiz, 2);
    insere(&raiz, 7);
    insere(&raiz, 11);    
    printf("\nArvore antes de inserir: ");
    imprime(raiz);
    insere(&raiz, 15);
    printf("\nArvore depois de inserir: ");
    imprime(raiz);
    limpa(raiz);
    printf("\n\n");

    raiz = NULL;
    printf("Inserindo 8 - Caso 1");
    insere(&raiz, 20);
    insere(&raiz, 4);
    printf("\nArvore antes de inserir: ");
    imprime(raiz);
    insere(&raiz, 8);
    printf("\nArvore depois de inserir: ");
    imprime(raiz);
    limpa(raiz);
    printf("\n\n");

    raiz = NULL;
    printf("Inserindo 8 - Caso 2");
    insere(&raiz, 20);
    insere(&raiz, 4);
    insere(&raiz, 26);
    insere(&raiz, 9);
    insere(&raiz, 3);
    printf("\nArvore antes de inserir: ");
    imprime(raiz);
    insere(&raiz, 8);
    printf("\nArvore depois de inserir: ");
    imprime(raiz);
    limpa(raiz);
    printf("\n\n");

    raiz = NULL;
    printf("Inserindo 8 - Caso 3");
    insere(&raiz, 20);
    insere(&raiz, 4);
    insere(&raiz, 26);
    insere(&raiz, 9);
    insere(&raiz, 3);
    insere(&raiz, 21);
    insere(&raiz, 30);
    insere(&raiz, 2);
    insere(&raiz, 7);
    insere(&raiz, 11);    
    printf("\nArvore antes de inserir: ");
    imprime(raiz);
    insere(&raiz, 8);
    printf("\nArvore depois de inserir: ");
    imprime(raiz);
    limpa(raiz);
    printf("\n\n");

    raiz = NULL;
    printf("Removendo 1 - Caso 1");
    insere(&raiz, 2);
    insere(&raiz, 1);
    insere(&raiz, 4);
    insere(&raiz, 3);
    insere(&raiz, 5);
    printf("\nArvore antes de remover: ");
    imprime(raiz);
    remover(&raiz, 1);
    printf("\nArvore depois de remover: ");
    imprime(raiz);
    limpa(raiz);
    printf("\n\n");

    raiz = NULL;
    printf("Removendo 1 - Caso 2");
    insere(&raiz, 6);
    insere(&raiz, 2);
    insere(&raiz, 9);
    insere(&raiz, 1);
    insere(&raiz, 8);    
    insere(&raiz, 4);
    insere(&raiz, 11);
    insere(&raiz, 3);
    insere(&raiz, 7);
    insere(&raiz, 5);
    insere(&raiz, 12);
    insere(&raiz, 10);
    insere(&raiz, 13);
    printf("\nArvore antes de remover: ");
    imprime(raiz);
    remover(&raiz, 1);
    printf("\nArvore depois de remover: ");
    imprime(raiz);
    limpa(raiz);
    printf("\n\n");

    raiz = NULL;
    printf("Removendo 1 - Caso 3");
    insere(&raiz, 5);
    insere(&raiz, 2);
    insere(&raiz, 8);
    insere(&raiz, 1);
    insere(&raiz, 3);    
    insere(&raiz, 7);
    insere(&raiz, 10);
    insere(&raiz, 4);
    insere(&raiz, 6);
    insere(&raiz, 11);
    insere(&raiz, 9);
    insere(&raiz, 12);
    printf("\nArvore antes de remover: ");
    imprime(raiz);
    remover(&raiz, 1);
    printf("\nArvore depois de remover: ");
    imprime(raiz);
    limpa(raiz);
    printf("\n\n");
}

int main(){
    Nodo *raiz = NULL; 
        
    do{ 
        raiz = NULL;
        printf("MENU:\n 1.Primeiro Cenário\n 2.Segundo Cenário\n 3.Sair\n"); 
        switch (getchar()){
            case '1':
                caso1(raiz);
                break;
            case '2':
                caso2(raiz);
                break;
            case '3':
                exit(1);
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    
    }while(getchar());
    
    exit (0);
}
