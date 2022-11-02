#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

typedef struct info{
    string name, birthday;
    int acc_number, balance, contactnumber;
} INFO;

typedef struct node{
    INFO user;
    struct node* next;
} NODE;

class atmClass{
    private:
        NODE *n, *p, *q, *temp, *receiver;
        INFO user;
        char pin[7];
        int i, accnum;
        void encrypt();
        void decrypt();
    public:
        void makenull();
        void locate();
        void locate2();
        void current_user();
        void add(INFO user);
        void add2();
        void pincode();
        void insertcard();
        void removecard();
        void reg_acc();
        void save();
        void retrieve();
        void saving_pin();
        void retrieve_pin();
        void balance_inquiry();
        void withdraw();
        void deposit();
        void fund_transfer();
        void change_pincode();
};

int menu();


int main(){
    atmClass ATM;
    ATM.makenull();
    ATM.retrieve();
    ATM.insertcard();
    ATM.locate2();
    switch (menu()) {
    system("cls");
    case 1: system("cls"); ATM.balance_inquiry(); break;
    case 2: system("cls"); ATM.withdraw(); ATM.save(); ATM.removecard(); break;
    case 3: system("cls"); ATM.deposit(); ATM.save(); break;
    case 4: system("cls"); ATM.fund_transfer(); ATM.save(); break;
    case 5: system("cls"); ATM.change_pincode(); ATM.saving_pin(); break;
    default: cout<<"Please select from 1 to 5!"<<endl; system("pause");
    }
}

void atmClass::makenull(){
    n = NULL;
}

void atmClass::add(INFO user){
    
    p=q=n;
    temp = new NODE;
    temp->user.name = user.name;
    temp->user.acc_number = user.acc_number;
    temp->user.balance = user.balance;
    temp->next = p;
    while(p!=NULL){
        q = p;
        p = p->next;
    }
    if (p==n)
        n = temp;
    else
        q->next = temp;
    temp->next = p;
}

void atmClass::insertcard(){

    fstream fp;
    string input, checker;
    int ch, amount;

    do{
        system("cls");
        cout <<"Please insert card...\n";
        fp.open("pinrecord.txt", ios::in);
    }while(!fp);

    system("cls");

    getline(fp,checker);
    srand(time(NULL));
    accnum = (rand()%(999999)+10000);
    user.acc_number = accnum;

    if(checker.length()==0){
        cout<<"\nYOUR ACCOUNT IS NOT REGISTER\n";
        cout<<"\n[1] REGISTER\n"<<"\n[2] EXIT\n";
        cout<<"\nPLEASE SELECT YOUR NUMBER OF CHOICE: ";
        cin>>ch;

    switch (ch){
    case 1: system("cls");
            cout<<"\nREGISTRATION";
            cout<<"\nACCOUNT NUMBER: "<<user.acc_number;
            cout<<"\nNAME: "; cin.ignore(); getline(cin,user.name);
            cout<<"\nBIRTHDAY:  "; cin.ignore(); getline(cin,user.birthday);
            cout<<"\nCONTACT NUMBER: ";cin>>user.contactnumber;    
            cout<<"\nENTER AMOUNT: ";cin>>amount;
            
            while(amount<500 || amount>20000 ){
            system("cls");
            cout<<"\nATM ONLY ACCEPTS MINIMUM OF 500 PESOS AND MAXIMUM OF 20,000 PESOS PER DEPOSIT";
            cout<<"\nEnter Initial Amount: ";
            cin>>amount;
            }
            user.balance = amount;
            cout<<"PIN: "; pincode();
            system("cls");

            cout<<"\nACCOUNT IS NOW REGISTERED";
            cout<<"\n=========================\n";
            cout<<"\nACCOUNT NUMBER: "<<user.acc_number;
            cout<<"\nNAME: "<<user.name;
            cout<<"\nBIRTHDAY: "<<user.birthday;
            cout<<"\nCONTACT NUMBER: "<<user.contactnumber;
            cout<<"\nACCOUNT BALANCE: "<<user.balance;
            encrypt(); saving_pin(); add(user); save(); system("pause"); break;
    case 2: removecard(); exit(0); break; } 
    }  
    else{
        while(input!=pin){
        system("cls");
        cout<<"\nLOG IN";
        system("cls");
        cout<<"\nENTER PIN: ";
        pincode();
        input=pin;
        retrieve_pin();
        decrypt();
        }
        cout<<"\nACCOUNT SUCCESSFULLY LOG IN\n";
    }
}

void atmClass::removecard(){
    fstream fp;
    do{ system("cls");
        cout <<"Please remove card...";
        fp.open("pinrecord.txt",ios::out);
    }while(fp);
    cout <<"Thank you for banking with MYLUGI BANK ";
    exit(0);
}

