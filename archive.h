// Pega os estados e os alfabetos da fita e de estados
char *states(FILE* pEntrada, char *statesMT, char *tapeAlphabet);

// Funcao que le as transi��es da MT e retorna a matriz da mesma
char **transactions(FILE* pEntrada, int *rows);

// Funcao que le os estados iniciais e finais
char *ffStates(FILE* pEntrada, char *inicialState, int *count_finals);

