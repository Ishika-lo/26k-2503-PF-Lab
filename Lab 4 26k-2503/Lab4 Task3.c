#include <stdio.h>
int main(){
	int total;
	int missing;
	int duplicate;
	
	printf("enter the total records");
	scanf("%d", &total);
	getchar();
	
	printf("enter missing records");
	scanf("%d", &missing);
	getchar();
	
	printf("enter the duplicate");
	scanf("%d", &duplicate);
	
	if(total == 0){
		printf("invalid score");
	}
	else {
		float Mpercent = ((float)missing/total)*100;
		float Dpercent = ((float)duplicate/total)*100;
		
		if (Mpercent >30){
			printf("Poor Quality Dataset");
		}
	}
	else {
		if (Dpercent >20){
			printf("Dataset Requires Cleaning");
		}
		else{
			printf("Dataset Ready for Training");
		}
	}
}
