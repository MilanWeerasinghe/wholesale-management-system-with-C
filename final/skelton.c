#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <conio.h>
#include<time.h>

#define SIZE 50
#define BILLSIZE 20
#define ENTER_KEY 13
#define BACKSPACE_KEY 8

enum bool {FALSE,TRUE};
enum choice {YES=1,NO=2};
enum userAccountType {OWNER = 1, SALES_REP};
enum ownerMainMenu {ADD_ACCOUNT = 1, ADD_PRODUCT, EDIT_PRODUCT, SEARCH_PRODUCT, AVAILABLE_STOCK, OUT_OF_STOCK, EXPIRING_STOCK, BILL_INVOICE, DELETE_PRODUCT, EXIT};
enum salesRepMainMenu {SEARCH = 1, VIEW_AVAILABLE_STOCK, VIEW_OUT_OF_STOCK, VIEW_EXPIRING_STOCK, EXIT_PROGRAM};

struct date
{
    int year;
    int month;
    int date;
};
struct product
{
    char name[20];
    char code[20];
    char company[20];
    double unitPrice;
    int quantity;
    struct date expireDate;
};
struct billItem
{
    char itemName[30];
    double unitPrice;
    int quantity;
    double oneItemTotal;
};

struct invoice
{
    int billNumber;
    char customerName[30];
    char address[50];
    double totalAmount;
    int discountRate;
    double discountValue;
    double netAmount;

};

//Function Prototype
void welcome();
void login(int *userType);
void readUserNamePassword(char *username, char *password);
int verifyLoginData(const char *userName,const char* Password);

void userRegistration();
void readUserType(int* userType);
int verifyRegistrationData(const int userType, const char* username);
void saveLoginDetails(const char username[],const char password[],const int userType);

void menuForOwner(int* userChoice);
void menuForSalesRep(int *userChoice);

void addProductDetails(struct product item[], int* productCount);
void readProduct(struct product *item, const int indexNo);
int compareProductCode(const struct product item[],const int indexNo);
void validatePrice(const double enteredPrice, int *validityStatus);
void validateQuantity(const int enteredQuantity, int *validityStatus);
void validateDate(struct product item[], const int indexNo, int *validityStatus);


void availableStock(struct product item[], const int productCount);
void printAvailableStock(const struct product item[], const double totalAmount,const double oneItemTotal[], const int productCount);
void calculateTotalAmount(double oneItemValue[], double* totalAmount,const struct product item[], const int productCount);

void outOfStock(const struct product item[], const int productCount);
void printOutOfStock(const struct product item[],const int indexNo[],const int indexCount);
void compareQuantity(const struct product item[], int zeroQtyProductIndexNo[], int* indexCount,const int productCount);

void expiredStock(const struct product item[], const int productCount);
void printExpiringStock(const struct product item[],const int indexNo[], const int indexCount, const int expireYear);
int getExpireYear();
void compareExpireDate(const struct product item[], const int expireYear, int expiredProductIndexNo[],int* indexCount, const int productCount);

void searchProduct(const struct product item[],const int productCount);
void printSearchDetails(const struct product item[],const int productAvailability,const int productIndexNo);
void readName(char* userEnteredName);
int compareProductName(const struct product item[],const char *userEnteredName,int* productIndexNo, const int productCount);

void editProduct(struct product item[],const int productCount);

void billInvoice(struct product item[], const int productCount);
void printCustomerInvoice(const struct invoice invoiceNo, const struct billItem itemNo[], const int count);
void readCustomerDetails(char* customerName, char* address);
void readProductDetails(struct billItem *itemNo,const int count);
int validateDetails(const struct product item[],struct billItem itemNo[], const int indexNo, const int productCount, int* productIndexNo);
void getOneItemTotal(struct billItem *itemNo, const int count);
void getTotal(const struct billItem itemNo[], double *totalAmount, const int count);
void getDiscount(struct invoice *invoiceNo);
void getNetAmount(struct invoice *invoiceNo);
void reduceQuantity(struct product item[], const int userEnteredQuantity, const int productIndexNo);

void deleteData(struct product item[], int* productCount);
int confirmDeletion(const int productAvailability);
void deleteTheRecord(const struct product item[], int productIndexNo, const int productCount);

void saveProductDetailsToFlie(const struct product item[],const int indexNo);
void saveDataToTempFile(const struct product item[], const int productCount);
void saveInvoiceDataToFile(const struct invoice invoiceNo, const struct billItem itemNo[], const int count);
void getBillNo(int* billNumber);
void readProductDetailsFromFlie(struct product item[], int* productCount);
void saveInvoiceDataToFile();

void printStatment1(const int productAvailability);
void printStatement2(const int haveSameName);
void printStatement3();
int choice();

