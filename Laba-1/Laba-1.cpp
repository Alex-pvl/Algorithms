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
    string str;
    int line = rand() % 5 + 5;
    for (int i = 0; i < line; i++) {
        char B = (90 - randChar());
        str += B;
    }
    return str;
}

void testTableOpen() {
    srand(time(0));
    int size, k1;
    double alpha;
    cout << "Введите количество элементов: ";
    cin >> size;
    cout << "Введите заполненность хеш-таблицы: ";
    cin >> alpha;
    TableOpen<string, int>* tableOpen = new TableOpen<string, int>(size);
    k1 = tableOpen->getCapacity() * alpha;
    cout << "items count (ОА): " << tableOpen->getCapacity() << endl;
    string* arr1 = new string[k1];
    int I1 = 0, D1 = 0, S1 = 0;
    for (int i = 0; i < k1; i++) {
        arr1[i] = SRand();
        tableOpen->Insert(arr1[i], 1);
    }
    for (int i = 0; i < k1 / 2; i++) {
        if (i % 10 == 0) {// 10% промаха
            // удаление случайного элемента
            tableOpen->Delete(SRand());
            D1 += tableOpen->getCounter();
            // вставка уже существующего элемента
            tableOpen->Insert(arr1[rand() % k1], 1);
            I1 += tableOpen->getCounter();
            // поиск по случайному ключу
            try {
                tableOpen->Data(SRand());
                S1 += tableOpen->getCounter();
            }
            catch (int& ex) {}
        }
        else {
            // удаление существующего ключа
            int del = rand() % k1;
            tableOpen->Delete(arr1[del]);
            D1 += tableOpen->getCounter();
            // вставка с новым ключом
            string newKey = SRand();
            tableOpen->Insert(newKey, 1);
            I1 += tableOpen->getCounter();
            arr1[del] = newKey;
            // поиск существующего ключа
            try {
                tableOpen->Data(arr1[rand() % k1]);
                S1 += tableOpen->getCounter();
            }
            catch (int& ex) {}
        }
    }
    cout << "Хеш-таблица с открытой адресацией:\n";
    cout << "items count: " << tableOpen->getSize() << endl;
    cout << "alpha: " << (double)tableOpen->getSize() / (double)tableOpen->getCapacity() << endl;
    cout << "count insert: " << double(I1) / double(k1) * 2.0 << endl;
    cout << "count delete: " << double(D1) / double(k1) * 2.0 << endl;
    cout << "count search: " << double(S1) / double(k1) * 2.0 << endl;
    delete tableOpen;
    delete[] arr1;
}

void testTableChain() {
    srand(time(0));
    int size, k2;
    double alpha;
    cout << "Введите количество элементов: ";
    cin >> size;
    cout << "Введите заполненность хеш-таблицы: ";
    cin >> alpha;
    TableChain<string, int>* tableChain = new TableChain<string, int>(size);
    k2 = tableChain->getCapacity() * alpha;
    cout << "items count (ЦК): " << tableChain->getCapacity() << endl;
    string* arr2 = new string[k2];
    int I2 = 0, D2 = 0, S2 = 0;
    for (int i = 0; i < k2; i++) {
        arr2[i] = SRand();
        tableChain->Insert(arr2[i], 1);
    }
    for (int i = 0; i < k2 / 2; i++) {
        if (i % 10 == 0) {// 10% промаха
            // удаление случайного элемента
            tableChain->Delete(SRand());
            D2 += tableChain->getCounter();
            // вставка уже существующего элемента
            tableChain->Insert(arr2[rand() % k2], 1);
            I2 += tableChain->getCounter();
            // поиск по случайному ключу
            try {
                tableChain->Data(SRand());
                S2 += tableChain->getCounter();
            }
            catch (int& ex) {}
        }
        else {
            // удаление существующего ключа
            int del = rand() % k2;
            tableChain->Delete(arr2[del]);
            D2 += tableChain->getCounter();
            // вставка с новым ключом
            string newKey = SRand();
            tableChain->Insert(newKey, 1);
            I2 += tableChain->getCounter();
            arr2[del] = newKey;
            // поиск существующего ключа
            try {
                tableChain->Data(arr2[rand() % k2]);
                S2 += tableChain->getCounter();
            }
            catch (int& ex) {}
        }
    }
    cout << "Хеш-таблица с цепочками коллизий:\n";
    cout << "items count: " << tableChain->getSize() << endl;
    cout << "alpha: " << (double)tableChain->getSize() / (double)tableChain->getCapacity() << endl;
    cout << "count insert: " << double(I2) / double(k2) * 2.0 << endl;
    cout << "count delete: " << double(D2) / double(k2) * 2.0 << endl;
    cout << "count search: " << double(S2) / double(k2) * 2.0 << endl;
    delete tableChain;
    delete[] arr2;
}



