#include <stdio.h>

void printsensordata(void *sensorinfo, char infotype){
    if(infotype=='f'){
        float *tempptr=(float *)sensorinfo;
        printf("Temperature: %.2f Celsius\n",*tempptr);
    }else if(infotype=='i'){
        int *motionptr=(int *)sensorinfo;
        if(*motionptr==1){
            printf("Motion detected\n");
        }else{
            printf("No motion\n");
        }
    }else if(infotype=='c'){
        char *doorptr=(char *)sensorinfo;
        if(*doorptr=='O'){
            printf("Door open\n");
        }else if(*doorptr=='C'){
            printf("Door closed\n");
        }
    }
}

int main(){
    float roomtemperature=24.5;
    int ismotiondetected=1;
    char frontdoorstatus='C';

    printf("Smart home sensor status \n");

    printsensordata(&roomtemperature,'f');
    printsensordata(&ismotiondetected,'i');
    printsensordata(&frontdoorstatus,'c');

    return 0;
}
