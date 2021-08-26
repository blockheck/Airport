//#include <iomanip>
#include "airport_f.h"
#include <ctime>
#include <iomanip>

using namespace std;

const char *FileTickets="tickets.dat";

static Flight F;
static Tickets T;
static Plane P;

int lastTicket(){
    int n=0;
    ifstream fin(FileTickets,ios::binary);
    if(fin.fail()){
        cerr<<"���� �� ������";
        exit(1);
    }
    while(!fin.read((char*)&T, sizeof(Tickets)).eof()){
        n=T.getTickedKey();};
    fin.close();
    return n;
}

Flight PlacesRed(Flight &F){
    if(F.Places!=0)
        F.Places=F.Places - 1;
    else cout<<"��� ����!";
    return F;
}

istream &operator>>(istream &in, Tickets &T){
    int input;
    int a=lastTicket();T.TicketKey=a+1;
    cout<<"����� �����: ";in>>T.Cashbox;
    cout<<endl; spisFlight();
    cout<<"��� �����: ";int h;cin>>h;
    F=findFlight(h);
    while (F.getPlaces()==0) {
        printf("��� ���� �� ��������� �����. ��������� ����: ");
        cin>>h;
        F=findFlight(h);
    }
    PlacesRed(F);
    T.NomerFlight = F.getNomerFlight();
    T.date = F.getDate();
    cout<<endl<<"����� ������. ����������: "<<endl;
    cout<<left<<setw(9)<<"|� ������"<<setw(8)<<"|� �����"<<setw(8)<<"|� �����"<<setw(28)<<"|����� ������      |"<<endl;
    cout<<T;

    cout<<"�� ������������� ������?"<<" ������� '1', ��� �������������, ��� '0', ����� ������ �������: ";
    cin>>input;
    if(input == 1){
        cout<<"������� ���������"<<endl;
        return in;
    } else {
        cin>>T;
    }
}

int spisTickets(){
	spisFlight();
	cout<<"������� ����� �����, ������ �������� ���������� �������: ";int input;cin>>input;
	F=findFlight(input);
	if(F.Places!=CheckTicketsFree(F)){
    ifstream fin(FileTickets,ios::binary|ios::in|ios::ate);
    double file_size = fin.tellg();
    if (file_size == 0 || file_size==-1){
        cout<<"���� ������ ��� �� ������. �������� ���������� � ������� ������ 9 �������� ����."<<endl; fin.close();}
    else{
        ifstream fin(FileTickets,ios::binary);
        cout<<left<<setw(9)<<"|� ������"<<setw(8)<<"|� �����"<<setw(8)<<"|� �����"<<setw(28)<<"|����� ������      |"<<endl;
        while(!fin.read((char*)&T,sizeof(Tickets)).eof())
        {
        	if(T.getNomerFlight()==F.getNomerFlight())
            cout<<T;
        }
        fin.close(); return 0;
    }
}
else { cout<<"��� ��������� �������."<<endl; }
}

int CheckTicketsFree(Flight& F){
    int count=0; int kolvo;
    ifstream fin(FileTickets,ios::binary|ios::in|ios::ate);
    double file_size = fin.tellg();
    if (file_size == 0 || file_size==-1){
        cout<<"���� ������ ��� �� ������. �������� ���������� � ������� ������ 9 �������� ����."<<endl; fin.close();}
    else{
        ifstream fin(FileTickets,ios::binary);
        while(!fin.read((char*)&T,sizeof(Tickets)).eof())
        {
            if(T.getNomerFlight()==F.getNomerFlight())
                count++;
            kolvo = F.getPlaces()-count;
        }
        fin.close();
    }
    return kolvo;
}

void printTime(const Tickets &T) {
	tm* p_tm=localtime(&T.date);
    cout<<right<<setfill ('0')<<setw(2)<<p_tm->tm_mday<<"."<<setw(2)<<p_tm->tm_mon+1<<"."<<p_tm->tm_year+1900<<"  "<<setw(2)<<p_tm->tm_hour<<setw(1)<<":"<<setw(2)<<p_tm->tm_min<<left<<setfill (' ');
}

ostream& operator<<(ostream &out, const Tickets &T){
    out<<left<<"|"<<setw(8)<<T.TicketKey<<"|"<<setw(7)<<T.Cashbox<<"|"<<setw(7)<<T.NomerFlight<<"|";printTime(T);cout<<" |"<<endl;
}

int DeletorTickets(){
	spisTickets();
	cout<<"����� ������, ������� ����� �������: ";int atr;cin>>atr;
	
    ofstream fout("tickets_key.bin", ios::binary);
    ifstream fin(FileTickets,ios::binary);
    while(!fin.read(reinterpret_cast<char*>(&T),sizeof(Tickets)).eof()){
        if(T.getTickedKey()!=atr){
            fout.write(reinterpret_cast<const char*>(&T),sizeof(T));
        }
    }
    fin.close();
    fout.close();
    remove(FileTickets);
    rename("tickets_key.bin", "tickets.dat");
}

void addTickets(){
    zap(FileTickets,T);
}