void main()
{

    struct product item[SIZE]; // Declaring a structure for getting product list

    int userChoice=0;
    int userType = OWNER;
    int productCount = 0;

    system("COLOR 0E");

    welcome();
    login(&userType);
    readProductDetailsFromFlie(item, &productCount); // Read the product list from file

    if(userType == OWNER)
    {
        do
        {
            menuForOwner(&userChoice);
            system("cls");
            switch(userChoice)
            {
            case ADD_ACCOUNT:
                userRegistration();
                break;

            case ADD_PRODUCT:
                addProductDetails(item, &productCount);
                break;

            case EDIT_PRODUCT:
                editProduct(item, productCount);
                break;

            case SEARCH_PRODUCT:
                searchProduct(item, productCount);
                break;

            case AVAILABLE_STOCK:
                availableStock(item, productCount);
                break;

            case OUT_OF_STOCK:
                outOfStock(item, productCount);
                break;

            case EXPIRING_STOCK:
                expiredStock(item, productCount);
                break;

            case BILL_INVOICE:
                billInvoice(item, productCount);
                break;

            case DELETE_PRODUCT:
                deleteData(item, &productCount);
                break;

            case EXIT:
                exit(0);
                break;
            }
        }
        while(userChoice!=EXIT);
    }

    else if(userType == SALES_REP)
    {
        do
        {
            menuForSalesRep(&userChoice);
            system("cls");
            switch(userChoice)
            {
            case SEARCH:
                searchProduct(item, productCount);
                break;

            case VIEW_AVAILABLE_STOCK:
                availableStock(item, productCount);
                break;

            case VIEW_OUT_OF_STOCK:
                outOfStock(item, productCount);
                break;

            case VIEW_EXPIRING_STOCK:
                expiredStock(item, productCount);
                break;

            case EXIT_PROGRAM:
                exit(0);
                break;
            }
        }
        while(userChoice!=EXIT_PROGRAM);
    }


}
void welcome() // Welcome screen
{
    time_t currentTime;
    time(&currentTime);

    printf("\n\n\n\n\n\t\t\t\t\t\t   %s",ctime(&currentTime));
    printf("\n\n\n\t\t\t\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1");
    printf("\n\t\t\t\xB1\xB1                                                                       \xB1\xB1");
    printf("\n\t\t\t\xB1\xB1                             W E L C O M E                             \xB1\xB1");
    printf("\n\t\t\t\xB1\xB1                                                                       \xB1\xB1");
    printf("\n\t\t\t\xB1\xB1                                  T O                                  \xB1\xB1");
    printf("\n\t\t\t\xB1\xB1                                                                       \xB1\xB1");
    printf("\n\t\t\t\xB1\xB1         W H O L E S A L E   M A N A G E M E N T   S Y S T E M         \xB1\xB1");
    printf("\n\t\t\t\xB1\xB1                                                                       \xB1\xB1");
    printf("\n\t\t\t\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1");

    printf("\n\n\n\t\t\t Press any key to continue");
    getch();
    system("cls");

}

void menuForOwner(int *userChoice)//main menu for owner
{
    int rtn;

    printf("\n\n\t\t\t\t\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1          WELCOME TO           \xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1          ");
    printf("\n\t\t\t\t\xB1\xB1\t        WHOLESALE MANAGEMENT SYSTEM              \xB1\xB1\n");
    printf("\n\n\t\t\t\t\t           **** Main Menu ****  \n\n\n");
    printf("\t\t\t\t\t <1> CREATE A NEW ACCOUNT \n\n");
    printf("\t\t\t\t\t <2> ADD PRODUCT\n\n");
    printf("\t\t\t\t\t <3> EDIT PRODUCT\n\n");
    printf("\t\t\t\t\t <4> SEARCH PRODUCT\n\n");
    printf("\t\t\t\t\t <5> VIEW AVAILABLE STOCK\n\n");
    printf("\t\t\t\t\t <6> VIEW OUT OF STOCK\n\n");
    printf("\t\t\t\t\t <7> VIEW EXPIRING PRODUCT\n\n");
    printf("\t\t\t\t\t <8> BILL CUSTOMER INVOICE\n\n");
    printf("\t\t\t\t\t <9> DELETE PRODUCT\n\n");
    printf("\t\t\t\t\t<10> EXIT\n\n");

    printf("\t\t\t\t\t Choice [1-10] : ");

    rtn = scanf("%d",userChoice);
    if(rtn == 0)
    {
        *userChoice = 11;
        printf("\n\t\t\t\t\tInvalid input!! Press Enter");
        getch();
        fflush(stdin);
    }


}

void menuForSalesRep(int *userChoice)//main menu for sales rep
{
    int rtn;

    printf("\n\n\t\t\t\t\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1          WELCOME TO           \xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1          ");
    printf("\n\t\t\t\t\xB1\xB1\t        WHOLESALE MANAGEMENT SYSTEM              \xB1\xB1\n");
    printf("\n\n\t\t\t\t\t           **** Main Menu ****  \n\n\n");
    printf("\t\t\t\t\t <1> SEARCH PRODUCT\n\n");
    printf("\t\t\t\t\t <2> VIEW AVAILABLE STOCK\n\n");
    printf("\t\t\t\t\t <3> VIEW OUT OF STOCK\n\n");
    printf("\t\t\t\t\t <4> VIEW EXPIRING PRODUCT\n\n");
    printf("\t\t\t\t\t <5> EXIT\n\n");

    printf("\t\t\t\t\t Choice [1-5] : ");

    rtn = scanf("%d",userChoice);
    if(rtn == 0)
    {
        *userChoice = 11;
        printf("\n\t\t\t\t\tInvalid input!! Press Enter");
        getch();
        fflush(stdin);
    }


}


void login(int *userType)
{
    int i = 1;
    int size =0;

    char username[20];
    char password[20];

    FILE *login;
    login = fopen("ownerLoginDetails.txt", "r");

    if(login != NULL)
    {
        fseek (login, 0, SEEK_END);

        size = ftell (login);
        rewind(login);
        fclose(login);

        if (size!=0)
        {

            printf("\n\n\n\n\n\t\t\t    \xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1 L O G I N \xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1");

            do
            {
                readUserNamePassword(username, password);
                *userType = verifyLoginData(username, password);
                if(i == 5)
                {
                    exit(0);
                }
                i++;
            }
            while(*userType == FALSE);

            printf("\n\n\t\t\t\t\t Press any key to continue");
            getch();

            system("cls");

        }
        else
        {
            userRegistration();
        }
    }
    else
    {
        login = fopen("ownerLoginDetails.txt", "w");
        fclose(login);
        userRegistration();
    }


}

