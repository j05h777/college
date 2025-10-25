%{
#include <stdio.h>
int count = 1;
%}

%%
^$          { printf("%5d (empty line)\n", count++); }
.*          { printf("%-50s", yytext); }
\n          { printf("%5d\n", count++); }
%%

int main(int argc, char *argv[]){
    if(argc<2){
    printf("required argument <filename>\n./a.out <filename>");
    return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if(!file){
        perror("Error opening file");
        return 1;
    }
    yyin = file;
    yylex();
    fclose(file);
    return 0;
}

int yywrap(){return 1;}
