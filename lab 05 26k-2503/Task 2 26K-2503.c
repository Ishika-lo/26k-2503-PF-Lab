#include <stdio.h>
int main (){

    int age;
    float income, credit;
    char loan;
    printf("enter age ");
    scanf("%d", &age);
    printf("enter income ");
    scanf("%f", &income);
    printf("enter credit score ");
    scanf("%f", &credit);
    printf("enter existing loan status (Y/N) ");
    scanf(" %c", &loan);
    
    if (age>=21){
    	if(income>=100000 && credit>=750 && loan=='N'){
    		printf("High Approval Chance");
    			}
    		else if (income>=75000 && credit>=650 && loan=='Y'){
    			printf("Manual Review");
    				}
				else if(income>=50000 && credit>=600 ){
				printf("Possibly Eligible");
					}	
				else{
					printf("Rejected");
				}
			}
				else{
			         printf("Rejected");
			         	} 
			         	return 0;
	
}
