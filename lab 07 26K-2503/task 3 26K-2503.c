#include <stdio.h>
int main(){
    char secret_messages[3][100];

    printf("Enter 3 secret messages (uppercase and spaces only):\n");
    for (int i = 0; i < 3; i++){
        printf("Message %d: ", i+1);
        scanf(" %[A-Z ]", secret_messages[i]);
    }

    printf("\n Decrypted Intel \n");
    for (int i = 0; i < 3; i++){
        int spaces = 0;
        for (int j = 0; secret_messages[i][j] != '\0'; j++) {
            if (secret_messages[i][j] == ' ') {
                spaces++;
            }
        }
        int words = spaces + 1; // Assuming single spaces between words
        printf("Valid Message: %s | Word Count: %d\n", secret_messages[i], words);
    }

    return 0;
}
