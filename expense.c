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
void printSeparator();
int getNextId();

/* --- Global Constants --- */
const char *DATA_FILE = "expenses.txt";
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
        printf("5. Exit\n");
        printSeparator();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addExpense(); break;
            case 2: viewAllExpenses(); break;
            case 3: generateMonthlyReport(); break;
            case 4: generateYearlyReport(); break;
            case 5: 
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
    scanf("%float", &e.amount);

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
            printf(" - %02d/%02d: $%.2f (%s)\n", e.day, e.month, e.amount, e.category);
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
}

/* --- Function for Yearly Report --- */
void generateYearlyReport() {
    FILE *fp;
    Expense e;
    int targetYear;
    float total = 0;

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
        if (e.year == targetYear) {
            total += e.amount;
        }
    }

    printSeparator();
    printf("TOTAL EXPENSE FOR YEAR %d: $%.2f\n", targetYear, total);
    printSeparator();
    fclose(fp);
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