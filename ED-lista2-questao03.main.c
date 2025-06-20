/*
** Função : Sistema de Registro de Estudantes
** Autor : Erick e Daysila
** Data : 18/06/2025
** Observações: Arquivo de teste do Sistema de Registro de Estudantes
*/

#include "estudante.h"

void mostrarMenu() {
    printf("\n=== SISTEMA DE REGISTRO DE ESTUDANTES ===\n");
    printf("1.  Adicionar estudante\n");
    printf("2.  Listar estudantes\n");
    printf("3.  Buscar estudante\n");
    printf("4.  Remover estudante\n");
    printf("5.  Atualizar nota\n");
    printf("6.  Mostrar historico de notas\n");
    printf("7.  Adicionar na fila de matricula\n");
    printf("8.  Processar fila de matricula\n");
    printf("9.  Mostrar fila de matricula\n");
    printf("10. Adicionar no inicio da fila de atendimento\n");
    printf("11. Adicionar no fim da fila de atendimento\n");
    printf("12. Atender do inicio da fila\n");
    printf("13. Atender do fim da fila\n");
    printf("14. Mostrar fila de atendimento\n");
    printf("15. Contar estudantes (recursivo)\n");
    printf("0.  Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    ListaEstudantes *lista = criarLista();
    PilhaHistorico *pilha = criarPilha();
    FilaMatricula *fila = criarFila();
    DequeAtendimento *deque = criarDeque();

    if (!lista || !pilha || !fila || !deque) {
        printf("Erro!\n");
        return 1;
    }

    int opcao;
    char nome[MAX_NOME];
    char disciplina[MAX_DISCIPLINA];
    char motivo[50];
    int matricula, disc;
    float nota;
    Estudante estudante;
    Estudante *encontrado;
    HistoricoNota historico;

    printf("Sistema iniciado com sucesso!\n");

    do {
        mostrarMenu();
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                printf("\n--- ADICIONAR ESTUDANTE ---\n");
                printf("Nome: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strlen(nome)-1] = '\0'; 
                printf("Matricula: ");
                scanf("%d", &matricula);

                printf("Nota 1: ");
                scanf("%f", &estudante.notas[0]);
                printf("Nota 2: ");
                scanf("%f", &estudante.notas[1]);
                printf("Nota 3: ");
                scanf("%f", &estudante.notas[2]);
                getchar();

                strcpy(estudante.nome, nome);
                estudante.matricula = matricula;

                adicionarEstudante(lista, estudante);
                break;

            case 2:
                listarEstudantes(lista);
                break;

            case 3:
                printf("\n--- BUSCAR ESTUDANTE ---\n");
                printf("Matricula: ");
                scanf("%d", &matricula);
                getchar();

                encontrado = buscarEstudante(lista, matricula);
                if (encontrado != NULL) {
                    printf("Estudante encontrado!\n");
                    printf("Nome: %s\n", encontrado->nome);
                    printf("Matricula: %d\n", encontrado->matricula);
                    printf("Notas: %.2f, %.2f, %.2f\n", 
                           encontrado->notas[0], encontrado->notas[1], encontrado->notas[2]);
                    printf("Media: %.2f\n", calcularMedia(*encontrado));
                } else {
                    printf("Estudante nao encontrado!\n");
                }
                break;

            case 4:
                printf("\n--- REMOVER ESTUDANTE ---\n");
                printf("Matricula: ");
                scanf("%d", &matricula);
                getchar();

                removerEstudante(lista, matricula);
                break;

            case 5:
                printf("\n--- ATUALIZAR NOTA ---\n");
                printf("Matricula: ");
                scanf("%d", &matricula);
                printf("Disciplina (0, 1 ou 2): ");
                scanf("%d", &disc);
                printf("Nova nota: ");
                scanf("%f", &nota);
                getchar();

                atualizarNota(lista, pilha, matricula, disc, nota);
                break;

            case 6:
                mostrarHistorico(pilha);
                break;

            case 7:
                printf("\n--- ADICIONAR NA FILA DE MATRICULA ---\n");
                printf("Matricula: ");
                scanf("%d", &matricula);
                getchar();
                printf("Disciplina: ");
                fgets(disciplina, MAX_DISCIPLINA, stdin);
                disciplina[strlen(disciplina)-1] = '\0';

                adicionarNaFila(fila, matricula, disciplina);
                break;

            case 8:
                printf("\n--- PROCESSAR MATRICULA ---\n");
                if (removerDaFila(fila, &matricula, disciplina)) {
                    printf("Matricula processada com sucesso!\n");
                }
                break;

            case 9:
                mostrarFila(fila);
                break;

            case 10:
                printf("\n--- ADICIONAR NO INICIO DA FILA DE ATENDIMENTO ---\n");
                printf("Matricula: ");
                scanf("%d", &matricula);
                getchar();
                printf("Motivo: ");
                fgets(motivo, 50, stdin);
                motivo[strlen(motivo)-1] = '\0';

                adicionarInicioDeque(deque, matricula, motivo);
                break;

            case 11:
                printf("\n--- ADICIONAR NO FIM DA FILA DE ATENDIMENTO ---\n");
                printf("Matricula: ");
                scanf("%d", &matricula);
                getchar();
                printf("Motivo: ");
                fgets(motivo, 50, stdin);
                motivo[strlen(motivo)-1] = '\0';

                adicionarFimDeque(deque, matricula, motivo);
                break;

            case 12:
                printf("\n--- ATENDER DO INICIO ---\n");
                if (removerInicioDeque(deque, &matricula, motivo)) {
                    printf("Atendimento realizado!\n");
                }
                break;

            case 13:
                printf("\n--- ATENDER DO FIM ---\n");
                if (removerFimDeque(deque, &matricula, motivo)) {
                    printf("Atendimento realizado!\n");
                }
                break;

            case 14:
                mostrarDeque(deque);
                break;

            case 15:
                printf("\n--- CONTAGEM RECURSIVA ---\n");
                printf("Total de estudantes (recursivo): %d\n", 
                       contarEstudantesRecursivo(lista->inicio));
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }

    } while(opcao != 0);


    liberarLista(lista);
    liberarPilha(pilha);
    liberarFila(fila);
    liberarDeque(deque);

    printf("Sistema encerrado!\n");
    return 0;
}
