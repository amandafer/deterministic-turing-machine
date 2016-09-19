// Funcao que verifica se a palavra foi lida completamente
int readWord(char *word);

// Encontra a transicao correspondente
int findTransaction(char **matrix, char letter, int rows, char *actualState, char *tape, int *position);

int turingMachine(char *actualState, char *tape, char **matrix, int rows, char* my_word);

