#include <stdio.h>
#define TOLL_RATE 50
void processVehicle(char vehicleType[]){
static int totalVehicles=0;
static int totalRevenue=0;
totalVehicles++;
totalRevenue=totalRevenue+TOLL_RATE;
printf("processed: %s | total vehicles: %d | total toll collected: %d pkr\n",vehicleType,totalVehicles,totalRevenue);
}
int main(){
processVehicle("car");
processVehicle("truck");
processVehicle("bike");
processVehicle("bus");
return 0;
}
