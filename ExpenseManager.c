#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 50
#define M 30
#define MAX_CATEGORIES 5

char incomeCategories[MAX_CATEGORIES][N] = {
    "Salary",
    "Grants",
    "Rental",
    "Awards",
    "Dividends"
};

char expenseCategories[MAX_CATEGORIES][N] = {
    "Food",
    "Travel",
    "Shopping",
    "Bills",
    "Education"
};

double currentIncome = 0;
double currentExpense = 0;

struct treeNode {
    char date[M];
    double amount;
    char category[N];
    struct treeNode* left;
    struct treeNode* right;
};

struct record {
    double x;
    double y;
};

struct treeNode* incomeRoot = NULL;
struct treeNode* expenseRoot = NULL;

struct treeNode* createTreeNode(char x[], double y, char z[]);
void insertTreeNode(struct treeNode** root, struct treeNode* newNode);
void displayTreeByCategory(struct treeNode* root, char searchCategory[]);
void displayTreeByDate(struct treeNode* root, char searchDate[]);
void deleteTree(struct treeNode* root);
void writeTreeToFile(struct treeNode* root, const char* filename);
struct treeNode* readTreeFromFile(const char* filename);
void writeRecordToFile(struct record* point, const char* filename);
struct record* readRecordFromFile(const char* filename);
bool isDateValid(int day, int month, int year);

