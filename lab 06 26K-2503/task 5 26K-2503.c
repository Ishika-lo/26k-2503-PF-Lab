#include <stdio.h>
int main (){
	int n;
	int i=1;
	unsigned long long fact=1,fact1=1,factn=1, cat;
	
	printf("enter n:");
	scanf("%d", &n);
	
	
	for(i=1; i<=2*n; i++){
	fact= fact*i;
    }
    for(i=1; i<=n+1; i++){
	fact1= fact1*i;
    }
    for(i=1; i<=n; i++){
	factn= factn*i;
    }
    cat= fact/(factn*fact1);
    printf("the Catalan number is %llu", cat);
    return 0;
}

