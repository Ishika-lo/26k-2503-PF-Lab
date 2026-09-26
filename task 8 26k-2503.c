#include <stdio.h>
int main(){
    int permission;

    printf("Enter user permission value ");
    scanf("%d", &permission);
    if (permission<=15 && permission >=0){
    printf("\nAllowed Operations:");
    if (permission & 1){
        printf("- View model\n");
    }
    if (permission & 2){
        printf("Train model\n");
    }
    if (permission & 4){
        printf("Test model\n");
    }
    if (permission & 8){
        printf("Deploy model\n");
    }
    if (permission == 0){
        printf("No permissions granted\n");
    }

    if ((permission & 2) && (permission & 8)) {
        printf("Special status: User has BOTH training and deployment permissions");
    } else {
        printf("\nSpecial status: User does NOT have both training and deployment permissions ");
    }
}
    else {
    	printf("invalid permission entered");
	}
    return 0;
}
