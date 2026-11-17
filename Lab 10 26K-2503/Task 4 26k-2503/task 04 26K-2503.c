#include <stdio.h>
int main(){
    char name[50];
    int num;
    float amount;

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", name);
    printf("Enter Account Number: ");
    scanf("%d", &num);
    
    printf("Enter Withdrawal Amount: ");
    scanf("%f", &amount);
    FILE *ptr = fopen("bank_log.txt", "a");

    if (ptr == NULL){
        printf("Error: Could not open file.\n");
    }
	 else{
        fprintf(ptr, "Name: %s, Account: %d, Withdrawn: %.2f\n", name,num,amount);
        fclose(ptr);
        
        printf("Transaction logged successfully.\n");
    }

    return 0;
}