void readUserNamePassword(char *username, char *password)
{

    int i=0;
    char character = 'A';


    printf("\n\n\t\t\t\t\t  Username : ");
    scanf("%s", username);
    printf("\t\t\t\t\t  Password : ");

    while(i<20)
    {
        password[i] = getch();
        character = password[i];
        if(character == ENTER_KEY)
        {
            break;
        }

        if(character != BACKSPACE_KEY)
        {

            printf("*");
            i++;
        }

        else
        {
            i--;
            if(i<0)
            {
                i++;
            }
            else
            {
                printf("\b \b");
            }
        }
    }

    password[i] = '\0';

}

void readUserType(int* userType)
{
    int rtn =0;


    printf("\n\n\t\t\t\tEnter account type 1. Owner \n");
    printf("\t\t\t\t                   2. Sales Rep \n");
    printf("\n\t\t\t\t            Choice : ");
    rtn = scanf("%d", userType);

    if(rtn ==0)
    {
        printf("\n\t\t\t\tInvalid input\n");
    }



}

int verifyLoginData(const char *userName,const char* Password)
{
    FILE *ownerLoginDetails;
    FILE *salesRepLoginDetails;

    char storedOwnerUserName[20];
    char storedOwnerPassword[20];
    char storedSalesRepUserName[20];
    char storedSalesRepPassword[20];

    int userLoginType = OWNER;


    ownerLoginDetails = fopen("ownerLoginDetails.txt", "r");
    fscanf(ownerLoginDetails,"%s\n", &storedOwnerUserName);
    fscanf(ownerLoginDetails,"%s\n", &storedOwnerPassword);

    fclose(ownerLoginDetails);

    salesRepLoginDetails = fopen("salesRepLoginDetails.txt", "r");
    fscanf(salesRepLoginDetails,"%s \n", &storedSalesRepUserName);
    fscanf(salesRepLoginDetails,"%s \n", &storedSalesRepPassword);

    fclose(salesRepLoginDetails);


    if(strcmp(userName, storedOwnerUserName)== 0 && strcmp(Password, storedOwnerPassword)== 0)
    {
        printf("\n\n\t\t\t\t\t Login Successful..\n");
        userLoginType = OWNER;
    }
    else if(strcmp(userName, storedSalesRepUserName)== 0 && strcmp(Password, storedSalesRepPassword)== 0)
    {
        printf("\n\n\t\t\t\t\t Login Successful..\n");
        userLoginType = SALES_REP;
    }
    else
    {
        printf("\n\n\t\t\t\t\t Login Failed!!!\n");
        userLoginType = FALSE;
    }

    return userLoginType;
}


void userRegistration() // Register a new user account
{
    int i =0;
    char username[20];
    char password[20];
    int isVerifyCorrect = TRUE;
    int userType = SALES_REP;

    printf("\n\n\n\t                               ***** Create A New Account *****       \n\n\n");

    do
    {
        printf("\n\n\t\t\tUsername and Password should be less than 20 characters\n\n");
        readUserNamePassword(username, password);
        readUserType(&userType);

        isVerifyCorrect = verifyRegistrationData(userType, username);

        if(i == 3)
        {
            exit(0);
        }
        i++;
    }
    while(isVerifyCorrect == FALSE);

    saveLoginDetails(username, password, userType);

    printf("\n\n\t\t\t\tAccount created successfully...\n\n\n ");
    printf("\n\t\t\t\tPress any key to continue ");
    getch();

    system("cls");

}

int verifyRegistrationData(const int userType, const char *username)
{
    int size = 0;
    char storedUsername[20];
    int isVerifyCorrect = TRUE;
    FILE *loginDetails;

    if(userType == OWNER)
    {
        loginDetails = fopen("ownerLoginDetails.txt", "r");
        fscanf(loginDetails, "%s", &storedUsername);
        fclose(loginDetails);
    }
    else if(userType == SALES_REP)
    {

        loginDetails = fopen("ownerLoginDetails.txt", "r");

        if(loginDetails != NULL)
        {
            fseek (loginDetails, 0, SEEK_END);

            size = ftell (loginDetails);
            rewind(loginDetails);
            fclose(loginDetails);

            if (size==0)
            {
                printf("\n\t\t\tTo Access The System, First You Need Do Create An Owner Account...\n");
                isVerifyCorrect = FALSE;
            }
            else
            {
                loginDetails = fopen("salesRepLoginDetails.txt", "r");
                fscanf(loginDetails, "%s", &storedUsername);
                fclose(loginDetails);
            }

        }
        else
        {
            printf("\n\t\t\tTo Access The System, First You Need Do Create An Owner Account...\n");
            isVerifyCorrect = FALSE;
        }

    }
    else
    {
        printf("\n\t\t Invalid input!!!\n");
        isVerifyCorrect = FALSE;
    }


    if(strcmp(username, storedUsername)==0)
    {
        printf("\n\t\t\t\tEntered username already exist.. Try another\n");
        isVerifyCorrect = FALSE;

    }
    else
    {
        if(userType == SALES_REP)

        {
            loginDetails = fopen("ownerLoginDetails.txt", "r");
            fscanf(loginDetails, "%s", &storedUsername);
            fclose(loginDetails);

            if(strcmp(username, storedUsername)==0)
            {
                printf("\n\t\t\t\tEntered username already exist.. Try another\n");
                isVerifyCorrect = FALSE;
            }
        }
        else if(userType == OWNER)
        {
            loginDetails = fopen("salesRepLoginDetails.txt", "r");
            fscanf(loginDetails, "%s", &storedUsername);
            fclose(loginDetails);

            if(strcmp(username, storedUsername)==0)
            {
                printf("\n\t\t\t\tEntered username already exist.. Try another\n");
                isVerifyCorrect = FALSE;
            }
        }
    }

    return isVerifyCorrect;
}

