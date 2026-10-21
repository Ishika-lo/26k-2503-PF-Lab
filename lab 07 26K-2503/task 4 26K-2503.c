#include <stdio.h>
int main(){
    char word_grid[3][100];

    printf("Enter 3 rows of space-separated words:\n");
    for (int i = 0; i < 3; i++) {
        scanf(" %[^\n]", word_grid[i]); 
    }

    int max_length = 0;
    int max_row = 0;
    int max_col = 0;
    for (int i = 0; i<3; i++){
        int current_length =0;
        int word_start_col =0;
        for (int j = 0; word_grid[i][j] !='\0'; j++){
            if (word_grid[i][j] != ' ') {
                if (current_length == 0) word_start_col = j; // Mark start of a new word
                current_length++;
            } 
            
            // If space is hit or string ends, evaluate the word
            if (word_grid[i][j] == ' ' || word_grid[i][j+1] == '\0'){
                if (current_length>max_length){
                    max_length = current_length;
                    max_row = i;
                    max_col = word_start_col;
                }
                current_length = 0; // Reset for the next word
            }
        }
    }

    printf("\nLongest word starts at Row %d, Col %d with length %d.\n", max_row, max_col, max_length);
    return 0;
}
