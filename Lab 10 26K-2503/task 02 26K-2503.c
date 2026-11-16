#include <stdio.h>
#include <string.h>
int main(){
    char names[10][50];
    char tempname[50];
    int i, j;

    printf("Enter 10 student names:\n");
    for (i=0; i<10; i++){
        fgets(names[i],50,stdin);
    }

    for (i=0; i<9; i++){
        for (j=0;j<9-i; j++){
            if (strcmp(names[j], names[j + 1])>0){
                strcpy(tempname, names[j]);
                strcpy(names[j], names[j +1]);
                strcpy(names[j+1], tempname);
            }
        }
    }

    printf("\nSorted Alphabetical Order:\n");
    for (i=0; i<10; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}
