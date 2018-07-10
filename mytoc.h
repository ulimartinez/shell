char ** mytoc(char *str, char delim);
void printTokens(char **tokens, char delim);
int veclen(char **vec);
void removeLast(char **vec);
#ifndef DELIMS
#define SPACE_DELIM ' '
#define PIPE_DELIM '|'
#define COLON_DELIM ':'
#define EQ_DELIM '='
#endif
