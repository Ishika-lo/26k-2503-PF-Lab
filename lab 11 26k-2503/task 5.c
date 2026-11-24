#include <stdio.h>
struct HospitalRecord{
int roomNo;
char ward[20];
struct PatientInfo{
int patientID;
char patientName[30];
}patient;
};
int main(){
struct HospitalRecord rec={204,"emergency",{55,"sara"}};
struct HospitalRecord *ptr=&rec;
printf("room no: %d\n",ptr->roomNo);
printf("ward: %s\n",ptr->ward);
printf("patient id: %d\n",ptr->patient.patientID);
printf("patient name: %s\n",ptr->patient.patientName);
return 0;
}