void atmClass::saving_pin(){
    fstream fp, fp2;
    fp.open("pinrecord.txt", ios::out); 
    fp <<accnum<<'\n';
    fp <<pin <<'\n';
    fp.close();

    fp2.open("userdata.txt",ios::out);
    fp2<<user.name<<endl;
    fp2<<user.acc_number<<'\n';
    fp2<<user.birthday<<'\n';
    fp2<<user.contactnumber<<'\n';
    cout<<"\nACCOUNT SUCCESSFULLY SAVED!";
    fp2.close();
}

void atmClass::retrieve_pin(){
    fstream fp, fp2;
    fp.open("pinrecord.txt", ios::in);
    while(!fp.eof()){
        fp >>accnum;
        fp >>pin;
    }
    fp.close();

    fp2.open("userdata.txt",ios::in);
    
    fp2>>user.name;
    fp2>>user.acc_number;
    fp2>>user.birthday;
    fp2>>user.contactnumber;
    fp2.close();

}

void atmClass::save(){

    p=n;
    fstream datalist;
    datalist.open("alldata.txt", ios::out);

    while (p!=NULL){
        datalist<<p->user.name<<'\n'<<p->user.acc_number<<'\n'<<p->user.balance<<'\n';
        p=p->next;
    }
    datalist.close();
 
}

void atmClass::retrieve(){
    
    fstream datalist;
    datalist.open("alldata.txt",ios::in);

    if(!datalist){
        cout<<"File error.\n";
        system("pause");
    }
    else{
        while(true){
            getline(datalist, user.name);
            datalist>>user.acc_number>>user.balance;
            datalist.ignore();

            if(!datalist.eof())
                add(user);
            else
                break;
        }
        datalist.close();
    }
}



void atmClass::pincode(){
    int index =0;
    char ch;
    while((ch=getch())!=13 && index<5){
        if (index<0)
            index=0;
        if(ch==8){//backspace ascii is 8
            putch('\b');
            putch(' ');
            putch('\b');
            index--;
        continue;
        }
        if(isdigit(ch)){
            pin[index++]=ch;
        putchar('*');
        }
    }
    if (index==5)
        pin[index++]=ch;
    pin[index]='\0';
    }

    void atmClass::encrypt(){
    int i=0;
    while(pin[i]!='\0'){
        pin[i]=pin[i] + 70;
        i++;
        }
}

void atmClass::decrypt(){
int i=0;
while(pin[i]!='\0'){
    pin[i]=pin[i] - 70;
    i++;
    }
}

int menu(){
    int ans;
    system("cls");
    cout<<"\n[1] BALANCE INQUIRY";
    cout<<"\n[2] WITHDRAW MONEY";
    cout<<"\n[3] DEPOSIT";
    cout<<"\n[4] FUND TRANSFER";
    cout<<"\n[5] CHANGE PIN";
    cout<<"SELECT (1-4): "; cin>>ans;
    return(ans);
}

void atmClass::balance_inquiry(){

    string input;
    char ans;

    while(input!=pin){
        system("cls");
        cout<<"\nENTER PIN: ";
        pincode();
        input=pin;
        retrieve_pin();
        decrypt();
    }
    
    cout<<"\nBALANCE INQUIRY";
    cout<<"\nACCOUNT NUMBER: "<<p->user.acc_number;
    cout<<"\nYOUR BALANCE IS: "<<p->user.balance;
    cout<<"\nDO YOU WANT TO DO ANOTHER TRANSACTION?";
    cout<<"\nIF YES PLEASE ENTER [Y] IF NO PRESS ANY KEY [N]";
    cout<<"\nAnswer: "; cin>>ans;
    system("pause");
    if(ans=='Y' || ans=='y'){
        system("cls");
        menu();
    }
    else {
        save();
        cout<<"THANK YOU FOR BANKING WITH US!";
        system("pause");
        exit(0);
    }
}

