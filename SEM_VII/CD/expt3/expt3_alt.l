%{
#include <stdio.h>
#include <stdlib.h>
%}
%%
[0-9]+	printf("Decimal: %d => Hexadecimal %x", atoi(yytext), atoi(yytext));
.*	printf("Invalid input");
%%
int main()
{
printf("Enter a decimal number: ");
yylex();
return 0;
}
int yywrap()
{
return 1;
}
