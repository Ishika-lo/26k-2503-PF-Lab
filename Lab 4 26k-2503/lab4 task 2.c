#include <stdio.h>
int main(){
	int c_score;
	
	printf("Enter the confidence score: ");
	scanf("%d", &c_score);
	
	if(c_score < 0 || c_score>100){
	
		printf("Invalid Score");
	}
	
	else if(c_score >= 0 && c_score <=49){
		printf("Low Confidence");
	}
	else if (c_score >=50 && c_score <=79){
		printf("Moderate Confidence");
	}
	else {
		printf("High Confidence");
	}
}