void atmClass::withdraw(){

    int withdraw, op;
    string input;

     while(input!=pin){
        system("cls");
        cout<<"\nENTER PIN: ";
        pincode();
        input=pin;
        retrieve_pin();
        decrypt();
    }

    system("cls");
    cout<<"\nPLEASE SELECT AN AMOUNT: ";

    cout<<"\n1. 500";
    cout<<"\n2. 1000";
    cout<<"\n3. 2000";
    cout<<"\n4. 3000";
    cout<<"\n5. 5000";
    cout<<"\n6. 6000";
    cout<<"\n7. 8000";
    cout<<"\n8. 10,000";
    cout<<"\n9. ENTER AMOUNT";
    cout<<"\nCHOICE: ";cin>>op;
    
    switch (op)
    {
    case 1: cout<<"\nYou have selected 500"; withdraw = 500; break;
    case 2: cout<<"\nYou have selected 1000"; withdraw = 1000; break;
    case 3: cout<<"\nYou have selected 2000"; withdraw = 2000; break;
    case 4: cout<<"\nYou have selected 3000"; withdraw = 3000; break;
    case 5: cout<<"\nYou have selected 5000"; withdraw = 5000; break;
    case 6: cout<<"\nYou have selected 6000"; withdraw = 6000; break;
    case 7: cout<<"\nYou have selected 8000"; withdraw = 8000; break;
    case 8: cout<<"\nYou have selected 10,000"; withdraw = 10000; break;
    case 9: cout<<"\nEnter amount: "; cin>>withdraw; break;
    }

    while ((withdraw%100)!=0 || withdraw>(p->user.balance-500) || withdraw>50000)
    {
        cout<<"\nNOTE: THIS MACHINE ONLY ACCEPTS & DISPENSE 1000, 500, AND 100";
        cout<<"\nEnter Amount: ";
        cin>>withdraw;
        
        if(withdraw>(p->user.balance-500)){
            system("cls");
            cout<<"\nInsufficient Balance";
        }

        if(withdraw>50000){
            system("cls");
            cout<<"Amount should not exist from 50000";
        }
    }
    p->user.balance = p->user.balance - withdraw;

    cout<<"\nYOUR ACCOUNT BALANCE IS:  "<<p->user.balance;
    system("pause");
    cout<<"\nTHANK YOU FOR BANKING WITH US";
    system("cls");
}

void atmClass::deposit(){

    string input;
    int deposit, ch;

    while(input!=pin){
        system("cls");
        cout<<"\nENTER PIN: ";
        pincode();
        input=pin;
        retrieve_pin();
        decrypt();
    }

    cout<<"\nDEPOSIT";
    cout<<"\nPlease enter amount: ";
    cin>>deposit;
    
    if((deposit%100)!=0){
        cout<<"\n100, 500, 1000";
    }
    else if(deposit>20000){
        cout<<"\nThis ATM is not accepting large amount of money.";
    }
    else{
        cout<<"\nYou have entered: "<<deposit;
        cout<<"\nIs the amount correct? [Press 1 to confirm]";
        cout<<"\nInsert more cash? [Press 2 to confirm]\n";
        cin>>ch;
        if(ch==1){
            cout<<"\nYou have deposit "<<deposit<<" pesos.";
        } else{
            cout<<"\nPlease enter amount: ";
            cin>>deposit;
        }
    }
    p->user.balance = p->user.balance + deposit;
    cout<<"\nYour Current Balance: "<<p->user.balance;
}


void atmClass::fund_transfer(){

    int fund, total;

    cout<<"\nEnter User Account Number: ";
    cin>>accnum;
    
    locate();

    if (receiver==NULL){
        cout<<"\nUSER ACCOUNT NOT FOUND.";
        system("pause");
    }
    
    else{
        cout<<"\nUSER INFO";
        cout<<"\nNAME: "<<receiver->user.name;
        cout<<"\nACCOUNT NUMBER: "<<receiver->user.acc_number;

        cout<<"\nEnter amount: ";
        cin>>fund;
        if((fund%100)!=0){
            cout<<"\n100, 500, 1000";
        }
        else if(fund>(p->user.balance-500)){
            cout<<"\nInsufficient Amount";
        }
        else{
            p->user.balance -= fund;
            receiver->user.balance += fund;
            cout<<"\nYou have transfered "<<fund;
            cout<<"\nYour Current Balance is "<<p->user.balance;
            }
    }
}

void atmClass::change_pincode(){
   
    p=q=n;

    string input;

    if(p==NULL){
        cout<<"DATA DOES NOT EXIST";
        system("pause");
    }
    else{

        while(input!=pin){
        system("cls");
        cout<<"\nENTER PIN: ";
        pincode();
        input=pin;
        retrieve_pin();
        decrypt();
        }

        cout<<"\nENTER NEW PIN: "; pincode(); encrypt();
        cout<<"\nPIN SUCCESSFULLY CHANGE.";

        system("pause");
    }
}

void atmClass::locate(){

    receiver = n;

    while(receiver!=NULL && accnum!=receiver->user.acc_number){
        receiver = receiver->next;
    }

}

void atmClass::locate2(){
   
    p=n;
    retrieve_pin();
    while(p!=NULL && accnum!=p->user.acc_number){
        p = p->next;
    }

    system("cls");
    cout<<p->user.name<<p->user.acc_number;
    system("pause");
}