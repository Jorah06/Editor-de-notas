#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct cadastro {
    int matricula;
    char aluno[100];
    float nota[3];
    float media;
} cadastro;

void abrir(FILE **ab) {
    *ab = fopen("alunos.txt", "r+");
    if (*ab == NULL) {
        printf("ERRO ao abrir o arquivo!");
        exit(1);
    }
}

void contadora(FILE **ab, int *linhas) {
    char contador;
    *linhas = 0;
    while ((contador = fgetc(*ab)) != EOF) {
        if (contador == '\n') {
            ++*linhas;
        }
    }
}

void scan(cadastro *p, int linhas, FILE **ab) {
    for (int i = 0; i < linhas; i++) {
        fscanf(*ab, "%d", &p[i].matricula);
        fscanf(*ab, "%s", &p[i].aluno);
        fscanf(*ab, "%f", &p[i].nota[0]);
        fscanf(*ab, "%f", &p[i].nota[1]);
        fscanf(*ab, "%f", &p[i].nota[2]);
    }
}

void bubbleSort(cadastro *p, int linhas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < linhas - 1; j++) {
            if (p[j].matricula > p[j + 1].matricula) {
                cadastro aux = p[j];
                p[j] = p[j + 1];
                p[j + 1] = aux;
            }
        }
    }
}

void imprime(cadastro *p, int linhas) {
    for (int i = 0; i < linhas; i++) {
        printf(" %d ", p[i].matricula);
        printf(" %s ", p[i].aluno);
        printf(" %.2f ", p[i].nota[0]);
        printf(" %.2f ", p[i].nota[1]);
        printf(" %.2f\n", p[i].nota[2]);
    }
}

void media(cadastro *p, int linhas) {
    for (int i = 0; i < linhas; i++) {
        p[i].media = (p[i].nota[0] + p[i].nota[1] + p[i].nota[2]) / 3;
    }
}

int busca(cadastro *p, int linhas, int CMatricula) {
    printf("Digite a matricula do aluno\n");
    scanf("%d", &CMatricula);
    int i = 0;
    int t = 0;
    for (int i = 0; i < linhas; i++) {
        if (p[i].matricula == CMatricula) {
            printf(" %d ", p[i].matricula);
            printf(" %s ", p[i].aluno);
            printf(" %.2f ", p[i].nota[0]);
            printf(" %.2f ", p[i].nota[1]);
            printf(" %.2f\n\n\n", p[i].nota[2]);
            t = 1;
            return i;
        }
    }
    if (t == 0) {
        printf("MATRICULA NAO ENCONTRADA\n");
        return -1;
    }
}

void escrever_arquivo(cadastro *p, int linhas) {
    FILE *ab = fopen("alunos.txt", "w");
    if (ab == NULL) {
        printf("ERRO ao abrir o arquivo!");
        exit(1);
    }
    for (int i = 0; i < linhas; i++) {
        fprintf(ab, "%d ", p[i].matricula);
        fprintf(ab, "%s ", p[i].aluno);
        fprintf(ab, "%.2f ", p[i].nota[0]);
        fprintf(ab, "%.2f ", p[i].nota[1]);
        fprintf(ab, "%.2f\n", p[i].nota[2]);
    }
    fclose(ab);
}

int main() {
    int escolha = 0, opcao = 0, linhas = 0, posicao = 0;
    float mediaGeral = 0;
    FILE *ab;
    abrir(&ab);
    contadora(&ab, &linhas);
    fclose(ab);
    abrir(&ab);
    cadastro *p;
    p = (cadastro*) malloc(linhas * sizeof(cadastro));
    scan(p, linhas, &ab);
    media(p, linhas);

    while(1) {
        printf("\n   ESCOLHA UMA OPCAO:\n\n");
        printf("1  Mostrar arquivo completo\n");
        printf("2  Mostrar apenas os nomes\n");
        printf("3  Mostrar os nomes e suas respectivas notas finas\n");
        printf("4  Buscar aluno\n");
        printf("5  Mostrar os alunos por ordem de matricula\n");
        printf("6  Editar notas de aluno\n");
        printf("7  Imprimir os dados do aluno que obteve a maior nota\n");
        printf("8  Imprimir os dados do aluno que obteve a menor nota\n");
        printf("9  Imprimir a quantidade de alunos aprovados e reprovados\n\n");
        printf("0  Sair do programa\n");
        scanf("%d", &escolha);

        switch(escolha) {
            case 1:
                imprime(p, linhas);
                break;
            case 2:
                for (int i = 0; i < linhas; i++) {
                    printf("%s\n", p[i].aluno);
                }
                break;
            case 3:
                for (int i = 0; i < linhas; i++) {
                    printf("%s ", p[i].aluno);
                    printf(" %.2f\n", p[i].media);
                }
                break;
            case 4:
                posicao = busca(p, linhas, posicao);
                break;
            case 5:
                bubbleSort(p, linhas);
                imprime(p, linhas);
                break;
            case 6:
                posicao = busca(p, linhas, posicao);
                printf(" 1 Para editar a primeira nota do aluno\n");
                printf(" 2 Para editar a segunda nota do aluno\n");
                printf(" 3 Para editar a terceira nota do aluno\n");
                scanf("%d", &opcao);
                switch(opcao) {
                    case 1:
                        printf("Digite a primeira nota\n");
                        scanf("%f", &p[posicao].nota[0]);
                        break;
                    case 2:
                        printf("Digite a segunda nota\n");
                        scanf("%f", &p[posicao].nota[1]);
                        break;
                    case 3:
                        printf("Digite a terceira nota\n");
                        scanf("%f", &p[posicao].nota[2]);
                        break;
                    default:
                        printf("OPCAO INVALIDA!");
                        break;
                }
                media(p, linhas);
                break;
            case 7:
                 for (int i = 0; i < linhas; i++) {
                    if (p[i].media > maior) {
                        maior = p[i].media;
                        maiorI = i;
                    }
                }
                printf("O aluno com a maior nota foi %s e sua nota foi: %.2f\n", p[maiorI].aluno, maior);
                break;
            case 8:
                int menorI = 0;
                float menor = 11;
                for (int i = 0; i < linhas; i++) {
                    if (p[i].media < menor) {
                        menor = p[i].media;
                        menorI = i;
                    }
                }
                printf("O aluno com a menor nota foi %s e sua nota foi: %.2f\n", p[menorI].aluno, menor);
                break;
            case 9:
                int aprovados = 0, reprovados = 0;
                for (int i = 0; i < linhas; i++) {
                    if (p[i].media >= 6) {
                        aprovados++;
                    } else {
                        reprovados++;
                    }
                    mediaGeral += p[i].media;
                }
                mediaGeral = mediaGeral / linhas;
                printf("Quantidade de alunos aprovados: %d\n", aprovados);
                printf("Quantidade de alunos reprovados: %d\n", reprovados);
                printf("A media geral dos alunos foi: %.2f\n", mediaGeral);
                break;
            case 0:
                escrever_arquivo(p, linhas);
                free(p);
                fclose(ab);
                exit(0);
            default:
                printf("OPCAO INVALIDA!");
                break;
        }
    }
    return 0;
}