int main() {
    int option;
    double b;
    char c[N], a[M];
    char s1[15], s2[15], s3[15];
    char searchDate[M];
    int day, month, year;

    struct record* point;

    point = readRecordFromFile("Record.bin");
    if (point != NULL) {
        currentIncome = point->x;
        currentExpense = point->y;
        free(point);
    }

    incomeRoot = readTreeFromFile("myincome.bin");
    expenseRoot = readTreeFromFile("myexpense.bin");

    do {
        printf("                                  _______________________________________________\n");
        printf("                                       YOUR INCOME   =      %.2lf INR     \n     ", currentIncome);
        printf("                                  YOUR EXPENSE  =      %.2lf INR     \n     ", currentExpense);
        printf("                                  YOUR BALANCE  =      %.2lf INR     \n     ", currentIncome - currentExpense);
        printf("                             _______________________________________________\n");
        printf("ENTER AN OPTION FROM BELOW \n\n");
        printf("1. INSERT INCOME \n");
        printf("2. INSERT EXPENSE \n");
        printf("3. VIEW INCOME RECORD BY CATEGORY\n");
        printf("4. VIEW EXPENSE RECORD BY CATEGORY\n");
        printf("5. VIEW INCOME RECORD BY DATE\n");
        printf("6. VIEW EXPENSE RECORD BY DATE\n");
        printf("7. EXIT\n");
        scanf("%d", &option);
        printf("\n\n\n");

        switch (option) {
            case 1:
                printf("*************   INSERT INCOME   *************\n\n");
                printf("Enter The Date (e.g., day month year):\n");
                scanf("%d %d %d", &day, &month, &year);
                if (!isDateValid(day, month, year)) {
                    printf("Invalid date. Please enter a valid date.\n");
                    break;
                }
                snprintf(a, M, "%d %d %d", day, month, year);
                printf("Enter The Amount:\n");
                if (scanf("%lf", &b) != 1) {
                    printf("Invalid amount. Please enter a valid numerical amount.\n");
                    while (getchar() != '\n');
                    break;
                }

                // Select an Income Category
                printf("1.Salary  2.Grants  3.Rental  4.Awards  5.Dividends \nSelect an Income Category (1-5) or enter a custom category: ");
                int incomeCategory;
                scanf("%d", &incomeCategory);
                if (incomeCategory >= 1 && incomeCategory <= MAX_CATEGORIES) {
                    printf("Category %d: %s\n", incomeCategory, incomeCategories[incomeCategory - 1]);
                    strcpy(c, incomeCategories[incomeCategory - 1]);
                } else {
                    printf("Enter a custom Income Category: ");
                    scanf("%s", c);
                }

                currentIncome += b;
                insertTreeNode(&incomeRoot, createTreeNode(a, b, c));
                writeTreeToFile(incomeRoot, "myincome.bin");
                break;

            case 2:
                printf("*************    INSERT EXPENSE   *************\n\n");
                printf("Enter The Date (e.g., day month year):\n");
                scanf("%d %d %d", &day, &month, &year);
                if (!isDateValid(day, month, year)) {
                    printf("Invalid date. Please enter a valid date.\n");
                    break;
                }
                snprintf(a, M, "%d %d %d", day, month, year);
                printf("Enter The Amount:\n");
                if (scanf("%lf", &b) != 1) {
                    printf("Invalid amount. Please enter a valid numerical amount.\n");
                    while (getchar() != '\n');
                    break;
                }

                // Select an Expense Category
                printf("1.Food  2.Travel  3.Shopping  4.Bills  5.Education \nSelect an Expense Category (1-5) or enter a custom category: ");
                int expenseCategory;
                scanf("%d", &expenseCategory);
                if (expenseCategory >= 1 && expenseCategory <= MAX_CATEGORIES) {
                    printf("Category %d: %s\n", expenseCategory, expenseCategories[expenseCategory - 1]);
                    strcpy(c, expenseCategories[expenseCategory - 1]);
                } else {
                    printf("Enter a custom Expense Category: ");
                    scanf("%s", c);
                }

                currentExpense += b;
                insertTreeNode(&expenseRoot, createTreeNode(a, b, c));
                writeTreeToFile(expenseRoot, "myexpense.bin");
                break;

            case 3:
                printf("*********   VIEW INCOME RECORD BY CATEGORY   *********\n\n");
                char searchCategory[N];
                printf("Enter a category to view (or 'All' to view all income records): ");
                scanf("%s", searchCategory);
                displayTreeByCategory(incomeRoot, searchCategory);
                break;

            case 4:
                printf("*********   VIEW EXPENSE RECORD BY CATEGORY   *********\n\n");
                printf("Enter a category to view (or 'All' to view all expense records): ");
                scanf("%s", searchCategory);
                displayTreeByCategory(expenseRoot, searchCategory);
                break;

            case 5:
                printf("*********   VIEW INCOME RECORD BY DATE   *********\n\n");
                printf("Enter a date to view income records (e.g., day month year): ");
                scanf("%d %d %d", &day, &month, &year);
                if (!isDateValid(day, month, year)) {
                    printf("Invalid date. Please enter a valid date.\n");
                    break;
                }
                snprintf(searchDate, M, "%d %d %d", day, month, year);
                displayTreeByDate(incomeRoot, searchDate);
                break;

            case 6:
                printf("*********   VIEW EXPENSE RECORD BY DATE   *********\n\n");
                printf("Enter a date to view expense records (e.g., day month year): ");
                scanf("%d %d %d", &day, &month, &year);
                if (!isDateValid(day, month, year)) {
                    printf("Invalid date. Please enter a valid date.\n");
                    break;
                }
                snprintf(searchDate, M, "%d %d %d", day, month, year);
                displayTreeByDate(expenseRoot, searchDate);
                break;

            case 7:
                point = (struct record*)malloc(sizeof(struct record));
                point->x = currentIncome;
                point->y = currentExpense;
                writeRecordToFile(point, "Record.bin");
                free(point);
                break;

            default:
                printf("WRONG OPTION SELECTED - Enter a Valid Option\n");
                break;
        }
    } while (option != 7);

    deleteTree(incomeRoot);
    deleteTree(expenseRoot);

    return 0;
}

bool isDateValid(int day, int month, int year) {
    if (year < 2000 || year > 2023) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        daysInMonth[2] = 29;  
    }

    if (day < 1 || day > daysInMonth[month]) {
        return false;
    }

    return true;
}

