#include <stdio.h>
int main(){
	float data ;
	float priceGB;
	float Discount;
	
	printf("Enter Data used: ");
	scanf("%f", &data);
	getchar();
	
	printf("Enter Price per GB: ");
	scanf("%f", &priceGB);
	getchar();
	
	float Basic_Cost = (data * priceGB);
	
	if(data < 50){
		Discount = 0.0 ;
	}	
	else if(data >= 50 && data <100){
		Discount = (5.0/100)*Basic_Cost;		
	} 
	else if(data >=100 && data<200){
		Discount = (10.0/100)*Basic_Cost;
	}
	else{
		Discount = (15.0/100) * Basic_Cost;
	}
	
	float Discounted_Price = Basic_Cost - Discount;
	
	printf("The cost of data is  %.2f", Basic_Cost);
	printf("\nThe discount on the data used is %.2f", Discount);
	printf("\nThe price after discount is %.2f", Discounted_Price);
}
