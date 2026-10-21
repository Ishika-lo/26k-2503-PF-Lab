#include <stdio.h>
int main(){
    char sentences[3][100];

    printf("Enter 3 semicolon-separated sentences in one line:\n");
    for (int i=0; i<3;i++){
        scanf(" %[^;]%*c", sentences[i]); 
    }

    printf("\nVowel Analysis \n");
    for (int i = 0; i < 3; i++){
        int vowels =0;
        for (int j =0; sentences[i][j] !='\0'; j++){
            char ch = sentences[i][j];
            // Case-insensitive check
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
                ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U'){
                vowels++;
            }
        }
        printf("Sentence %d: %s | Vowels: %d\n", i + 1, sentences[i], vowels);
    }

    return 0;
}
