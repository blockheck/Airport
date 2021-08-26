#include "airport_f.h"
#include <windows.h>
#include <iostream>

void print_menu() {
    system("cls");
    cout<<endl<<"������� ����� ����:\n";
    cout<<"1. ����� ���������\n";
    cout<<"2. ����� ������\n";
    cout<<"3. ����� �������\n";
    cout<<"4. ��������� ������� ��������� ���� �� �����\n";
    cout<<"5. ������� ����� ��������\n";
    cout<<"6. �������� ��������� �� �����\n";
    cout<<"7. ����� ������� ����\n";
    cout<<"8. ������ �������� �� ������ �����\n";
    cout<<"9. ������� ������\n";
    cout<<"10. ����� ��� ������������� �������\n";
    cout<<"11. ���������� � �������������� ���������� � ����\n";
    cout<<"12. ����� �� ���������\n";
    cout<<">";
}

void add_print_menu() {
    system("cls");
    cout<<"��� ����� ��������?:\n";
    cout<<"1. �������� �������\n";
    cout<<"2. �������� ����\n";
    cout<<"3. ������������� ����\n";
    cout<<"4. ������������� �������\n";
    cout<<"5. ������� �����\n";
    cout<<"6. �����\n";
    cout<<">";
}

void add_menu() {
    int variant;
    do {
        add_print_menu();
        variant = get_variant(6); // �������� ����� ���������� ������ ����

        switch (variant) {
        case 1:
            addPlane();
            break;

        case 2:
            addFlight();
            break;

        case 3:
            Editor();
            break;

        case 4:
            EditorPlane();
            break;
                                
			case 5:
            DeletorTickets();
            break;
        }
        if (variant != 6)
            system("pause");
    } while (variant != 6);
}

int main(int argc, char *argv[])
{
    system("color F0");
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    int variant;

    do {
        print_menu();

        variant = get_variant(12);

        switch (variant) {
        case 1:
            spisPlane();
            break;

        case 2:
            spisFlight();
            break;

        case 3:
            spisTickets();
            break;

        case 4:
            CheckFree();
            break;

        case 5:
            PlaneFlight();
            break;

        case 6:
            RaspisaniePlane();
            break;

        case 7:
            bigCostFlight();
            break;

        case 8:
            emptyFlight();
            break;

        case 9:
            addTickets();
            break;
            
            case 10:
            OneLanding();
            break;

        case 11:
            add_menu();
            break;
        }

        if (variant != 12)
            system("pause");
    } while (variant != 12);
}

