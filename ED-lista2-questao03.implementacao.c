/*
** Função : Sistema de Registro de Estudantes
** Autor : Erick e Daysila
** Data : 18/06/2025
** Observações: Implementação do Sistema de Registro de Estudantes
*/

#include "estudante.h"


ListaEstudantes* criarLista() {
    ListaEstudantes *lista = (ListaEstudantes*)malloc(sizeof(ListaEstudantes));
    if (lista == NULL) {
        printf("Error\n");
        return NULL;
    }
    lista->inicio = NULL;
    lista->tamanho = 0;
    return lista;
}

void adicionarEstudante(ListaEstudantes *lista, Estudante estudante) {
    NoLista *novoNo = (NoLista*)malloc(sizeof(NoLista));
    if (novoNo == NULL) {
        printf("Error\n");
        return;
    }
    
    novoNo->estudante = estudante;
    novoNo->proximo = lista->inicio;
    lista->inicio = novoNo;
    lista->tamanho++;
    
    printf("Estudante %s adicionado com sucesso!\n", estudante.nome);
}

int removerEstudante(ListaEstudantes *lista, int matricula) {
    NoLista *atual = lista->inicio;
    NoLista *anterior = NULL;
    
    while (atual != NULL) {
        if (atual->estudante.matricula == matricula) {
            if (anterior == NULL) {
                lista->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            printf("Estudante %s removido!\n", atual->estudante.nome);
            free(atual);
            lista->tamanho--;
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("Estudante nao encontrado!\n");
    return 0;
}

Estudante* buscarEstudante(ListaEstudantes *lista, int matricula) {
    NoLista *atual = lista->inicio;
    
    while (atual != NULL) {
        if (atual->estudante.matricula == matricula) {
            return &(atual->estudante);
        }
        atual = atual->proximo;
    }
    
    return NULL;
}

void listarEstudantes(ListaEstudantes *lista) {
    printf("\n=== LISTA DE ESTUDANTES ===\n");
    if (lista->tamanho == 0) {
        printf("Nenhum estudante cadastrado.\n");
        return;
    }
    
    NoLista *atual = lista->inicio;
    int i = 1;
    
    while (atual != NULL) {
        printf("%d. Nome: %s\n", i, atual->estudante.nome);
        printf("   Matricula: %d\n", atual->estudante.matricula);
        printf("   Notas: %.2f, %.2f, %.2f\n", 
               atual->estudante.notas[0], 
               atual->estudante.notas[1], 
               atual->estudante.notas[2]);
        printf("   Media: %.2f\n", calcularMedia(atual->estudante));
        printf("   ---\n");
        atual = atual->proximo;
        i++;
    }
    printf("Total: %d estudantes\n", lista->tamanho);
}

void liberarLista(ListaEstudantes *lista) {
    NoLista *atual = lista->inicio;
    while (atual != NULL) {
        NoLista *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

//pilha

PilhaHistorico* criarPilha() {
    PilhaHistorico *pilha = (PilhaHistorico*)malloc(sizeof(PilhaHistorico));
    if (pilha == NULL) {
        printf("Error\n");
        return NULL;
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

void empilharHistorico(PilhaHistorico *pilha, HistoricoNota historico) {
    NoPilha *novoNo = (NoPilha*)malloc(sizeof(NoPilha));
    if (novoNo == NULL) {
        printf("Error\n");
        return;
    }
    
    novoNo->historico = historico;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
    pilha->tamanho++;
}

int desempilharHistorico(PilhaHistorico *pilha, HistoricoNota *historico) {
    if (pilha->topo == NULL) {
        printf("A pilha está vazia!\n");
        return 0;
    }
    
    NoPilha *topo = pilha->topo;
    *historico = topo->historico;
    pilha->topo = topo->proximo;
    free(topo);
    pilha->tamanho--;
    return 1;
}

void mostrarHistorico(PilhaHistorico *pilha) {
    printf("\n=== HISTORICO DE NOTAS ===\n");
    if (pilha->tamanho == 0) {
        printf("Nenhum historico disponivel.\n");
        return;
    }
    
    NoPilha *atual = pilha->topo;
    int i = 1;
    
    while (atual != NULL) {
        printf("%d. Matricula: %d\n", i, atual->historico.matricula);
        printf("   Disciplina: %d\n", atual->historico.disciplina);
        printf("   Nota anterior: %.2f\n", atual->historico.notaAnterior);
        printf("   ---\n");
        atual = atual->proximo;
        i++;
    }
}

void liberarPilha(PilhaHistorico *pilha) {
    NoPilha *atual = pilha->topo;
    while (atual != NULL) {
        NoPilha *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(pilha);
}

// fila

FilaMatricula* criarFila() {
    FilaMatricula *fila = (FilaMatricula*)malloc(sizeof(FilaMatricula));
    if (fila == NULL) {
        printf("Erro ao criar fila!\n");
        return NULL;
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

void adicionarNaFila(FilaMatricula *fila, int matricula, char *disciplina) {
    NoFila *novoNo = (NoFila*)malloc(sizeof(NoFila));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }
    
    novoNo->matricula = matricula;
    strcpy(novoNo->disciplina, disciplina);
    novoNo->proximo = NULL;
    
    if (fila->fim == NULL) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    } else {
        fila->fim->proximo = novoNo;
        fila->fim = novoNo;
    }
    
    fila->tamanho++;
    printf("Estudante %d adicionado na fila para %s\n", matricula, disciplina);
}

int removerDaFila(FilaMatricula *fila, int *matricula, char *disciplina) {
    if (fila->inicio == NULL) {
        printf("Fila vazia!\n");
        return 0;
    }
    
    NoFila *primeiro = fila->inicio;
    *matricula = primeiro->matricula;
    strcpy(disciplina, primeiro->disciplina);
    
    fila->inicio = primeiro->proximo;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    printf("Estudante %d matriculado em %s\n", *matricula, disciplina);
    free(primeiro);
    fila->tamanho--;
    return 1;
}

void mostrarFila(FilaMatricula *fila) {
    printf("\n=== FILA DE MATRICULA ===\n");
    if (fila->tamanho == 0) {
        printf("Fila vazia.\n");
        return;
    }
    
    NoFila *atual = fila->inicio;
    int i = 1;
    
    while (atual != NULL) {
        printf("%d. Matricula: %d - Disciplina: %s\n", 
               i, atual->matricula, atual->disciplina);
        atual = atual->proximo;
        i++;
    }
    printf("Total na fila: %d\n", fila->tamanho);
}

void liberarFila(FilaMatricula *fila) {
    NoFila *atual = fila->inicio;
    while (atual != NULL) {
        NoFila *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(fila);
}

//deque
DequeAtendimento* criarDeque() {
    DequeAtendimento *deque = (DequeAtendimento*)malloc(sizeof(DequeAtendimento));
    if (deque == NULL) {
        printf("Error\n");
        return NULL;
    }
    deque->inicio = NULL;
    deque->fim = NULL;
    deque->tamanho = 0;
    return deque;
}

void adicionarInicioDeque(DequeAtendimento *deque, int matricula, char *motivo) {
    NoDeque *novoNo = (NoDeque*)malloc(sizeof(NoDeque));
    if (novoNo == NULL) {
        printf("Error\n");
        return;
    }
    
    novoNo->matricula = matricula;
    strcpy(novoNo->motivo, motivo);
    novoNo->anterior = NULL;
    novoNo->proximo = deque->inicio;
    
    if (deque->inicio == NULL) {
        deque->fim = novoNo;
    } else {
        deque->inicio->anterior = novoNo;
    }
    
    deque->inicio = novoNo;
    deque->tamanho++;
    printf("Estudante %d adicionado no inicio da fila\n", matricula);
}

void adicionarFimDeque(DequeAtendimento *deque, int matricula, char *motivo) {
    NoDeque *novoNo = (NoDeque*)malloc(sizeof(NoDeque));
    if (novoNo == NULL) {
        printf("Error\n");
        return;
    }
    
    novoNo->matricula = matricula;
    strcpy(novoNo->motivo, motivo);
    novoNo->proximo = NULL;
    novoNo->anterior = deque->fim;
    
    if (deque->fim == NULL) {
        deque->inicio = novoNo;
    } else {
        deque->fim->proximo = novoNo;
    }
    
    deque->fim = novoNo;
    deque->tamanho++;
    printf("Estudante %d adicionado no fim da fila\n", matricula);
}

int removerInicioDeque(DequeAtendimento *deque, int *matricula, char *motivo) {
    if (deque->inicio == NULL) {
        printf("Deque vazio!\n");
        return 0;
    }
    
    NoDeque *primeiro = deque->inicio;
    *matricula = primeiro->matricula;
    strcpy(motivo, primeiro->motivo);
    
    deque->inicio = primeiro->proximo;
    if (deque->inicio == NULL) {
        deque->fim = NULL;
    } else {
        deque->inicio->anterior = NULL;
    }
    
    printf("Estudante %d atendido\n", *matricula);
    free(primeiro);
    deque->tamanho--;
    return 1;
}

int removerFimDeque(DequeAtendimento *deque, int *matricula, char *motivo) {
    if (deque->fim == NULL) {
        printf("Deque vazio!\n");
        return 0;
    }
    
    NoDeque *ultimo = deque->fim;
    *matricula = ultimo->matricula;
    strcpy(motivo, ultimo->motivo);
    
    deque->fim = ultimo->anterior;
    if (deque->fim == NULL) {
        deque->inicio = NULL;
    } else {
        deque->fim->proximo = NULL;
    }
    
    printf("Estudante %d atendido (removido do fim do deque)\n", *matricula);
    free(ultimo);
    deque->tamanho--;
    return 1;
}

void mostrarDeque(DequeAtendimento *deque) {
    printf("\n=== FILA DE ATENDIMENTO ===\n");
    if (deque->tamanho == 0) {
        printf("Fila vazia.\n");
        return;
    }
    
    NoDeque *atual = deque->inicio;
    int i = 1;
    
    while (atual != NULL) {
        printf("%d. Matricula: %d - Motivo: %s\n", 
               i, atual->matricula, atual->motivo);
        atual = atual->proximo;
        i++;
    }
    printf("Total na fila: %d\n", deque->tamanho);
}

void liberarDeque(DequeAtendimento *deque) {
    NoDeque *atual = deque->inicio;
    while (atual != NULL) {
        NoDeque *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(deque);
}


float calcularMedia(Estudante estudante) {
    return (estudante.notas[0] + estudante.notas[1] + estudante.notas[2]) / 3.0;
}

void atualizarNota(ListaEstudantes *lista, PilhaHistorico *pilha, int matricula, int disciplina, float novaNota) {
    Estudante *estudante = buscarEstudante(lista, matricula);
    if (estudante == NULL) {
        printf("Estudante nao encontrado!\n");
        return;
    }
    
    if (disciplina < 0 || disciplina > 2) {
        printf("Disciplina invalida! Use 0, 1 ou 2.\n");
        return;
    }
    

    HistoricoNota historico;
    historico.matricula = matricula;
    historico.disciplina = disciplina;
    historico.notaAnterior = estudante->notas[disciplina];
    
    empilharHistorico(pilha, historico);
    
    // update
    estudante->notas[disciplina] = novaNota;
    printf("Nota da disciplina %d atualizada para %.2f\n", disciplina, novaNota);
    printf("Nova media: %.2f\n", calcularMedia(*estudante));
}

int contarEstudantesRecursivo(NoLista *no) {
    if (no == NULL) {
        return 0;
    }
    return 1 + contarEstudantesRecursivo(no->proximo);
}