void addProductDetails(struct product item[], int* productCount)//add products to the system
{
    char userChoice = 'y';
    int indexNo = *productCount;

    printf("\n\n\t\t\t\t**** ADD PRODUCT DETAILS ****\n\n\n");

    do
    {
        readProduct(item, indexNo);
        saveProductDetailsToFlie(item, indexNo);
        printf("\n\t\tEnter 'Y' to add more or any key to goto Main menu : ");
        scanf("%c",&userChoice);

        indexNo++;

        printf("\n");

    }
    while(userChoice=='Y' || userChoice=='y');
    fflush(stdin);
    *productCount = indexNo;

    system("cls");


}

void readProduct(struct product *item, const int indexNo) // Read product details
{
    int productIndexNo=0;
    int validityStatus = FALSE;
    int haveSameName=FALSE;
    int haveSameCode=FALSE;

    do
    {
        printf("\t\t\t\tProduct name : ");
        scanf("%s", item[indexNo].name);
        fflush(stdin);
        haveSameName = compareProductName(item,item[indexNo].name,&productIndexNo, indexNo);
        printStatement2(haveSameName);

    }
    while(haveSameName == TRUE);

    do
    {
        printf("\t\t\t\tProduct code : ");
        scanf("%s", item[indexNo].code);

        haveSameCode = compareProductCode(item,indexNo);
    }
    while(haveSameCode == TRUE);

    printf("\t\t\t\tCompany name : ");
    scanf("%s", item[indexNo].company);

    do
    {
        printf("\t\t\t\tUnit price   : ");
        scanf("%lf", &item[indexNo].unitPrice);

        validatePrice(item[indexNo].unitPrice, &validityStatus);

    }
    while(validityStatus==FALSE);

    do
    {
        printf("\t\t\t\tQuantity     : ");
        scanf("%d", &item[indexNo].quantity);

        validateQuantity(item[indexNo].quantity, &validityStatus);

    }
    while(validityStatus==FALSE);

    do
    {
        printf("\t\t\t\tExpire date   \n");
        printf("\t\t\t\t       Year  : ");
        scanf("%d", &item[indexNo].expireDate.year);
        printf("\t\t\t\t      Month  : ");
        scanf("%d", &item[indexNo].expireDate.month);
        printf("\t\t\t\t       Date  : ");
        scanf("%d", &item[indexNo].expireDate.date);

        validateDate(item, indexNo, &validityStatus);

    }
    while(validityStatus==FALSE);
    fflush(stdin);
}

int compareProductCode(const struct product item[],const int indexNo) // Compare the entered Product code exists in the system
{
    int checkCode=0;
    int haveSameCode =FALSE;


    for(int i=0; i<indexNo; i++)
    {
        checkCode = strcmp(item[indexNo].code,item[i].code);
        if(checkCode == 0)
        {
            printf("\n\t\t\t\t  Product Code already exists in system!!!\n\n");
            haveSameCode = TRUE;
        }
    }
    return haveSameCode;
}


void validatePrice(const double enteredPrice, int *validityStatus)
{
    if(enteredPrice<=0)
    {
        printf("\n\t\t\t\t  Invalid Price!!! Please enter again\n");
        *validityStatus = FALSE;
    }
    else
    {
        *validityStatus = TRUE;
    }

}

void validateQuantity(const int enteredQuantity, int* validityStatus)
{
    if(enteredQuantity<=0)
    {
        printf("\n\t\t\t\t  Invalid Quantity!!! Please enter again\n");
        *validityStatus = FALSE;
    }
    else
    {
        *validityStatus = TRUE;
    }
}

void validateDate(struct product item[],const int indexNo, int* validityStatus)
{
    int checkValidate = TRUE;



    if(item[indexNo].expireDate.date<=0 || item[indexNo].expireDate.date>31)
    {
        checkValidate =FALSE;
    }

    else  if (item[indexNo].expireDate.month<=0 || item[indexNo].expireDate.month>12)
    {
        checkValidate=FALSE;
    }
    else if(item[indexNo].expireDate.year<=0)
    {
        checkValidate=FALSE;
    }


    if(checkValidate==FALSE)
    {
        printf("\n\t\t\t\t  Invalid expire date!!! Please enter again\n");
        *validityStatus = FALSE;
    }
    else
    {
        *validityStatus = TRUE;
    }

}


