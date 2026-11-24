#include "report.h"
#include "billing.h"
#include "product.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

static void FormatNow(char *out, size_t size)
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    if (local == NULL || strftime(out, size, "%Y-%m-%d %H:%M", local) == 0)
    {
        snprintf(out, size, "unknown");
    }
}

SalesReport BuildSalesReport(void)
{
    SalesReport report;
    memset(&report, 0, sizeof(report));

    double total = 0;
    for (int i = 0; i < saleCount; i++)
    {
        report.billCount++;
        report.itemsSold += sales[i].totalQuantity;
        total += sales[i].totalAmount;

        if (sales[i].totalAmount > report.highestBill)
        {
            report.highestBill = sales[i].totalAmount;
        }
        if (sales[i].vipNumber > 0)
        {
            bool seenBefore = false;
            for (int j = 0; j < i; j++)
            {
                if (sales[j].vipNumber == sales[i].vipNumber)
                {
                    seenBefore = true;
                    break;
                }
            }
            if (!seenBefore)
            {
                report.vipCustomers++;
            }
        }
    }

    report.totalSales = (float)total;
    report.averageBill = (report.billCount > 0) ? (float)(total / report.billCount) : 0;
    report.lowStockProducts = CountLowStock();
    FormatNow(report.generated, sizeof(report.generated));

    return report;
}

bool SaveSalesReport(const char *filename, const SalesReport *report)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return false;
    }

    fprintf(file, "SmartShop - Sales Report\n");
    fprintf(file, "Generated: %s\n", report->generated);
    fprintf(file, "------------------------------\n");
    fprintf(file, "Number of bills     : %d\n",   report->billCount);
    fprintf(file, "Items sold          : %d\n",   report->itemsSold);
    fprintf(file, "Total sales         : %.2f\n", report->totalSales);
    fprintf(file, "Average bill        : %.2f\n", report->averageBill);
    fprintf(file, "Highest bill        : %.2f\n", report->highestBill);
    fprintf(file, "VIP customers       : %d\n",   report->vipCustomers);
    fprintf(file, "Low-stock products  : %d\n",   report->lowStockProducts);

    return fclose(file) == 0;
}
