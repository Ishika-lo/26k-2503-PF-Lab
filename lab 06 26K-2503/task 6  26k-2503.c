#include <stdio.h>
int main() {
    int n,digit;
    int odd=0;
    int even=0;

    printf("Enter meter reading: ");
    scanf("%d", &n);
    while (n>0){
        digit= n%10;
        n=n / 10;
        if (digit%2==0){
        	even++;
		}
		else {
		 odd++;
		}
    }
    printf("the number of even digits are %d", even);
    printf("\nthe number of odd digits are %d", odd);
    return 0;
}
    
