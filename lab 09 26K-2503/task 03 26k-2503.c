#include <stdio.h>

int main(){
    int picture[3][3];
    int (*ptr)[3]=picture;
    int row, col;

    printf("Enter 9 pixel values for the 3x3 picture:\n");
    for(row=0;row<3;row++){
        for(col=0;col<3;col++){
            scanf("%d",(*(ptr+row)+col));
        }
    }

    for(row=0;row<3;row++){
        for(col=0;col<3;col++){
            *(*(ptr+row)+col)=*(*(ptr+row)+col)*2;
        }
    }

    printf("Updated picture pixels:\n");
    for(row=0;row<3;row++){
        for(col=0;col<3;col++){
            printf("%d ",*(*(ptr+row)+col));
        }
        printf("\n");
    }

    return 0;
}
