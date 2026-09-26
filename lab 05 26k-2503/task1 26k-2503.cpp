#include <stdio.h>

int main() {
    float programming, math, ai, attendance;
    
    printf("Enter Programming marks (0-100):");
    scanf("%f", &programming);
    printf("Enter Mathematics marks (0-100):");
    scanf("%f", &math);
    printf("Enter AI marks (0-100):");
    scanf("%f", &ai);
    printf("Enter Attendance percentage (0-100):");
    scanf("%f", &attendance);

  
    if (programming >= 50 && math >= 50 && ai >= 50 && attendance >= 75) {
        float average = (programming + math + ai) / 3;
        printf("Student is eligible.\n");
        printf("Average Marks: %.2f\n", average);

      
        if (average >= 80) {
            printf("Performance: excellent\n");
        } else if (average >= 70) {
            printf("Performance: very good\n");
        } else if (average >= 60) {
            printf("Performance: good\n");
        } else if (average >= 50) {
            printf("Performance: satisfactory\n");
        } else {
            printf("Performance: Poor\n");
        }
    } else {
        printf("\nStudent is Not Eligible\n");
    }

    return 0;
}
