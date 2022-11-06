/*
    ABBEGAIL MILES LEONEN
    BSCS-NS-2B
    PROJECT IN DATA STRUCTURES AND ALGORITHM
*/

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#include <locale>
#include <Windows.h>

using namespace std;

typedef struct info{
    string name, birthday;
    int acc_number, balance,  contact_num;
} INFO;

typedef struct node{
    INFO user;
    struct node* next;
} NODE;

class atmClass{
    private:
        NODE *n, *p, *q, *temp, *receiver;
        INFO user;
        string MENU[7];
        char pin[7];
        string input;
        int i, accnum;
        void encrypt();
        void decrypt();
    public:
        void makenull();
        void locate();
        void leave();
        void current_user();
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
        void withdraw();
        void deposit();
        void fund_transfer();
        void change_pincode();
};

class comma_numpunct : public numpunct<char>
{
  protected:
    virtual char do_thousands_sep() const{
        return ',';
    }

    virtual string do_grouping() const{
        return "\03";
    }
};


locale comma_locale(locale(), new comma_numpunct());
void loading_ani();
void SetColor(int ForgC);
void gotoxy(int x,int y);
void setFontStyle(int FontSize);
void ShowConsoleCursor(bool showFlag);


int main(){

    atmClass ATM;
    ATM.makenull();
    //ATM.insertcard();
    ATM.retrieve();
    ATM.insertcard();

    setFontStyle(23);
    gotoxy(45, 12);
    string Menu[7] = {"BALANCE INQUIRY", "WITHDRAW ", "DEPOSIT ", "FUND TRANSFER", "CHANGE PINCODE", "EXIT "};
    int pointer = 0;
    const char ENTER = 13;//ASCII code for ENTER Key
    char ch = ' ';
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while(true){
        system("cls");
        ShowConsoleCursor(false);
        SetColor(14); gotoxy(50,2);
        cout<< R"(
                         ____      _     _   _  _  __   ____  ____      _     ____
                        | __ )    / \   | \ | || |/ /  / ___||  _ \    / \   |  _ \
                        |  _ \   / _ \  |  \| || ' /  | |    | |_) |  / _ \  | |_) |
                        | |_) | / ___ \ | |\  || . \  | |___ |  _ <  / ___ \ |  __/
                        |____/ /_/   \_\|_| \_||_|\_\  \____||_| \_\/_/   \_\|_|

        )"<<endl;SetColor(15);
        gotoxy(40,10);cout<<">++('>";
        gotoxy(40,11);cout<<">++('>";
        gotoxy(40,12);cout<<">++('>";
        gotoxy(40,13);cout<<">++('>";
        gotoxy(40,14);cout<<">++('>";
        gotoxy(40,15);cout<<">++('>";
        gotoxy(28, 18);
        cout<<"USE UP OR DOWN ARROW KEYS TO NAVIGATE THROUGH MENU";

        for(int i=0; i<6; ++i){
            //This will highlight the choice in the menu
            if(i==pointer){
                gotoxy(48,10+i);
                SetConsoleTextAttribute(hConsole, 14);
                cout << Menu[i] << endl;
            }else{
                gotoxy(48,10+i);
                SetConsoleTextAttribute(hConsole, 15); // set color of the text to white
                cout << Menu[i] << endl;
            }
             SetConsoleTextAttribute(hConsole, 15);
        }
        //This will check the key stroke that is being pressed in keyboard
        while(true){
            if(GetAsyncKeyState(VK_UP) != 0){
                --pointer;
                if(pointer == -1){
                    pointer = 6;
                }
                break;
            }else if(GetAsyncKeyState(VK_DOWN) != 0){
                ++pointer;
                if(pointer == 7){
                    pointer = 0;
                }
                break;
            }else if(ch=getch() == ENTER){
                switch(pointer){
                    case 0: ShowConsoleCursor(true);
                            ATM.balance_inquiry();
                            ATM.save();
                            ATM.leave();
                            break;

                    case 1: ShowConsoleCursor(true);
                            ATM.withdraw();
                            ATM.save();
                            ATM.leave();
                            break;

                    case 2: ShowConsoleCursor(true);
                            ATM.deposit();
                            ATM.save();
                            ATM.leave();
                            break;

                    case 3: ShowConsoleCursor(true);
                            ATM.fund_transfer();
                            ATM.save();
                            ATM.leave();
                            break;
                    case 4: ShowConsoleCursor(true);
                            ATM.change_pincode();
                            ATM.save();
                            ATM.leave();
                            break;
                    case 5: ShowConsoleCursor(false);
                            exit(0);
                }
                break;
            }
        }

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
    string checker;
    int ch, amount;

    setFontStyle(23);

    while(!fp){
        gotoxy(41,6); SetColor(4); cout<<"PLEASE INSERT CARD"; SetColor(15);
        system("pause");
        fp.open("D:\\pinrecord.txt", ios::in);
    }

    getline(fp,checker);
    srand(time(NULL));
    accnum = (rand()%(999999)+10000);
    user.acc_number = accnum;
    gotoxy(45,6);
    if(checker.length()==0){
        gotoxy(41,6); SetColor(4); cout<<"YOUR ACCOUNT IS NOT REGISTERED"; SetColor(15);
        gotoxy(36,8); cout<<"[1] REGISTER";gotoxy(36,9);cout<<"[2] EXIT";
        gotoxy(36,10); cout<<"PLEASE SELECT YOUR NUMBER OF CHOICE: ";
        cin>>ch;

    switch (ch){
    case 1: system("cls");
            gotoxy(45,6); SetColor(2); cout<<"REGISTRATION"; SetColor(15);
            gotoxy(35,8); cout<<"ACCOUNT NUMBER: "<<user.acc_number;
            cin.ignore();
            gotoxy(35,9); cout<<"NAME: "; getline(cin, user.name);
            gotoxy(35,10); cout<<"BIRTHDAY: "; getline(cin, user.birthday);
            gotoxy(35,11); cout<<"CONTACT NUMBER: "; cin>>user.contact_num;
            gotoxy(35,12); cout<<"AMOUNT: ";cin>>amount;

            while(amount<500 || amount>20000){
            system("cls");
            gotoxy(15,8); SetColor(4); cout<<"!!ATM ONLY ACCEPTS MINIMUM OF 500 PESOS AND MAXIMUM OF 20,000 PESOS PER DEPOSIT!!"; SetColor(15);
            gotoxy(35,10); cout<<"Enter Initial Amount: "; cin>>amount;}
            user.balance = amount;
            gotoxy(35,13); cout<<"PIN: "; pincode();

            system("cls");
            gotoxy(34,6); SetColor(14); cout<<"WELCOME"; SetColor(15);
            gotoxy(40,10); cout<<"ACCOUNT IS NOW REGISTERED";
            gotoxy(40,11); cout<<"=========================";
            gotoxy(40,12); cout<<"ACCOUNT NUMBER: "<<user.acc_number;
            gotoxy(40,13); cout<<"NAME: "<<user.name;
            gotoxy(40,14); cout<<"BIRTHDAY: "<<user.birthday;
            gotoxy(40,15); cout<<"CONTACT NUMBER: "<<user.contact_num;
            gotoxy(40,16); cout.imbue(comma_locale);cout<<"ACCOUNT BALANCE: "<<setprecision(2)<<fixed<<user.balance<<" pesos";
            encrypt(); saving_pin(); add(user); save(); gotoxy(40,17); system("pause"); break;
    case 2: removecard(); exit(0); break; }
    }
    else{
        while(input!=pin){
        system("cls");
        gotoxy(50,6); SetColor(14); cout<<"LOG IN"; SetColor(15);
        gotoxy(40,8); cout<<"ENTER PIN: ";
        pincode();
        input=pin;
        retrieve_pin();
        decrypt();
        }
        gotoxy(40,10); cout<<"LOG IN SUCCESSFULLY!";
        gotoxy(40,11); system("pause");
    }
}

