%{
#include <stdio.h>
%}

%%
%%
int main(int argc, char *argv[]){
    int n, i, sum=0;
    float avg;
    printf("Enter number count: ");
    scanf("%d", &n);
    int num[n];
    for(i=0;i<n;i++){scanf("%d", &num[i]);}

    for(i=0;i<n;i++){sum+=num[i];}
    avg = sum*1.0/n;
    printf("Sum: %d, Average: %f\n", sum, avg);
    return 0;
}

int yywrap(){return 1;}