struct treeNode* createTreeNode(char x[], double y, char z[]) {
    struct treeNode* newNode = (struct treeNode*)malloc(sizeof(struct treeNode));
    strcpy(newNode->date, x);
    newNode->amount = y;
    strcpy(newNode->category, z);
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insertTreeNode(struct treeNode** root, struct treeNode* newNode) {
    if (*root == NULL) {
        *root = newNode;
    } else {
        if (newNode->amount < (*root)->amount) {
            insertTreeNode(&(*root)->left, newNode);
        } else {
            insertTreeNode(&(*root)->right, newNode);
        }
    }
}

void displayTree(struct treeNode* root, int a3) {
    if (a3 == 3) {
        if (root == NULL) {
            printf("NO RECORDS AVAILABLE\n\n");
        } else {
            displayTree(root->left, a3);
            printf("Date: %s\nAmount: %.2lf INR\nCategory: %s\n\n", root->date, root->amount, root->category);
            displayTree(root->right, a3);
        }
    } else if (a3 == 4) {
        if (root == NULL) {
            printf("NO RECORDS AVAILABLE\n\n");
        } else {
            displayTree(root->left, a3);
            printf("Date: %s\nAmount: %.2lf INR\nCategory: %s\n\n", root->date, root->amount, root->category);
            displayTree(root->right, a3);
        }
    }
}

void displayTreeByCategory(struct treeNode* root, char searchCategory[]) {
    if (root == NULL) {
        return;
    } else {
        displayTreeByCategory(root->left, searchCategory);
        if (strcmp(searchCategory, "All") == 0 || strcmp(root->category, searchCategory) == 0) {
            printf("Category: %s\nDate: %s\nAmount: %.2lf INR\n\n", root->category, root->date, root->amount);
        }
        displayTreeByCategory(root->right, searchCategory);
    }
}

void displayTreeByDate(struct treeNode* root, char searchDate[]) {
    if (root == NULL) {
        return;
    } else {
        displayTreeByDate(root->left, searchDate);
        if (strcmp(root->date, searchDate) == 0) {
            printf("Date: %s\nCategory: %s\nAmount: %.2lf INR\n\n", root->date, root->category, root->amount);
        }
        displayTreeByDate(root->right, searchDate);
    }
}

void deleteTree(struct treeNode* root) {
    if (root == NULL) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

void writeTreeToFile(struct treeNode* root, const char* filename) {
    FILE* fpointer = fopen(filename, "wb");
    if (fpointer != NULL) {
        if (root != NULL) {
            fwrite(root, sizeof(struct treeNode), 1, fpointer);
            writeTreeToFile(root->left, filename);
            writeTreeToFile(root->right, filename);
        }
        fclose(fpointer);
    } else {
        printf("CANNOT SAVE DATA...TRY AGAIN\n\n");
    }
}

struct treeNode* readTreeFromFile(const char* filename) {
    FILE* fpointer = fopen(filename, "rb");
    struct treeNode* root = NULL;
    if (fpointer != NULL) {
        struct treeNode node;
        while (fread(&node, sizeof(struct treeNode), 1, fpointer)) {
            insertTreeNode(&root, createTreeNode(node.date, node.amount, node.category));
        }
        fclose(fpointer);
    }
    return root;
}

void writeRecordToFile(struct record* point, const char* filename) {
    FILE* fpointer = fopen(filename, "wb");
    if (fpointer != NULL) {
        fwrite(point, sizeof(struct record), 1, fpointer);
        fclose(fpointer);
    } else {
        printf("FILE OPEN ERROR\n");
    }
}

struct record* readRecordFromFile(const char* filename) {
    FILE* fpointer = fopen(filename, "rb");
    struct record* ptr = NULL;
    if (fpointer != NULL) {
        ptr = (struct record*)malloc(sizeof(struct record));
        fread(ptr, sizeof(struct record), 1, fpointer);
        fclose(fpointer);
    }
    return ptr;
}