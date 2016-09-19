#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_function.h"

#define MAX 100

// Pega os estados e os alfabetos da fita e de estados
char *states(FILE* pEntrada, char *statesMT, char *tapeAlphabet) {
    if (pEntrada == NULL) {
        printf("It was not possible to read the file!\n");
        return NULL;
    } else {
        int i = 0;
        char *inputAlphabet, temp;

        tapeAlphabet = memAllocS(MAX);
        inputAlphabet = memAllocS(MAX);
        statesMT = memAllocS(MAX);

        //Estados da Maquina de Turing
        while (temp != ';'){
            fscanf(pEntrada, "%c", &temp);

            if (temp != ' ') {
                statesMT[i] = temp;
                i++;
            }
        }

        // Alfabeto de Entrada
        i = 0;
        fscanf(pEntrada, "%c", &temp);
        while (temp != ';') {
            fscanf(pEntrada, "%c", &temp);
            if (temp != ' ' && temp != ';') {
                inputAlphabet[i] = temp;
                i++;
            }
        }

        // Alfabeto da fita
        i = 0;
        fscanf(pEntrada, "%c", &temp);
        while (temp != ';') {
            fscanf(pEntrada, "%c", &temp);
            if (temp != ' ') {
                tapeAlphabet[i] = temp;
                i++;
            }
        }

        return inputAlphabet;
    }
}

// Funcao que le as transi��es da MT e retorna a matriz da mesma
char **transactions(FILE* pEntrada, int *rows) {
    if (pEntrada == NULL) {
        printf("It was not possible to read the file!\n");
        return NULL;
    } else {
        int i = 0, j = 0, max_rows = 0, max_columns = 0, count = 0;
        char temp;
        char **matrix = memAlloc(MAX, MAX);
        fscanf(pEntrada, "%c", &temp);

        while (temp != ';') {
            fscanf(pEntrada, "%c", &temp);
            if (count == 6) {
                j = 0, count = 0;
                i++;
            }

            if (count > 0 && temp != ',' && temp != ';' && temp != '\n' && temp != '\0') {
                matrix[i][j] = temp;
                j++;
                count++;
            }
            // Define o tamanho da matriz
            if(i > max_rows)
                max_rows = i;
            if(j > max_columns)
                max_columns = j;

            if (count == 0 && temp == '(')
                count++;
        }
        *rows = max_rows;
        return matrix;
    }
}

// Funcao que le os estados iniciais e finais
char *ffStates(FILE* pEntrada, char *initialState, int *count_finals) {
    if (pEntrada == NULL) {
        printf("It was not possible to read the file!\n");
        return NULL;
    } else {
        char temp, *finalState;
        int i = 0;
        finalState = memAllocS(MAX);

        // Estado inicial da MT
        fscanf(pEntrada, "%c", &temp);
        fscanf(pEntrada, "%c", &temp);
        *initialState = temp;

        fscanf(pEntrada, "%c", &temp);
        fscanf(pEntrada, "%c", &temp);

        // Leem-se os estados finais da MT
        while(temp != ';') {
            fscanf(pEntrada, "%c", &temp);
            if (temp != ' ' && temp != ';') {
                finalState[i] = temp;
                i++;
            }
        }
        *count_finals = i;
        return finalState;
    }
}

