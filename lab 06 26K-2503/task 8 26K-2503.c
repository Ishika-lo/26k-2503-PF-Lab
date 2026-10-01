#include <stdio.h>
int main (){
	int arr[9];
	int i,n,max,min,num;
	int found=0;
	int val,pos, del;
	for (i=0; i<8; i++) {
    printf("Enter element %d: ", i);
    scanf("%d", &n);
    arr[i]=n;
}
    max=arr[0];
    min=arr[0];
    printf("\n the elements of the array are: ");
    for (i=0; i<8; i++) {
    	printf("%d, ", arr[i]);
    	
    
    		if (arr[i]>max){
    			max= arr[i];
			}
			if (arr[i]<min){
    			min= arr[i];
			}
			 
		}
		printf("\nMaximum element is: %d", max);
        printf("\nMinimum element is: %d\n", min); 
        printf("\nEnter a number to search: ");
        scanf("%d", &num);
        for (i=0; i<8; i++){
        	if (arr[i]==num){
		
        	printf("The number %d is found at position %d (index %d)\n", num,i+1,i);
        	found=1;
        	}	
		}
		if (found==0)
		printf("the number %d is not found", num);
		printf("\nEnter value to insert: ");
		scanf("%d", &val);
		printf("\nEnter index to insert value (0-8): ");
		scanf("%d", &pos);
        for (i=8; i>pos; i--) {
    arr[i] = arr[i-1];
    
}	
    arr[pos]=val;
    printf("\n The array after insertion is:");
    for (i=0; i<9; i++)
    { printf("%d, ", arr[i]);
	}
	printf("\nEnter index to delete (0-8): ");
		scanf("%d", &del);
		for (i=del; i<8; i++) {
    arr[i]=arr[i+1];
}
 printf("\n The array after deletion is:");
    for (i=0; i<8; i++)
    { printf("%d, ", arr[i]);
	}
}
