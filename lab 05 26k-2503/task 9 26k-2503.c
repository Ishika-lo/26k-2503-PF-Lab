#include <stdio.h>
#include <math.h>
int main (){
	int choice;
	float num, base, exp;
	printf("AI application math operations Menu\n");
    printf("1.Square Root\n");
    printf("2.Power\n");
    printf("3.Absolute Value\n");
    printf("4.Floor\n");
    printf("5.Ceiling\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);
	switch (choice) {
        case 1:
            printf("Enter a number: ");
            scanf("%f", &num);
            if (num>=0) {
                printf("square root of %.2f is %.2f", num, sqrt(num));
            } else {
                printf("invalid number");
            }
            break;
            case 2:
            printf("Enter base: ");
            scanf("%f", &base);
            printf("Enter exponenet: ");
            scanf("%f", &exp);
            printf("%.2f raised to the power %.2f is %.2f", base, exp, pow(base,exp));
            break;
            case 3:
            printf("Enter a number ");
            scanf("%f", &num);
            printf("the absoulte value of %.2f is %.2f",num, fabs(num));
            break;
            case 4:
            printf("Enter a number ");
            scanf("%f", &num);
            printf("the floor value of %.2f is %.0f",num, floor(num));
            break;
            case 5:
            printf("Enter a number ");
            scanf("%f", &num);
            printf("the ceiling value of %.2f is %.0f",num, ceil(num));
            break;
            default:
            	printf("invalid choice enetered");
            
}
return 0;
}
