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

    return 0;
}
void infoClient(Client client){

}
void infoAccount(Account account){

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

}

Account searchAccountByNumber(int number){

}
void withdraw(Account account, float value){

}
void deposit(Account account, float value){

}
void transfer(Account origem_account, Account destine_account, float value){

}
