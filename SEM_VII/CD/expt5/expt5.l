%{
#include <stdio.h>
#include <stdlib.h>
float sum = 0.0;
int count = 0;
int expected_count = 0;
%}

%%
[0-9]+(\.[0-9]+)? {
    if (count < expected_count) {
        sum += atof(yytext);
        count++;
        if (count == expected_count) {
            float average = sum / expected_count;
            printf("\nFinal Result:\n");
            printf("Expected Terms: %d\n", expected_count);
            printf("Total Sum: %.2f\n", sum);
            printf("Calculated Average: %.4f\n", average);
            printf("\n");
        }
    }
}
.|\n ;
%%

int main(void) {
    printf("Enter number of terms: ");
    if (scanf("%d", &expected_count) != 1 || expected_count <= 0) {
        fprintf(stderr, "Invalid number of terms entered. Exiting.\n");
        return 1;
    }
    while (getchar() != '\n');
    printf("Enter the %d numbers: \n",expected_count);
    yylex();
    if (count < expected_count) {
        printf("\nWarning: Only %d out of %d numbers were processed before input ended.\n", count, expected_count);
    }

    return 0;
}

int yywrap(){return 1;}