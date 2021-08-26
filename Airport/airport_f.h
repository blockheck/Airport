#ifndef AIRPORT_F_H
#define AIRPORT_F_H

#include <iostream>
#include <iomanip>
#include <time.h>
#include <fstream>

using namespace std;

class Flight {
protected:
    int FlightKey;
    int NomerFlight;
    int PlaneKey;
    int LandingCount;
    char Landing[100][100];
    time_t DepartureTime;
    time_t ArrivalTime;
    int Places;
    int Price;
public:
    Flight(){FlightKey = 0;};

    friend istream& operator>>(istream &in, Flight &F);
    friend ostream& operator<<(ostream &out,  Flight &F);
    int getFlightKey(){return FlightKey;};
    int getNomerFlight(){return NomerFlight;};
    int getLandingCount(){return LandingCount;};
    int getPlaneKey(){return PlaneKey;};
    char* getLanding(){return *Landing;};
    time_t& getDate(){return DepartureTime;};
    time_t& getArrDate(){return ArrivalTime;};
    int getPlaces(){return Places;};
    int getPrice(){return Price;};
    friend Flight PlacesRed(Flight &F);
    friend Flight& findFlight(int k);
    friend Flight& PlacesSet(Flight A, int k);
    friend string LandingPrint(Flight F,int n);
    friend ostream& operator<<(ostream&out, tm* p_tm);
    friend int emptyFlight();
    friend int Editor();
    friend int spisTickets();
};

class Tickets : public Flight {
protected:
    int TicketKey;
    int Cashbox;
    int NomerFlight;
    time_t date;
public:
    Tickets(){};
    friend istream& operator>>(istream &in, Tickets &T);
    friend ostream& operator<<(ostream &out, const Tickets &T);
    friend void printTime(const Tickets &T);
    int getTickedKey(){return TicketKey;};
        int getNomerFlight(){return NomerFlight;};
};

class Plane : public Flight {
protected:
    int PlaneKey;
    char Name[30];
    char Category[20];
    int NumberOfSeats;
public:
    Plane(){PlaneKey = 0;};
    friend istream& operator>>(istream &in, Plane &P);
    friend ostream& operator<<(ostream &out, const Plane &P);
    friend ostream& operator<<(ostream&out, tm* p_tm);
    int getPlaneKey(){return PlaneKey;};
    char* getName(){return Name;};
    int getNumberOfSeats(){return NumberOfSeats;};
    friend Plane& findPlane(int k);
    friend char GetPlaneName(int key);
        friend void readFile();
        friend int EditorPlane();
        friend Plane& SetPlane(Plane A, int k);
};


void addFlight();
void addPlane();
void addTickets();

int emptyFlight();
int spisPlane();
int RaspisaniePlaneAdd(time_t date);
int spisFlight();
int spisTickets();
int bigCostFlight();
void readFile();
int Editor();
int get_variant(int count) ;

int PlaneFlight();
int PlaneFindFlight(Plane &P);
int PlaneFindTimeFlightAdd(Plane &P,time_t date);
int PlaneFindTimeFlight(Plane &p);
Plane& RaspisaniePlane();

int CheckTicketsFree(Flight& F);
int CheckFree();

int Deletor();
int Deletor(Flight &F);
int Deletor(Plane &P);
int DeletorPlane();
int EditorPlane();
int DeletorTickets();

int OneLanding();

Flight& findFlight(int k);
Plane& findPlane(int k);

template <class M>
void zap(const char *Fname, M&A){
    ofstream fout(Fname,ios::binary|ios::app);
    cin>>A;
    if(fout.fail())
    {
        cerr<<"Файл не открыт";
        exit(1);
    }
    fout.write(reinterpret_cast<const char*>(&A),sizeof(A));
    fout.close();
}

#endif // AIRPORT_F_H

