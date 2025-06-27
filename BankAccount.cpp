#include <iostream>

using namespace std;

class account{
private:

    int accountNumber;
    double accountBalance;
    const static double interestRate ; //3%

public:

    void enterAccountData();
    double computeInterest(int);
    void displayAccount();
    int getAccountNumber();
    void setAccountNumber(int);
    double getAccountBalance();
    void setAccountBalance(double);

};

    const double account::interestRate = 0.03;  // Definition outside the class for a constant static variable

    int account::getAccountNumber(){
        return accountNumber;
    }

    void account::setAccountNumber(int accNo){
        accountNumber = accNo;
    }

    double account::getAccountBalance(){
        return accountBalance;
    }

    void account::setAccountBalance(double accBal){
        accountBalance = accBal;
    }

    void account::enterAccountData(){
    // best practice is to prompt in main then use setters
        cout<< "\nEnter the account number : ";
        cin>> accountNumber;

        while (accountNumber < 1000 || accountNumber > 9999){
            cout<<"\nInvalid Account Number, An account number must be a 4-digit number. Please Try Again. ";
            cout<< "\nEnter the account number : ";
            cin>> accountNumber;
        }

        cout<< "\nEnter the account starting balance : ";
        cin>> accountBalance;

        while (accountBalance < 0 || accountBalance > 100000){
            cout<<"\nInvalid Account Balance, Balance cannot be a negative value or above 100 000. Please Try Again.";
            cout<< "\nEnter the account starting balance : ";
            cin>> accountBalance;
        }

    }

    double account::computeInterest(int yearsofInterest){

        double depositAmt, withdrawalAmt ;

        cout<< "\nEnter the account's deposit amount : ";
        cin>> depositAmt; //same for both accounts

        cout<< "\nEnter the account's withdrawal amount : ";
        cin>> withdrawalAmt; //same for both accounts

        for (int i = 0; i < yearsofInterest; i++){

            double intrestEarned = (0.83 * interestRate) * accountBalance * i;
            accountBalance = accountBalance + intrestEarned + depositAmt - withdrawalAmt ;

            cout<<"\nInterest for year "<<i<<" is : R"<<accountBalance;
        }

        return accountBalance;
    }

    void account::displayAccount(){

        cout<<"\n*************Account Information**************"<<endl;
        cout<<"Account Number : "<<accountNumber<<endl;
        cout<<"Balance : "<<accountBalance<<endl;
        cout<<"Interest Rate : "<<interestRate<<endl;
    }



int main(){

    int arrLength = 10;
    account accountData[arrLength];
    double transferAmount;
    int checkDigit, holdingTerm;
    char input;

    for (int i = 0; i < arrLength; i++){
        accountData[i].enterAccountData();
        checkDigit = accountData[i].getAccountNumber() % 5;
        accountData[i].setAccountNumber((accountData[i].getAccountNumber() * 10) + checkDigit);//account number plus the check digit

        cout<<"\nDo you want to continue ? Y\\N >>";
        cin>>input;

        input = toupper(input);

        if(input == 'Y')
            continue;
        else{
            if(input == 'N')
                i = arrLength;
            else{
                cout<<"Invalid Input. Stopping ....";
                i = arrLength;
            }
        }

    };

    cout<< "\nEnter the account's holding term : ";
    cin>> holdingTerm; //same for all accounts
    while (holdingTerm < 0 || holdingTerm > 10){
        cout<< "\nInvalid Input! The account term must be between 0 and 10 years.\nEnter the account's holding term : ";
        cin>> holdingTerm;
    }


    for (int i = 0; i < arrLength; i++){

        accountData[i].computeInterest(holdingTerm);

        if(accountData[i].getAccountNumber() == accountData[i+1].getAccountNumber()){
            cout<<"\n\nThe Account Numbers Are The Same. Failed To Do Operation.";
        //output metrics
            accountData[i].displayAccount();
            cout<< "\nCheck Digit : " << checkDigit <<endl;
        }

        else{ //different accounts

            cout<< "\nPlease Note that the amount you are about to enter is to be deducted from the first account.";
            cout<< "\nEnter the transfer amount : ";
            cin>> transferAmount;

            accountData[i].setAccountBalance(accountData[i].getAccountBalance() - transferAmount);//transferred to account i++
            cout<< "\nBalance(After Transfer, First Account) : "<< accountData[i].getAccountBalance();

            if (accountData[i].getAccountBalance() <= 0){
                cout<< "\nBalance(After Transfer, First Account) : "<< accountData[i].getAccountBalance();
                if(accountData[i+1].getAccountBalance() > 100000)
                    cout<<"\nWarning! Transfered Account Balance Above 100 000 ";

                accountData[i+1].displayAccount();
                cout<< "\nBalance(After Transfer,Second Account) : "<< accountData[i+1].getAccountBalance();
                }
            else{//none negative balance after transfer
                if(accountData[i].getAccountBalance() < 10)
                    cout<< "\nWarning! Account Below R10. ";

                cout<< "\nBalance(After Transfer, First Account) : "<< accountData[i].getAccountBalance();

                accountData[i].displayAccount();

                accountData[i + 1].setAccountBalance(accountData[i + 1].getAccountBalance() + transferAmount);
                //accountData[i+1].accountBalance += transferAmount;

                if(accountData[i+1].getAccountBalance() > 100000)
                cout<<"\nWarning! Account Balance Above 100 000 ";
                //you need to add the transferred amount to the second account, please change that.
            cout<< "\nBalance(After Transfer, Second Account) : "<< accountData[i+1].getAccountBalance();
        }
    }
    };
    // display a table
    for(int j = 0; j < arrLength; j++ ){
        cout<<"\n\n\n***********Final Account Summary***********";
        accountData[j].displayAccount();
    }
    return 0;
}