void availableStock(struct product item[], const int productCount)// Display available stock
{
    double oneItemValue[SIZE];
    double totalAmount=0;

    printf("\n\n\t                               ***** Available Stock Details *****       \n\n\n");

    if(productCount == 0)
    {
        printStatement3();
    }
    else
    {
        calculateTotalAmount(oneItemValue,&totalAmount,item, productCount);
        printAvailableStock(item,totalAmount,oneItemValue, productCount);
    }


    printf("\n\t\t\tPress any key to goto Main menu");
    getch();

    system("cls");
}
void printAvailableStock(const struct product item[], const double totalAmount,const double oneItemTotal[], const int productCount)
{

    printf("\t------------------------------------------------------------------------------------------------\n");
    printf("\tProduct Name     Code     Product Company     Expire Date     UnitPrice    Quantity       Total \n");
    printf("\t------------------------------------------------------------------------------------------------\n");
    for(int i=0; i<productCount; i++)
    {
        printf("\t %-11s    %-5s      %-14s     %4d/%02d/%02d     %8.2lf     %6d       %9.2lf \n",item[i].name,item[i].code,item[i].company,item[i].expireDate.year,item[i].expireDate.month,item[i].expireDate.date,item[i].unitPrice,item[i].quantity,oneItemTotal[i]);
    }
    printf("\t------------------------------------------------------------------------------------------------\n");
    printf("\n\tAvailable Stock Value : %.2lf\n\n\n",totalAmount);

}
void calculateTotalAmount(double oneItemValue[], double* totalAmount,const struct product item[], const int productCount)// Calculate the available stock value
{

    for(int i=0; i<productCount; i++)
    {
        oneItemValue[i] = item[i].unitPrice * item[i].quantity;
        *totalAmount += oneItemValue[i];
    }

}

void outOfStock(const struct product item[],const int productCount)// Display OUT OF STOCK
{
    int zeroQtyProductIndexNo[SIZE];
    int indexCount=0;

    printf("\n\n\t                             ***** Out Of Stock Details *****\n\n\n");

    if(productCount == 0)
    {
        printStatement3();
    }
    else
    {
        compareQuantity(item, zeroQtyProductIndexNo,&indexCount, productCount);
        printOutOfStock(item, zeroQtyProductIndexNo,indexCount);
    }


    printf("\n\t\t\tPress any key to goto Main menu");
    getch();

    system("cls");
}
void printOutOfStock(const struct product item[],const int indexNo[],const int indexCount)
{

    if(indexCount==0)
    {
        printf("\t\t\t No Out Of Stocks!!! \n");
    }
    else
    {
        printf("\t\t\t---------------------------------------------------------\n");
        printf("\t\t\tProduct Name     Code     Product Company     Unit Price \n");
        printf("\t\t\t---------------------------------------------------------\n");
        for(int i=0; i<indexCount; i++)
        {
            printf("\t\t\t %-11s    %5s      %-14s     %8.2lf \n",item[indexNo[i]].name,item[indexNo[i]].code,item[indexNo[i]].company,item[indexNo[i]].unitPrice);
        }
        printf("\t\t\t---------------------------------------------------------\n");
        printf("\n\t\t\tAmount of Out Of Stock Products : %d\n\n\n", indexCount);
    }
}

void compareQuantity(const struct product item[], int zeroQtyProductIndexNo[], int* indexCount, const int productCount)// Compare the product quantity whether it is zero or not
{
    int i=0;
    int j=0;
    for(i=0; i<productCount; i++)
    {
        if(item[i].quantity== 0)
        {
            zeroQtyProductIndexNo[j]=i;
            j++;

        }
    }
    *indexCount=j;
}

void expiredStock(const struct product item[], const int productCount)// Display Expire Stock in year 2021
{
    int expiredProductIndexNo[SIZE];
    int indexCount=0;
    int expiredYear = 0;

    printf("\n\n\t                                 ***** Expiring Product Details *****\n\n\n");

    if(productCount == 0)
    {
        printStatement3();
    }
    else
    {
        expiredYear = getExpireYear();
        compareExpireDate(item, expiredYear, expiredProductIndexNo, &indexCount, productCount);
        printExpiringStock(item,expiredProductIndexNo,indexCount, expiredYear);
    }


    printf("\n\t\t\tPress any key to goto Main menu");
    getch();

    system("cls");
}
void printExpiringStock(const struct product item[],const int indexNo[], const int indexCount, const int expireYear)
{

    if(indexCount==0)
    {
        printf("\t\t\t No Expiring Product in %d....\n", expireYear);
    }
    else
    {
        printf("\t\t\tExpire in %d\n", expireYear);
        printf("\t\t\t------------------------------------------------------------------------\n");
        printf("\t\t\tProduct Name     Code     Product Company     Expire Date     Quantity  \n");
        printf("\t\t\t------------------------------------------------------------------------\n");
        for(int i=0; i<indexCount; i++)
        {
            printf("\t\t\t %-11s    %-5s      %-14s     %4d/%02d/%02d     %6d \n",item[indexNo[i]].name,item[indexNo[i]].code,item[indexNo[i]].company,item[indexNo[i]].expireDate.year,item[indexNo[i]].expireDate.month,item[indexNo[i]].expireDate.date,item[indexNo[i]].quantity);
        }
        printf("\t\t\t------------------------------------------------------------------------\n");
        printf("\n\t\t\tAmount of Expiring Products : %d\n\n\n", indexCount);
    }
}

int getExpireYear()
{
    int expireYear = 0;
    printf("\n\n\t\t\tPlease enter a year to check : ");
    scanf("%d", &expireYear);
    printf("\n\n");

    return expireYear;
}
void compareExpireDate(const struct product item[], const int expireYear, int expiredProductIndexNo[], int* indexCount, const int productCount) // Compare expire Date whether it is expiring 2021 or not
{
    int i=0;
    int j=0;
    for(i=0; i<productCount; i++)
    {
        if(item[i].expireDate.year== expireYear) // THIS YEAR means 2021
        {
            expiredProductIndexNo[j]=i;
            j++;

        }
    }
    *indexCount=j;
}

