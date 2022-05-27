#pragma once
#include <iostream>
#include <string>
#include "TableOpen.h"
#include "TableChain.h"
#include <math.h>
#include <time.h>
using namespace std;

int randCahr() {
    return (rand() % 26);
}

string SRand() {
    string str;
    int lenght = (rand() % 6) + 5;
    for (int i = 0; i < lenght; i++) {
        char c = (90 - randCahr());
        str += c;
    }
    return str;
}

void testTable(bool form) {
    int size;
    cin >> size;
    //HashTable<string, int>* table = new HashTable<string, int>(form, size);
}

int main() {
    setlocale(LC_ALL, "ru");
    int mainMode = -1, tableMode = -1, size = 0;
    string key = "";
    int data = 0;
    TableOpen<string, int>* tableOpen = nullptr;
    TableChain<string, int>* tableChain = nullptr;
    //TableOpen<string, int>::Iterator iterOpen(*tableOpen);
    //TableChain<string, int>::Iterator iterChain(*tableOpen);
    string mainMenu = "\n1 - Хеш-таблица с открытой адресацией\n2 - Хеш-таблица с цепочками коллизий\n3 - тестирование трудоемкости операций АТД\n4 - оценка хи-квадрат\n0 - выход";
    string menuTables = "\n1 - опрос размера таблицы\n2 - опрос количества элементов в таблице\n3 - опрос пустоты таблицы\n4 - очистка таблицы\n5 - поиск элемента по ключу k\n6 - вставка элемента по ключу k\n7 - удаление элемента по ключу k\n8 - запрос прямого итератора begin()\n9 - запрос \"неустановленного\" прямого итератора end()\n10 - доступ по чтению к значению текущего элемента *\n11 - доступ по записи к текущему значению *\n12 - переход к следующему элементу в хеш-таблице\n13 - проверка равенства прямому итератору begin()\n14 - проверка равенства прямому итератору end()\n15 - вывод структуры хеш-таблицы на экран\n16 - опрос числа проб, выполненных последней операцией\n0 - выход в главное меню\n";
    cout << mainMenu;
    while (mainMode != 0) {
        cout << "> ";
        cin >> mainMode;
        switch (mainMode) {
        case 1:
            cout << "Введите размер хеш-таблицы: ";
            cin >> size;
            tableOpen = new TableOpen<string, int>(size);
            cout << menuTables;
            while (tableMode != 0) {
                cout << "> ";
                cin >> tableMode;
                switch (tableMode) {
                case 1:
                    cout << tableOpen->getCapacity() << endl;
                    break;
                case 2:
                    cout << tableOpen->getSize() << endl;
                    break;
                case 3:
                    cout << tableOpen->IsEmpty() << endl;
                    break;
                case 4:
                    tableOpen->Clear();
                    break;
                case 5:
                    cin >> key;
                    try
                    {
                        cout << tableOpen->Data(key) << endl;
                    }
                    catch (...)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 6:
                    cin >> key;
                    cin >> data;
                    cout << tableOpen->Insert(key, data) << endl;
                    break;
                case 7:
                    cin >> key;
                    cout << tableOpen->Delete(key) << endl;
                    break;
                case 8:
                    //iterOpen = tableOpen->begin();
                    break;
                case 9:
                    //iterOpen = tableOpen->end();
                    break;
                case 10:
                    try
                    {
                        //cout << *iterOpen << endl;
                    }
                    catch (...)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 11:
                    try
                    {
                        //cin >> *iterOpen;
                    }
                    catch (...)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 12:
                    try
                    {
                        //iterOpen++;
                    }
                    catch (...)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 13:
                    //cout << (iterOpen == tableOpen->begin()) << endl;
                    break;
                case 14:
                    //cout << (iterOpen == tableOpen->end()) << endl;
                    break;
                case 15:
                    tableOpen->Print();
                    break;
                case 16:
                    cout << tableOpen->NumOfProbes();
                case 0:
                    break;
                default:
                    break;
                }
            }
            break;
        case 2:
            cout << "Введите размер хеш-таблицы: ";
            cin >> size;
            tableChain = new TableChain<string, int>(size);
            cout << menuTables;
            while (tableMode != 0) {
                cout << "> ";
                cin >> tableMode;
                switch (tableMode) {
                case 1:
                    cout << tableChain->getCapacity() << endl;
                    break;
                case 2:
                    cout << tableChain->getSize() << endl;
                    break;
                case 3:
                    cout << tableChain->IsEmpty() << endl;
                    break;
                case 4:
                    tableChain->Clear();
                    break;
                case 5:
                    cin >> key;
                    try
                    {
                        cout << tableChain->Data(key) << endl;
                    }
                    catch (...)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 6:
                    cin >> key;
                    cin >> data;
                    cout << tableChain->Insert(key, data) << endl;
                    break;
                case 7:
                    cin >> key;
                    cout << tableChain->Delete(key) << endl;
                    break;
                case 8:
                    //iterChain = tableChain->begin();
                    break;
                case 9:
                    //iterChain = tableChain->end();
                    break;
                case 10:
                    try
                    {
                        //cout << *iterChain << endl;
                    }
                    catch (...)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 11:
                    try
                    {
                        //cin >> *iterChain;
                    }
                    catch (...)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 12:
                    try
                    {
                        //iterChain++;
                    }
                    catch (...)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 13:
                    //cout << (iterChain == tableChain->begin()) << endl;
                    break;
                case 14:
                    //cout << (iterChain == tableChain->end()) << endl;
                    break;
                case 15:
                    tableChain->Print();
                    break;
                case 16:
                    cout << tableChain->NumOfProbes();
                case 0:
                    break;
                default:
                    break;
                }
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 0:
            return -1;
        }
    }
}

/*int main() {
    setlocale(LC_ALL, "ru");
    int mode = -1;
    RandTree<int, int> rt;
    BST<int, int>::Iterator iter(rt);
    BST<int, int>::RevIterator riter(rt);
    BST<int, int>::Iterator checkBegin;
    BST<int, int>::RevIterator checkRBegin;
    BST<int, int>::Iterator checkEnd;
    BST<int, int>::RevIterator checkREnd;
    string menu = "\n1 - Опрос размера дерева\n2 - Очистка дерева\n3 - Проверка дерева на пустоту\n4 - Доступ по чтению к данным по ключу\n5 - Доступ по записи к данным по ключу\n6 - Включение данных с заданным ключом\n7 - Удаление данных с заданным ключом\n8 - Вывод дерева на экран\n9 - Запрос прямого итератора\n10 - Запрос \"неустановленного\" прямого итератора\n11 - Операция доступа по чтению к текущему значению прямого итератора *\n12 - Операция доступа по записи к текущему значению прямого итератора *\n13 - Операция инкремента для перехода к следующему значению в списке для прямого итератора\n14 - Проверка равенства прямого итератора узлу с минимальным ключом\n15 - Проверка равенства прямого итератора \"неустановленному\" прямому итератору\n16 - Проверка неравенства прямого итератора узлу с минимальным ключом\n17 - Проверка неравенства прямого итератора \"неустановленному\" прямому итератору\n18 - Запрос обратного итератора\n19 - Запрос \"неустановленного\" обратного итератора\n20 - Операция доступа по чтению к текущему значению обратного итератора *\n21 - Операция доступа по записи к текущему значению обратного итератора *\n22 - Операция инкремента для перехода к предыдущему по ключу узлу в дереве для прямого итератора\n23 - Проверка равенства обратного итератора узлу с максимальным ключом\n24 - Проверка равенства обратного итератора \"неустановленному\" обратному итератору\n25 - Проверка неравенства обратного итератора узлу с максимальным ключом\n26 - Проверка неравенства обратного итератора \"неустановленному\" обратному итератору\n27 - Запустить тест трудоёмкости операций случайного дерева\n28 - Запустить тест трудоёмкости операций вырожденного дерева\n29 - Вывод меню\n30 - Вывод на экран последовательности ключей при обходе узлов дерева по схеме L -> R -> t\n0 - Завершение программы\n";
    cout << "Доступные команды:" << menu << endl;
    int value, key, newValue, treeSize;
    int n;
    while (mode != 0) {
        cout << "> ";
        cin >> mode;
        switch (mode)
        {
        case 1:
            treeSize = rt.getSize();
            cout << treeSize << endl;
            break;
        case 2:
            rt.clear();
            cout << "Дерево очищено" << endl;
            break;
        case 3:
            cout << rt.isEmpty() << endl;
            break;
        case 4:
            cin >> key;
            try
            {
                cout << rt.get(key) << endl;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 5:
            cin >> key >> newValue;
            try
            {
                rt.get(key) = newValue;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 6:
            cin >> key >> value;
            cout << rt.put(key, value) << endl;
            break;
        case 7:
            cin >> key;
            cout << rt.remove(key) << endl;
            break;
        case 8:
            rt.printVert();
            break;
        case 9:
            iter = rt.begin();
            break;
        case 10:
            iter = rt.end();
            break;
        case 11:
            try
            {
                cout << *iter << endl;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 12:
            cin >> newValue;
            try
            {
                *iter = newValue;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 13:
            try
            {
                ++iter;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 14:
            checkBegin = rt.begin();
            cout << (iter == checkBegin) << endl;
            break;
        case 15:
            checkEnd = rt.end();
            cout << (iter == checkEnd) << endl;
            break;
        case 16:
            checkBegin = rt.begin();
            cout << (iter != checkBegin) << endl;
            break;
        case 17:
            checkEnd = rt.end();
            cout << (iter != checkEnd) << endl;
            break;
        case 18:
            riter = rt.rbegin();
            break;
        case 19:
            riter = rt.rend();
            break;
        case 20:
            try
            {
                cout << *riter << endl;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 21:
            cin >> newValue;
            try
            {
                *riter = newValue;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 22:
            try
            {
                ++riter;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 23:
            checkRBegin = rt.rbegin();
            cout << (riter == checkRBegin) << endl;
            break;
        case 24:
            checkREnd = rt.rend();
            cout << (riter == checkREnd) << endl;
            break;
        case 25:
            checkRBegin = rt.rbegin();
            cout << (riter != checkRBegin) << endl;
            break;
        case 26:
            checkREnd = rt.rend();
            cout << (riter != checkREnd) << endl;
            break;
        case 27:
            cin >> n;
            test_rand(n);
            break;
        case 28:
            cin >> n;
            test_ord(n);

            break;
        case 29:
            cout << "Доступные команды:" << menu << endl;
            break;
        case 30:
            rt.printLRT();
            break;
        case 0:
            return -1;
        default:
            break;
        }
    }

    return 0;
}*/