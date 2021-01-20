#ifndef ACOUNTHOLDER_H
#define ACCOUNTHOLDER_H

#include<iostream>
#include<map>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "DB.h"
#include "email.h"
using namespace std;
class Accountholder{
       mutable string first_name,last_name,email;
       double balance;
       string mobile;
	   string  pin;
       string account_no;
	   map<string,string> customer;
       public:
	   Accountholder();
	   void find_user();
       void withdraw();
       void deposit();
       void change_mobile_no() ;

       void change_pin() ;
       void display_balance() const;
       void display_details() const;
       void fund_transfer();
       void display_statement();
       ~Accountholder();
};

Accountholder::Accountholder(){

    cout << "\t\t\t\t    =========================================" << endl;
    cout << "\t\t\t\t          ||   WELCOME TO  ATM   ||" << endl;
    cout << "\t\t\t\t    =========================================" << endl;



    find_user();
}
void Accountholder::find_user()
{
    string entered_account_no, entered_pin;

        cout << "Enter your correct Account no.: "<< endl;
        cin >> entered_account_no;
        customer  = find_details(entered_account_no);
        account_no=customer["account_no"];
	    first_name=customer["first_name"];
		last_name=customer["last_name"];
		pin=customer["pin"];
	    balance=stof(customer["balance"]);
		mobile=customer["mobile"];
	    email=customer["email"];

       if(pin=="-1"){
		   string otp;
		   string entered_otp;
		   string entered_pin1;

		   cout<<"Your Pin has not been set."<<endl;
		   otp=send_otp(email);
		   cout<<"Please verify that it's you by entering the OTP sent on your registered email id."<<endl;
		   cin>>entered_otp;
		   if(otp==entered_otp){
			   cout << "Enter your PIN" << endl;
                cin >> entered_pin1;
				 while (entered_pin1.length() != 4)
    {
        cout << "Incorrect  (choose a pin of 4 digits) " << endl;
        cout << "Enter valid pin" << endl;
        cin >> entered_pin1;
    }
				pin=entered_pin1;
				cout<<"Pin set successfully!!"<<endl;

		   }
		   else{
			   cout<<"Wrong OTP. Please try again later."<<endl;


		   }

	   }
else{
    cout << "Enter PIN" << endl;
    cin >> entered_pin;


    while (pin!= entered_pin)
    {

        cout << "Enter correct PIN "<< endl;
        cin >>entered_pin;


    }

}
}

 void Accountholder::withdraw()
{
float amt_withdraw;
    cout << "Enter amount to be withdrawn : " << endl;
    cin >> amt_withdraw;
    while (balance < amt_withdraw)
    {
        cout << "You don't have sufficient funds " << endl;
        cout << "Enter correct amount" << endl;
        cin >> amt_withdraw;
    }
    balance=balance-amt_withdraw;
    string pr="Self cash withdrawal";
    add_transaction(amt_withdraw,balance,account_no,pr,0);
    cout << "Success!!" << endl;
}
 void Accountholder::deposit()
{
float amt_deposit;
    cout << "Enter amount to be deposited : " << endl;
    cin >> amt_deposit;
   while (amt_deposit < 100 && amt_deposit > 20000)
    {
        cout << "You can only deposit amout between Rs. 100 and Rs. 20000" << endl;
        cout << "Enter correct amount" << endl;
        cin >> amt_deposit;
    }
    balance=balance+amt_deposit;
    string pr="Self cash deposit";
    add_transaction(amt_deposit,balance,account_no,pr,0);
    cout << "Success!!" << endl;
}
void Accountholder::display_details() const
{
	cout << "Account Number : " << account_no << endl;
    cout << "Name : " << first_name<<" "<<last_name << endl;
    cout << "Mobile_Number : " << mobile << endl;
    cout << "Email : " << email << endl;

}
void Accountholder::display_balance() const
{
	cout << "Your Balance is : " << balance << endl;
}
void Accountholder::change_mobile_no()
{    cout<<"You chose changing mobile number."<<endl;
string entered_otp;
		   string otp=send_otp(email);
	 cout<<"Please verify that it's you by entering the OTP sent on your registered email id."<<endl;
		   cin>>entered_otp;
		   if(otp==entered_otp){
			   string entered_mn;
    cout << "Enter new mobile number : " << endl;
    cin >> entered_mn;
    while (entered_mn.length() != 10)
    {
        cout << "Incorrect Number (must be of 10 digits) " << endl;
        cout << "Enter correct mobile number" << endl;
        cin >> entered_mn;
    }
    mobile=entered_mn;
    cout << "Mobile Number changed Successfully!!" << endl;

		   }
		   else{
			   cout<<"Wrong OTP. Please try again later."<<endl;


		   }
}
void Accountholder::change_pin()
{
        cout<<"You chose changing pin."<<endl;
string entered_otp;
		   string otp=send_otp(email);
	 cout<<"Please verify that it's you by entering the OTP sent on your registered email id."<<endl;
		   cin>>entered_otp;
		   if(otp==entered_otp){
			   string entered_newpin;
    cout << "Enter new pin : " << endl;
    cin >> entered_newpin;
    while (entered_newpin.length() != 4)
    {
        cout << "Incorrect pin (must be of 4 digits) " << endl;
        cout << "Enter a valid pin." << endl;
        cin >> entered_newpin;
    }
    pin=entered_newpin;
    cout << "Pin changed Successfully!!" << endl;

		   }
		   else{
			   cout<<"Wrong OTP. Please try again later."<<endl;


		   }
}
void Accountholder::fund_transfer()
{
    double to_be_transferred;
    string entered_account_no, entered_pin;
   cout << "Enter amount to be transferred : " << endl;
    cin >> to_be_transferred;
    while (balance < to_be_transferred)
    {
        cout << "You don't have sufficient funds " << endl;
        cout << "Enter correct amount" << endl;
        cin >> to_be_transferred;
    }
    balance=balance-to_be_transferred;
     cout << "Enter correct Account no. of account receiving funds:";
        cin >> entered_account_no;
       map<string,string> receiver=find_details(entered_account_no);
      double newbalance=stof(receiver["balance"])+to_be_transferred;
       stringstream ss2;
    ss2<<newbalance;
    string bala=ss2.str();
      receiver["balance"]=bala;
      update(receiver);
      string pr="Fund Transfer to account no. "+entered_account_no;
      string pr1="Fund Transfer from account no. "+account_no;
      add_transaction(to_be_transferred,balance,account_no,pr,1);
      add_transaction(to_be_transferred,newbalance,entered_account_no,pr1,2);
}
 void Accountholder::display_statement()
 {
cout<<"Your account statement is as follows:"<<endl;
display_transactions(account_no);





 }
Accountholder::~Accountholder()
{
    stringstream ss2;
    ss2<<balance;
    string bala=ss2.str();
		customer["pin"]=pin;
	  customer["balance"]=bala;
		customer["mobile"]=mobile;
		update(customer);

}

#endif
