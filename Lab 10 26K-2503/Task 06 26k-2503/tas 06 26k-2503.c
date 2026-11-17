#include <stdio.h>
#include <string.h>

int main(){
    char user[50];
    char pass[50];
    
    char typed[50];
    char typedp[50];
    int found=0; 
    FILE *ptr=fopen("credentials.txt","r");

    if(ptr==NULL){
        printf("Error: File not found!\n");
    }
	else{
        printf("Enter Username: ");
        scanf("%s",typed);
        printf("Enter Password: ");
        scanf("%s",typedp);
        while(fscanf(ptr,"%s %s",user,pass)!=EOF){
            if(strcmp(typed,user)==0 && strcmp(typedp,pass)==0){
                found=1;
                break;
            }
        }
        
        fclose(ptr);
		        if(found==1){
            printf("Access Granted!\n");
        }
		else
		{
            printf("Access Denied!\n");
        }
    }

    return 0;
}
