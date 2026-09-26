#include <stdio.h>
int main (){
	char type;
	float confidence;
	printf("enter user type A for aurthorized, U for unauthorized ");
    scanf("%c", &type);
	printf("enter confidence score (1-100)");
    scanf("%f", &confidence);
    (confidence >= 80) ? printf("Face Recognized\n") : 
(confidence >= 50) ? printf("Manual Verification\n") : printf("Not Recognized\n");
if (confidence >=80 && type=='A'){
	printf("Access Granted");
}
else if (confidence <50 || type=='U'){
		printf("Access Denied");
}
else{ printf("maunal verification");
}
return 0;
}
