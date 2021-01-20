#include "Accountholder.h"
#include<iostream>

int main(){

    Accountholder acc;
    bool again=true;
    do{



        cout<<"1. Deposit"<<endl;
        cout<<"2. Cash Withdrawl"<<endl;
        cout<<"3. Balance Enquiry"<<endl;
        cout<<"4. Change Mobile No."<<endl;
        cout<<"5. Change your ATM Pin"<<endl;
        cout<<"6. Account Details"<<endl;
        cout<<"7. Transfer funds"<<endl;
        cout<<"8. Account Statement"<<endl;
        cout<<"9. Exit"<<endl;
        int ch;
        cout<<"Enter Your Choice : ";
        cin>>ch;
        switch(ch){
            case 1: acc.deposit();
                    break;
            case 2: acc.withdraw();
                    break;
            case 3: acc.display_balance();
                    break;
            case 4: acc.change_mobile_no();
                    break;
            case 5: acc.change_pin();
                    break;
            case 6: acc.display_details();
                    break;
            case 7:acc.fund_transfer();
                   break;
            case 8:acc.display_statement();
                   break;
            case 9: again=false;cout<<"Thanks for using our ATM.Have a nice day."<<endl;
                    break;
            default : cout<<"You Entered Wrong Choice "<<endl;
                    cout<<"Please Enter your Choice Again..";


        }


    }while(again);


    return 0;
}
