#include "airport_f.h"
#include <windows.h>
#include <iostream>

void print_menu() {
    system("cls");
    cout<<endl<<"Введите пункт меню:\n";
    cout<<"1. Вывод самолетов\n";
    cout<<"2. Вывод рейсов\n";
    cout<<"3. Вывод билетов\n";
    cout<<"4. Проверить наличие свободных мест на рейсе\n";
    cout<<"5. Вывести рейсы самолета\n";
    cout<<"6. Загрузка самолетов по датам\n";
    cout<<"7. Самый дорогой рейс\n";
    cout<<"8. Замена самолета на пустом рейсе\n";
    cout<<"9. Продажа билета\n";
    cout<<"10. Рейсы без промежуточных посадок\n";
    cout<<"11. Добавление и редактирование информации в базе\n";
    cout<<"12. Выйти из программы\n";
    cout<<">";
}

void add_print_menu() {
    system("cls");
    cout<<"Что нужно добавить?:\n";
    cout<<"1. Добавить самолет\n";
    cout<<"2. Добавить рейс\n";
    cout<<"3. Редактировать рейс\n";
    cout<<"4. Редактировать самолет\n";
    cout<<"5. Удалить билет\n";
    cout<<"6. Назад\n";
    cout<<">";
}

void add_menu() {
    int variant;
    do {
        add_print_menu();
        variant = get_variant(6); // получаем номер выбранного пункта меню

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

