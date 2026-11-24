#include <stdio.h>
struct Item{
int ID;
char Name[30];
int Quantity;
float UnitPrice;
};
int main(){
struct Item items[5];
int i,searchID,found=0;
float totalValue=0;
for(i=0;i<5;i++){
printf("enter details for item %d (id name qty price): ",i+1);
scanf("%d %s %d %f",&items[i].ID,items[i].Name,&items[i].Quantity,&items[i].UnitPrice);
totalValue=totalValue+(items[i].Quantity*items[i].UnitPrice);
}
printf("total inventory value: %.2f\n",totalValue);
printf("enter item id to search: ");
scanf("%d",&searchID);
for(i=0;i<5;i++){
if(items[i].ID==searchID){
printf("id: %d | name: %s | qty: %d | unit price: %.2f\n",items[i].ID,items[i].Name,items[i].Quantity,items[i].UnitPrice);
found=1;
}
}
if(found==0)
printf("item not found\n");
return 0;
}0
