#include <stdio.h>
int main(){
    int confidence;
	float threshold;

    printf("Enter model confidence score (0 - 100): ");
    scanf("%d", &confidence);

    printf("Enter required confidence threshold (0 - 100): ");
    scanf("%f", &threshold);
    printf("Confidence level: ");
    if (confidence >= 90) {
        printf("Very High");
    } else if (confidence >= 75) {
        printf("High");
    } else if (confidence >= 50) {
        printf("Moderate");
    } else {
        printf("Low");
    }
    if (confidence >= threshold && confidence >= 50) {
        printf("\nDecision: Prediction Accepted");
    } else {
        printf("\nDecision: Prediction Rejected");
    }

    return 0;
}
