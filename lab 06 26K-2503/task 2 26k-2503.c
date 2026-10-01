#include <stdio.h>
int main (){
	int digit,n;
	printf("enter your ticket number ");
       scanf("%d", &n);
    while (n>0){

       
	   digit=n%10;
	   n=n/10;
	    printf("%d", digit);
}
	  
}
