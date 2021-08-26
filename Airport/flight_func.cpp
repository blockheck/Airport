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
        printf("Некорректное значение. Повторите ввод: ");
        cin>>a;
    }
    return a;
}


int lastFlight(){
    int n=0;
    ifstream fin(FileFlight,ios::binary);
    if(fin.fail()){
        cerr<<"Файл не открыт";
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
    char s[100]; // строка для считывания введённых данных
    scanf("%s", s); // считываем строку

    // пока ввод некорректен, сообщаем об этом и просим повторить его
    while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count) {
        printf("Нет введенного пункта. Попробуйте снова: "); // выводим сообщение об ошибке
        scanf("%s", s); // считываем строку повторно
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
    cout<<"Введите номер рейса, который нужно отредактировать: ";int k;cin>>k;
    F=findFlight(k);
    cout<<F;
    do {
        cout<<"1. Код рейса"<<endl;
        cout<<"2. Самолет"<<endl;
        cout<<"3. Посадки"<<endl;
        cout<<"4. Время вылета"<<endl;
        cout<<"5. Время приземления"<<endl;
        cout<<"6. Кол-во мест"<<endl;
        cout<<"7. Цена"<<endl;
        cout<<"8. Отмена"<<endl;

        cout<<"Введите номер пункта, который нужно отредактировать: ";

        kp = get_variant(8);

        switch (kp) {
        F=findFlight(k);
        case 1:
            cout<<"Номер рейса: ";cin>>F.NomerFlight;
            break;
        case 2:{
            int input;
            RaspisaniePlaneAdd(F.getDate());
            //  strcpy(F.Plane,P.getName());
            cout<<"Код самолета, выполняющего рейс: ";int h;cin>>h;
            P=findPlane(h);
            F.PlaneKey = P.getPlaneKey();
            cout<<"На "<<P.getName()<<" доступно "<<P.getNumberOfSeats()<<" мест. Введите '1', для подтверждения, или '0' для изменения кол-ва мест: ";
            cin>>input;
            if(input == 1){
                F.Places=P.getNumberOfSeats();
            } else {
                cout<<"Введите кол-во мест на рейсе: "; int col; cin>>col;
                while (col < 1 || col > P.getNumberOfSeats()) {
                    printf("Некорректное значение. Повторите ввод: ");
                    cin>>col;
                }
                F.Places=col;
            }
            break;
        }
        case 3:
            cout<<"Введите количество промежуточных посадок с учетом конечного пункта: ";int n;cin>>n;


            while (n < 1 || n > 5) {
                printf("Количество посадок не может быть больше 5. Повторите ввод: ");
                cin>>n;
            }

            F.LandingCount = n;

            for (int i = 0; i < n; i++) {
                cout << "[" << i + 1 << "]" << ": ";
                string a; cin>>a;
                while(!AirportCodeCheck(a)){
                    cout<<"Код аэропорта не найден. Повторите ввод: ";cin>>a;
                }
                strcpy (F.Landing[i], a.c_str());
            }
            break;
        case 4:{
            int input;
            int sec=F.ArrivalTime-F.DepartureTime;
            cout<<"Время вылета ";int dd,mm,yy,hh,min;
            cout<<endl<<"День: "; cin>>dd; dd=TimeCheck(dd, 1, 31);
            cout<<"Месяц: "; cin>>mm;  mm=TimeCheck(mm, 1, 12);
            cout<<"Год: "; cin>>yy;  yy=TimeCheck(yy, 2020, 2025);
            cout<<"Часов: "; cin>>hh; hh=TimeCheck(hh, 0, 23);
            cout<<"Минут: "; cin>>min; min=TimeCheck(min, 0, 59);
            F.DepartureTime=do_time(hh,min,mm,dd,yy);

            cout<<"Длительность полета. Часов: "<<sec/3600<<" минут: "<<(sec/60)%60<<endl;
            cout<<"Вы подтверждаете длительность полета?"<<" Введите '1', для подтверждения, или '0', чтобы ввести новую длительность полета: ";
            cin>>input;
            if(input == 1){
                cout<<"Успешно добавлено"<<endl;
                F.ArrivalTime = F.DepartureTime+sec;
            } else {
                cout<<endl<<"Часов в полете: ";int hours;cin>>hours;
                cout<<"Минут в полет: ";int minute;cin>>minute;
                sec = (minute*60)+(hours*3600);
                F.ArrivalTime = F.DepartureTime+sec;
            }
            break;
        }

        case 5:{
            cout<<"Длительность полета ";
            cout<<endl<<"Часов в полете: ";int hours;cin>>hours;
            cout<<"Минут в полет: ";int minute;cin>>minute;
            int sec = (minute*60)+(hours*3600);
            F.ArrivalTime = F.DepartureTime+sec;
            break;
        }

        case 6:
            int input;
            cout<<"На "<<P.getName()<<" доступно "<<P.getNumberOfSeats()<<" мест. Введите '1', для подтверждения, или '0' для изменения кол-ва мест: ";
            cin>>input;
            if(input == 1){
                F.Places=P.getNumberOfSeats();
            } else {
                cout<<"Введите кол-во мест на рейсе: "; int col; cin>>col;
                while (col < 1 || col > P.getNumberOfSeats()) {
                    printf("Некорректное значение. Повторите ввод: ");
                    cin>>col;
                }
                F.Places=col;
            }
            break;


        case 7:
            cout<<"Цена за билет: ";cin>>F.Price;
            break;

        }
        if(kp!=8){
            cout<<left<<setw(9)<<"|№ Рейса"<<setw(11)<<"|Код рейса"<<setw(17)<<"|Самолет"<<setw(21)<<"|Посадки"<<setw(18)<<"|Время вылета"<<setw(18)<<"|Время приземления"<<setw(13)<<"|Кол-во мест"<<"|Цена    |"<<endl;
            cout<<F;
            int input;
            cout<<"Вы подтверждаете данные?"<<" Введите '1', для подтверждения, или '0', чтобы начать сначала: ";
            cin>>input;
            if(input == 1){
                cout<<"Успешно изменено"<<endl;
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
        cerr<<"Файл не открыт.";   exit(3); }
    cout<<endl<<left<<setw(9)<<"|№ Рейса"<<setw(11)<<"|Код рейса"<<setw(24)<<"|Свободных мест  |"<<endl;
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
    cout<<"Код рейса: ";in>>F.NomerFlight;
    cout<<"Введите количество промежуточных посадок с учетом конечного пункта: ";int n;cin>>n;


    while (n < 1 || n > 5) {
        printf("Количество посадок не может быть больше 5. Повторите ввод: ");
        cin>>n;
    }

    F.LandingCount = n;

    for (int i = 0; i < n; i++) {
        cout << "[" << i + 1 << "]" << ": ";
        string a; cin>>a;
        while(!AirportCodeCheck(a)){
            cout<<"Код аэропорта не найден. Повторите ввод: ";cin>>a;
        }
        strcpy (F.Landing[i], a.c_str());
    }


    cout<<"Время вылета ";int dd,mm,yy,hh,min;
    cout<<endl<<"День: "; cin>>dd; dd=TimeCheck(dd, 1, 31);
    cout<<"Месяц: "; cin>>mm;  mm=TimeCheck(mm, 1, 12);
    cout<<"Год: "; cin>>yy;  yy=TimeCheck(yy, 2020, 2025);
    cout<<"Часов: "; cin>>hh; hh=TimeCheck(hh, 0, 23);
    cout<<"Минут: "; cin>>min; min=TimeCheck(min, 0, 59);
    F.DepartureTime=do_time(hh,min,mm,dd,yy);

    cout<<"Длительность полета ";
    cout<<endl<<"Часов в полете: ";int hours;cin>>hours;
    cout<<"Минут в полет: ";int minute;cin>>minute;
    int sec = (minute*60)+(hours*3600);
    F.ArrivalTime = F.DepartureTime+sec;
    cout<<"Цена за билет: ";in>>F.Price;

    //    cout<<endl; spisPlane();
    //    cout<<"Код самолета, выполняющего рейс: ";int h;cin>>h;
    //    P=findPlane(h);
    RaspisaniePlaneAdd(F.DepartureTime);
    //  strcpy(F.Plane,P.getName());
    cout<<"Код самолета, выполняющего рейс: ";int h;cin>>h;
    P=findPlane(h);
    F.PlaneKey = P.getPlaneKey();
    cout<<"На "<<P.getName()<<" доступно "<<P.getNumberOfSeats()<<" мест. Введите '1', для подтверждения, или '0' для изменения кол-ва мест: ";
    cin>>input;
    if(input == 1){
        F.Places=P.getNumberOfSeats();
    } else {
        cout<<"Введите кол-во мест на рейсе: "; int col; cin>>col;
        while (col < 1 || col > P.getNumberOfSeats()) {
            printf("Некорректное значение. Повторите ввод: ");
            cin>>col;
        }
        F.Places=col;
    }

    cout<<left<<setw(9)<<"|№ Рейса"<<setw(11)<<"|Код рейса"<<setw(17)<<"|Самолет"<<setw(21)<<"|Посадки"<<setw(18)<<"|Время вылета"<<setw(18)<<"|Время приземления"<<setw(13)<<"|Кол-во мест"<<"|Цена    |"<<endl;
    cout<<F;

    cout<<"Вы подтверждаете данные?"<<" Введите '1', для подтверждения, или '0', чтобы начать сначала: ";
    cin>>input;
    if(input == 1){
        cout<<"Успешно добавлено"<<endl;
        return in;
    } else {
        cin>>F;
    }
}

int spisFlight(){
    ifstream fin(FileFlight,ios::binary|ios::in|ios::ate);
    double file_size = fin.tellg();
    if (file_size == 0 || file_size==-1){
        cout<<"Файл пустой или не найден. Добавьте информацию с помощью пункта 10 главного меню."<<endl; fin.close();}
    else{
        ifstream fin(FileFlight,ios::binary);
        cout<<left<<setw(9)<<"|№ Рейса"<<setw(11)<<"|Код рейса"<<setw(17)<<"|Самолет"<<setw(21)<<"|Посадки"<<setw(18)<<"|Время вылета"<<setw(18)<<"|Время приземления"<<setw(13)<<"|Кол-во мест"<<"|Цена    |"<<endl;
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
        cout<<"Файл пустой или не найден. Добавьте информацию с помощью пункта 10 главного меню."<<endl; fin.close();}
    else{
        int max=0; Flight D;
        ifstream fin(FileFlight,ios::binary);
        cout<<left<<setw(9)<<"|№ Рейса"<<setw(11)<<"|Код рейса"<<setw(17)<<"|Самолет"<<setw(21)<<"|Посадки"<<setw(18)<<"|Время вылета"<<setw(18)<<"|Время приземления"<<setw(13)<<"|Кол-во мест"<<"|Цена    |"<<endl;
        while(!fin.read(reinterpret_cast<char*>(&F),sizeof(Flight)).eof())
            if (F.getPrice() > max){max = F.getPrice();D=findFlight(F.getFlightKey());};
        cout<<D;
        fin.close();
    }
    return 0;
}


int PlaneFindFlight(Plane &P){
    cout<<left<<setw(9)<<"|№ Ключа"<<setw(11)<<"|№ Рейса"<<setw(17)<<"|Самолет"<<setw(21)<<"|Посадки"<<setw(18)<<"|Время вылета"<<setw(18)<<"|Время приземления"<<setw(13)<<"|Кол-во мест"<<"|Цена    |"<<endl;
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
                cout<<"|Загрузка самолета в день рейса:                                   |"<<endl;
                SetConsoleTextAttribute(console, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); cout<<"|"<<p_tm<<" — "; p_tm=localtime(&temp); cout<<p_tm;  cout << " - пересечение времени       |" << endl;
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
            cout<<"|"<<p_tm<<" — "; p_tm=localtime(&F.getArrDate()); cout<<p_tm<<"                             |"<<endl;
        }
    }
    fin.close();
    return a;
}

int OneLanding(){
    ifstream fin(FileFlight,ios::binary);
    cout<<left<<setw(9)<<"|№ Ключа"<<setw(11)<<"|№ Рейса"<<setw(17)<<"|Самолет"<<setw(21)<<"|Посадки"<<setw(18)<<"|Время вылета"<<setw(18)<<"|Время приземления"<<setw(13)<<"|Кол-во мест"<<"|Цена    |"<<endl;
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
        cerr<<"Файл не открыт.";   exit(3); }
        cout<<left<<setw(9)<<"|№ Рейса"<<setw(11)<<"|Код рейса"<<setw(17)<<"|Самолет"<<setw(21)<<"|Посадки"<<setw(18)<<"|Время вылета"<<setw(18)<<"|Время приземления"<<setw(13)<<"|Кол-во мест"<<"|Цена    |"<<endl;
    while(!fin.read(reinterpret_cast<char*>(&F),sizeof(Flight)).eof()){
        double a = CheckTicketsFree(F);
        if(((a/F.getPlaces())*100)>50){
            cout<<F;
        }
    }
    cout<<"На каком рейсе заменить самолет, или введите 0 для выхода: ";int atr;cin>>atr;
    if(atr!=0){
    F=findFlight(atr);
    spisPlane();
    int ayy;
    cout<<"На какой самолет заменить: ";cin>>ayy;
    P=findPlane(ayy);
    F.PlaneKey=P.getPlaneKey();
    cout<<"На "<<P.getName()<<" доступно "<<P.getNumberOfSeats()<<" мест. Введите '1', для подтверждения, или '0' для изменения кол-ва мест: ";
    int input; cin>>input;
    if(input == 1){
        F.Places=P.getNumberOfSeats();
    } else {
        cout<<"Введите кол-во мест на рейсе: "; int col; cin>>col;
        while (col < 1 || col > P.getNumberOfSeats()) {
            printf("Некорректное значение. Повторите ввод: ");
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
    cout<<"Номер рейса, который нужно удалить: ";int atr;cin>>atr;
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

