#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int idCount = 0;
int numCount = 0;
int realCount = 0;
int opCount = 0;
int kwCount = 0;
int invalidCount = 0;

bool isDelimiter(char c) {
    return (c == ';' || c == '.' || c == ',' || c == ' ' || c == '\t' || c == '\n');
}

bool isKeyword(char* str) {
    char* keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
        "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
    };

    int keywords_len = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < keywords_len; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return true;
    }
    return false;
}

bool validIdentifier(char* str) {
    if (!((str[0] >= 'a' && str[0] <= 'z') ||
          (str[0] >= 'A' && str[0] <= 'Z') ||
          str[0] == '_'))
        return false;
    for (int i = 1; str[i] != '\0'; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9') ||
               str[i] == '_'))
            return false;
    }
    return true;
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '>' || ch == '<' || ch == '=');
}

bool isInteger(char* str) {
    int len = strlen(str);
    if (len == 0) return false;
    for (int i = 0; i < len; i++) {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return false;
    }
    return true;
}

bool isRealNumber(char* str) {
    int len = strlen(str);
    bool hasDecimal = false;
    if (len == 0) return false;

    for (int i = 0; i < len; i++) {
        if (str[i] == '.') {
            if (hasDecimal) return false; //has more than one dot
            hasDecimal = true;
        } else if (!(str[i] >= '0' && str[i] <= '9')) {
            return false;
        }
    }
    return hasDecimal;
}

char* subString(char* str, int left, int right) {
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));
    for (int i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return subStr;
}

void parse(char* str) {
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len && left <= right) {
        if (!isDelimiter(str[right]) && !isOperator(str[right]))
            right++;

        // Single character operator or delimiter
        if ((isDelimiter(str[right]) || isOperator(str[right])) && left == right) {
            if (isOperator(str[right])) {
                printf("'%c' IS AN OPERATOR\n", str[right]);
                opCount++;
            }
            right++;
            left = right;
        }

        else if ((isDelimiter(str[right]) || isOperator(str[right])) && left != right || (right == len && left != right)) {

            char* subStr = subString(str, left, right - 1);

            if (isKeyword(subStr)) {
                printf("'%s' IS A KEYWORD\n", subStr);
                kwCount++;
            }
            else if (isInteger(subStr)) {
                printf("'%s' IS AN INTEGER\n", subStr);
                numCount++;
            }
            else if (isRealNumber(subStr)) {
                printf("'%s' IS A REAL NUMBER\n", subStr);
                realCount++;
            }
            else if (validIdentifier(subStr)) {
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);
                idCount++;
            }
            else {
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
                invalidCount++;
            }
            free(subStr);

            if (isOperator(str[right])) {
                printf("'%c' IS AN OPERATOR\n", str[right]);
                opCount++;
                right++;
            }
            left = right;
        }
        else
            right++;
    }
}

int main() {
    FILE *fp = fopen("test.c", "r");
    if (fp == NULL) {
        printf("File error\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        parse(line);
    }

    fclose(fp);

    printf("\nTOKEN COUNTS\n");
    printf("Keywords: %d\n", kwCount);
    printf("Identifiers: %d\n", idCount);
    printf("Integers: %d\n", numCount);
    printf("Real Numbers: %d\n", realCount);
    printf("Operators: %d\n", opCount);
    printf("Invalid Identifiers: %d\n", invalidCount);

    return 0;
}