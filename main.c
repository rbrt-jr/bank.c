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

}
void makeWithdraw(){

}
void makeDeposit(){

}
void makeTransfer(){

}
void listAccounts(){

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
