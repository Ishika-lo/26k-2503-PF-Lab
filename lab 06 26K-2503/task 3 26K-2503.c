#include <stdio.h>
int main (){
	int i,j=0,k,n;
	
	
	for(i=1; i<16; i++){
		printf ("enter 1 if a student is present and 0 if absent ");
		scanf ("%d", &n);
		if (n==1){
		
		   j++;}
		   
		
	}
	k=30-j;
	printf("The total no of students present are %d", j);
	printf("\nThe total no of students absent are %d", k);
}
