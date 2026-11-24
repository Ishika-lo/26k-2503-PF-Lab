#include <stdio.h>
struct Address{
char City[30];
int ZipCode;
char State[30];
};
struct Student{
int RollNo;
char Name[30];
float CGPA;
struct Address studentAddress;
};
int main(){
struct Student student1={101,"ali",3.6,{"karachi",75500,"sindh"}};
printf("roll no: %d\n",student1.RollNo);
printf("name: %s\n",student1.Name);
printf("cgpa: %.2f\n",student1.CGPA);
printf("city: %s\n",student1.studentAddress.City);
printf("zip code: %d\n",student1.studentAddress.ZipCode);
printf("state: %s\n",student1.studentAddress.State);
return 0;
}
