/* 
Group : 
B25IT1141 : Abhay Padavalkar
B25IT1142 : Saddab Ansari
B25IT1149 : Ishan Desai
B25IT1161 : Ankit Kharche

Problem Statement :
Design and Implement an Expense Tracker using C Language
Develop a comprehensive expense tracker application that records daily expenses, 
categorizes them, generates detailed monthly and annual reports, 
and provides budget management features for users to track and optimize
their spending habits.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- Structure Definition --- */
typedef struct {
    int id;
    int day;
    int month;
    int year;
    float amount;
    char category[50];
    char note[100];
} Expense;

/* --- Function Declarations --- */
void addExpense();
void viewAllExpenses();
void generateMonthlyReport();
void generateYearlyReport();
void setBudget();
void checkBudget(int month, int year);
void printSeparator();
int getNextId();

/* --- Global Constants --- */
const char *DATA_FILE   = "expenses.txt";
const char *BUDGET_FILE = "budget.txt";

int main() {
    int choice;

    while(1) {
        // Main Menu UI
        printSeparator();
        printf("\t  PERSONAL EXPENSE TRACKER\n");
        printSeparator();
        printf("1. Add New Expense\n");
        printf("2. View All Expenses\n");
        printf("3. Generate Monthly Report\n");
        printf("4. Generate Annual Report\n");
        printf("5. Set Monthly Budget\n");
        printf("6. Exit\n");
        printSeparator();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addExpense(); break;
            case 2: viewAllExpenses(); break;
            case 3: generateMonthlyReport(); break;
            case 4: generateYearlyReport(); break;
            case 5: setBudget(); break;
            case 6:
                printf("Exiting... Thank you for using Expense Tracker.\n");
                exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

/* --- Function to Add Expense --- */
void addExpense() {
    FILE *fp;
    Expense e;

    // Open file in Append mode
    fp = fopen(DATA_FILE, "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n--- Add New Expense ---\n");

    // Auto-generate ID (simplified logic)
    e.id = getNextId();

    printf("Enter Date (DD MM YYYY): ");
    scanf("%d %d %d", &e.day, &e.month, &e.year);

    printf("Enter Amount: ");
    scanf("%f", &e.amount);   /* BUG FIX: was "%float", must be "%f" */

    // Using " %[^\n]" to read string with spaces
    printf("Enter Category (e.g., Food, Travel): ");
    scanf(" %[^\n]", e.category);

    printf("Enter Note/Description: ");
    scanf(" %[^\n]", e.note);

    // Write to file
    fprintf(fp, "%d %d %d %d %.2f %s\n%s\n",
            e.id, e.day, e.month, e.year, e.amount, e.category, e.note);
    printf("Expense added successfully!\n");
    fclose(fp);

    // After adding, automatically check budget for that month/year
    checkBudget(e.month, e.year);
}

/* --- Function to View All Expenses --- */
void viewAllExpenses() {
    FILE *fp;
    Expense e;
    int count = 0;

    fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        printf("No records found. Add an expense first.\n");
        return;
    }

    printSeparator();
    printf("%-5s %-12s %-15s %-10s %-20s\n", "ID", "Date", "Category", "Amount", "Note");
    printSeparator();

    // Loop through file until End Of File (EOF)
    // Note format in fscanf must match fprintf
    while (fscanf(fp, "%d %d %d %d %f %[^\n]\n%[^\n]\n",
                  &e.id, &e.day, &e.month, &e.year, &e.amount, e.category, e.note) != EOF) {
        printf("%-5d %02d/%02d/%04d   %-15s $%-9.2f %-20s\n",
               e.id, e.day, e.month, e.year, e.category, e.amount, e.note);
        count++;
    }

    if(count == 0) {
        printf("No expenses recorded yet.\n");
    }

    fclose(fp);
    printf("\nPress any key to continue...");
    getchar(); getchar(); // Pause screen
}

/* --- Function for Monthly Report --- */
void generateMonthlyReport() {
    FILE *fp;
    Expense e;
    int targetMonth, targetYear;
    float total = 0;
    int found = 0;

    printf("\n--- Monthly Report ---\n");
    printf("Enter Month and Year (MM YYYY): ");
    scanf("%d %d", &targetMonth, &targetYear);

    fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        printf("No data available.\n");
        return;
    }

    printSeparator();
    printf("Expenses for %02d/%04d:\n", targetMonth, targetYear);

    while (fscanf(fp, "%d %d %d %d %f %[^\n]\n%[^\n]\n",
                  &e.id, &e.day, &e.month, &e.year, &e.amount, e.category, e.note) != EOF) {

        if (e.month == targetMonth && e.year == targetYear) {
            printf(" - %02d/%02d: $%.2f (%s) | %s\n",
                   e.day, e.month, e.amount, e.category, e.note);
            total += e.amount;
            found = 1;
        }
    }

    printSeparator();
    if (found) {
        printf("TOTAL EXPENSE FOR MONTH: $%.2f\n", total);
    } else {
        printf("No expenses found for this month.\n");
    }
    fclose(fp);

    // Show budget warning after displaying the report
    if (found) {
        checkBudget(targetMonth, targetYear);
    }
}

