#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

typedef struct {
    int code;
    char name[50];
    char email[50];
    char financialNumber[20];
    char dob[20];
    char registrationDate[20];
} Client;

typedef struct {
    int number;
    Client client;
    float limit;
    float balance;
    float fullBalance; // limit + balance
} Account;

void menu();
void infoClient(Client client);
void infoAccount(Account account);
void creatAccount();
void makeWithdraw();
void makeDeposit();
void makeTransfer();
void listAccounts();
float updateFullBalance(Account account);
Account searchAccountByNumber(int number);
void withdraw(Account account, float value);
void deposit(Account account, float value);
void transfer(Account origem_account, Account destine_account, float value);

static Account accounts[50];
static int counter_accounts = 0;
static int counter_clients = 0;


int main(){

    menu();

    return 0;
}

void menu(){
    int option = 0;
    printf("\t\t\t ATM\n");
    printf("1 - Creat account\n");
    printf("2 - Withdraw\n");
    printf("3 - Deposit\n");
    printf("4 - Transfer\n");
    printf("5 - List\n");
    printf("6 - Quit\n");

    scanf("%d", &option);
    getchar();

    switch(option){
        case 1:
            creatAccount();
            menu();
            break;
        case 2:
            makeWithdraw();
            menu();
            break;
        case 3:
            makeDeposit();
            menu();
            break;
        case 4:
            makeTransfer();
            menu();
            break;
        case 5:
            listAccounts();
            menu();
            break;
        case 6:
            printf("Thank you!\n\n");
            Sleep(3);
            exit(0);
            break;
        default:
            printf("Invalid option\n\n");
            Sleep(3);
            menu();
            break;
    }
    return 0;
}
void infoClient(Client client){
    printf("Code: %d \nName: %s \nDate of Birth: %s \nDate of Registration: %s\n",
           client.code, strtok(client.name, "\n"), strtok(client.dob, "\n"), strtok(client.registrationDate, "\n"));
}

void infoAccount(Account account){
    printf("Number of Account: %d \nClient: %s \nDate of Birth: %s \nDate of Registration: %s \nFull Balance: %.2f\n",
           account.number, strtok(account.client.name, "\n"), strtok(account.client.dob, "\n") ,strtok(account.client.registrationDate, "\n"),
           account.fullBalance);
}
void creatAccount(){
    Client client;

    //############### Date of registration ############
    char day[3];
    char month[3];
    char year[5];
    char dateRegistration[20];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //day
    if(tm.tm_mday < 10){
        sprintf(day, "0%d", tm.tm_mday);
    } else {
        sprintf(day, "%d", tm.tm_mday);
    }
    //month
    if((tm.tm_mon + 1) < 10){
        sprintf(month, "0%d", tm.tm_mon);
    } else {
        sprintf(month, "%d", tm.tm_mon);
    }
    //year
    sprintf(year, "%d", tm.tm_year + 1900);

    strcpy(dateRegistration, "");
    strcat(dateRegistration, day);
    strcat(dateRegistration, "/");
    strcat(dateRegistration, month);
    strcat(dateRegistration, "/");
    strcat(dateRegistration, year);
    strcat(dateRegistration, "\0");
    strcpy(client.registrationDate, dateRegistration);

    //############# Create client ###################
    printf("\t\tEnter costumer data\n");
    client.code = counter_clients + 1;

    printf("Customer name: ");
    fgets(client.name, 50, stdin);

    printf("Customer email: ");
    fgets(client.email, 50, stdin);

    printf("Consumer financial number: ");
    fgets(client.financialNumber, 20, stdin);

    printf("Date of birth: ");
    fgets(client.dob, 20, stdin);

    counter_clients++;

    // ############ Create account ####################
    accounts[counter_accounts].number = counter_accounts  + 1;
    accounts[counter_accounts].client = client;
    accounts[counter_accounts].balance = 0.0;
    accounts[counter_accounts].limit = 0.0;
    accounts[counter_accounts].fullBalance = updateFullBalance(accounts[counter_accounts]);
    printf("Account was created successfully\n\n");

    printf("\tData of created account\n");
    infoAccount(accounts[counter_accounts]);
    counter_accounts++;
    Sleep(5);
    menu();
}
void makeWithdraw(){
    if(counter_accounts > 0){
        int number;
        printf("Enter number account: ");
        scanf("%d", &number);

        Account account = searchAccountByNumber(number);

        if(account.number == number){
            float value;
            printf("Enter the value: $ ");
            scanf("%f", &value);
            withdraw(account, value);
        } else {
            printf("The account %d was not found\n", number);
        }

    } else {
        printf("There is not the account for withdrawing\n");
    }

    Sleep(3);
    menu();
}
void makeDeposit(){
    if(counter_accounts > 0){
        int number;
        printf("Enter number account: ");
        scanf("%d", &number);

        Account account = searchAccountByNumber(number);

        if(account.number == number){
            float value;
            printf("Enter the value: $ ");
            scanf("%f", &value);
            deposit(account, value);
        } else {
            printf("The account %d was not found\n", number);
        }

    } else {
        printf("There is not the account for depositing\n");
    }

    Sleep(3);
    menu();
}
void makeTransfer(){
    if(counter_accounts > 0){
        int originNumber, destineNumber;
        printf("Enter your number account: ");
        scanf("%d", &originNumber);
        Account originAcc = searchAccountByNumber(originNumber);

        if(originNumber == originAcc.number){
            printf("Enter destine account number: ");
            scanf("%d", &destineNumber);

            Account destineAcc = searchAccountByNumber(destineNumber);
            float value;
            if(destineNumber == destineAcc.number){
                printf("Enter the value for transfer: $ ");
                scanf("%f", &value);
                transfer(originAcc, destineAcc, value);
            } else {
                printf ("The destine account %d was not found\n", destineNumber);
            }

        } else {
            printf("The origin account %d was not found\n", originNumber);
        }

    } else {
        printf("There are no accounts for transfers\n");
    }

    Sleep(3);
    menu();
}
void listAccounts(){
    if(counter_accounts > 0){
        for(int i = 0; i < counter_accounts; i++){
            infoAccount(accounts[i]);
            printf("\n");
            Sleep(2);
        }
    } else {
        printf("There are not registered accounts\n");
    }

    Sleep(3);
    menu();
}

