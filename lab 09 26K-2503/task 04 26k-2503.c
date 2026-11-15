#include <stdio.h>
int add(int num1, int num2){
    return num1+num2;
}

int multiply(int num1, int num2){
    return num1*num2;
}

int findmax(int num1, int num2){
    if(num1>num2){
        return num1;
    }else{
        return num2;
    }
}

int compute(int a, int b, int (*mathoperation)(int,int)){
    return mathoperation(a,b);
}

int main(){
    int firstval, secondval;

    printf("Enter first integer: ");
    scanf("%d",&firstval);

    printf("Enter second integer: ");
    scanf("%d",&secondval);

    int resultsum=compute(firstval,secondval,add);
    int resultmult=compute(firstval,secondval,multiply);
    int resultmax=compute(firstval,secondval,findmax);

    printf("Sum is: %d\n",resultsum);
    printf("Product is: %d\n",resultmult);
    printf("Maximum is: %d\n",resultmax);

    return 0;
}
