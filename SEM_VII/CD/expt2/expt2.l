%{
// CD Experiment 2
// Joshua Fernandes 22CO16
// 22.09.2025
#include <stdio.h>
%}
D [0-9]
L [a-zA-Z]
%%
{D}+\.{D}+	printf("%s is a real number", yytext);
{D}+		printf("%s is an integer", yytext);
{L}+		printf("%s is a word", yytext);
.*		printf("Invalid input!");
%%
int main()
{
printf("\nInput: ");
yylex();
return 0;
}

int yywrap()
{
return 1;
}
