#include <windows.h>
#include <iomanip>
#include <iostream>
#include <ctime>
#include "airport_f.h"

using namespace std;

const char *FileFlight="flight.dat";
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
static Flight F;
static Plane P;

int AirportCodeCheck(string a) {
    ifstream ifn("airport_code.txt");
    bool is_found = false;

    string str;
    while(getline(ifn,str))
    {
        if(str.find(a) != std::string::npos)
        {
            is_found = true;
            break;
        }
    }
    ifn.close();
    return is_found;
}

int TimeCheck(int a, int b, int c) {
    while (a < b || a > c) {
        printf("������������ ��������. ��������� ����: ");
        cin>>a;
    }
    return a;
}


int lastFlight(){
    int n=0;
    ifstream fin(FileFlight,ios::binary);
    if(fin.fail()){
        cerr<<"���� �� ������";
        exit(1);
    }
    while(!fin.read((char*)&F, sizeof(Flight)).eof()){
        n=F.getFlightKey();};
    fin.close();
    return n;
}

string LandingPrint(Flight F,int n){
    string b;
    for (int i = 0; i<n; i++) {
        b+=F.Landing[i];b+=" ";
    }
    return b;
}

Flight& findFlight(int k){
    ifstream fin(FileFlight,ios::binary);
    fin.seekg((k-1)*sizeof(Flight));
    fin.read((char*)&F,sizeof(Flight));
    return F;
}

Flight& PlacesSet(Flight A, int k){
    ofstream fin(FileFlight,ios::in | ios::out | ios::binary);
    fin.seekp((k-1)*sizeof(Flight));
    fin.write((char*)&A,sizeof(Flight));
    fin.close();
}

int get_variant(int count) {
    int variant;
    char s[100]; // ������ ��� ���������� �������� ������
    scanf("%s", s); // ��������� ������

    // ���� ���� �����������, �������� �� ���� � ������ ��������� ���
    while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count) {
        printf("��� ���������� ������. ���������� �����: "); // ������� ��������� �� ������
        scanf("%s", s); // ��������� ������ ��������
    }

    return variant;
}

time_t do_time (int hour, int minute, int month, int day, int year)
{
    tm tmp = tm();
    tmp.tm_hour = hour;
    tmp.tm_min = minute;
    tmp.tm_mday = day;
    tmp.tm_mon = month - 1;
    tmp.tm_year = year - 1900;
    return mktime(&tmp);
}

