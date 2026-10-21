#include <stdio.h>
int main(){
   
    char student_names[3][50]; 
    int marks[3][3];

  
    for (int i = 0; i < 3; i++){
        printf("Enter full name of student %d: ", i + 1);
        scanf(" %[^\n]", student_names[i]); 

        printf("Enter 3 subject marks for %s: ", student_names[i]);
        for (int j = 0; j < 3; j++){
            scanf("%d", &marks[i][j]);
        }
    }

    printf("\nStudent Report \n");
 
    for (int i = 0; i < 3; i++){
        int sum = 0;
        for (int j = 0; j < 3; j++){
            sum += marks[i][j];
        }
        printf("Name: %s | Average Marks: %d\n", student_names[i], sum / 3);
    }

    return 0;
}