void searchProduct(const struct product item[],const int productCount) // Search Product details
{
    char userEnteredName[20];
    int productAvailability=FALSE;
    int productIndexNo=0;
    int count =0;

    printf("\n\n\t                               ***** Search Product Details *****\n\n\n");

    if(productCount == 0)
    {
        printStatement3();
    }
    else
    {
        do
        {

            readName(userEnteredName);
            productAvailability = compareProductName(item,userEnteredName,&productIndexNo, productCount);
            printStatment1(productAvailability);
            count++;

            if(count==5)
            {
                break;
            }

        }
        while(productAvailability==FALSE);

        printSearchDetails(item,productAvailability,productIndexNo);
    }

    printf("\n\n\t\t\tPress any key to goto Main menu");
    getch();

    system("cls");
}
void printSearchDetails(const struct product item[],const int productAvailability,const int productIndexNo)
{
    if(productAvailability==TRUE)
    {


        printf("\t\t\t\t |Product Name    : %s\n",item[productIndexNo].name);
        printf("\t\t\t\t |Product Code    : %s\n",item[productIndexNo].code);
        printf("\t\t\t\t |Product company : %s\n",item[productIndexNo].company);
        printf("\t\t\t\t |Unit Price      : %.2lf\n",item[productIndexNo].unitPrice);
        printf("\t\t\t\t |Stock Quantity  : %d\n",item[productIndexNo].quantity);
        printf("\t\t\t\t |Expire Date     : %d/%02d/%02d\n",item[productIndexNo].expireDate.date,item[productIndexNo].expireDate.month,item[productIndexNo].expireDate.year);
    }

}

void readName(char* userEnteredName)// Read product name
{
    printf("\n\t\t\t\tEnter Product Name : ");
    scanf("%s", userEnteredName);
}
int compareProductName(const struct product item[],const char *userEnteredName,int* productIndexNo, const int productCount) // Compare product name whether it is exists in the system
{
    int productAvailability=FALSE;
    int i=0;
    int check =0;
    for(i=0; i<productCount; i++)
    {
        check = strcmp(item[i].name,userEnteredName);

        if(check ==0)
        {
            productAvailability=TRUE;

            *productIndexNo=i;

        }
    }
    return productAvailability;
}

void editProduct(struct product item[], const int productCount) // Edit already added product details
{
    char userEnteredName[20];
    int productAvailability=FALSE;
    int productIndexNo=0;
    int count =0;

    printf("\n\n\t                     ***** Edit Product Details *****\n\n\n");

    if(productCount == 0)
    {
        printStatement3();
    }
    else
    {
        do
        {
            readName(userEnteredName);
            productAvailability = compareProductName(item,userEnteredName,&productIndexNo, productCount);
            printStatment1(productAvailability);

            count++;

            if(count==5)
            {
                break;
            }
        }
        while(productAvailability==FALSE);

        if(productAvailability==TRUE)
        {
            printf("\n\n\t                     ----- Enter New Details -----\n\n\n");
            readProduct(item, productIndexNo);
            saveDataToTempFile(item,productCount);
        }
    }
    printf("\n\n\t\t\tPress any key to goto Main menu");
    getch();

    system("cls");

}


void billInvoice(struct product item[], const int productCount) // Create customer invoice
{

    struct billItem itemNo[BILLSIZE]; // Declare a structure to store invoice details
    struct invoice invoiceNo; // Declare a structure to store invoice details

    int count =0;
    int productIndexNo =0;
    int validation=FALSE;
    int userChoice=YES;


    printf("\n\t\t\t\t     **** Enter Bill Details ****\n\n\n\n");

    if(productCount == 0)
    {
        printStatement3();
    }
    else
    {
        do
        {
            getBillNo(&invoiceNo.billNumber);
            invoiceNo.billNumber++;

            readCustomerDetails(invoiceNo.customerName,invoiceNo.address);

            do
            {
                do
                {
                    readProductDetails(itemNo, count);
                    validation = validateDetails(item,itemNo, count, productCount, &productIndexNo);

                    if(validation==TRUE)
                    {
                        getOneItemTotal(itemNo, count);
                        reduceQuantity(item, itemNo[count].quantity, productIndexNo);
                        count++;
                    }
                    else
                    {
                        break;
                    }
                }
                while(validation == FALSE);

                printf("\n\t\t\t\t   Add item again  \n");
                userChoice = choice();
            }
            while(userChoice == YES);

            getTotal(itemNo, &invoiceNo.totalAmount, count);
            getDiscount(&invoiceNo);
            getNetAmount(&invoiceNo);

            printCustomerInvoice(invoiceNo, itemNo, count);

            saveDataToTempFile(item,productCount);
            saveInvoiceDataToFile(invoiceNo, itemNo, count);

            printf("\n\t\t\t\tCreate another Invoice ?\n\n");

            userChoice = choice();

            if(userChoice == YES)
            {
                count =0;
                invoiceNo.billNumber++;
            }
            printf("\n");

        }
        while(userChoice == YES);
    }
    printf("\n\t\t\t\tPress any key to goto Main menu");
    getch();

    system("cls");
}
void printCustomerInvoice(const struct invoice invoiceNo, const struct billItem itemNo[], const int count)
{

    printf("\n\n\t                              ***** Customer Invoice *****       \n\n\n");
    printf("\t\t\t                   Bill No : %d\n", invoiceNo.billNumber);
    printf("\t\t\t             Customer Name : %s\n", invoiceNo.customerName);
    printf("\t\t\t                   Address : %s\n\n", invoiceNo.address);
    printf("\t\t\t---------------------------------------------------\n");
    printf("\t\t\tProduct Name     UnitPrice    Quantity       Total \n");
    printf("\t\t\t---------------------------------------------------\n");
    for(int i=0; i<count; i++)
    {
        printf("\t\t\t %-11s    %8.2lf     %6d       %8.2lf \n",itemNo[i].itemName, itemNo[i].unitPrice, itemNo[i].quantity, itemNo[i].oneItemTotal);
    }
    printf("\t\t\t---------------------------------------------------\n");
    printf("\n\t\t\tTotal     : %.2lf",invoiceNo.totalAmount);
    printf("\n\t\t\tDiscount  : %.2lf",invoiceNo.discountValue);
    printf("\n\t\t\tNet Value : %.2lf\n\n\n",invoiceNo.netAmount);
}

