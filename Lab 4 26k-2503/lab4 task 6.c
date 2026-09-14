#include <stdio.h>
int main(){
	int obstacle ; 
	int person ; 
	float battery;
	
	printf("Tell about obstacle (1 if an obstacle is detected, otherwise 0)");
	scanf("%d", &obstacle);
	getchar();
	
	 printf("Tell battery percentage");
	scanf("%f", &battery);
	
	if (obstacle==1){
		printf("Tell about person (1 if an person is detected, otherwise 0)");
		scanf("%d", &person);
		if (person==1){
		printf("emergency stop");
		
	}
		else {
    		printf("change direction");	}}
   
	else {
    	if (battery<20){
		printf("Return to charging station");
			}

     else {
	 printf("Continue moving");
	 }
    
}
}
	
