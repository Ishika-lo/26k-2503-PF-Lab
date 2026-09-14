#include <stdio.h>
int main (){
	int num1;
	int num2;
	int num3;
	
	printf("Enter the num1: ");
	scanf("%d", &num1);
	getchar();
	
	printf("Enter the num2: ");
	scanf("%d", &num2);
	
	getchar();
	
	printf("Enter the num3: ");
	scanf("%d", &num3);
	
	if(num1 >num2 && num1 > num3){
		printf("num1 is the grestest");
	}
	else if (num2> num3 && num2>num1){
	    printf("num2 is the greatest");
	}
	else if(num3 > num1 && num3 > num2){
		printf("num3 is greatest");
	}
	else if(num1==num2 && num1> num3){
		printf("num1 is greatest");
	}
	else if(num2==num3 && num2>num1){
		printf("num 2 is greatest");
		
	}
	else {
		(num1==num2 && num2==num3);
		printf(" All three are equal");
	} 

	

	
}