void readCustomerDetails(char* customerName, char* address)
{
    printf("\t\tEnter Customer Name  : ");
    scanf("%s", customerName);
    printf("\t\tEnter Address        : ");
    scanf("%s", address);
}
void readProductDetails(struct billItem *itemNo,const int count)
{
    printf("\n\t\tEnter Product Name   : ");
    scanf("%s", itemNo[count].itemName);
    printf("\t\tEnter Quantity       : ");
    scanf("%d", &itemNo[count].quantity);
}
int validateDetails(const struct product item[],struct billItem itemNo[], const int indexNo, const int productCount, int* productIndexNo)
{
    int productAvailability=FALSE;
    int j=0;


    for(int i=0; i<productCount; i++)
    {
        if(strcmp(itemNo[indexNo].itemName,item[i].name)==0)
        {
            productAvailability=TRUE;
            itemNo[indexNo].unitPrice = item[i].unitPrice;
            *productIndexNo = i;
            j=i;

        }

    }
    if(productAvailability==TRUE)
    {
        if(itemNo[indexNo].quantity>0)
        {
            if(itemNo[indexNo].quantity<=item[j].quantity)
            {
                productAvailability=TRUE;

            }
            else
            {
                printf("\n\t\tSorry!!! There is only %d pieces in stock..\n",item[j].quantity);
                productAvailability=FALSE;

            }
        }
        else
        {
            printf("\n\t\t\tInvalid Input!!!\n");
            productAvailability=FALSE;

        }
    }
    else
    {
        printf("\n\t\tCan't find the name in the system!!!\n");
        productAvailability=FALSE;

    }
    return productAvailability;
}

void getOneItemTotal(struct billItem *itemNo, const int count) // Calculate a item value
{
    itemNo[count].oneItemTotal= itemNo[count].unitPrice * itemNo[count].quantity;


}

void getTotal(const struct billItem itemNo[], double *totalAmount, const int count)// Calculate invoice total value
{
    *totalAmount = 0;
    for(int i=0; i<count; i++)
    {
        *totalAmount += itemNo[i].oneItemTotal;
    }
}

void getDiscount(struct invoice *invoiceNo)// Calculate discount value
{

    printf("\n\t\tEnter Discount Rate %%: ");
    scanf("%d", &invoiceNo->discountRate);

    invoiceNo->discountValue = invoiceNo->totalAmount * (invoiceNo->discountRate/100.0);

}
void getNetAmount(struct invoice *invoiceNo)// Calculate net value of the invoice after the discount added
{
    invoiceNo->netAmount = invoiceNo->totalAmount - invoiceNo->discountValue;
}

void reduceQuantity(struct product item[], const int userEnteredQuantity, const int productIndexNo)// Reduce the system quantity after the invoice is created
{
    item[productIndexNo].quantity = item[productIndexNo].quantity - userEnteredQuantity;
}

void deleteData(struct product item[],int *productCount) // Delete product data in the system
{
    char userEnteredName[20];
    int productAvailability=FALSE;
    int productIndexNo=0;
    int count = *productCount;
    int isConfirmed = NO;
    int i = 0;

    printf("\n\n\t                          ***** Delete Product Details *****\n\n\n");

    if(*productCount == 0)
    {
        printStatement3();
    }
    else
    {
        do
        {
            readName(userEnteredName);
            productAvailability = compareProductName(item,userEnteredName,&productIndexNo,count);
            printStatment1(productAvailability);
            i++;

            if(i == 3)
            {
                break;
            }
        }
        while(productAvailability == FALSE);

        isConfirmed = confirmDeletion(productAvailability);

        if(isConfirmed == YES)
        {

            deleteTheRecord(item, productIndexNo, count);
            readProductDetailsFromFlie(item, productCount);
            printf("\n\t\t\tDeletion Successful...");

        }
    }
    printf("\n\n\t\t\t\tPress any key to goto Main menu");
    getch();

    system("cls");
}
int confirmDeletion(const int productAvailability)
{
    int userChoice=NO;
    int confirm = NO;
    if(productAvailability==TRUE)
    {

        printf("\n\t\t\t\tDelete the record ?\n\n");

        userChoice=choice();

        if(userChoice==YES)
        {
            confirm = YES;
        }
        else
        {
            confirm = NO;
        }
    }

    return confirm;
}

void deleteTheRecord(const struct product item[], int productIndexNo, const int productCount)
{

    FILE *temp;

    temp = fopen("tempFile.txt", "w");

    for(int i=0; i<productIndexNo; i++)
    {
        fprintf(temp,"%s %s %s %d %d %d %lf %d\n",item[i].name, item[i].code, item[i].company,item[i].expireDate.year, item[i].expireDate.month, item[i].expireDate.date, item[i].unitPrice, item[i].quantity);
    }
    for(int i= productIndexNo+1; i< productCount; i++)
    {
        fprintf(temp,"%s %s %s %d %d %d %lf %d\n",item[i].name, item[i].code, item[i].company,item[i].expireDate.year, item[i].expireDate.month, item[i].expireDate.date, item[i].unitPrice, item[i].quantity);
    }
    fclose(temp);

    remove("productDetails.txt");
    rename("tempFile.txt", "productDetails.txt");
}


