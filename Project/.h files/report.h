#ifndef REPORT_H
#define REPORT_H
#include <stdbool.h>

typedef struct {
    int   billCount;
    int   itemsSold;
    float totalSales;
    float averageBill;
    float highestBill;
    int   vipCustomers;
    int   lowStockProducts;
    char  generated[20];
} SalesReport;

SalesReport BuildSalesReport(void);
bool SaveSalesReport(const char *filename, const SalesReport *report);

#endif
