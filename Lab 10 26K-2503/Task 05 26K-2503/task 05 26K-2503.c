#include <stdio.h>

int main(){
    char rollno[15];
    char name[50];
    int marks;

    FILE *ptr=fopen("marks.txt","r");

    if(ptr==NULL){
        printf("Error: File Not Found!\n");
    }
	else{
        printf("Roll No \t Name \t\t Marks\n");
        while(fscanf(ptr,"%s %s %d",rollno,name,&marks)!=EOF){
            printf("%s \t\t %s \t\t %d\n",rollno,name,marks);
        }
        
        fclose(ptr);
    }
    return 0;
}