void saveLoginDetails(const char username[],const char password[],const int userType)// Save username, Password and user type
{
    FILE *loginDetails;
    if(userType == OWNER)
    {
        loginDetails = fopen("ownerLoginDetails.txt", "w");
        fprintf(loginDetails, "%s\n", username);
        fprintf(loginDetails, "%s\n", password);
        fprintf(loginDetails, "%d\n", userType);

        fclose(loginDetails);
    }
    else if(userType == SALES_REP)
    {
        loginDetails = fopen("salesRepLoginDetails.txt", "w");
        fprintf(loginDetails, "%s\n", username);
        fprintf(loginDetails, "%s\n", password);
        fprintf(loginDetails, "%d\n", userType);

        fclose(loginDetails);
    }
}

void saveDataToTempFile(const struct product item[], const int productCount)// Temporary save product details to a file
{
    FILE *temp;

    temp = fopen("tempFile.txt", "w");

    for(int i=0; i<productCount; i++)
    {
        fprintf(temp,"%s %s %s %d %d %d %lf %d\n",item[i].name, item[i].code, item[i].company,item[i].expireDate.year, item[i].expireDate.month, item[i].expireDate.date, item[i].unitPrice, item[i].quantity);
    }
    fclose(temp);

    remove("productDetails.txt");
    rename("tempFile.txt", "productDetails.txt");


}
void saveProductDetailsToFlie(const struct product item[],const int indexNo )// save product details to a file
{
    FILE *productDetails;

    productDetails = fopen("productDetails.txt", "a");
    fprintf(productDetails,"%s %s %s %d %d %d %lf %d\n",item[indexNo].name,item[indexNo].code,item[indexNo].company,item[indexNo].expireDate.year,item[indexNo].expireDate.month,item[indexNo].expireDate.date,item[indexNo].unitPrice,item[indexNo].quantity);
    fclose(productDetails);
}

void saveInvoiceDataToFile(const struct invoice invoiceNo, const struct billItem itemNo[], const int count)// save invoice details to a file
{
    int i = 0;


    FILE *invoice;
    FILE *billNo;

    billNo = fopen("billNo.txt", "w");
    fprintf(billNo,"%d\n", invoiceNo.billNumber);
    fclose(billNo);

    invoice = fopen("invoice.txt", "a+");
    fprintf(invoice,"%s\n", invoiceNo.customerName);
    fprintf(invoice,"%s\n", invoiceNo.address);

    for(i=0; i< count; i++)
    {
        fprintf(invoice,"%-10s  %-15lf  %-10d  %-15lf\n",itemNo[i].itemName, itemNo[i].unitPrice, itemNo[i].quantity, itemNo[i].oneItemTotal);
    }

    fprintf(invoice,"%lf\n", invoiceNo.totalAmount);
    fprintf(invoice,"%d\n", invoiceNo.discountRate);
    fprintf(invoice,"%lf\n",invoiceNo.discountValue);
    fprintf(invoice,"%lf\n\n",invoiceNo.netAmount);

    fclose(invoice);
}

void getBillNo(int* billNumber)// get Invoice number
{

    int size = 0;

    FILE *billNo;
    billNo = fopen("billNo.txt", "r");

    if(billNo != NULL)
    {
        fseek (billNo, 0, SEEK_END);

        size = ftell (billNo);
        rewind(billNo);

        if (size!=0)
        {
            fscanf(billNo, "%d\n", billNumber);

        }
        else
        {
            *billNumber = 0;
        }

    }
    else
    {
        *billNumber = 0;

    }
    fclose(billNo);
}

void readProductDetailsFromFlie(struct product item[], int* productCount)// access the product details file
{
    int i = 0;
    int size = 0;

    FILE *productDetails;
    productDetails = fopen("productDetails.txt", "r");

    if(productDetails != NULL)
    {
        fseek (productDetails, 0, SEEK_END);

        size = ftell (productDetails);
        rewind(productDetails);

        if (size!=0)
        {
            while(!feof(productDetails))
            {

                fscanf(productDetails,"%s %s %s %d %d %d %lf %d\n",&item[i].name, &item[i].code, &item[i].company,&item[i].expireDate.year, &item[i].expireDate.month, &item[i].expireDate.date, &item[i].unitPrice, &item[i].quantity);
                i++;
            }

        }

    }
    else
    {
        productDetails = fopen("productDetails.txt", "w");

    }
    fclose(productDetails);

    *productCount = i;
}
void printStatment1(const int productAvailability) // This use for some functionality
{
    if(productAvailability==TRUE)
    {

        printf("\n\n\t\t\t\t ---Record Found---\n\n");

    }
    else
    {
        printf("\n\t\t\t\t  No Records Found!!!\n");

    }

}

void printStatement2(const int haveSameName)// This use for some functionality
{
    if(haveSameName == TRUE)
    {
        printf("\n\t\t\t\t  Product name already exists in system!!!\n\n");
    }
}

void printStatement3()
{
    printf("\n\n\t\t\tSystem has NO RECORDS about product details !!!\n\n");

}
int choice() // get user choice in some functions
{
    int choice=YES;
    printf("\t\t\t           1. Yes\n");
    printf("\t\t\t           2. No\n");
    printf("\n\t\t                   Choice (1 or 2) : ");
    scanf("%d", &choice);
    return choice;
}
