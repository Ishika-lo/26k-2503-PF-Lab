#include <stdio.h>
int main (){
	int digit,n;
	int sum=0;
	printf("enter a 4 digit pin ");
       scanf("%d", &n);
    while (n>0){

       
	   digit=n%10;
	   n=n/10;
	   sum=sum+ digit;
}
	   if (sum>10){
	 
	   printf("strong pin"); 
	    } else{
	
	   printf("weak pin"); 
	   	} 
		return 0;	
}
