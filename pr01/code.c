/* Implement a simple lexical analyzer using c language for given language */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// List of keywords for this example language
char *keywords[] = {"int", "float", "if", "else", "while", "return"};
int keyword_count = 6;

// Function to check if a string is a keyword
int isKeyword(char buffer[]) {
    for (int i = 0; i < keyword_count; i++) {
        if (strcmp(buffer, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
        return 1;
    return 0;
}

// Function to check if a character is a separator
int isSeparator(char ch) {
    if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ';' || ch == ',')
        return 1;
    return 0;
}

int main() {
    char code[MAX];
    char buffer[MAX];
    int i = 0, j = 0;

    printf("Enter code (max 100 characters):\n");
    fgets(code, MAX, stdin);

    while (code[i] != '\0') {
        // Skip whitespaces, tabs, and newlines
        if (code[i] == ' ' || code[i] == '\t' || code[i] == '\n') {
            i++;
            continue;
        }

        // If operator
        if (isOperator(code[i])) {
            printf("Operator: %c\n", code[i]);
            i++;
        }
        // If separator
        else if (isSeparator(code[i])) {
            printf("Separator: %c\n", code[i]);
            i++;
        }
        // If identifier or keyword
        else if (isalpha(code[i])) {
            j = 0;
            while (isalnum(code[i])) {
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';
            if (isKeyword(buffer))
                printf("Keyword: %s\n", buffer);
            else
                printf("Identifier: %s\n", buffer);
        }
        // If number
        else if (isdigit(code[i])) {
            j = 0;
            while (isdigit(code[i])) {
                buffer[j++] = code[i++];
            }
            buffer[j] = '\0';
            printf("Number: %s\n", buffer);
        }
        else {
            printf("Unknown token: %c\n", code[i]);
            i++;
        }
    }

    return 0;
}