void testXI() {
    cout << "Качество хэш-функции по критерию хи-квадрат\n";
    srand(time(0));

    //Опрос параметров тестирования
    int N, delta;
    long long M;
    cout << "Количество вставляемых элементов: ";
    cin >> N;

    //Выбираем размер из чисел Мерсене
    int sizes[] = { 4, 8, 16, 32, 64, 128, 256, 512,
                   1024, 2048, 4096, 8192, 16384, 32768, -1 };
    delta = N - sizes[0];
    long long index = 0;
    while (sizes[index + 1] != -1 && abs(sizes[index + 1] - N) < delta) {
        ++index;
        delta = abs(sizes[index] - N);
    }
    M = sizes[index];
    cout << "Размер массива: " << M << endl;

    //Создаём массив счётчиков
    int* counter = new int[M];
    for (int i = 0; i < M; ++i)
        counter[i] = 0;

    //Тестирование
    string val;
    int key;
    for (int i = 0; i < 20 * M; ++i) {
        val = SRand();
        index = 0;
        char k = val[0];
        index += (int)k - 64;
        for (int i = 1; val[i] != '\0'; i++) {
            k = val[i];
            index *= 26;
            index += (int)k - 64;
        }
        double A = 0.6180339887;
        long long h = M * fmodl(index * A, 1.0);
        (counter[h])++;
    }

    //Рассчёт результата
    double m1 = M - sqrt((double)M);
    double m2 = M + sqrt((double)M);
    double hi = 0;
    for (int i = 0; i < M; ++i)
        hi += (counter[i] - 20.0) * (counter[i] - 20.0);
    hi /= 20.0;

    cout << "Результаты [m - sqrt(m)] [XI] [m + sqrt(m)]:\n";
    cout << '[' << m1 << "] [" << hi << "] [" << m2 << "]\n";
    delete[] counter;
}

int main() {
    setlocale(LC_ALL, "ru");
    int mainMode = -1, tableMode1 = -1, tableMode2 = -1, size = 0;
    string key = "";
    int data = 0;
    TableOpen<string, int>* tableOpen = nullptr;
    TableChain<string, int>* tableChain = nullptr;
    TableOpen<string, int>::Iterator* iterOpen = nullptr;
    TableChain<string, int>::Iterator* iterChain = nullptr;
    string mainMenu = "1 - Хеш-таблица с открытой адресацией\n2 - Хеш-таблица с цепочками коллизий\n3 - тестирование трудоемкости операций хеш-таблицы с открытой адресацией\n4 - тестирование трудоемкости операций хеш-таблицы с цепочкой коллизий\n5 - оценка хи-квадрат\n0 - выход\n";
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
            iterOpen = new TableOpen<string, int>::Iterator(*tableOpen);
            while (tableMode1 != 0) {
                cout << "> ";
                cin >> tableMode1;
                switch (tableMode1) {
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
                    *iterOpen = tableOpen->begin();
                    break;
                case 9:
                    *iterOpen = tableOpen->end();
                    break;
                case 10:
                    try
                    {
                        cout << *(*iterOpen) << endl;
                    }
                    catch (int &a)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 11:
                    try
                    {
                        cin >> **iterOpen;
                    }
                    catch (...)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 12:
                    try
                    {
                        ++(*iterOpen);
                    }
                    catch (...)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 13:
                    cout << (*iterOpen == tableOpen->begin()) << endl;
                    break;
                case 14:
                    cout << (*iterOpen == tableOpen->end()) << endl;
                    break;
                case 15:
                    tableOpen->Print();
                    break;
                case 16:
                    cout << tableOpen->NumOfProbes();
                case 0:
                    cout << mainMenu << endl;
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
            iterChain = new TableChain<string, int>::Iterator(*tableChain);
            while (tableMode2 != 0) {
                cout << "> ";
                cin >> tableMode2;
                switch (tableMode2) {
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
                    *iterChain = tableChain->begin();
                    break;
                case 9:
                    *iterChain = tableChain->end();
                    break;
                case 10:
                    try
                    {
                        cout << **iterChain << endl;
                    }
                    catch (...)
                    {
                        cout << "Исключение\n";
                    }
                    break;
                case 11:
                    try
                    {
                        cin >> **iterChain;
                    }
                    catch (...)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 12:
                    try
                    {
                        ++(*iterChain);
                    }
                    catch (...)
                    {
                        cerr << "Исключение\n";
                    }
                    break;
                case 13:
                    cout << (*iterChain == tableChain->begin()) << endl;
                    break;
                case 14:
                    cout << (*iterChain == tableChain->end()) << endl;
                    break;
                case 15:
                    tableChain->Print();
                    break;
                case 16:
                    cout << tableChain->NumOfProbes();
                    break;
                case 0:
                    cout << mainMenu << endl;
                    break;
                default:
                    break;
                }
            }
            break;
        case 3:
            testTableOpen();
            break;
        case 4:
            testTableChain();
            break;
        case 5:
            testXI();
            break;
        case 0:
            return -1;
        }
    }
}