float updateFullBalance(Account account){
    return account.balance + account.limit;
}

Account searchAccountByNumber(int number){
    Account acc;
    if(counter_accounts > 0){
        for(int i = 0; i < counter_accounts; i++){
            if(accounts[i].number == number){
                acc = accounts[i];
            }
        }
    }
    return acc;
}
void withdraw(Account account, float value){
    if(value > 0 && account.fullBalance >= value){
        for(int i = 0; i < counter_accounts; i++){
            if(accounts[i].number == account.number){
                if(accounts[i].balance >= value){
                    accounts[i].balance = accounts[i].balance - value;
                    accounts[i].fullBalance = updateFullBalance(accounts[i]);
                    printf("Withdrew the money\n");
                } else {
                    float remaining = accounts[i].balance + value;
                    accounts[i].balance = 0.0;
                    accounts[i].fullBalance = updateFullBalance(accounts[i]);
                    printf("Withdrew the money\n");
                }
            }
        }
    } else {
        printf("The value is higher than your available balance\n");
    }
}
void deposit(Account account, float value){
    if(value > 0){
        for(int i = 0; i < counter_accounts; i++){
            if(accounts[i].number == account.number){
                accounts[i].balance = account.balance + value;
                accounts[i].fullBalance = updateFullBalance(accounts[i]);
                printf("Successfully Deposited\n");
            }
        }
    } else {
        printf("Error! Try again\n");
    }
}
void transfer(Account origem_account, Account destine_account, float value){
    if(value > 0 && origem_account.fullBalance >= value){
        for(int origemAcc = 0; origemAcc < counter_accounts; origemAcc++){
            if(accounts[origemAcc].number == origem_account.number){
                for(int destineAcc = 0; destineAcc < counter_accounts; destineAcc++){
                    if(accounts[destineAcc].number == destine_account.number){
                        if(accounts[origemAcc].balance >= value){
                            accounts[origemAcc].balance = accounts[origemAcc].balance - value;
                            accounts[destineAcc].balance = accounts[destineAcc].balance + value;
                            accounts[origemAcc].fullBalance = updateFullBalance(accounts[origemAcc]);
                            accounts[destineAcc].fullBalance = updateFullBalance(accounts[destineAcc]);
                            printf("Successfully transferred\n");
                        } else {
                            float remaining = accounts[origemAcc].balance - value;
                            accounts[origemAcc].limit = accounts[origemAcc].limit + remaining;
                            accounts[origemAcc].balance = 0.0;
                            accounts[destineAcc].balance = accounts[destineAcc].balance + value;
                            accounts[origemAcc].fullBalance = updateFullBalance(accounts[origemAcc]);
                            accounts[destineAcc].fullBalance = updateFullBalance(accounts[destineAcc]);
                            printf("Successfully transferred\n");
                        }
                    }
                }
            }
        }
    } else {
        printf("This operation is not possible with current balance available\n");
    }
}
