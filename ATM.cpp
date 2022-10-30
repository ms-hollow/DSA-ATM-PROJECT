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
        void save();
        void retrieve();
        void saving_pin();
        void retrieve_pin();
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
    if (p==n)
        n = temp;
    else
        q->next = temp;
    temp->next = p;
}


void atmClass::insertcard(){

    INFO ac;
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
    ac.acc_number = accnum;

    if(checker.length()==0){
        cout<<"\nYOUR ACCOUNT IS NOT REGISTER\n";
        cout<<"\n[1] REGISTER\n"<<"\n[2] EXIT\n";
        cout<<"\nPLEASE SELECT YOUR NUMBER OF CHOICE: ";
        cin>>ch;

    switch (ch){
    case 1: system("cls");
            cout<<"\nREGISTRATION";
            cout<<"\nACCOUNT NUMBER: "<<ac.acc_number;
            cout<<"\nNAME: "; cin.ignore(); getline(cin,ac.name);
            cout<<"\nBIRTHDAY: ";cin.ignore(); getline(cin,ac.birthday);
            cout<<"\nCONTACT NUMBER: ";cin>>ac.contactnumber;    
            cout<<"\nENTER AMOUNT: ";cin>>amount;
            
            while(amount>20000){
            system("cls");
            cout<<"\nATM ONLY ACCEPTS P 20,000 PER DEPOSIT";
            cout<<"\nEnter Initial Amount: ";
            cin>>amount;
            }
            ac.balance = amount;
            cout<<"PIN: "; pincode(); encrypt(); saving_pin();
            system("cls");

            cout<<"\nACCOUNT IS NOW REGISTERED";
            cout<<"\n=========================\n";
            cout<<"\nACCOUNT NUMBER: "<<ac.acc_number;
            cout<<"\nNAME: "<<ac.name;
            cout<<"\nBIRTHDAY: "<<ac.birthday;
            cout<<"\nCONTACT NUMBER: "<<ac.contactnumber;
            cout<<"\nACCOUNT BALANCE: "<<ac.balance;
            save(); add(ac); system("pause"); break;
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
    menu();
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
    NODE *p;
    fp.open("pinrecord.txt", ios::out); 
    fp <<pin <<'\n';
    fp <<accnum;
    fp.close();
}

void atmClass::retrieve_pin(){
    fstream fp;
    fp.open("pinrecord.txt", ios::in);
    while(!fp.eof()){
        fp >>pin;
        fp >>accnum;
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

void atmClass::save(){

    INFO user;
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

void atmClass::retrieve(){
    fstream fp;
    INFO user;
    fp.open("userdata.txt",ios::in);
    if(!fp){
        cout<<"FILE ERROR\n";
        system("pause");
    }
    else{
        while(true){
            getline(fp, user.name);
            fp>>user.acc_number>>user.birthday>>user.contactnumber>>user.balance;
            fp.ignore();

            if(!fp.eof())
                add(user);
            else
                break;
        }
        fp.close();
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

    cout<<"\nENTER PIN: "; pincode();
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