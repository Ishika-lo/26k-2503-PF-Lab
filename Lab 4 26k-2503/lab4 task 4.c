#include <stdio.h>
int main(){
	float Maccuracy;
	float Platency;
	float Mapproval;
	 
	printf("Enter model accuracy");
    scanf("%f", &Maccuracy);
    getchar();
    
    	 
	printf("Enter Prediction latency");
    scanf("%f", &Platency);
    getchar();
    
    printf("Enter Model approval status");
    scanf("%f", &Mapproval);
    
    if (Maccuracy<90 && Platency> 100){
       printf("Accuracy is high and latency too high");
   }
    else if (Mapproval==0 && Platency> 100){
       printf("Model not approved and latency too high");
   }
    else if (Maccuracy<90 && Mapproval== 0){
       printf("Accuracy is high and Model not approved ");
   }
       
    else if(Maccuracy < 90){
    	printf("Accuracy is too low");
	}
	else if (Platency > 100){
		printf("latency too high");
	}
	else if (Mapproval = 0 ){
	    printf ("Model is not approved");
	}
    else{
        printf("model deployed");
	}	
}

