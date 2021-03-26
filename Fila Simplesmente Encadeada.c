#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_STR 80

typedef char texto_t[TAM_STR];

typedef struct Contato_T
{
    int id;
    texto_t nome;
    texto_t endereco;
    texto_t telefone_res;
    texto_t telefone_cel;
    texto_t data_nascimento;
} Contato;

Contato* criarContato()
{
    Contato *contato = (Contato *) malloc(sizeof(Contato));
    printf("Identificador: ");
    scanf("%d", &contato->id);
    return contato;
}

void mostrarContato(Contato *contato)
{
    printf("Identificador: %d\n", contato->id);
}

typedef Contato TipoItem;

typedef struct Celula_T {
    TipoItem *item;
    struct Celula_T *proximo;
} Celula;

Celula* criarCelula (TipoItem *item, Celula *ant, Celula *prox)
{
    Celula *celula = (Celula *) malloc(sizeof(Celula));

    if (celula != NULL) 
    { 
        celula->item = item;
        celula->proximo = prox;
    }
    return celula;
}

typedef struct FilaUnica_T
{
    Celula *primeiro; 
    Celula *ultimo;    
    int quantos;   
} FilaUnica;

FilaUnica* criarFilaUnica()
{
    FilaUnica *fila = (FilaUnica *) malloc(sizeof(FilaUnica));

    if (fila != NULL) 
    {
        fila->primeiro = fila->ultimo = NULL;
        fila->quantos = 0;   
    }        
    return fila;
}

int estah_vazia(FilaUnica *fila)
{
    if ((fila == NULL) || (fila->quantos == 0))
        return 1;

    return 0;
}

int item_ehIgual(TipoItem *item1, TipoItem *item2)
{
    if ((item1 != NULL) && (item2 != NULL) && (item1->id == item2->id))
        return 1;

    return 0;
}

int inserir(FilaUnica *fila, TipoItem *item)
{
    if (fila == NULL) 
        return 0;
    else 
    {
        Celula *novo = criarCelula(item, fila->ultimo, NULL);

        if (novo == NULL)
            return 0;   

        if (estah_vazia(fila) == 1)
            fila->primeiro = fila->ultimo = novo;
        else {
            fila->ultimo->proximo = novo;
            fila->ultimo = novo;
        }
        fila->quantos++;
        return 1;
    }
}

TipoItem* excluir(FilaUnica *fila)
{
    if ((fila == NULL) || (estah_vazia(fila) == 1))
        return NULL;

    Celula *aux = fila->primeiro;
    fila->primeiro = aux->proximo;
    fila->quantos--;
    TipoItem *dado = aux->item;

    free(aux);
    return dado;
}

int tamanho(FilaUnica *fila){
    
    if (fila == NULL)
        return 0;

    return fila->quantos;
}

TipoItem** obterArray(FilaUnica *fila)
{
    TipoItem **array = (TipoItem**) malloc(tamanho(fila) * sizeof(TipoItem*));

    Celula *aux = fila->primeiro;
    for (int i = 0; i < tamanho(fila); i++)
    {
        array[i] = aux->item;
        aux = aux->proximo;
    }
    return array;
}

int menu ()
{
    int opcao;
    
    printf("\n1. Adicionar\n");
    printf("2. Remover\n");
    printf("3. Listar todos\n");
    printf("4. Sair\n");
    printf("\nOpcao: ");

    scanf("%d", &opcao);
    fflush(stdin);
    return opcao;
}

int main()
{
    int opcao = 4;
    FilaUnica *fila = criarFilaUnica();
    Contato *contato;
    int id; 

    // CARREGAR DADOS DO ARQUIVO - NA LISTA

    do {
        opcao = menu();

        switch(opcao)
        {
            case 1: printf("\n### ADICIONAR ####\n"); contato = criarContato(); inserir(fila, contato); break;

            case 2: printf("\n### REMOVER ####\n"); contato = excluir(fila);
             if (contato != NULL) 
                {
                    printf("*** Contato Excluido ***\n");
                    mostrarContato(contato);
                }
                else
                    printf("Excluir:: Sem contatos para excluir\n\n", id);
                    break;

            case 3: 
                printf("\n### LISTAR ####\n");
                Contato **contatos = obterArray(fila);
                for (int i = 0; i < tamanho(fila); i++) 
                {
                    printf("**************************\n");
                    mostrarContato(contatos[i]);
                }
            break;

            case 4: printf("\n### SAIR ####\n"); exit(1); break;                                                            
        }
        system("pause");
        system("cls");
    } 
    while(opcao != 4);
    // GRAVAR DADOS (DA LISTA) NO ARQUIVO (APAGANDO O ARQUIVO)
     return 0;
}