void atmClass::removecard(){
    fstream fp;

    do{ system("cls");
        gotoxy(41,6); SetColor(4); cout <<"PLEASE REMOVE CARD"; SetColor(15); system("pause");
        fp.open("D:\\pinrecord.txt",ios::out);
    }while(fp);
    SetColor(14); gotoxy(50,2);
        cout<< R"(
                         ____      _     _   _  _  __   ____  ____      _     ____
                        | __ )    / \   | \ | || |/ /  / ___||  _ \    / \   |  _ \
                        |  _ \   / _ \  |  \| || ' /  | |    | |_) |  / _ \  | |_) |
                        | |_) | / ___ \ | |\  || . \  | |___ |  _ <  / ___ \ |  __/
                        |____/ /_/   \_\|_| \_||_|\_\  \____||_| \_\/_/   \_\|_|

        )"<<endl;SetColor(15);
    gotoxy(24,10); cout <<"Thank you for banking with us! See you in future transactions!";
    exit(0);
}

void atmClass::saving_pin(){
    fstream fp;
    fp.open("D:\\pinrecord.txt",ios::out);
    fp<<accnum<<'\n';
    fp<<pin <<'\n';
    fp.close();
}

void atmClass::retrieve_pin(){
    fstream fp;
    fp.open("D:\\pinrecord.txt",ios::in);
    while(!fp.eof()){
        fp>>accnum;
        fp>>pin;
    }
    fp.close();
}

