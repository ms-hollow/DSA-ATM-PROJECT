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
void SetColor(int ForgC);
void gotoxy(int x,int y);
void setFontStyle(int FontSize);
void ShowConsoleCursor(bool showFlag);


int main(){

    atmClass ATM;
    ATM.makenull();
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
                            //system("pause");
                            break;

                    case 1: ShowConsoleCursor(true);
                            ATM.withdraw();
                            ATM.save();
                            //system("pause");
                            break;

                    case 2: ShowConsoleCursor(true);
                            ATM.deposit();
                            ATM.save();
                            //system("pause");
                            break;

                    case 3: ShowConsoleCursor(true);
                            ATM.fund_transfer();
                            ATM.save();
                            //system("pause");
                            break;
                    case 4: ShowConsoleCursor(true);
                            ATM.change_pincode();
                            ATM.save();
                            //system("pause");
                            break;
                    case 5: ShowConsoleCursor(false);
                            cout<<"EXIT\n";
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
    string input, checker;
    int ch, amount;
    setFontStyle(23);
    do{
        system("cls");
        cout <<"Please insert card...\n";
        fp.open("G:\\pinrecord.txt", ios::in);
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
            gotoxy(40,6); cout<<"ACCOUNT IS NOW REGISTERED";
            gotoxy(40,7); cout<<"=========================\n";
            gotoxy(40,8); cout<<"ACCOUNT NUMBER: "<<user.acc_number;
            gotoxy(40,9); cout<<"NAME: "<<user.name;
            gotoxy(40,10); cout<<"BIRTHDAY: "<<user.birthday;
            gotoxy(40,11); cout<<"CONTACT NUMBER: "<<user.contact_num;
            gotoxy(40,12); cout.imbue(comma_locale);cout<<"ACCOUNT BALANCE: "<<setprecision(2)<<fixed<<user.balance<<" pesos";
            encrypt(); saving_pin(); add(user); save(); system("pause"); break;
    case 2: removecard(); exit(0); break; }
    }
    else{
        while(input!=pin){
        system("cls");
        SetColor(14); gotoxy(50,2);
        cout<< R"(

        )"<<endl;SetColor(15);
        gotoxy(50,6); SetColor(2); cout<<"LOG IN"; SetColor(15);
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
        cout <<"Please remove card...";
        fp.open("G:\\pinrecord.txt",ios::out);
    }while(fp);
    cout <<"Thank you for banking with MYLUGI BANK ";
    exit(0);
}

void atmClass::saving_pin(){
    fstream fp, fp2;
    fp.open("G:\\pinrecord.txt",ios::out);
    fp<<accnum<<'\n';
    fp<<pin <<'\n';
    fp.close();

    fp2.open("G:\\userdata.txt",ios::out);
    fp2<<user.name<<endl;
    fp2<<user.acc_number<<'\n';
    fp2<<user.birthday<<'\n';
    fp2<<user.contact_num<<'\n';
    cout<<"\nACCOUNT SUCCESSFULLY SAVED!";
    fp2.close();
}

void atmClass::retrieve_pin(){
    fstream fp, fp2;
    fp.open("G:\\pinrecord.txt",ios::in);
    while(!fp.eof()){
        fp>>accnum;
        fp>>pin;
    }
    fp.close();

    fp2.open("G:\\userdata.txt",ios::in);
    while(!fp2.eof()){
    fp2>>user.name;
    fp2>>user.acc_number;
    fp2>>user.birthday;
    fp2>>user.contact_num;
    }
    fp2.close();
}

void atmClass::save(){
    p=n;
    fstream datalist;

    datalist.open("data.txt", ios::out);
    while (p!=NULL){
        datalist<<p->user.name<<'\n'<<p->user.acc_number<<'\n'<<p->user.balance<<'\n';
        p=p->next;
    }
    datalist.close();
}

