#include <stdio.h>
int main(){
    float sensor_data[3][4]; 
    int faulty_col;
    printf("Enter temperature data for 3 days and 4 sensors:\n");
    for (int i=0; i<3;i++){
        for (int j=0; j<4; j++){
            scanf("%f", &sensor_data[i][j]);
        }
    }
    printf("Enter the column index (0-3) of the faulty sensor to delete: ");
    scanf("%d",&faulty_col);
    for (int i = 0; i < 3; i++) {
        for (int j = faulty_col; j < 3; j++) { // Loop goes up to 2, shifting col 3 into col 2
            sensor_data[i][j] = sensor_data[i][j + 1]; 
        }
    }
    printf("\nUpdated Sensor Data (3x3):\n");
    for (int i=0; i<3;i++) {
        for (int j=0; j<3; j++) { // Only print first 3 columns now
            printf("%.2f\t", sensor_data[i][j]);
        }
        printf("\n");
    }

    return 0;
}
