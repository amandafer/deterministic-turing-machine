#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archive.h"
#include "MT.h"
#include "mem_function.h"

#define MAX 100
#define FILEOUTPUT "output.txt"

int main(int argc, char *argv[]) {
    char *inputFile = argv[1];

    FILE *pEntrada = fopen(inputFile, "r");

    int rows, i, j, count_finals;
    char *statesMT, *inputAlphabet, *tapeAlphabet, initialState, *finalState, **matrix;
    statesMT = memAllocS(MAX);
    tapeAlphabet = memAllocS(MAX);

    // Usuario digita a palavra que deseja testar na Maquina de Turing
    char *my_word = memAllocS(MAX);
    printf("Type the word to be tested on the machine: \n");
    scanf("%s", my_word);

    // Descobrem-se os estados e os alfabetos da fita e de entrada
    inputAlphabet = states(pEntrada, statesMT, tapeAlphabet);

    // Retorna uma matriz de transicoes e seu tamanho
    matrix = transactions(pEntrada, &rows);

    // Retorna o estado inicial e os estados finais
    finalState = ffStates(pEntrada, &initialState, &count_finals);

    // Verifica se a palavra lida e valida
    int valid = 1;
    
    if(my_word[0] != '_') {
        for(i = 0; i < strlen(my_word); i++) {
            for(j = 0; j < strlen(inputAlphabet); j++) {
                if (my_word[i] == inputAlphabet[j]){
                    valid = 0;
                }
            }
            
            if(valid == 1) {
                printf("Try another word!\n\n");
                return 0;
            }
        }
    } else {
        my_word[0] = '-';
    }

    // Cria a fita com inicio <, palavra, e -
    int size = strlen(my_word) + 2;
    char *tape = memAllocS(size);
    tape[0] = '<';
    
    for (i = 1; i < size - 1; i++) {
        tape[i] = my_word[i - 1];
    }
    tape[size - 1] = '-';

    // Roda-se a Maquina de Turing
    char actualState = initialState;
    int accept = turingMachine(&actualState, tape, matrix, rows, my_word);

    // Verifica se a palavra foi totalmente lida e se esta no estado aceitante
    if (accept == 0) {
        for (i = 0; i < count_finals; i++) {
            if (actualState == finalState[i] || actualState+48 == finalState[i]) {
                printf("The word is valid and on an accept state.\n\n");
                return 0;
            }
        }
    }
    // Caso a palavra nao seja aceita pela MT, retorna-se NAO
    printf("The word was not accepted for this machine.\n\n");

    // Libero o espaco da matriz e vetores
    freeMem(matrix, 5);
    freeMemS(statesMT);
    freeMemS(tapeAlphabet);
    freeMemS(inputAlphabet);
    freeMemS(finalState);
    return 0;
}