int Editor(){
    Flight F;
    spisFlight();
    int kp;
    cout<<"������� ����� �����, ������� ����� ���������������: ";int k;cin>>k;
    F=findFlight(k);
    cout<<F;
    do {
        cout<<"1. ��� �����"<<endl;
        cout<<"2. �������"<<endl;
        cout<<"3. �������"<<endl;
        cout<<"4. ����� ������"<<endl;
        cout<<"5. ����� �����������"<<endl;
        cout<<"6. ���-�� ����"<<endl;
        cout<<"7. ����"<<endl;
        cout<<"8. ������"<<endl;

        cout<<"������� ����� ������, ������� ����� ���������������: ";

        kp = get_variant(8);

        switch (kp) {
        F=findFlight(k);
        case 1:
            cout<<"����� �����: ";cin>>F.NomerFlight;
            break;
        case 2:{
            int input;
            RaspisaniePlaneAdd(F.getDate());
            //  strcpy(F.Plane,P.getName());
            cout<<"��� ��������, ������������ ����: ";int h;cin>>h;
            P=findPlane(h);
            F.PlaneKey = P.getPlaneKey();
            cout<<"�� "<<P.getName()<<" �������� "<<P.getNumberOfSeats()<<" ����. ������� '1', ��� �������������, ��� '0' ��� ��������� ���-�� ����: ";
            cin>>input;
            if(input == 1){
                F.Places=P.getNumberOfSeats();
            } else {
                cout<<"������� ���-�� ���� �� �����: "; int col; cin>>col;
                while (col < 1 || col > P.getNumberOfSeats()) {
                    printf("������������ ��������. ��������� ����: ");
                    cin>>col;
                }
                F.Places=col;
            }
            break;
        }
        case 3:
            cout<<"������� ���������� ������������� ������� � ������ ��������� ������: ";int n;cin>>n;


            while (n < 1 || n > 5) {
                printf("���������� ������� �� ����� ���� ������ 5. ��������� ����: ");
                cin>>n;
            }

            F.LandingCount = n;

            for (int i = 0; i < n; i++) {
                cout << "[" << i + 1 << "]" << ": ";
                string a; cin>>a;
                while(!AirportCodeCheck(a)){
                    cout<<"��� ��������� �� ������. ��������� ����: ";cin>>a;
                }
                strcpy (F.Landing[i], a.c_str());
            }
            break;
        case 4:{
            int input;
            int sec=F.ArrivalTime-F.DepartureTime;
            cout<<"����� ������ ";int dd,mm,yy,hh,min;
            cout<<endl<<"����: "; cin>>dd; dd=TimeCheck(dd, 1, 31);
            cout<<"�����: "; cin>>mm;  mm=TimeCheck(mm, 1, 12);
            cout<<"���: "; cin>>yy;  yy=TimeCheck(yy, 2020, 2025);
            cout<<"�����: "; cin>>hh; hh=TimeCheck(hh, 0, 23);
            cout<<"�����: "; cin>>min; min=TimeCheck(min, 0, 59);
            F.DepartureTime=do_time(hh,min,mm,dd,yy);

            cout<<"������������ ������. �����: "<<sec/3600<<" �����: "<<(sec/60)%60<<endl;
            cout<<"�� ������������� ������������ ������?"<<" ������� '1', ��� �������������, ��� '0', ����� ������ ����� ������������ ������: ";
            cin>>input;
            if(input == 1){
                cout<<"������� ���������"<<endl;
                F.ArrivalTime = F.DepartureTime+sec;
            } else {
                cout<<endl<<"����� � ������: ";int hours;cin>>hours;
                cout<<"����� � �����: ";int minute;cin>>minute;
                sec = (minute*60)+(hours*3600);
                F.ArrivalTime = F.DepartureTime+sec;
            }
            break;
        }

        case 5:{
            cout<<"������������ ������ ";
            cout<<endl<<"����� � ������: ";int hours;cin>>hours;
            cout<<"����� � �����: ";int minute;cin>>minute;
            int sec = (minute*60)+(hours*3600);
            F.ArrivalTime = F.DepartureTime+sec;
            break;
        }

        case 6:
            int input;
            cout<<"�� "<<P.getName()<<" �������� "<<P.getNumberOfSeats()<<" ����. ������� '1', ��� �������������, ��� '0' ��� ��������� ���-�� ����: ";
            cin>>input;
            if(input == 1){
                F.Places=P.getNumberOfSeats();
            } else {
                cout<<"������� ���-�� ���� �� �����: "; int col; cin>>col;
                while (col < 1 || col > P.getNumberOfSeats()) {
                    printf("������������ ��������. ��������� ����: ");
                    cin>>col;
                }
                F.Places=col;
            }
            break;


        case 7:
            cout<<"���� �� �����: ";cin>>F.Price;
            break;

        }
        if(kp!=8){
            cout<<left<<setw(9)<<"|� �����"<<setw(11)<<"|��� �����"<<setw(17)<<"|�������"<<setw(21)<<"|�������"<<setw(18)<<"|����� ������"<<setw(18)<<"|����� �����������"<<setw(13)<<"|���-�� ����"<<"|����    |"<<endl;
            cout<<F;
            int input;
            cout<<"�� ������������� ������?"<<" ������� '1', ��� �������������, ��� '0', ����� ������ �������: ";
            cin>>input;
            if(input == 1){
                cout<<"������� ��������"<<endl;
                PlacesSet(F,k);
            }
            else{
                break;
            }
            break;
        }
        if (kp != 8)
            system("pause");
    } while (kp != 8);

}

