#include <stdio.h>
#include <stdlib.h>

// Funcao que aloca memoria para matrizes
char **memAlloc(int linha, int coluna) {
    char **matrix;
    int count;
    matrix = (char**)malloc(linha*sizeof(char*));
    
    for (count = 0 ; count < linha ; count++) {
        matrix[count] = (char**)malloc(coluna*sizeof(char*));
    }
    
    if (matrix == NULL) {
        printf("ERRO: N�o h� mem�ria sufuciente");
        return NULL;
    } else
        return matrix;
}

// Funcao que libera a memoria de matrizes
void freeMem(char **matriz, int y) {
    int i;
    
    for (i = 0; i < y; i++) {
        free(matriz[i]);
    }
    free(matriz);
}


// Funcao que aloca memoria para vetores
char *memAllocS(int coluna) {
    char *string;
    string = (char*)malloc(coluna*sizeof(char*));
    
    if (string == NULL) {
        printf("ERRO: N�o h� mem�ria sufuciente");
        return NULL;
    } else
        return string;
}

// Funcao que libera a memoria de vetores
void freeMemS(char *string) {
    free(string);
}


