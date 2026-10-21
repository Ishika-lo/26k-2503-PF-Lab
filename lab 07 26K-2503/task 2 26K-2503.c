#include <stdio.h>
int main(){
    char logs[3][30]; 
    int total_uppercase = 0;

    printf("Enter 1 CSV log entry (e.g., Admin User, Access Granted, 10:45AM):\n");
    scanf(" %[^,], %[^,], %[^\n]", logs[0], logs[1], logs[2]);
    for (int i = 0; i < 3; i++){
        for (int j = 0; logs[i][j] != '\0'; j++){
            if (logs[i][j] >= 'A' && logs[i][j] <= 'Z') {
                total_uppercase++;
            }
        }
    }

    printf("\nParsed Log Fields:\n");
    printf("Username: %s\nStatus: %s\nTimestamp: %s\n",logs[0],logs[1],logs[2]);
    printf("Total uppercase letters: %d\n",total_uppercase);

    return 0;
}
