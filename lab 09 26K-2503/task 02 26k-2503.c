#include <stdio.h>

void withdraw(int *bankbalance, int cashneeded){
    if(cashneeded<=*bankbalance){
        *bankbalance=*bankbalance-cashneeded;
        printf("Withdrawal successful!\n");
    }else{
        printf("Transaction Declined: insufficient balance\n");
    }
}

void deposit(int *bankbalance, int cashtoadd){
    *bankbalance=*bankbalance+cashtoadd;
    printf("Deposit successful! New balance is: %d\n",*bankbalance);
}

int main(){
    int mymoney=15000;
    int userchoice;
    int enteredamount;

    printf("Current balance: %d\n",mymoney);
    printf("Press 1 for withdraw (Debit) or 2 for deposit (Credit): ");
    scanf("%d",&userchoice);

    printf("Enter the amount: ");
    scanf("%d",&enteredamount);

    if(userchoice==1){
        withdraw(&mymoney,enteredamount);
    }else if(userchoice==2){
        deposit(&mymoney,enteredamount);
    }else{
        printf("Invalid choice.\n");
    }

    printf("Final account balance is: %d\n",mymoney);

    return 0;
}
