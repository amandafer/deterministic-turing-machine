#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mem_function.h"
#include "MT.h"

// Funcao que verifica se a palavra foi lida completamente
int readWord(char *word) {
    int i;
    for (i = 0; i < strlen(word); i++) {
        if (word[i] != '-')
            return 1;
    }
    return 0;
}

// Encontra a transicao correspondente
int findTransaction(char **matrix, char letter, int rows, char *actualState, char *tape, int *position) {
    int i;

    // Procura-se, na matriz de transicao, qual se refere a letra lida naquele momento
    for (i = 0; i < rows; i++) {
        // A transicao eh retornada caso a letra e estado da transicao forem os mesmos do atual momento
        if ((*actualState == matrix[i][0] || *actualState+48 == matrix[i][0]) && letter == matrix[i][1]) {
            *actualState = matrix[i][4];

            // recebe a letra que sera escrita na fita
            tape[*position] = matrix[i][2];

            // Recebe a direcao da fita
            if (matrix[i][3] == 'D')
                *position += 1;
            else if (matrix[i][3] == 'E')
                *position -= 1;

            return 0;
        }
    }
    // Caso nenhuma transicao tenha sido encontrada, uma transicao especial eh procurada
    for (i = 0; i < rows; i++) {
        // A transicao eh retornada caso a letra lida seja '-' e estado da transicao for o mesmo do atual momento
        if ((*actualState == matrix[i][0] || *actualState+48 == matrix[i][0]) && matrix[i][1] == '-' && letter == '-') {
            *actualState = matrix[i][4];

            // Recebe a direcao da fita
            if (matrix[i][3] == 'D')
                *position += 1;
            else if (matrix[i][3] == 'E')
                *position -= 1;

            return 0;
        }
    }
    // Caso nao exista nenhuma transicao correspondente
    return 1;
}

int turingMachine(char *actualState, char *tape, char **matrix, int rows, char* my_word) {
    char letter, *thisTrans;
    thisTrans = memAllocS(5);
    int position = 1, readW;

    // Enquanto existe transicao
    while (1) {
        letter = tape[position];

        // Procura-se a transicao referente a letra lida, estado atual
        /// Obs.: o topo da pilha deve ser observado, para os casos em que a transicao dependa do mesmo
        int exists = findTransaction(matrix, letter, rows, actualState, tape, &position);

        // Se nao existe mais nenhuma transicao a ser feita
        if (exists == 1) {
            readW = readWord(my_word);
            // Verifica se toda a palavra foi lida
            if (readW == 1) {
                return 1;
            }
            else
                return 0;
        }
        else {
            // Se existe transicao, a palavra lida eh 'cortada'
            if (position  <= strlen(my_word) + 1)
                my_word[position - 2] = '-';
        }
    }
    return 1;
}
