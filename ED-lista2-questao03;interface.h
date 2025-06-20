/*
** Função : Sistema de Registro de Estudantes
** Autor : Erick e Daysila
** Data : 18/06/2025
** Observações: Arquivo de teste do Sistema de Registro de Estudantes
*/

#ifndef ESTUDANTE_H
#define ESTUDANTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_DISCIPLINA 30


typedef struct {
    char nome[MAX_NOME];
    int matricula;
    float notas[3]; 
} Estudante;


typedef struct {
    int matricula;
    float notaAnterior;
    int disciplina; 
} HistoricoNota;

// Lista
typedef struct NoLista {
    Estudante estudante;
    struct NoLista *proximo;
} NoLista;

typedef struct {
    NoLista *inicio;
    int tamanho;
} ListaEstudantes;

// Pilha
typedef struct NoPilha {
    HistoricoNota historico;
    struct NoPilha *proximo;
} NoPilha;

typedef struct {
    NoPilha *topo;
    int tamanho;
} PilhaHistorico;

// Fila
typedef struct NoFila {
    int matricula;
    char disciplina[MAX_DISCIPLINA];
    struct NoFila *proximo;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
    int tamanho;
} FilaMatricula;

// Deque
typedef struct NoDeque {
    int matricula;
    char motivo[50];
    struct NoDeque *proximo;
    struct NoDeque *anterior;
} NoDeque;

typedef struct {
    NoDeque *inicio;
    NoDeque *fim;
    int tamanho;
} DequeAtendimento;

// Funçõe  da Lista
ListaEstudantes* criarLista();
void adicionarEstudante(ListaEstudantes *lista, Estudante estudante);
int removerEstudante(ListaEstudantes *lista, int matricula);
Estudante* buscarEstudante(ListaEstudantes *lista, int matricula);
void listarEstudantes(ListaEstudantes *lista);
void liberarLista(ListaEstudantes *lista);

// Funçõe  da Pilha
PilhaHistorico* criarPilha();
void empilharHistorico(PilhaHistorico *pilha, HistoricoNota historico);
int desempilharHistorico(PilhaHistorico *pilha, HistoricoNota *historico);
void mostrarHistorico(PilhaHistorico *pilha);
void liberarPilha(PilhaHistorico *pilha);

// Funçõe  da Fila
FilaMatricula* criarFila();
void adicionarNaFila(FilaMatricula *fila, int matricula, char *disciplina);
int removerDaFila(FilaMatricula *fila, int *matricula, char *disciplina);
void mostrarFila(FilaMatricula *fila);
void liberarFila(FilaMatricula *fila);

// Funçõe  do Deque
DequeAtendimento* criarDeque();
void adicionarInicioDeque(DequeAtendimento *deque, int matricula, char *motivo);
void adicionarFimDeque(DequeAtendimento *deque, int matricula, char *motivo);
int removerInicioDeque(DequeAtendimento *deque, int *matricula, char *motivo);
int removerFimDeque(DequeAtendimento *deque, int *matricula, char *motivo);
void mostrarDeque(DequeAtendimento *deque);
void liberarDeque(DequeAtendimento *deque);

// Funçõe 
float calcularMedia(Estudante estudante);
void atualizarNota(ListaEstudantes *lista, PilhaHistorico *pilha, int matricula, int disciplina, float novaNota);
int contarEstudantesRecursivo(NoLista *no);

#endif

