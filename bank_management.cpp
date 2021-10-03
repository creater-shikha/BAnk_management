#include<iostream>
#include<fstream>
#include<map>
using namespace std;
class  InsufficientFunds
{
private:
    /* data */
public:
     InsufficientFunds(/* args */);
    ~ InsufficientFunds();
};

 InsufficientFunds:: InsufficientFunds(/* args */)
{
}

 InsufficientFunds::~ InsufficientFunds()
{
};

class Account{
    private:
    long account;
    string FirstName;
    string LastName;
    float balance;
   static long nextAccount;
    
    public:
   Account(){
    }
    Account(string a,string b,float c){
        nextAccount++;
        FirstName=a;
        LastName=b;
         account=nextAccount;
         balance=c;
       
    }
    long getAccount(){return account;}
    string getFirstName(){return FirstName;}
    string getlastname(){return LastName;}
    float balances(){return balance;}
    void deposite(float amount){
     
     
     balance+=amount;

    }
    void withdrawal(float amount){
     if(balance-amount<500)
     throw InsufficientFunds();
     
     balance-=amount;
    }
  static void setLastAccount(long accountNumber){
     nextAccount=accountNumber;
  }
   static long getLastAccount(){
     return nextAccount;
  }
    
friend ofstream &operator <<(ofstream &ofs,Account &acc);//operator overloading for reading the file
friend ifstream &operator >>(ifstream &ifs,Account &acc);//operator overloading for writing the file
friend ostream &operator <<(ostream &os,Account &acc);    //operator overloading of insertion  operator
};
long Account::nextAccount=0;
// long Account::nextAccount=0;
class Bank{
    private:
    map<long ,Account>m;
   public:
        Bank();
        Account OpenAccount(string a, string b,float c);
        Account BalanceEnqurie(long AccountNumber);
        Account Deposite(long acountNumber, float amount);
        Account Withdrawal(long acountNumber, float amount);
        void CloseAccount(long accountNumber);
        void showall();
  ~Bank();
      
};
int main(){ Account acc;
Bank ban;
 string a,b;
 int choice;
 float balance;
float amount;
long accountnumber;          
        cout<<"\n****Banking System****"<<endl;  
        do{
     
        cout<<"\t\t\nSelect one option below";
        cout<<"\t\t\n1. Open an Account ";
        cout<<"\t\t\n2. Balance Enquiry";
        cout<<"\t\t\n3. Deposit";
        cout<<"\t\t\n4. Withdrawal";
        cout<<"\t\t\n5. close an Account ";
        cout<<"\t\t\n6. Show all Account";
        cout<<"\t\t\n7. Quit\n\n";
        
        cout<<"Enter your Choice: ";
        cin>>choice;
       switch (choice)
            { 
               
            case 1:
           cout<<"FirstName :";
            cin>>a;
            cout<<"LastName :";
            cin>>b;
            cout<<"Initial Amount :";
            cin>>balance;
            acc=  ban. OpenAccount(a,b,balance);
           cout<<"\n\n"; 
         cout<<"Congradulation Account is Created"<<endl;
           cout<<acc;
           cout<<"\n\n";
                break;
            case 2:
            cout<<"Enter the account number :";
            cin>>accountnumber;
               acc=ban.BalanceEnqurie(accountnumber);
               cout<<endl<<"Your account detail is : "<<endl;
               cout<<acc;
               cout<<"\n\n";
                break;  
            case 3:
            cout<<"Enter the ammount to be deposite :"<<endl;
            cin>>amount;
               acc=ban.Deposite(accountnumber,amount);
               cout<<endl<<"Amount is deposite ";
               cout<<acc;
               cout<<"\n\n";
                break;      
            case 4:
             cout<<"Enter the ammount to be deposite :"<<endl;
            cin>>amount;
               acc=ban.Withdrawal(accountnumber,amount);
       cout<<endl<<"Amount is withdrawal ";
               cout<<acc;
               cout<<"\n\n";
                break;
            case 5:
             cout<<"Enter the account number :";
            cin>>accountnumber;
               ban.CloseAccount(accountnumber);
               cout<<endl<<"Account is closed "<<endl;
               cout<<acc;
               cout<<"\n\n";
                break;
            case 6:
            ban.showall();
            cout<<"\n\n";
            break;
               
            case 7:
               break;
            default:
                 cout<<"\nEnter your choice";
                 exit(0);
              
            }
        }while(choice!=7);
  

    return 0;
}
ofstream &operator <<(ofstream &ofs,Account &acc){
    ofs<<acc.account<<endl;
    ofs<<acc.FirstName<<endl;
    ofs<<acc.LastName<<endl;
    ofs<<acc.balance<<endl;
    return ofs;
}
ifstream &operator >>(ifstream &ifs,Account &acc){
ifs>>acc.account;
ifs>>acc.FirstName;
ifs>>acc.LastName;
ifs>>acc.balance;
    return ifs;
}
ostream &operator <<(ostream &os,Account &acc){
    os<<"First Name :"<<acc.getFirstName()<<endl;
     os<<"Last Name :"<<acc.getlastname()<<endl;
     os<<"Account Number:"<<acc.getAccount()<<endl;
     os<<"Balance:"<<acc.balances()<<endl;
     return os;

}
Bank::Bank(){
    Account b;
    ifstream infile;
    infile.open("Bank.data");
    if(!infile){
        return;
    }
    while (!infile.eof()){
        infile >> b;  
        m.insert(pair<long ,Account>(b.getAccount(),b));  }
        Account::setLastAccount(b.getAccount());
        infile.close();}
    
Account Bank::OpenAccount(string fname,string lname,float balance){
    ofstream outfile;
    Account b(fname,lname,balance);
    m.insert(pair<long ,Account>(b.getAccount(),b));
    outfile.open("Bank.data",ios::trunc);
    map<long,Account>::iterator itr;
    for(itr=m.begin();itr!=m.end();itr++){
        outfile<<itr->second;
    }
    outfile.close();
    return b;

}
Account Bank::BalanceEnqurie(long accountnumber){
map<long,Account>::iterator itr=m.find(accountnumber);
return itr->second;
}
Account Bank::Deposite(long accountnumber,float amount){
  map<long,Account>::iterator itr=m.find(accountnumber);
itr->second.deposite(amount);
return itr->second;
}
Account Bank::Withdrawal(long accountnumber,float amount){
  map<long,Account>::iterator itr=m.find(accountnumber);
itr->second.withdrawal(amount);
return itr->second;
}
void Bank::CloseAccount(long accountnumber){
  map<long,Account>::iterator itr=m.find(accountnumber);
  cout<<"Account Delete"<<itr->second<<endl;
  m.erase(accountnumber);}
void Bank::showall(){
     map<long,Account>::iterator itr;
    for(itr=m.begin();itr!=m.end();itr++){
        cout<<"Acount"<<itr->first<<endl<<itr->second<<endl;
    }
}
Bank::~Bank(){
    ofstream outfile;
    outfile.open("Bank.data",ios::trunc);
    map<long,Account>::iterator itr;
    for(itr=m.begin();itr!=m.end();itr++){
        outfile<<itr->second;
    }
    outfile.close();

    
}