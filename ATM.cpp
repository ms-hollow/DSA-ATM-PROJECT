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
        NODE *n;
        INFO user;
        char pin[7];
        int i, accnum;
        void encrypt();
        void decrypt();
    public:
        void makenull();
        void add(INFO user);
        void pincode();
        void insertcard();
        void removecard();
        void reg_acc();
        void save_acc();
        void retrieve_acc();
        void saving_pin();
        void retrieve_pin();
        void save_datalist();
        void retrieve_datalist();
        void balance_inquiry();
};

int menu();


int main(){
    atmClass ATM;
    ATM.insertcard();
    switch (menu()) {
    system("cls");
    case 1: system("cls"); ATM.balance_inquiry(); break;
    default: cout<<"Please select from 1 to 4!"<<endl; system("pause");
    }

}

void atmClass::makenull(){
    n = NULL;
}

void atmClass::add(INFO user){
    
    NODE *p, *q, *temp;
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
            cout<<"\nBIRTHDAY: ";cin.ignore(); getline(cin,user.birthday);
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
            save_acc(); encrypt(); saving_pin(); add(user); save_datalist(); system("pause"); break;
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
    fp.close();
    cout <<"Thank you for banking with MYLUGI BANK ";
    exit(0);
}

void atmClass::saving_pin(){
    fstream fp;
    fp.open("pinrecord.txt", ios::out); 
    fp <<accnum<<'\n';
    fp <<pin <<'\n';
    fp.close();
}

void atmClass::save_acc(){

    fstream accoutInfos;
    accoutInfos.open("userdata.txt",ios::out);
    accoutInfos<<user.name<<endl;
    accoutInfos<<user.acc_number<<'\n';
    accoutInfos<<user.birthday<<'\n';
    accoutInfos<<user.contactnumber<<'\n';
    accoutInfos<<user.balance<<'\n';
    cout<<"\nACCOUNT SUCCESSFULLY SAVED!";
    accoutInfos.close();
 
}

void atmClass::retrieve_acc(){
    fstream accoutInfos;
    accoutInfos.open("userdata.txt",ios::in);
    accoutInfos>>user.name;
    accoutInfos>>user.acc_number;
    accoutInfos>>user.birthday;
    accoutInfos>>user.contactnumber;
    accoutInfos>>user.balance;
    accoutInfos.close();
}

void atmClass::retrieve_pin(){
    fstream fp;
    fp.open("pinrecord.txt", ios::in);
    while(!fp.eof()){
        fp >>accnum;
        fp >>pin;
    }
    fp.close();
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
    NODE *p, *q, *temp;
    p=q=n;
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
        system("pause");
        cout<<"THANK YOU FOR BANKING WITH US!";
        exit(0);
    }
}

void atmClass::save_datalist(){
    fstream fp;
    fp.open("alldata.txt", ios::out);
    NODE *p;
    p=n;
    while (p!=NULL){
        fp<<p->user.name<<'\n'<<p->user.acc_number<<'\n'<<p->user.balance<<'\n';
        p=p->next;
    }
    fp.close();
}

void atmClass::retrieve_datalist(){
    fstream fp;
    fp.open("alldata.txt",ios::in);
    if(!fp){
        cout<<"File error.\n";
        system("pause");
    }
    else{
        while(true){
            getline(fp, user.name);
            fp>>user.acc_number>>user.balance;
            fp.ignore();

            if(!fp.eof())
                add(user);
            else
                break;
        }
        fp.close();
    }
}