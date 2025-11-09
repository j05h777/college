%{
#include <stdio.h>
%}
D	[0-9]
L	[a-zA-Z]
K	int|float|char|return|if|else|while
WS	[ \n\t]+
OP	[\+\-\*=]
ROP	==|>=|<=|<|>
PUNC	["';\(\)\{\}]
%%
{WS}				
{K}			printf("%s is a keyword\n", yytext);
{L}+({L}|{D})*		printf("%s is an identifier\n", yytext);
{D}+|{D}+.{D}+		printf("%s is a number\n", yytext);
{OP}			printf("%s is an operator\n", yytext);
{ROP}			printf("%s is a relational operator\n", yytext);
{PUNC}			printf("%s is a punctuator\n", yytext);
.			printf("Invalid token: %s\n", yytext);
%%
int main(){
printf("Enter input:\n");
yylex();
return 0;
}

int yywrap(){
return 1;
}
