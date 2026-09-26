#include <stdio.h>
int main(){
	
	char c1;
	int c2;
	printf("Enter category, A for animal, V for vehicle, F for food, H for human ");
	scanf(" %c", &c1);
	switch(c1){
		case 'A': 
		case 'a':
		        printf("enter 1 for cat 2 for dog 3 for bird ");
		        scanf("%d", &c2);
		        switch(c2){
		        	case 1: printf("Animal-cat");
					break;
					case 2: printf("Animal-dog");
					break;
					case 3: printf("Animal-bird");
					break;
					default: printf("invalid choice entered");
					}
					break;
				
		case 'V': 
		case 'v':
		        printf("enter 1 for car 2 for bus 3 for bike ");
		        scanf("%d", &c2);
		        switch(c2){
		        	case 1: printf("Vehicle-car");
					break;
					case 2: printf("Vehicle-bus");
					break;
					case 3: printf("Vehicle-bike");
					break;
				    default: printf("invalid choice entered");
					}
						break;
				
		case 'F': 
		case 'f':
		        printf("enter 1 for pizza 2 for burger 3 for biryani ");
		        scanf("%d", &c2);
		        switch(c2){
		        	case 1: printf("Food-pizza");
					break;
					case 2: printf("Food-burger");
					break;
					case 3: printf("Food-biryani");
					break;
				    default: printf("invalid choice entered");
					}
						break;
				
		case 'H':
		case 'h':
		        printf("enter 1 for male 2 for female 3 for child ");
		        scanf("%d", &c2);
		        switch(c2){
		        	case 1: printf("Human-male");
					break;
					case 2: printf("Human-female");
					break;
					case 3: printf("Human-child");
					break;
				    default: printf("invalid choice entered");
					}
					break;
					default: printf("invalid choice entered");
	}
		  return 0;      
	}
