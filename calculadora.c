#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

void empilhar(Pilha *p, float valor) {
    if (p->topo == TAMANHO_MAX_PILHA - 1) {
        printf("Estouro da pilha\n");
        exit(1);
    }
    p->itens[++p->topo] = valor;
}

float desempilhar(Pilha *p) {
    if (p->topo == -1) {
        printf("Substituicao da pilha\n");
        exit(1);
    }
    return p->itens[p->topo--];
}

float avaliar_posfixada(char *expressao) {
    Pilha p;
    p.topo = -1;

    char *token = strtok(expressao, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) { 
            empilhar(&p, atof(token));
        } else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
                   strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 ||
                   strcmp(token, "^") == 0 || strcmp(token, "sen") == 0 ||
                   strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
                   strcmp(token, "log") == 0 || strcmp(token, "raiz") == 0) {
            float operando2 = desempilhar(&p);
            float operando1;
            float resultado;

            if (strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 ||
                strcmp(token, "tg") == 0 || strcmp(token, "log") == 0 ||
                strcmp(token, "raiz") == 0) {
                operando1 = 0; 
            } else {
                operando1 = desempilhar(&p);
            }

            if (strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0) {

                operando2 = operando2 * M_PI / 180.0;
            }

            if (strcmp(token, "sen") == 0) {
                resultado = sin(operando2);
            } else if (strcmp(token, "log") == 0) {
                resultado = log10(operando2);
            } else if (strcmp(token, "raiz") == 0) {
                resultado = sqrt(operando2);
            } else if (strcmp(token, "cos") == 0) {
                resultado = cos(operando2);
            } else if (strcmp(token, "tg") == 0) {
                resultado = tan(operando2);
            } else {
                switch (*token) {
                    case '/':
                        resultado = operando1 / operando2;
                        break;
                    case '^':
                        resultado = pow(operando1, operando2);
                        break;
                    case '+':
                        resultado = operando1 + operando2;
                        break;
                    case '-':
                        resultado = operando1 - operando2;
                        break;
                    case '*':
                        resultado = operando1 * operando2;
                        break;
                    default:
                        printf("Expressao invalida\n");
                        exit(1);
                }
            }
            empilhar(&p, resultado);
        } else {
            printf("Token invalido: %s\n", token);
            exit(1);
        }
        token = strtok(NULL, " ");
    }
    return desempilhar(&p);
}

void exibir_operacoes() {
    printf("Operacoes disponiveis:\n");
    printf("sen : Seno\n");
    printf("cos : Cosseno\n");
    printf("tg : Tangente\n");
    printf("log : Logaritmo de base 10\n");
    printf("raiz : Raiz quadrada\n");
    printf("+ : Soma\n");
    printf("- : Subtracao\n");
    printf("* : Multiplicacao\n");
    printf("/ : Divisao\n");
    printf("^ : Potenciacao\n");
}
