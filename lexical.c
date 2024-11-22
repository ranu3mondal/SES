#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_TOKENS 1000
#define MAX_LEXEME_LEN 10
typedef struct {
    int line;
    char lexeme[MAX_LEXEME_LEN];
    char type[20];
} Token;
Token tokens[MAX_TOKENS];
int token_count = 0;
// Add a token
void add_token(int line, const char *lexeme, const char *type) {
    if (token_count >= MAX_TOKENS) return;
    tokens[token_count].line = line;
    strncpy(tokens[token_count].lexeme, lexeme, MAX_LEXEME_LEN);
    strncpy(tokens[token_count].type, type, 20);
    token_count++;
}
// Check token type
void check_and_add_token(int line, const char *lexeme) {
    if (strcmp(lexeme, "int") == 0 || strcmp(lexeme, "float") == 0 || strcmp(lexeme, "if") == 0 || 
        strcmp(lexeme, "else") == 0 || strcmp(lexeme, "while") == 0 || strcmp(lexeme, "return") == 0) {
        add_token(line, lexeme, "KEYWORD");
    } else if (isdigit(lexeme[0])) {
        add_token(line, lexeme, "NUMBER");
    } else if (isalpha(lexeme[0]) || lexeme[0] == '_') {
        add_token(line, lexeme, "IDENTIFIER");
    } else if (strchr("+-*/%=", lexeme[0])) {
        add_token(line, lexeme, "OPERATOR");
    } else if (strchr("{}();,", lexeme[0])) {
        add_token(line, lexeme, "PUNCTUATOR");
    } else {
        add_token(line, lexeme, "UNKNOWN");
    }
}
// Tokenize a line
void tokenize_line(const char *line, int line_number) {
    char buffer[MAX_LEXEME_LEN];
    int index = 0;
int i;
    for (i = 0; line[i] != '\0'; i++) {
        if (isspace(line[i])) {
            if (index > 0) {
                buffer[index] = '\0';
                check_and_add_token(line_number, buffer);
                index = 0;
            }
        } else if (strchr("+-*/%={}();,", line[i])) {
            if (index > 0) {
                buffer[index] = '\0';
                check_and_add_token(line_number, buffer);
                index = 0;
            }
            char punctuator[2] = {line[i], '\0'};
            check_and_add_token(line_number, punctuator);
        } else {
            buffer[index++] = line[i];
        }
    }
if (index > 0) {
        buffer[index] = '\0';
        check_and_add_token(line_number, buffer);
    }
}
// Print tokens
void print_tokens() {
    printf("%-5s %-15s %-15s\n", "Line", "Lexeme", "Token Type");
    printf("--------------------------------------\n");
    int i;
    for (i = 0; i < token_count; i++) {
        printf("%-5d %-15s %-15s\n", tokens[i].line, tokens[i].lexeme, tokens[i].type);
    }
}
int main() {
    FILE *file = fopen("input.c", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
char line[1024];
    int line_number = 1;
while (fgets(line, sizeof(line), file)) {
        tokenize_line(line, line_number);
        line_number++;
    }
fclose(file);
    print_tokens();
    return 0;
}