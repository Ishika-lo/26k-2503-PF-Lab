#include <stdio.h>
#include <math.h>
int main(){
float acc, score, confidence;
int dataset, role, status, perm;

printf("Enter accuracy: ");
scanf("%f", &acc);

printf("Enter confidence: ");
scanf("%f", &confidence);

printf("Enter dataset size: ");
scanf("%d", &dataset);

printf("Enter user role (1-Admin, 2-Developer, 3-Researcher): ");
scanf("%d", &role);

printf("Enter model status (1-Ready, 2-Testing, 3-Training): ");
scanf("%d", &status);

printf("Enter permission value (0-15): ");
scanf("%d", &perm);
    score = round((acc+confidence)/2);
    printf("Model Score: %.2f\n", score);
    printf("Dataset Variable Memory: %zu bytes\n", sizeof(dataset));
    switch (role) {
        case 1:
            printf("User Role: Admin\n");
            switch (status) {
                case 1: printf("Model Status: Ready\n"); break;
                case 2: printf("Model Status: Testing\n"); break;
                case 3: printf("Model Status: Training\n"); break;
                default: printf("Model Status: Invalid\n"); break;
            }
            break;

        case 2:
            printf("User Role: Developer\n");
            switch (status) {
                case 1: printf("Model Status: Ready\n"); break;
                case 2: printf("Model Status: Testing\n"); break;
                case 3: printf("Model Status: Training\n"); break;
                default: printf("Model Status: Invalid\n"); break;
            }
            break;
            case 3:
            printf("User Role: Researcher\n");
            switch (status) {
                case 1: printf("Model Status: Ready\n"); break;
                case 2: printf("Model Status: Testing\n"); break;
                case 3: printf("Model Status: Training\n"); break;
                default: printf("Model Status: Invalid\n"); break;
            }
            break;

        default:
            printf("User Role: Invalid Role\n");
            break;
    }
    printf("Deployment Permission: %s\n", (perm & 8) ? "Granted" : "Denied");
        if (acc >= 80 && confidence >= 75 && dataset>= 1000) {
        	if (status == 1) {
        		if (perm & 8) {
        			printf("Result: model is READY for deployment.\n");
            } else {
                printf("Result: model is NOT ready.");
    }
     }else {
            printf("Result: model is NOT ready.");
        
    }
    }
	return 0;
}



