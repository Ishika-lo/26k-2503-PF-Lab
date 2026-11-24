#include <stdio.h>
struct Product{
int ID;
char Name[30];
char Category[30];
float Price;
int StockQuantity;
};
void displayProductDetails(struct Product p){
float final=p.Price-(p.Price*0.05);
printf("id: %d\n",p.ID);
printf("name: %s\n",p.Name);
printf("category: %s\n",p.Category);
printf("original price: %.2f\n",p.Price);
printf("final price (5%% off): %.2f\n",final);
printf("stock: %d\n\n",p.StockQuantity);
}
int main(){
struct Product p1={101,"watch","accessories",1500.0,10};
struct Product p2={102,"shoes","fashion",2000.0,5};
displayProductDetails(p1);
displayProductDetails(p2);
return 0;
}
