#include <stdio.h>
int calculateChecksum(int transactionID){
if(transactionID<10)
return transactionID;
int sum=0;
while(transactionID>0){
sum=sum+(transactionID%10);
transactionID=transactionID/10;
}
return calculateChecksum(sum);
}
int main(){
int id;
printf("enter transaction id: ");
scanf("%d",&id);
printf("checksum: %d\n",calculateChecksum(id));
return 0;
}