int CheckFree(){
    ifstream fin(FileFlight,ios::binary);
    if(fin.fail()){
        cerr<<"���� �� ������.";   exit(3); }
    cout<<endl<<left<<setw(9)<<"|� �����"<<setw(11)<<"|��� �����"<<setw(24)<<"|��������� ����  |"<<endl;
    while(!fin.read(reinterpret_cast<char*>(&F),sizeof(Flight)).eof())
    {
        cout<<left<<"|"<<setw(8)<<F.getFlightKey()<<"|"<<setw(10)<<F.getNomerFlight()<<"|"<<setw(16)<<
              CheckTicketsFree(F); cout<<"|"<<endl;
    }
    fin.close();
    return 0;
}

istream &operator>>(istream &in, Flight &F){
    int a=lastFlight();F.FlightKey=a+1;
    int input;
    cout<<"��� �����: ";in>>F.NomerFlight;
    cout<<"������� ���������� ������������� ������� � ������ ��������� ������: ";int n;cin>>n;


    while (n < 1 || n > 5) {
        printf("���������� ������� �� ����� ���� ������ 5. ��������� ����: ");
        cin>>n;
    }

    F.LandingCount = n;

    for (int i = 0; i < n; i++) {
        cout << "[" << i + 1 << "]" << ": ";
        string a; cin>>a;
        while(!AirportCodeCheck(a)){
            cout<<"��� ��������� �� ������. ��������� ����: ";cin>>a;
        }
        strcpy (F.Landing[i], a.c_str());
    }


    cout<<"����� ������ ";int dd,mm,yy,hh,min;
    cout<<endl<<"����: "; cin>>dd; dd=TimeCheck(dd, 1, 31);
    cout<<"�����: "; cin>>mm;  mm=TimeCheck(mm, 1, 12);
    cout<<"���: "; cin>>yy;  yy=TimeCheck(yy, 2020, 2025);
    cout<<"�����: "; cin>>hh; hh=TimeCheck(hh, 0, 23);
    cout<<"�����: "; cin>>min; min=TimeCheck(min, 0, 59);
    F.DepartureTime=do_time(hh,min,mm,dd,yy);

    cout<<"������������ ������ ";
    cout<<endl<<"����� � ������: ";int hours;cin>>hours;
    cout<<"����� � �����: ";int minute;cin>>minute;
    int sec = (minute*60)+(hours*3600);
    F.ArrivalTime = F.DepartureTime+sec;
    cout<<"���� �� �����: ";in>>F.Price;

    //    cout<<endl; spisPlane();
    //    cout<<"��� ��������, ������������ ����: ";int h;cin>>h;
    //    P=findPlane(h);
    RaspisaniePlaneAdd(F.DepartureTime);
    //  strcpy(F.Plane,P.getName());
    cout<<"��� ��������, ������������ ����: ";int h;cin>>h;
    P=findPlane(h);
    F.PlaneKey = P.getPlaneKey();
    cout<<"�� "<<P.getName()<<" �������� "<<P.getNumberOfSeats()<<" ����. ������� '1', ��� �������������, ��� '0' ��� ��������� ���-�� ����: ";
    cin>>input;
    if(input == 1){
        F.Places=P.getNumberOfSeats();
    } else {
        cout<<"������� ���-�� ���� �� �����: "; int col; cin>>col;
        while (col < 1 || col > P.getNumberOfSeats()) {
            printf("������������ ��������. ��������� ����: ");
            cin>>col;
        }
        F.Places=col;
    }

    cout<<left<<setw(9)<<"|� �����"<<setw(11)<<"|��� �����"<<setw(17)<<"|�������"<<setw(21)<<"|�������"<<setw(18)<<"|����� ������"<<setw(18)<<"|����� �����������"<<setw(13)<<"|���-�� ����"<<"|����    |"<<endl;
    cout<<F;

    cout<<"�� ������������� ������?"<<" ������� '1', ��� �������������, ��� '0', ����� ������ �������: ";
    cin>>input;
    if(input == 1){
        cout<<"������� ���������"<<endl;
        return in;
    } else {
        cin>>F;
    }
}

