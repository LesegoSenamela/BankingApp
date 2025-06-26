#include <iostream>

using namespace std;

struct account{
    int accountNumber;
    double accountBalance;
    double interestRate;
};


account enterAccountData(){
    account BankAccount;

    cout<< "\nEnter the account number : ";
    cin>> BankAccount.accountNumber;

    while (BankAccount.accountNumber < 1000 || BankAccount.accountNumber > 9999){
        cout<<"\nInvalid Account Number, An account number must be a 4-digit number. Please Try Again. ";
        cout<< "\nEnter the account number : ";
        cin>> BankAccount.accountNumber;
    }

    cout<< "\nEnter the account starting balance : ";
    cin>> BankAccount.accountBalance;

    while (BankAccount.accountBalance < 0 || BankAccount.accountBalance > 100000){
        cout<<"\nInvalid Account Balance, Balance cannot be a negative value or above 100 000. Please Try Again.";
        cout<< "\nEnter the account starting balance : ";
        cin>> BankAccount.accountBalance;
    }

    cout<< "\nEnter the account's interest rate : ";
    cin>> BankAccount.interestRate;

    while(BankAccount.interestRate < 0 || BankAccount.interestRate > 0.15){
        cout<< "\nInvalid Interest Rate, Interest rate must be between 0 and 0.15. Please try again.";
        cout<< "\nEnter the account's interest rate : ";
        cin>> BankAccount.interestRate;
    }

    return BankAccount;
}

account computeInterest(account bankAccount){

    double depositAmt, withdrawalAmt ;
    int holdingTerm;

    cout<< "\nEnter the account's holding term : ";
    cin>> holdingTerm; //same for both accounts

    while (holdingTerm < 0 || holdingTerm > 10){
    cout<< "\nInvalid Input! The account term must be between 0 and 10 years.\nEnter the account's holding term : ";
    cin>> holdingTerm;
    }

    cout<< "\nEnter the account's deposit amount : ";
    cin>> depositAmt; //same for both accounts

    cout<< "\nEnter the account's withdrawal amount : ";
    cin>> withdrawalAmt; //same for both accounts

    double intrestEarned = (0.83 * bankAccount.interestRate) * bankAccount.accountBalance;
    bankAccount.accountBalance += ((intrestEarned + depositAmt) - withdrawalAmt);

    return bankAccount;
}

void displayAccount(account accountData){

    cout<<"\n*************Account Information**************"<<endl;
    cout<<"Account Number : "<<accountData.accountNumber<<endl;
    cout<<"Balance : "<<accountData.accountBalance<<endl;
    cout<<"Interest Rate : "<<accountData.interestRate<<endl;
}

int main(){

    account accountData[5];
    double transferAmount;
    int checkDigit;

    for (int i = 0; i < 5; i++){
        accountData[i] = enterAccountData();
        checkDigit = accountData[i].accountNumber % 5;
        accountData[i].accountNumber = (accountData[i].accountNumber * 10) + checkDigit;//account number plus the check digit
        accountData[i] = computeInterest(accountData[i]);

        if(accountData[i].accountNumber == accountData[i+1].accountNumber){
            cout<<"\n\nThe Account Numbers Are The Same. Failed To Do Operation.";
        //output metrics
            displayAccount(accountData[i]);
            cout<< "\nCheck Digit : " << checkDigit <<endl;
        }

        else{ //different accounts

            cout<< "\nPlease Note that the amount you are about to enter is to be deducted from the first account.";
            cout<< "\nEnter the transfer amount : ";
            cin>> transferAmount;

            accountData[i].accountBalance -= transferAmount;//transferred to account i++
            cout<< "\nBalance(After Transfer, First Account) : "<< accountData[i].accountBalance;

            if (accountData[i].accountBalance - transferAmount <= 0){
                cout<< "\nBalance(After Transfer, First Account) : "<< accountData[i].accountBalance;
                if(accountData[i+1].accountBalance > 100000)
                    cout<<"\nWarning! Transfered Account Balance Above 100 000 ";

                displayAccount(accountData[i+1]);
                cout<< "\nBalance(After Transfer,Second Account) : "<< accountData[i+1].accountBalance;
                }
            else{//none negative balance after transfer
                if(accountData[i].accountBalance < 10)
                    cout<< "\nWarning! Account Below R10. ";

                cout<< "\nBalance(After Transfer, First Account) : "<< accountData[i].accountBalance;

                displayAccount(accountData[i]);
                accountData[i+1].accountBalance += transferAmount;

                if(accountData[i+1].accountBalance > 100000)
                cout<<"\nWarning! Account Balance Above 100 000 ";

            cout<< "\nBalance(After Transfer, Second Account) : "<< accountData[i+1].accountBalance;
        }
    }
    };
    // display a table
    for(int j = 0; j < 5; j++ ){
        cout<<"\n\n\n***********Final Account Summary***********";
        displayAccount(accountData[j]);
    }
    return 0;
}

