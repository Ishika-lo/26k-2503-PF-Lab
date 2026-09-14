#include <stdio.h>
int main(){
	int User_Role ; 
	int status ; 
	int security ;
	
	printf("Enter User role (enter 1 for Admin , 2 for Researcher , 3 for Student)");
	scanf("%d", &User_Role);
	getchar();
	
	printf("Enter Account Status (1 for Active , 0 for Inactive)");
	scanf("%d", &status);
	getchar();
	
	printf("Enter Security Level");
	scanf("%d", &security);
	
	if (status==0){
       printf("Access denied");
}
    else if (User_Role == 1 && security<3) {
        printf("Admin access denied");
    }
    else if (User_Role == 1 && security>= 3){
        printf("Admin access granted");
    }
    else if (User_Role == 2 && security<2){
        printf("Researcher access denied");
    }
    else if (User_Role == 2 && security>=2){
        printf("Researcher access granted");
    }
    else if (User_Role == 3 && security<1){
        printf("Student access denied");
    }
    else if (User_Role == 3 && security>=1){
        printf("Student access granted");
    }
   
    else {
        printf("Access denied");
    }
}
       

