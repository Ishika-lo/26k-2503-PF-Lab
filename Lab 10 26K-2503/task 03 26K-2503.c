#include <stdio.h>
#include <string.h>
int main(){
    char email[100];
    char domain[100];
    
    printf("Enter employee email address: ");
    scanf("%s", email);
    char *at= strchr(email,'@');

    if (at== NULL){
        printf("Invalid Email Format\n");
    }
	 else{
        strcpy(domain, at + 1);
        printf("Extracted Domain: %s\n", domain);
    }
    return 0;
}
