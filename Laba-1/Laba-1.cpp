#include <iostream>
#include <string>
#include "List.cpp"
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    int mode = -1;
    List<int> list;
    List<int>::Iterator iter(list);
    List<int>::Iterator iter2(list);
    string menu = "\n1 - Опрос размера списка\n2 - Очистка списка\n3 - Проверка списка на пустоту\n4 - Опрос наличия заданного значения\n5 - Чтение значения с заданным номером в списке\n6 - Изменение значения с заданным номером в списке\n7 - Получение позиции в списке для заданного значения\n8 - Включение нового значения\n9 - Включение нового значения в позицию с заданным номером\n10 - Удаление заданного значения из списка\n11 - Удаление заданного значения из позиции с заданным номером\n12 - Запрос прямого итератора\n13 - Запрос \"неустановленного\" прямого итератора\n14 - Операция доступа по чтению к текущему значению *\n15 - Операция доступа по записи к текущему значению *\n16 - Операция инкремента для перехода к следующему значению в списке\n17 - Проверка равенства однотипных итераторов ==\n18 - Проверка равенства однотипных итераторов !=\n19 - Вывод элементов списка\n0 - Завершение программы\n";
    cout << "Доступные команды:" << menu << endl;
    int value, id, newValue, listSize;
    bool isAdded;
    while (mode != 0) {
        cout << "> ";
        cin >> mode;
        switch (mode)
        {
        case 1:
            listSize = list.getSize();
            cout << listSize << endl;
            break;
        case 2:
            list.clear();
            cout << "Список очищен" << endl;
            break;
        case 3:
            cout << list.isEmpty() << endl;
            break;
        case 4:
            cin >> value;
            cout << list.hasObject(value) << endl;
            break;
        case 5:
            cin >> id;
            cout << list.getObject(id) << endl;
            break;
        case 6:
            cin >> id >> newValue;
            list.editObject(newValue, id);
            break;
        case 7:
            cin >> value;
            id = list.getPosition(value);
            cout << id << endl;
            break;
        case 8:
            cin >> value;
            list.add(value);
            break;
        case 9:
            cin >> id >> value;
            cout << list.add(value, id) << endl;
            break;
        case 10:
            cin >> value;
            cout << list.remove(value) << endl;
            break;
        case 11:
            cin >> id;
            cout << list.removeAt(id) << endl;
            break;
        case 12:
            iter = list.begin();
            cout << *iter << endl;
            break;
        case 13:
            iter = list.end();
            cout << *iter << endl;
            break;
        case 14:
            iter = list.begin();
            cout << *iter << endl;
            break;
        case 15:
            iter = list.begin();
            ++iter;
            cin >> newValue;
            *iter = newValue;
            cout << *iter << endl;
            break;
        case 16:
            iter = list.begin();
            ++iter;
            cout << *iter << endl;
            break;
        case 17:
            iter = list.begin();
            iter2 = list.begin();
            cout << (iter == iter2) << endl;
            break;
        case 18:
            iter = list.begin();
            iter2 = list.begin();
            ++iter2;
            cout << (iter != iter2) << endl;
            break;
        case 19:
            list.print();
            cout << endl;
            break;
        case 0:
            return -1;
        default:
            break;
        }
        
    }

    
    return 0;
}
