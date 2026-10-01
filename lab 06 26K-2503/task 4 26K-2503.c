#include <stdio.h>
int main() {
    int n,digit;
    int rev=0;
    int ori;

    printf("Enter a library book code: ");
    scanf("%d", &n);
    ori = n;
    while (n>0){
        digit =n%10;
        rev= (rev*10) + digit;
        n= n / 10;
    }
    if (ori==rev){
        printf("It is a palindrome therfore it's valid");
    } else{
        printf("It is not a palindrome therefore it's not valid");
    }
    return 0;
}
