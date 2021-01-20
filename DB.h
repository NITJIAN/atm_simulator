#ifndef DATABASE_H
#define DATABASE_H
#include<iostream>
#include<winsock.h>  //mandatory to include else will show error in bacnkend libraries also must include above mysql.h
#include<mysql.h>
#include<string>
#include<windows.h>
#include<map>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;


map<string, string> find_details(string account_no)
{
    string dummy;
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn = mysql_init(0);
    conn =mysql_real_connect(conn,"remotemysql.com","7ylda3PEbQ","9jxeBjXw5c","7ylda3PEbQ",3306,NULL,0);
    map<string, string> details;
    if (conn)
    {
        stringstream ss;
        stringstream ss1;

        ss << "select * from accounts where account_no =  '" << account_no << "'";
        string query = ss.str();
        const char *q = query.c_str();
        int qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {    ss1<<row[4];
                  string abc=ss1.str();
                details["account_no"] = row[0];
				details["first_name"] = row[1];
				details["last_name"] = row[2];
                details["pin"] = row[3];
                details["balance"] = abc;
                details["mobile"] = row[5];
                details["email"] = row[6];

                return details;
            }
        }
        else
        {
            return details;
        }
    }


    mysql_close(conn);
}
void update(map<string, string> user)
{
     MYSQL *conn1;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn1 = mysql_init(0);
    conn1 =mysql_real_connect(conn1,"remotemysql.com","7ylda3PEbQ","9jxeBjXw5c","7ylda3PEbQ",3306,NULL,0);
if (conn1){
    int qstate;
    stringstream ss;
	stringstream bal;

    ss << "UPDATE accounts SET pin = '" << user["pin"] << "', balance= '" << user["balance"] << "'  ,  mobile= '" << user["mobile"] << "' WHERE account_no= '" << user["account_no"] << "'";
    string query = ss.str();
    const char *q = query.c_str();
    qstate = mysql_query(conn1, q);

    if (qstate == 0)
        cout << "Record Updated" << endl;
    else
        cout << "ATM Closed" << endl;
}
    mysql_close(conn1);
}
void add_transaction(double amount , double balance,string account_no,string particular,int f)
{   MYSQL *conn1;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn1 = mysql_init(0);
    conn1 =mysql_real_connect(conn1,"remotemysql.com","7ylda3PEbQ","9jxeBjXw5c","7ylda3PEbQ",3306,NULL,0);
    if (conn1){
    int qstate;
    if(f==0){
    if(particular=="Self cash withdrawal"){
        stringstream sw;
        sw<<"INSERT into transactions values('"<<account_no<<"',ADDTIME(sysdate(), '5:30'),'"<<particular<<"',"<<amount<<",0,"<<balance<<");";
        string query1 = sw.str();
        const char *q = query1.c_str();
    qstate = mysql_query(conn1, q);
    if (qstate == 0)
        cout << "Transaction Updated" << endl;
    else
        cout << "Transaction not Updated" << endl;
    }
    if(particular=="Self cash deposit"){
        stringstream sd;
        sd<<"INSERT into transactions values('"<<account_no<<"',ADDTIME(sysdate(), '5:30'),'"<<particular<<"',0,"<<amount<<","<<balance<<");";
        string query2 = sd.str();
        const char *q = query2.c_str();
    qstate = mysql_query(conn1, q);
     if (qstate == 0)
        cout << "Transaction Updated" << endl;
    else
        cout << "Transaction not Updated" << endl;
    }
    }
else if(f==1){
        stringstream sft;
        sft<<"INSERT into transactions values('"<<account_no<<"',ADDTIME(sysdate(), '5:30'),'"<<particular<<"',"<<amount<<",0,"<<balance<<");";
        string query1 = sft.str();
        const char *q = query1.c_str();
    qstate = mysql_query(conn1, q);
    if (qstate == 0)
        cout << "Transaction Updated" << endl;
    else
        cout << "Transaction not Updated" << endl;

}
else if(f==2){
    stringstream sft1;
        sft1<<"INSERT into transactions values('"<<account_no<<"',ADDTIME(sysdate(), '5:30'),'"<<particular<<"',0,"<<amount<<","<<balance<<");";
        string query1 = sft1.str();
        const char *q = query1.c_str();
    qstate = mysql_query(conn1, q);
    if (qstate == 0)
        cout << "Transaction Updated" << endl;
    else
        cout << "Transaction not Updated" << endl;

}
    }
     mysql_close(conn1);


}
void display_transactions(string account_no){

    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn = mysql_init(0);
    conn =mysql_real_connect(conn,"remotemysql.com","7ylda3PEbQ","9jxeBjXw5c","7ylda3PEbQ",3306,NULL,0);
    if (conn){

    stringstream ss;
        ss << "SELECT * from transactions where account_no =  '" << account_no << "'";
        string query = ss.str();
    const char *q = query.c_str();
        int qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            cout << "Account number : " << account_no<<endl;
            cout << "Date,Time:\tParticulars:\tDebit:\tCredit:\tBalance:\t"<<endl;
            while (row = mysql_fetch_row(res))
            {
                cout<<row[1]<<"\t";
                cout<<row[2]<<"\t";
                cout<<row[3]<<"\t";
                cout<<row[4]<<"\t";
                cout<<row[5]<<"\t";
                   cout<<endl;
            }
        }





    }

}

#endif