void atmClass::save(){
    p=n;
    fstream datalist, fp2;
    datalist.open("data.txt", ios::out);
    while (p!=NULL){
        datalist<<p->user.name<<'\n'<<p->user.acc_number<<'\n'<<p->user.balance<<'\n';
        p=p->next;
    }
    datalist.close();

    fp2.open("D:\\userdata.txt",ios::out);
    fp2<<user.name<<endl;
    fp2<<user.acc_number<<'\n';
    fp2<<user.birthday<<'\n';
    fp2<<user.contact_num<<'\n';
    fp2.close();
}

void atmClass::retrieve(){

    fstream datalist, fp2;

    datalist.open("data.txt",ios::in);
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
    fp2.open("D:\\userdata.txt",ios::in);
    while(!fp2.eof()){
    fp2>>user.name;
    fp2>>user.acc_number;
    fp2>>user.birthday;
    fp2>>user.contact_num;
    }
    fp2.close();
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
        SetColor(14); putchar('*'); SetColor(15);
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

void atmClass::balance_inquiry(){

    p=n;
    retrieve_pin();
    while(p!=NULL && accnum!=p->user.acc_number){
        p = p->next;
    }

    while(input!=pin){
        system("cls");
        gotoxy(40,10);cout<<"ENTER PIN: ";
        pincode();
        input=pin;
        retrieve_pin();
        decrypt();
    }
    system("cls");
    gotoxy(33,5); cout<<__DATE__; gotoxy(72,5); cout<<__TIME__;
    gotoxy(50,8); SetColor(14); cout<<"BALANCE INQUIRY"; SetColor(15);
    gotoxy(33,10); cout<<"ACCOUNT NUMBER: "<<p->user.acc_number;
    gotoxy(33,11); cout.imbue(comma_locale); cout<<"YOUR BALANCE IS: "<<setprecision(2)<<fixed<<p->user.balance<<" PESOS.";
    gotoxy(33,12); cout<<"THANK YOU FOR BANKING WITH US"; gotoxy(32,13); system("pause"); system("cls");
}

void atmClass::withdraw(){

    int withdraw, op;

    p=n;
    retrieve_pin();
    while(p!=NULL && accnum!=p->user.acc_number){
        p = p->next;
    }

    while(input!=pin){
        system("cls");
        gotoxy(40,10);cout<<"ENTER PIN: ";
        pincode();
        input=pin;
        retrieve_pin();
        decrypt();
    }

    system("cls");
    gotoxy(32,5); cout<<__DATE__; gotoxy(72,5); cout<<__TIME__;
    gotoxy(52,8); SetColor(14); cout<<"WITHDRAW"; SetColor(15);
    gotoxy(32,10); cout<<"PLEASE SELECT A VALUE: ";
    gotoxy(32,11); cout<<"[1] 500";
    gotoxy(32,12); cout<<"[2] 1,000";
    gotoxy(32,13); cout<<"[3] 2,000";
    gotoxy(32,14); cout<<"[4] 3,000";
    gotoxy(32,15); cout<<"[5] 5,000";
    gotoxy(32,16); cout<<"[6] 6,000";
    gotoxy(32,17); cout<<"[7] 8,000";
    gotoxy(32,18); cout<<"[8] 10,000";
    gotoxy(32,19); cout<<"[9] ENTER AMOUNT";
    gotoxy(32,20); cout<<"CHOICE: ";cin>>op;
    switch (op){
    case 1: gotoxy(32,22); cout<<"YOU SELECTED 500 PESOS"; withdraw = 500; break;
    case 2: gotoxy(32,22); cout<<"YOU SELECTED 1,000 PESOS"; withdraw = 1000; break;
    case 3: gotoxy(32,22); cout<<"YOU SELECTED 2,000 PESOS"; withdraw = 2000; break;
    case 4: gotoxy(32,22); cout<<"YOU SELECTED 3,000 PESOS"; withdraw = 3000; break;
    case 5: gotoxy(32,22); cout<<"YOU SELECTED 5,000 PESOS"; withdraw = 5000; break;
    case 6: gotoxy(32,22); cout<<"YOU SELECTED 6,000 PESOS"; withdraw = 6000; break;
    case 7: gotoxy(32,22); cout<<"YOU SELECTED 8,000 PESOS"; withdraw = 8000; break;
    case 8: gotoxy(32,22); cout<<"YOU SELECTED 10,000 PESOS"; withdraw = 10000; break;
    case 9: gotoxy(32,22); cout<<"ENTER AMOUNT: "; cin>>withdraw; break;
    }
    gotoxy(32,23); system("pause"); system("cls");
    while ((withdraw%100)!=0 || withdraw>(p->user.balance-500)){
        if(withdraw>(p->user.balance-500)){
        gotoxy(32,13); SetColor(4); cout<<"INSUFFICIENT BALANCE"; SetColor(15); gotoxy(32,14); system("pause"); system("cls");
        }
        gotoxy(22,10);SetColor(4);cout<<"NOTE: THIS MACHINE ONLY ACCEPTS & DISPENSE 1000, 500, AND 100 PESOS";SetColor(15);
        gotoxy(32,15); cout<<"ENTER AMOUNT: "; cin>>withdraw;
    }
    system("cls");
    p->user.balance = p->user.balance - withdraw;
    gotoxy(32,5); cout<<"PROCESSING "<<'\n'; loading_ani();
    gotoxy(32,7); cout<<"PLEASE ENTER ANY KEY"; getch();

    gotoxy(32,10); cout<<"YOU WITHDRAW "<<withdraw<<" PESOS.";
    cout.imbue(comma_locale); gotoxy(32,11); cout<<"YOUR CURRENT ACCOUNT BALANCE IS: "<<setprecision(2)<<fixed<<p->user.balance<<" PESOS."; gotoxy(32,12); system("pause");
    gotoxy(32,14); cout<<"THANK YOU FOR BANKING WITH US"; gotoxy(32,15); system("pause");
    system("cls");
}

void atmClass::deposit(){

    int deposit, ch, dep2;

    p=n;
    retrieve_pin();
    while(p!=NULL && accnum!=p->user.acc_number){
        p = p->next;
    }

    while(input!=pin){
        system("cls");
        gotoxy(40,10);cout<<"ENTER PIN: ";
        pincode();
        input=pin;
        retrieve_pin();
        decrypt();
    }

    system("cls");
    gotoxy(32,5); cout<<__DATE__; gotoxy(72,5); cout<<__TIME__;
    while (deposit%100!=0 || deposit>=20000){
        gotoxy(52,8); SetColor(14); cout<<"DEPOSIT"; SetColor(15);
        gotoxy(32,10); cout<<"ENTER AMOUNT: ";
        cin>>deposit;

    if((deposit%100)!=0){
        gotoxy(25,12);SetColor(4);cout<<"NOTE: THIS MACHINE ONLY ACCEPTS & DISPENSE 1000, 500, AND 100 PESOS";SetColor(15);gotoxy(22,13);system("pause");system("cls");
        gotoxy(22,14);system("pause");system("cls");
        }
    if(deposit>20000){
        gotoxy(32,12);SetColor(4);cout<<"THIS ATM DOES NOT ACCEPT LARGE AMOUNTS OF CASH";SetColor(15);
        gotoxy(22,14);system("pause");system("cls");
        }
    }
    cout.imbue(comma_locale);gotoxy(32,12);cout<<"YOU ENTERED: "<<setprecision(2)<<fixed<<deposit<<" PESOS.";
    dep2 = deposit;
    gotoxy(32,13); cout<<"IS THE AMOUNT CORRECT? [Press 1 to confirm] "; cin>>ch;
    if(ch==1){
        cout.imbue(comma_locale);gotoxy(32,16);cout<<"YOU DEPOSIT "<<setprecision(2)<<fixed<<deposit<<" PESOS."; gotoxy(32,17);system("pause"); system("cls");
    }
    p->user.balance += deposit;
    gotoxy(32,5); cout<<"PROCESSING "<<'\n'; loading_ani();
    gotoxy(32,7); cout<<"PLEASE ENTER ANY KEY"; getch();
    cout.imbue(comma_locale); gotoxy(32,9); cout<<"YOUR CURRENT BALANCE IS: "<<setprecision(2)<<fixed<<p->user.balance<<" PESOS.";
    gotoxy(32,12); cout<<"THANK YOU FOR BANKING WITH US"; gotoxy(32,13); system("pause"); system("cls");
}

void atmClass::fund_transfer(){

    int fund, total;

    p=n;
    retrieve_pin();
    while(p!=NULL && accnum!=p->user.acc_number){
        p = p->next;
    }

    while(input!=pin){
        system("cls");
        gotoxy(40,10); cout<<"ENTER PIN: ";
        pincode();
        input=pin;
        retrieve_pin();
        decrypt();
    }

    system("cls");
    gotoxy(32,5); cout<<__DATE__; gotoxy(72,5); cout<<__TIME__;
    gotoxy(52,8); SetColor(14); cout<<"FUND TRANSFER"; SetColor(15);

    gotoxy(32,10); cout<<"Enter User Account Number: "; cin>>accnum;
    system("cls");
    gotoxy(32,5); cout<<"PROCESSING "<<'\n'; loading_ani();
    gotoxy(32,7); cout<<"PLEASE ENTER ANY KEY"; getch();
    locate();

    if (receiver==NULL){
        gotoxy(32,8); cout<<"USER ACCOUNT NOT FOUND."; gotoxy(32,9); system("pause"); system("cls");
    }

    else{
        gotoxy(32,9);  cout<<"USER INFO";
        gotoxy(32,10);  cout<<"NAME: "<<receiver->user.name;
        gotoxy(32,11);  cout<<"ACCOUNT NUMBER: "<<receiver->user.acc_number;}

    while((fund%100)!=0 || fund>(p->user.balance-500)){
        gotoxy(32,14); cout<<"Enter amount: "; cin>>fund;
        if((fund%100)!=0){
            gotoxy(32,16); cout<<"NOTE: THIS MACHINE ONLY ACCEPTS & DISPENSE 1000, 500, AND 100 PESOS"; gotoxy(32,17); system("cls");
        }
        else if(fund>(p->user.balance-500)){
            gotoxy(32,16); cout<<"INSUFFICIENT BALANCE"; gotoxy(32,17); system("pause"); system("cls");
        }
    }
    gotoxy(32,17); cout<<"YOU ARE TRANSFERING "<<fund<<" PESOS TO "<<receiver->user.name;
    gotoxy(32,18); cout.imbue(comma_locale); cout<<"WITH AN ACCOUNT NUMBER OF "<<receiver->user.acc_number;
    gotoxy(32,19); cout<<"DO YOU WANT TO PROCEED THE TRANSACTION?"; getch();
    gotoxy(32,20); cout<<"PLEASE ENTER ANY KEY TO PROCEED"; getch();
    p->user.balance -= fund;
    receiver->user.balance += fund;
    gotoxy(32,21); cout<<"=================================================";
    gotoxy(32,22); cout<<"YOU SUCCESSFULLY TRANSFERED "<<fund<<" PESOS TO "<<receiver->user.acc_number;
    gotoxy(32,23); cout.imbue(comma_locale); cout<<"YOUR CURRENT BALANCE IS: "<<setprecision(2)<<fixed<<p->user.balance<<" PESOS.";
    gotoxy(32,24); cout<<"THANK YOU FOR BANKING WITH US"; gotoxy(32,25); system("pause");
    system("cls");
}

void atmClass::change_pincode(){

    string newpin, re_newpin;

    p=n;
    retrieve_pin();
    while(p!=NULL && accnum!=p->user.acc_number){
        p = p->next;
    }

    while(input!=pin){
    system("cls");
    gotoxy(40,10); cout<<"ENTER PIN: ";
    pincode();
    input=pin;
    retrieve_pin();
    decrypt();
    }

    system("cls");
    gotoxy(32,5); cout<<__DATE__; gotoxy(72,5); cout<<__TIME__;
    gotoxy(52,8); SetColor(14); cout<<"CHANGE PIN"; SetColor(15);

    gotoxy(32,10); cout<<"NAME: "<<p->user.name;
    gotoxy(32,11); cout<<"ACCOUNT NUMBER: "<<p->user.acc_number;

    while(input!=pin){
    system("cls");
    gotoxy(32,10); cout<<"ENTER PIN: ";
    pincode();
    input=pin;
    retrieve_pin();
    decrypt();
    }
    gotoxy(32,12); cout<<"ENTER NEW PIN: "; pincode();
    newpin = pin; retrieve_pin(); decrypt();
    while(newpin==pin){
        gotoxy(32,15); SetColor(4); cout<<"YOUR NEW PIN CANNOT BE THE SAME AS YOUR CURRENT PIN"; SetColor(15); gotoxy(32,16); system("pause"); system("cls");
        gotoxy(32,12); cout<<"ENTER NEW PIN: "; pincode(); newpin = pin; retrieve_pin(); decrypt();
    }
    gotoxy(32,13); cout<<"RE-ENTER PIN: "; pincode(); re_newpin = pin; decrypt();
    while(re_newpin!=newpin){
        gotoxy(32,15); SetColor(4); cout<<"ERROR: PIN DOES NOT MATCH"; SetColor(15); gotoxy(32,16); system("pause"); system("cls");
        gotoxy(32,13); cout<<"RE-ENTER PIN: "; pincode(); re_newpin = pin; decrypt();
    }
    encrypt();
    if(newpin==re_newpin){
    system("cls");
    gotoxy(32,5); cout<<"PROCESSING "<<'\n'; loading_ani();
    gotoxy(32,8); cout<<"PLEASE ENTER ANY KEY"; getch();
    gotoxy(32,9); cout<<"PIN SUCCESSFULLY CHANGE!";
    gotoxy(32,10); cout<<"ACCOUNT INFORMATION";
    gotoxy(32,11); cout<<"=========================";
    gotoxy(32,17); cout<<"THANK YOU FOR BANKING WITH US"; gotoxy(32,18); system("pause");
    encrypt(); saving_pin();
    system("cls");
    }
}

void atmClass::locate(){

    receiver = n;
    while(receiver!=NULL && accnum!=receiver->user.acc_number){
        receiver = receiver->next;
    }
}

void atmClass::leave(){

    char ans;
    SetColor(14); gotoxy(50,2);
        cout<< R"(
                         ____      _     _   _  _  __   ____  ____      _     ____
                        | __ )    / \   | \ | || |/ /  / ___||  _ \    / \   |  _ \
                        |  _ \   / _ \  |  \| || ' /  | |    | |_) |  / _ \  | |_) |
                        | |_) | / ___ \ | |\  || . \  | |___ |  _ <  / ___ \ |  __/
                        |____/ /_/   \_\|_| \_||_|\_\  \____||_| \_\/_/   \_\|_|

    )"<<endl;SetColor(15);
    gotoxy(32,10); cout<<"DO YOU WANT TO DO ANOTHER TRANSACTION?";
    gotoxy(32,11); cout<<"IF YES PLEASE ENTER [Y] IF NO PRESS ANY KEY [N]";
    gotoxy(32,12); cout<<"Answer: "; cin>>ans;
    gotoxy(32,13); system("pause");
    if(ans=='Y' || ans=='y'){
        return;
    }
    else {
        removecard();exit(0);
    }
}

void gotoxy(int x,int y){
    COORD coord = {0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void SetColor(int ForgC){
  WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

void setFontStyle(int FontSize){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = FontSize;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Courier New"); // font style
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void loading_ani(){
    gotoxy(32,6);
    SetColor(14);
    for(int i;i<20;i++){
        cout<<"-";
        for(long j=0;j<4000000;j++){}
    }
    SetColor(15);
}

