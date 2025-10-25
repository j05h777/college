%{
int line_num = 1;
%}
%%
\n      {printf("%s", yytext);
        line_num++;
        printf("%4d ", line_num);}
.       {ECHO;}
%%

int main() {
printf("%4d ", line_num);
yylex();
return 0;
}

int yywrap(void) {return 1;}
