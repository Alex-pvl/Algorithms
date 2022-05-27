#pragma once
#include <iostream>
#include <string>
#include "TableOpen.h"
#include "TableChain.h"
#include <math.h>
#include <time.h>
using namespace std;

int randChar() {
    return (rand() % 26);
}

string SRand() {
    srand(time(0));
    string str;
    int lenght = rand() % 6 + 5;
    for (int i = 0; i < lenght; i++) {
        char c = (90 - randChar());
        str += c;
    }
    return str;
}

void testTable() {
    srand(time(0));
    int size, k;
    double alpha;
    cout << "Введите количество элементов: ";
    cin >> size;
    cout << "Введите заполненность хеш-таблицы: ";
    cin >> alpha;
    TableOpen<string, int>* tableOpen = new TableOpen<string, int>(size);
    TableChain<string, int>* tableChain = new TableChain<string, int>(size);
    k = tableOpen->getCapacity() * alpha;
    cout << "items count (ОА): " << tableOpen->getCapacity() << endl;
    cout << "items count (ЦК): " << tableChain->getCapacity() << endl;

    string* arr = new string[k];

    int I1 = 0, D1 = 0, S1 = 0,
        I2 = 0, D2 = 0, S2 = 0;

    for (int i = 0; i < k; i++) {
        arr[i] = SRand();
        tableOpen->Insert(arr[i], 1);
        tableChain->Insert(arr[i], 1);
    }

    for (int i = 0; i < k / 2; i++) {
        if (i % 10 == 0) {// 10% промаха
            // удаление случайного элемента
            tableOpen->Delete(SRand());
            D1 += tableOpen->counter;

            tableChain->Delete(SRand());
            D2 += tableChain->counter;

            // вставка уже существующего элемента
            tableOpen->Insert(arr[rand() % k], 1);
            I1 += tableOpen->counter;

            tableChain->Insert(arr[rand() % k], 1);
            I2 += tableChain->counter;

            // поиск по случайному ключу
            try {
                tableOpen->Data(SRand());
                S1 += tableOpen->counter;
            }
            catch (int& ex) {}
            try {
                tableChain->Data(SRand());
                S2 += tableChain->counter;
            }
            catch (int& ex) {}
        }
        else {
            // удаление существующего ключа
            int del = rand() % k;
            tableOpen->Delete(arr[del]);
            D1 += tableOpen->counter;

            tableChain->Delete(arr[del]);
            D2 += tableChain->counter;

            // вставка с новым ключом
            string newKey = SRand();
            tableOpen->Insert(newKey, 1);
            I1 += tableOpen->counter;

            tableChain->Insert(newKey, 1);
            I2 += tableChain->counter;

            arr[del] = newKey;

            // поиск существующего ключа
            try {
                tableChain->Data(arr[rand() % k]);
                S2 += tableChain->counter;
            }
            catch (int& ex) {}
            try {
                tableChain->Data(arr[rand() % k]);
                S2 += tableChain->counter;
            }
            catch (int& ex) {}
        }


        
    }
    cout << "Хеш-таблица с открытой адресацией:\n";
    cout << "items count: " << tableOpen->getSize() << endl;
    cout << "alpha: " << (double)tableOpen->getSize() / (double)tableOpen->getCapacity() << endl;
    cout << "count insert: " << double(I1) / double(k) * 2.0 << endl;
    cout << "count delete: " << double(D1) / double(k) * 2.0 << endl;
    cout << "count search: " << double(S1) / double(k) * 2.0 << endl;
    delete tableOpen;
    cout << "Хеш-таблица с цепочками коллизий:\n";
    cout << "items count: " << tableChain->getSize() << endl;
    cout << "alpha: " << (double)tableChain->getSize() / (double)tableChain->getCapacity() << endl;
    cout << "count insert: " << double(I2) / double(k) * 2.0 << endl;
    cout << "count delete: " << double(D2) / double(k) * 2.0 << endl;
    cout << "count search: " << double(S2) / double(k) * 2.0 << endl;
    delete tableChain;

    delete[] arr;
}

void testXI() {
    srand(time(0));
    int N, delta;
    long long M;
    cout << "Количество вставляемых элементов: ";
    cin >> N;

    //Выбираем размер из чисел Мерсене
    int sizes[] = { 3, 7, 13, 31, 61, 127, 251, 509,
                   1021, 2039, 4093, 8191, 16381, 32749, -1 };
    delta = N - sizes[0];
    long long res = 0;
    while (sizes[res + 1] != -1 && abs(sizes[res + 1] - N) < delta) {
        ++res;
        delta = abs(sizes[res] - N);
    }
    M = sizes[res];
    cout << "Размер массива: " << M << endl;

    //Создаём массив счётчиков
    int* counters = new int[M];
    for (int i = 0; i < M; ++i)
        counters[i] = 0;
    //Тестирование
    string val;
    int key;
    cout << SRand() << endl;
    for (int i = 0; i < 20 * M; ++i) {
        val = SRand();
        res = 0;
        for (int i = 0; i < val.length(); i++) {
            res += val[val.length() - i - 1] * pow(26, i);
        }
        double A = 0.6180339887;
        long long h = M * fmodl(res * A, 1.0);
        (counters[h])++;
    }

    //Рассчёт результата
    double m1 = M - sqrt((double)M);
    double m2 = M + sqrt((double)M);
    double hi = 0;
    for (int i = 0; i < M; ++i)
        hi += (counters[i] - 20.0) * (counters[i] - 20.0);
    hi /= 20.0;

    cout << "Результаты [m - sqrt(m)] [XI] [m + sqrt(m)]:\n";
    cout << '[' << m1 << "] [" << hi << "] [" << m2 << "]\n";
    delete[] counters;
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
    string mainMenu = "1 - Хеш-таблица с открытой адресацией\n2 - Хеш-таблица с цепочками коллизий\n3 - тестирование трудоемкости операций АТД\n4 - оценка хи-квадрат\n0 - выход\n";
    string menuTables = "\n1 - опрос размера таблицы\n2 - опрос количества элементов в таблице\n3 - опрос пустоты таблицы\n4 - очистка таблицы\n5 - поиск элемента по ключу k\n6 - вставка элемента по ключу k\n7 - удаление элемента по ключу k\n8 - запрос прямого итератора begin()\n9 - запрос \"неустановленного\" прямого итератора end()\n10 - доступ по чтению к значению текущего элемента *\n11 - доступ по записи к текущему значению *\n12 - переход к следующему элементу в хеш-таблице\n13 - проверка равенства прямому итератору begin()\n14 - проверка равенства прямому итератору end()\n15 - вывод структуры хеш-таблицы на экран\n16 - опрос числа проб, выполненных последней операцией\n0 - выход в главное меню\n";
    cout << "Главное меню:\n" << mainMenu;
    while (mainMode != 0) {
        cout << "> ";
        cin >> mainMode;
        switch (mainMode) {
        case 1:
            cout << "Введите размер хеш-таблицы: ";
            cin >> size;
            tableOpen = new TableOpen<string, int>(size);
            cout << "Меню таблиц:\n" << menuTables;
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
            cout << "Меню таблиц:\n" << menuTables;
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
            testTable();
            break;
        case 4:
            testXI();
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