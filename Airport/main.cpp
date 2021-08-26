#include "airport_f.h"
#include <windows.h>
#include <iostream>

void print_menu() {
    system("cls");
    cout<<endl<<"Ââåäèòå ïóíêò ìåíþ:\n";
    cout<<"1. Âûâîä ñàìîëåòîâ\n";
    cout<<"2. Âûâîä ðåéñîâ\n";
    cout<<"3. Âûâîä áèëåòîâ\n";
    cout<<"4. Ïðîâåðèòü íàëè÷èå ñâîáîäíûõ ìåñò íà ðåéñå\n";
    cout<<"5. Âûâåñòè ðåéñû ñàìîëåòà\n";
    cout<<"6. Çàãðóçêà ñàìîëåòîâ ïî äàòàì\n";
    cout<<"7. Ñàìûé äîðîãîé ðåéñ\n";
    cout<<"8. Çàìåíà ñàìîëåòà íà ïóñòîì ðåéñå\n";
    cout<<"9. Ïðîäàæà áèëåòà\n";
    cout<<"10. Ðåéñû áåç ïðîìåæóòî÷íûõ ïîñàäîê\n";
    cout<<"11. Äîáàâëåíèå è ðåäàêòèðîâàíèå èíôîðìàöèè â áàçå\n";
    cout<<"12. Âûéòè èç ïðîãðàììû\n";
    cout<<">";
}

void add_print_menu() {
    system("cls");
    cout<<"×òî íóæíî äîáàâèòü?:\n";
    cout<<"1. Äîáàâèòü ñàìîëåò\n";
    cout<<"2. Äîáàâèòü ðåéñ\n";
    cout<<"3. Ðåäàêòèðîâàòü ðåéñ\n";
    cout<<"4. Ðåäàêòèðîâàòü ñàìîëåò\n";
    cout<<"5. Óäàëèòü áèëåò\n";
    cout<<"6. Íàçàä\n";
    cout<<">";
}

void add_menu() {
    int variant;
    do {
        add_print_menu();
        variant = get_variant(6); // ïîëó÷àåì íîìåð âûáðàííîãî ïóíêòà ìåíþ

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

