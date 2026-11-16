#include <stdio.h>
#include <string.h>

int main(){
    char feedback[250];
    char upfeedback[250];
    
    printf("Enter customer feedback: ");
    fgets(feedback,250,stdin);

    int len=strlen(feedback);
    printf("Total characters: %d\n",len-1);

    char *findgood=strstr(feedback,"good");
    char *findbad=strstr(feedback,"bad");

    if(findgood!=NULL){
        printf("Sentiment: Positive (contains 'good')\n");
    }
    
  if(findbad!=NULL){
        printf("Sentiment: Negative (contains 'bad')\n");
        
        int position=findbad-feedback; 
        
        strcpy(upfeedback,"");

        strncat(upfeedback,feedback,position);
        
        strcat(upfeedback,"not good");
        
        strcat(upfeedback,findbad+3);
        
        printf("Updated Review: %s",upfeedback);
    }
    
    if(findgood==NULL && findbad==NULL){
        printf("Sentiment: Neutral\n");
    }

    return 0;
}