/* --- Function for Yearly Report --- */
void generateYearlyReport() {
    FILE *fp;
    Expense e;
    int targetYear;
    float monthlyTotals[13] = {0}; /* index 1..12 for months */
    float grandTotal = 0;
    int found = 0;

    printf("\n--- Annual Report ---\n");
    printf("Enter Year (YYYY): ");
    scanf("%d", &targetYear);

    fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        printf("No data available.\n");
        return;
    }

    while (fscanf(fp, "%d %d %d %d %f %[^\n]\n%[^\n]\n",
                  &e.id, &e.day, &e.month, &e.year, &e.amount, e.category, e.note) != EOF) {
        if (e.year == targetYear && e.month >= 1 && e.month <= 12) {
            monthlyTotals[e.month] += e.amount;
            grandTotal += e.amount;
            found = 1;
        }
    }
    fclose(fp);

    printSeparator();
    printf("Annual Breakdown for %d:\n", targetYear);
    printSeparator();

    /* Month name lookup */
    const char *monthNames[] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    if (found) {
        for (int m = 1; m <= 12; m++) {
            if (monthlyTotals[m] > 0) {
                printf("  %-12s : $%.2f\n", monthNames[m], monthlyTotals[m]);
            }
        }
        printSeparator();
        printf("TOTAL EXPENSE FOR YEAR %d: $%.2f\n", targetYear, grandTotal);
    } else {
        printf("No expenses found for year %d.\n", targetYear);
    }
    printSeparator();
}

/* --- Function to Set Monthly Budget --- */
void setBudget() {
    FILE *fp;
    int month, year;
    float budgetAmount;

    printf("\n--- Set Monthly Budget ---\n");
    printf("Enter Month and Year (MM YYYY): ");
    scanf("%d %d", &month, &year);

    printf("Enter Budget Amount for %02d/%04d: $", month, year);
    scanf("%f", &budgetAmount);

    if (budgetAmount <= 0) {
        printf("Invalid budget amount. Must be greater than 0.\n");
        return;
    }

    /*
     * Budget file format: one entry per line
     *   MM YYYY AMOUNT
     * If a budget already exists for that month/year, we overwrite it.
     * Strategy: read all entries, update the matching one (or append), rewrite.
     */

    int bMonth, bYear;
    float bAmount;
    int updated = 0;

    /* Read existing budgets into a temporary buffer */
    #define MAX_BUDGETS 200
    int   bMonths[MAX_BUDGETS];
    int   bYears[MAX_BUDGETS];
    float bAmounts[MAX_BUDGETS];
    int   bCount = 0;

    fp = fopen(BUDGET_FILE, "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d %d %f", &bMonth, &bYear, &bAmount) == 3
               && bCount < MAX_BUDGETS) {
            bMonths[bCount]  = bMonth;
            bYears[bCount]   = bYear;
            bAmounts[bCount] = bAmount;
            bCount++;
        }
        fclose(fp);
    }

    /* Update existing entry or mark as new */
    for (int i = 0; i < bCount; i++) {
        if (bMonths[i] == month && bYears[i] == year) {
            bAmounts[i] = budgetAmount;
            updated = 1;
            break;
        }
    }
    if (!updated && bCount < MAX_BUDGETS) {
        bMonths[bCount]  = month;
        bYears[bCount]   = year;
        bAmounts[bCount] = budgetAmount;
        bCount++;
    }

    /* Rewrite the budget file */
    fp = fopen(BUDGET_FILE, "w");
    if (fp == NULL) {
        printf("Error saving budget!\n");
        return;
    }
    for (int i = 0; i < bCount; i++) {
        fprintf(fp, "%d %d %.2f\n", bMonths[i], bYears[i], bAmounts[i]);
    }
    fclose(fp);

    printf("Budget of $%.2f set for %02d/%04d successfully!\n",
           budgetAmount, month, year);

    /* Immediately show status against current spending */
    checkBudget(month, year);
}

/* --- Function to Check Budget vs Actual Spending --- */
void checkBudget(int month, int year) {
    FILE *fp;
    Expense e;
    float totalSpent = 0;
    float budget = -1;
    int bMonth, bYear;
    float bAmount;

    /* Read budget for this month/year */
    fp = fopen(BUDGET_FILE, "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d %d %f", &bMonth, &bYear, &bAmount) == 3) {
            if (bMonth == month && bYear == year) {
                budget = bAmount;
                break;
            }
        }
        fclose(fp);
    }

    /* No budget set — nothing to warn about */
    if (budget < 0) return;

    /* Sum expenses for this month/year */
    fp = fopen(DATA_FILE, "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d %d %d %d %f %[^\n]\n%[^\n]\n",
                      &e.id, &e.day, &e.month, &e.year,
                      &e.amount, e.category, e.note) != EOF) {
            if (e.month == month && e.year == year) {
                totalSpent += e.amount;
            }
        }
        fclose(fp);
    }

    float remaining = budget - totalSpent;
    float usedPct   = (totalSpent / budget) * 100.0f;

    printSeparator();
    printf("BUDGET STATUS for %02d/%04d:\n", month, year);
    printf("  Budget Set   : $%.2f\n", budget);
    printf("  Total Spent  : $%.2f (%.1f%%)\n", totalSpent, usedPct);

    if (totalSpent > budget) {
        printf("  Remaining    : -$%.2f\n", -remaining);
        printf("  !! WARNING: You have EXCEEDED your budget by $%.2f !!\n",
               totalSpent - budget);
    } else if (usedPct >= 80.0f) {
        printf("  Remaining    : $%.2f\n", remaining);
        printf("  ** ALERT: You have used %.1f%% of your budget. Spend carefully! **\n",
               usedPct);
    } else {
        printf("  Remaining    : $%.2f\n", remaining);
        printf("  You are within budget. Good job!\n");
    }
    printSeparator();
}

/* --- Helper: Get next ID based on file line count --- */
int getNextId() {
    FILE *fp = fopen(DATA_FILE, "r");
    int count = 0;
    char c;
    if (fp == NULL) return 1;

    // Logic: Count new lines to estimate records.
    // Since we write 2 lines per record (data + note), we divide by 2.
    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n') count++;
    }
    fclose(fp);
    return (count / 2) + 1;
}

/* --- Helper: Print a formatting line --- */
void printSeparator() {
    printf("--------------------------------------------------\n");
}
