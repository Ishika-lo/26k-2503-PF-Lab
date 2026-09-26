#include <stdio.h>
int main(){
	
	char c1;
	int c2;
	printf("Enter category, G for greeting, S for study, W for weather, H for help ");
	scanf(" %c", &c1);
	switch(c1){
		case 'G': 
		case 'g':
		        printf("enter 1 for displaying Hello 2 for displaying How are you 3 for displaying Goodbye ");
		        scanf("%d", &c2);
		        switch(c2){
		        	case 1: printf("Hello");
					break;
					case 2: printf("How are  you");
					break;
					case 3: printf("Goodbye");
					break;
					default: printf("invalid choice entered");
					}
					break;
				
		case 'S': 
		case 's':
		        printf("enter 1 for Programming 2 for Mathematics 3 for AI");
		        scanf("%d", &c2);
		        switch(c2){
		        	case 1: printf("Programming");
					break;
					case 2: printf("Mathematics");
					break;
					case 3: printf("AI");
					break;
				    default: printf("invalid choice entered");
					}
						break;
				
		case 'W': 
		case 'w':
		        printf("enter 1 for Today 2 for Tomorrow 3 for Forecast ");
		        scanf("%d", &c2);
		        switch(c2){
		        	case 1: printf("Today");
					break;
					case 2: printf("Tomorrow");
					break;
					case 3: printf("Forecast");
					break;
				    default: printf("invalid choice entered");
					}
						break;
				
		case 'H':
		case 'h':
		        printf("enter 1 for Chatbox 2 for Commands 3 for exit ");
		        scanf("%d", &c2);
		        switch(c2){
		        	case 1: printf("About chatbox");
					break;
					case 2: printf("Commands");
					break;
					case 3: printf("exit");
					break;
				    default: printf("invalid choice entered");
					}
					break;
					default: printf("invalid choice entered");
	}
		  return 0;      
	}
