//#include <iomanip>
#include "airport_f.h"

using namespace std;

const char *FilePlane="plane.dat";

static Plane P;


int lastPlane(){
    int n=0;
    ifstream fin(FilePlane,ios::binary);
    if(fin.fail()){
        cerr<<"Файл не открыт";
        exit(1);
    }
    while(!fin.read((char*)&P, sizeof(Plane)).eof()){
        n=P.getPlaneKey();};
    fin.close();
    return n;
}

istream &operator>>(istream &in, Plane &P){
    int input;
    int a=lastPlane();P.PlaneKey=a+1;
    cout<<"Название самолета: ";in>>P.Name;
    cout<<"Категория самолета: ";in>>P.Category;
    cout<<"Количество мест: ";in>>P.NumberOfSeats;

    cout<<left<<setw(16)<<"|№ Самолета"<<setw(20)<<"|Название"<<setw(19)<<"|Категория"<<setw(20)<<"|Кол-во мест|"<<endl;
    cout<<P;
    cout<<"Вы подтверждаете данные?"<<" Введите '1', для подтверждения, или '0', чтобы начать сначала: ";
    cin>>input;
    if(input == 1){
        cout<<"Успешно добавлено"<<endl;
        return in;
    } else {
        cin>>P;
    }
}

int spisPlane(){
    ifstream fin(FilePlane,ios::binary|ios::in|ios::ate);
    double file_size = fin.tellg();
    if (file_size == 0 || file_size==-1){
        cout<<"Файл пустой или не найден. Добавьте информацию с помощью пункта 10 главного меню."<<endl; fin.close(); exit(3);}
    else{
        ifstream fin(FilePlane,ios::binary);
        cout<<left<<setw(16)<<"|№ Самолета"<<setw(20)<<"|Название"<<setw(19)<<"|Категория"<<setw(20)<<"|Кол-во мест|"<<endl;
        while(!fin.read((char*)&P,sizeof(Plane)).eof())
            cout<<P;
        fin.close();
    }
    return 0;
}

int RaspisaniePlaneAdd(time_t date){
    ifstream fin(FilePlane,ios::binary|ios::in|ios::ate);
        double file_size = fin.tellg();
    if (file_size == 0 || file_size==-1){
        cout<<"Файл пустой или не найден. Добавьте информацию с помощью пункта 10 главного меню."<<endl; fin.close(); exit(3);}
    else{
    	        ifstream fin(FilePlane,ios::binary);
    cout<<left<<setw(16)<<"|№ Самолета"<<setw(20)<<"|Название"<<setw(19)<<"|Категория"<<setw(20)<<"|Кол-во мест|"<<endl;
    while(!fin.read((char*)&P,sizeof(Plane)).eof()){
        cout<<"|——————————————————————————————————————————————————————————————————|"<<endl;
        cout<<P;
        PlaneFindTimeFlightAdd(P,date);
    }
}
    fin.close();
    return 0;
}
 
Plane& RaspisaniePlane(){
    ifstream fin(FilePlane,ios::binary);
    if(fin.fail()){
        cerr<<"Файл не открыт.";   exit(3); }
    cout<<left<<setw(16)<<"|№ Самолета"<<setw(20)<<"|Название"<<setw(19)<<"|Категория"<<setw(20)<<"|Кол-во мест|"<<endl;
    while(!fin.read((char*)&P,sizeof(Plane)).eof()){
        cout<<"|——————————————————————————————————————————————————————————————————|"<<endl;
        cout<<P;
       PlaneFindTimeFlight(P);
    }
    fin.close();
}

ostream& operator<<(ostream &out, const Plane &P){
    out<<left<<"|"<<setw(15)<<P.PlaneKey<<"|"<<setw(19)<<P.Name<<"|"<<setw(18)<<P.Category<<"|"<<setw(11)<<P.NumberOfSeats<<"|"<<endl;
}

Plane& findPlane(int k){
    ifstream fin(FilePlane,ios::binary);
    fin.seekg((k-1)*sizeof(Plane));
    fin.read((char*)&P,sizeof(Plane));
    fin.close();
    return P;
}

int PlaneFlight(){
    spisPlane();
    int num;
    cout<<endl<<"Введите номер самолета, рейсы которого необходимо вывести: "; cin>>num;
    PlaneFindFlight(findPlane(num));
}

Plane& SetPlane(Plane A, int k){
    ofstream fin(FilePlane,ios::in | ios::out | ios::binary);
    fin.seekp((k-1)*sizeof(Plane));
    fin.write((char*)&A,sizeof(Plane));
    fin.close();
}

int EditorPlane(){

    Plane P;
    spisPlane();
    int kp;
    cout<<"Введите номер самолета, который нужно отредактировать: ";int k;cin>>k;
    P=findPlane(k);
    cout<<P;
    do {
        cout<<"1. Название"<<endl;
        cout<<"2. Категория"<<endl;
        cout<<"3. Количество мест"<<endl;
        cout<<"4. Отмена"<<endl;

        cout<<"Введите номер пункта, который нужно отредактировать: ";

        kp = get_variant(4);

        switch (kp) {
        P=findPlane(k);
        case 1:
            cout<<"Название: ";cin>>P.Name;
            break;
        case 2:
            cout<<"Категория: ";cin>>P.Category;
        case 3:
            cout<<"Количество мест: ";cin>>P.NumberOfSeats;
            break;
        }
        if(kp!=8){
            cout<<left<<setw(16)<<"|№ Самолета"<<setw(20)<<"|Название"<<setw(19)<<"|Категория"<<setw(20)<<"|Кол-во мест|"<<endl;
            cout<<P;
            int input;
            cout<<"Вы подтверждаете данные?"<<" Введите '1', для подтверждения, или '0', чтобы начать сначала: ";
            cin>>input;
            if(input == 1){
                cout<<"Успешно изменено"<<endl;
                SetPlane(P,k);
            }
            else{
                break;
            }
            break;
        }
        if (kp != 4)
            system("pause");
    } while (kp != 4);

}


void addPlane(){
    zap(FilePlane,P);
}