int spisFlight(){
    ifstream fin(FileFlight,ios::binary|ios::in|ios::ate);
    double file_size = fin.tellg();
    if (file_size == 0 || file_size==-1){
        cout<<"���� ������ ��� �� ������. �������� ���������� � ������� ������ 10 �������� ����."<<endl; fin.close();}
    else{
        ifstream fin(FileFlight,ios::binary);
        cout<<left<<setw(9)<<"|� �����"<<setw(11)<<"|��� �����"<<setw(17)<<"|�������"<<setw(21)<<"|�������"<<setw(18)<<"|����� ������"<<setw(18)<<"|����� �����������"<<setw(13)<<"|���-�� ����"<<"|����    |"<<endl;
        while(!fin.read(reinterpret_cast<char*>(&F),sizeof(Flight)).eof())
            cout<<F;
        fin.close();
        return 0;
    }
}

int bigCostFlight(){
    ifstream fin(FileFlight,ios::binary|ios::in|ios::ate);
    double file_size = fin.tellg();
    if (file_size == 0 || file_size==-1){
        cout<<"���� ������ ��� �� ������. �������� ���������� � ������� ������ 10 �������� ����."<<endl; fin.close();}
    else{
        int max=0; Flight D;
        ifstream fin(FileFlight,ios::binary);
        cout<<left<<setw(9)<<"|� �����"<<setw(11)<<"|��� �����"<<setw(17)<<"|�������"<<setw(21)<<"|�������"<<setw(18)<<"|����� ������"<<setw(18)<<"|����� �����������"<<setw(13)<<"|���-�� ����"<<"|����    |"<<endl;
        while(!fin.read(reinterpret_cast<char*>(&F),sizeof(Flight)).eof())
            if (F.getPrice() > max){max = F.getPrice();D=findFlight(F.getFlightKey());};
        cout<<D;
        fin.close();
    }
    return 0;
}


int PlaneFindFlight(Plane &P){
    cout<<left<<setw(9)<<"|� �����"<<setw(11)<<"|� �����"<<setw(17)<<"|�������"<<setw(21)<<"|�������"<<setw(18)<<"|����� ������"<<setw(18)<<"|����� �����������"<<setw(13)<<"|���-�� ����"<<"|����    |"<<endl;
    ifstream fin(FileFlight,ios::binary);
    while(!fin.read(reinterpret_cast<char*>(&F),sizeof(Flight)).eof()){
        if(F.getPlaneKey()==P.getPlaneKey())
            cout<<F;
    }
    fin.close();
    return 0;
}

ostream& operator<<(ostream&out, tm* p_tm){
    //return out<<put_time(p_tm, "%d.%m.%Y   %H:%M");
    return out<<right<<setfill ('0')<<setw(2)<<p_tm->tm_mday<<"."<<setw(2)<<p_tm->tm_mon+1<<"."<<p_tm->tm_year+1900<<"  "<<setw(2)<<p_tm->tm_hour<<setw(1)<<":"<<setw(2)<<p_tm->tm_min<<left<<setfill (' ');
}

