//#include <iomanip>
#include "airport_f.h"

using namespace std;

const char *FilePlane="plane.dat";

static Plane P;


int lastPlane(){
    int n=0;
    ifstream fin(FilePlane,ios::binary);
    if(fin.fail()){
        cerr<<"���� �� ������";
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
    cout<<"�������� ��������: ";in>>P.Name;
    cout<<"��������� ��������: ";in>>P.Category;
    cout<<"���������� ����: ";in>>P.NumberOfSeats;

    cout<<left<<setw(16)<<"|� ��������"<<setw(20)<<"|��������"<<setw(19)<<"|���������"<<setw(20)<<"|���-�� ����|"<<endl;
    cout<<P;
    cout<<"�� ������������� ������?"<<" ������� '1', ��� �������������, ��� '0', ����� ������ �������: ";
    cin>>input;
    if(input == 1){
        cout<<"������� ���������"<<endl;
        return in;
    } else {
        cin>>P;
    }
}

int spisPlane(){
    ifstream fin(FilePlane,ios::binary|ios::in|ios::ate);
    double file_size = fin.tellg();
    if (file_size == 0 || file_size==-1){
        cout<<"���� ������ ��� �� ������. �������� ���������� � ������� ������ 10 �������� ����."<<endl; fin.close(); exit(3);}
    else{
        ifstream fin(FilePlane,ios::binary);
        cout<<left<<setw(16)<<"|� ��������"<<setw(20)<<"|��������"<<setw(19)<<"|���������"<<setw(20)<<"|���-�� ����|"<<endl;
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
        cout<<"���� ������ ��� �� ������. �������� ���������� � ������� ������ 10 �������� ����."<<endl; fin.close(); exit(3);}
    else{
    	        ifstream fin(FilePlane,ios::binary);
    cout<<left<<setw(16)<<"|� ��������"<<setw(20)<<"|��������"<<setw(19)<<"|���������"<<setw(20)<<"|���-�� ����|"<<endl;
    while(!fin.read((char*)&P,sizeof(Plane)).eof()){
        cout<<"|������������������������������������������������������������������|"<<endl;
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
        cerr<<"���� �� ������.";   exit(3); }
    cout<<left<<setw(16)<<"|� ��������"<<setw(20)<<"|��������"<<setw(19)<<"|���������"<<setw(20)<<"|���-�� ����|"<<endl;
    while(!fin.read((char*)&P,sizeof(Plane)).eof()){
        cout<<"|������������������������������������������������������������������|"<<endl;
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
    cout<<endl<<"������� ����� ��������, ����� �������� ���������� �������: "; cin>>num;
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
    cout<<"������� ����� ��������, ������� ����� ���������������: ";int k;cin>>k;
    P=findPlane(k);
    cout<<P;
    do {
        cout<<"1. ��������"<<endl;
        cout<<"2. ���������"<<endl;
        cout<<"3. ���������� ����"<<endl;
        cout<<"4. ������"<<endl;

        cout<<"������� ����� ������, ������� ����� ���������������: ";

        kp = get_variant(4);

        switch (kp) {
        P=findPlane(k);
        case 1:
            cout<<"��������: ";cin>>P.Name;
            break;
        case 2:
            cout<<"���������: ";cin>>P.Category;
        case 3:
            cout<<"���������� ����: ";cin>>P.NumberOfSeats;
            break;
        }
        if(kp!=8){
            cout<<left<<setw(16)<<"|� ��������"<<setw(20)<<"|��������"<<setw(19)<<"|���������"<<setw(20)<<"|���-�� ����|"<<endl;
            cout<<P;
            int input;
            cout<<"�� ������������� ������?"<<" ������� '1', ��� �������������, ��� '0', ����� ������ �������: ";
            cin>>input;
            if(input == 1){
                cout<<"������� ��������"<<endl;
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

