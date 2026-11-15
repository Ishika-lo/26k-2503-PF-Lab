#include <stdio.h>

float calculatediscount(float shoppingbill, char membertype){
    float discountpercent=0.0;

    if(membertype=='P' || membertype=='p'){
        discountpercent=0.20;
    }else if(membertype=='G' || membertype=='g'){
        discountpercent=0.10;
    }else if(membertype=='S' || membertype=='s'){
        discountpercent=0.05;
    }

    if(shoppingbill>10000){
        discountpercent=discountpercent+0.02;
    }

    float discountmoney=shoppingbill*discountpercent;
    return discountmoney;
}

float calculatefinalbill(float priceafterdiscount){
    float taxamount= priceafterdiscount*0.15;
    float totalwithtax= priceafterdiscount+taxamount;
    float shippingfee= 0;

    if (priceafterdiscount<=  5000){
        shippingfee= 300;
    }else{
        shippingfee =0;
    }

    return totalwithtax + shippingfee;
}

int main(){
    float mybill;
    char mymembership;

    printf("Enter membership type (P for Platinum, G for Gold, S for Standard): ");
    scanf(" %c",&mymembership);

    printf("Enter total shopping amount: ");
    scanf("%f",&mybill);

    float moneysaved= calculatediscount(mybill,mymembership);
    float discountedprice=mybill-moneysaved;
    float finalpayment=calculatefinalbill(discountedprice);

    printf("Discount given: %.2f PKR\n",moneysaved);
    printf("Price after discount: %.2f PKR\n",discountedprice);
    printf("Final amount to pay: %.2f PKR\n",finalpayment);

    return 0;
}