int PlaneFindTimeFlightAdd(Plane &P,time_t date){
    int a=1;
    Flight F;
    ifstream fin(FileFlight,ios::binary);
    while(!fin.read(reinterpret_cast<char*>(&F),sizeof(Flight)).eof()){
        if(F.getPlaneKey()==P.getPlaneKey()){
            tm* p_tm=localtime(&F.getDate());
            time_t temp; temp = F.getArrDate()+(difftime(F.getArrDate(),F.getDate()));

            if (temp > date && F.getDate() < date)
            {
                cout<<"|�������� �������� � ���� �����:                                   |"<<endl;
                SetConsoleTextAttribute(console, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); cout<<"|"<<p_tm<<" � "; p_tm=localtime(&temp); cout<<p_tm;  cout << " - ����������� �������       |" << endl;
                SetConsoleTextAttribute(console, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
            }
        }
    }
    fin.close();
    return a;
}

int PlaneFindTimeFlight(Plane &P){
    int a=1;
    ifstream fin(FileFlight,ios::binary);
    while(!fin.read(reinterpret_cast<char*>(&F),sizeof(Flight)).eof()){
        if(F.getPlaneKey()==P.getPlaneKey()){
            tm* p_tm=localtime(&F.getDate());
            cout<<"|"<<p_tm<<" � "; p_tm=localtime(&F.getArrDate()); cout<<p_tm<<"                             |"<<endl;
        }
    }
    fin.close();
    return a;
}

int OneLanding(){
    ifstream fin(FileFlight,ios::binary);
    cout<<left<<setw(9)<<"|� �����"<<setw(11)<<"|� �����"<<setw(17)<<"|�������"<<setw(21)<<"|�������"<<setw(18)<<"|����� ������"<<setw(18)<<"|����� �����������"<<setw(13)<<"|���-�� ����"<<"|����    |"<<endl;
    while(!fin.read(reinterpret_cast<char*>(&F),sizeof(Flight)).eof()){
        if(F.getLandingCount()==1){
                        cout<<F;
        }
    }
    fin.close();
}

ostream& operator<<(ostream &out, Flight &F){
    tm* p_tm=localtime(&F.DepartureTime);
    P=findPlane(F.getPlaneKey());
    out<<left<<"|"<<setw(8)<<F.FlightKey<<"|"<<setw(10)<<F.NomerFlight<<"|"<<setw(16)<<P.getName()<<"|"<<setw(20);cout<<LandingPrint(F,F.LandingCount);cout<<"|"<<p_tm;p_tm=localtime(&F.ArrivalTime);cout<<"|"<<p_tm;cout<<"|"<<setw(12)<<F.Places<<"|"<<setw(8)<<F.Price<<"|"<<endl;
}

int emptyFlight(){
    ifstream fin(FileFlight,ios::binary);
    if(fin.fail()){
        cerr<<"���� �� ������.";   exit(3); }
        cout<<left<<setw(9)<<"|� �����"<<setw(11)<<"|��� �����"<<setw(17)<<"|�������"<<setw(21)<<"|�������"<<setw(18)<<"|����� ������"<<setw(18)<<"|����� �����������"<<setw(13)<<"|���-�� ����"<<"|����    |"<<endl;
    while(!fin.read(reinterpret_cast<char*>(&F),sizeof(Flight)).eof()){
        double a = CheckTicketsFree(F);
        if(((a/F.getPlaces())*100)>50){
            cout<<F;
        }
    }
    cout<<"�� ����� ����� �������� �������, ��� ������� 0 ��� ������: ";int atr;cin>>atr;
    if(atr!=0){
    F=findFlight(atr);
    spisPlane();
    int ayy;
    cout<<"�� ����� ������� ��������: ";cin>>ayy;
    P=findPlane(ayy);
    F.PlaneKey=P.getPlaneKey();
    cout<<"�� "<<P.getName()<<" �������� "<<P.getNumberOfSeats()<<" ����. ������� '1', ��� �������������, ��� '0' ��� ��������� ���-�� ����: ";
    int input; cin>>input;
    if(input == 1){
        F.Places=P.getNumberOfSeats();
    } else {
        cout<<"������� ���-�� ���� �� �����: "; int col; cin>>col;
        while (col < 1 || col > P.getNumberOfSeats()) {
            printf("������������ ��������. ��������� ����: ");
            cin>>col;
        }
        F.Places=col;
    }
    PlacesSet(F,atr);
    fin.close();
}
}

int deleteFlisht(){
    spisFlight();
    cout<<"����� �����, ������� ����� �������: ";int atr;cin>>atr;
    fstream fin(FileFlight,ios::binary|ios::app);
    F=findFlight(atr);
    while(!fin.read(reinterpret_cast<char*>(&F),sizeof(Flight)).eof()){
        fin.write(reinterpret_cast<const char*>(&findFlight(atr)),sizeof(&findFlight(atr)));
    }
    fin.close();
    return 0;
}

void addFlight(){
    zap(FileFlight,F);
}

