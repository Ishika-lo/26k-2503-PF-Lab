#include <stdio.h>
int main (){
	char str[50];
	char rev[50];
	int i,len=0;
	int vowels=0,consonants=0;
	int pal=1;
	
	printf("Enter a word: ");
	scanf("%s", str);
	
	printf("Original word is: %s\n", str);
	
	for (i=0; str[i]!='\0'; i++){
		len++;
	}
	printf("Length of word is: %d\n", len);
	
	for (i=0; i<len; i++){
		rev[i]=str[len-1-i];
	}
	rev[len]='\0';
	printf("Reversed word is: %s\n", rev);
	
	for (i=0; i<len; i++){
		if (str[i]!=rev[i]){
			pal=0;
		}
	}
	if (pal==1){
		printf("The word is a palindrome\n");
	}
	else{
		printf("The word is not a palindrome\n");
	}
	
	for (i=0; i<len; i++){
		if (str[i]=='a' || str[i]=='e' || str[i]=='i' || str[i]=='o' || str[i]=='u' || str[i]=='A' || str[i]=='E' || str[i]=='I' || str[i]=='O' || str[i]=='U'){
			vowels++;
		}
		else{
			consonants++;
		}
	}
	printf("Number of vowels: %d\n", vowels);
	printf("Number of consonants: %d\n", consonants);
	
	return 0;
}