void atmClass::retrieve(){

    fstream datalist;

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
        SetColor(2); putchar('*'); SetColor(15);
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

    char ans;

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
    gotoxy(45,8); SetColor(2); cout<<"BALANCE INQUIRY"; SetColor(15);
    gotoxy(33,10); cout<<"ACCOUNT NUMBER: "<<p->user.acc_number;
    gotoxy(33,11); cout.imbue(comma_locale); cout<<"YOUR BALANCE IS: "<<setprecision(2)<<fixed<<p->user.balance;
    gotoxy(33,13); cout<<"DO YOU WANT TO DO ANOTHER TRANSACTION?";
    gotoxy(33,14); cout<<"IF YES PLEASE ENTER [Y] IF NO PRESS ANY KEY [N]";
    gotoxy(33,15); cout<<"Answer: "; cin>>ans;
    gotoxy(33,16); system("pause");
    if(ans=='Y' || ans=='y'){
    MENU[i];
    }
    else {
        save();
        system("cls");
        gotoxy(45,10); cout<<"THANK YOU FOR BANKING WITH US!";
        gotoxy(45,11); system("pause");
        exit(0);
    }
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
        cout<<"\nENTER PIN: ";
        pincode();
        input=pin;
        retrieve_pin();
        decrypt();
    }

    system("cls");

    gotoxy(32,5); cout<<__DATE__; gotoxy(72,5); cout<<__TIME__;
    gotoxy(45,8); SetColor(2); cout<<"WITHDRAW"; SetColor(15);
    gotoxy(32,10); cout<<"\nPLEASE SELECT AN AMOUNT: ";
    cout<<"1. 500";
    cout<<"2. 1,000";
    cout<<"3. 2,000";
    cout<<"4. 3,000";
    cout<<"5. 5,000";
    cout<<"6. 6,000";
    cout<<"7. 8,000";
    cout<<"8. 10,000";
    cout<<"9. ENTER AMOUNT";
    cout<<"CHOICE: ";cin>>op;

    switch (op)
    {
    case 1: cout<<"\nYou have selected 500"; withdraw = 500; break;
    case 2: cout<<"\nYou have selected 1,000"; withdraw = 1000; break;
    case 3: cout<<"\nYou have selected 2,000"; withdraw = 2000; break;
    case 4: cout<<"\nYou have selected 3,000"; withdraw = 3000; break;
    case 5: cout<<"\nYou have selected 5,000"; withdraw = 5000; break;
    case 6: cout<<"\nYou have selected 6,000"; withdraw = 6000; break;
    case 7: cout<<"\nYou have selected 8,000"; withdraw = 8000; break;
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
            cout<<"Amount should not exist from 50,000";
        }
    }
    p->user.balance = p->user.balance - withdraw;

    cout.imbue(comma_locale); cout<<"\nYOUR ACCOUNT BALANCE IS:  "<<setprecision(2)<<fixed<<p->user.balance;
    system("pause");
    cout<<"\nTHANK YOU FOR BANKING WITH US";
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
        cout.imbue(comma_locale); cout<<"\nYou have entered: "<<setprecision(2)<<fixed<<deposit;
        dep2 = deposit;
        cout<<"\nIs the amount correct? [Press 1 to confirm]";
        cout<<"\nInsert more cash? [Press 2 to confirm]\n";
        cin>>ch;
        if(ch==1){
            cout.imbue(comma_locale);cout<<"\nYou have deposit "<<setprecision(2)<<fixed<<deposit<<" pesos.";
        } else{
            cout<<"\nPlease enter amount: ";
            cin>>deposit;
            deposit += dep2;
            cout.imbue(comma_locale); cout<<"\nThe total amount you entered is "<<setprecision(2)<<fixed<<" pesos.";
        }
    }
    p->user.balance += deposit;
    cout.imbue(comma_locale); cout<<"\nYour Current Balance: "<<setprecision(2)<<fixed<<p->user.balance;
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
        cout<<"\nENTER PIN: ";
        pincode();
        input=pin;
        retrieve_pin();
        decrypt();
    }

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

    string newpin;

    p=n;
    retrieve_pin();
    while(p!=NULL && accnum!=p->user.acc_number){
        p = p->next;
    }

    while(input!=pin){
    system("cls");
    cout<<"\nENTER PIN: ";
    pincode();
    input=pin;
    retrieve_pin();
    decrypt();
    }

    cout<<"\nNAME: "<<p->user.name;
    cout<<"\nACCOUNT NUMBER: "<<p->user.acc_number;

    cout<<"\nENTER NEW PIN: "; pincode();
    newpin = pin;
    cout<<"\nRE-ENTER PIN: "; pincode();
    retrieve_pin(); decrypt();
    while(newpin!=pin){
        system("cls");
        cout<<"\nPIN DOES NOT MATCH";
        cout<<"\nRE-ENTER PIN: "; pincode();
    }
    encrypt(); saving_pin();
    cout<<"\nPIN SUCCESSFULLY CHANGE!";
    system("pause");
}

void atmClass::locate(){

    receiver = n;
    while(receiver!=NULL && accnum!=receiver->user.acc_number){
        receiver = receiver->next;
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
