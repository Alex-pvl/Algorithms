#include <iostream>
#include <string>
#include "BST.cpp"
#include <math.h>
#include <time.h>
using namespace std;
typedef unsigned long long INT_64;

//переменная и константы генератора LineRand()
static INT_64 RRand = 15750;
const const INT_64 mRand = (1 << 63) - 1;
const const INT_64 aRand = 6364136223846793005;
const const INT_64 cRand = 1442695040888963407;

//функция установки первого случайного числа от часов
//компьютера
void sRand() {
    srand(time(0));
    RRand = (INT_64)rand();
}

//функция генерации случайного числа
//линейный конгруэнтный генератор Xi+1=(a*Xi+c)%m
//habr.com/ru/post/208178
INT_64 LineRand() {
    INT_64 y1, y2;
    y1 = (aRand * RRand + cRand) % mRand;
    y2 = (aRand * y1 + cRand) % mRand;
    RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 & 0xFFFFFFFF00000000LL) >> 32;
    return RRand;
}

//Тест трудоёмкости операций случайного BST-дерева
void test_rand(int n) {
    BST<INT_64, int> tree;
    INT_64* m = new INT_64[n];
    sRand();
    for (int i = 0; i < n; i++) {
        m[i] = LineRand();
        tree.put(m[i], 1);
    }
    cout << "items count: " << tree.getSize() << endl;
    double I = 0;
    double D = 0;
    double S = 0;
    tree.clearCount();
    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0) {
            tree.clearCount();
            tree.remove(LineRand());
            D+=tree.countNodes();
            tree.clearCount();
            tree.put(m[rand() % n], 1);
            I+=tree.countNodes();
            try {
                tree.clearCount();
                tree.get(LineRand());
                S+=tree.countNodes(); 
            }
            catch (const exception e) {
                S+=tree.countNodes(); 
            }
        }
        else {
            int ind = rand() % n;
            tree.clearCount();
            tree.remove(m[ind]);
            D+=tree.countNodes();
            INT_64 key = LineRand();
            tree.clearCount();
            tree.put(key, 1);
            I+=tree.countNodes();
            m[ind] = key;
            try {
                tree.clearCount();
                tree.get(m[rand() % n]);
                S+=tree.countNodes();
            }
            catch (const exception e) {
                S+=tree.countNodes(); 
            }
        }
    }
    //вывод результатов:
    //вывод размера дерева после теста
    cout << "items count: " << tree.getSize() << endl;
    //теоретической оценки трудоёмкости операций BST
    cout << "1.39*log2(n)= " << 1.39 * (log((double)n) / log(2.0)) << endl;
    //экспериментальной оценки трудоёмкости вставки
    cout << "Count insert: " << I / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления
    cout << "Count delete: " << D / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости поиска
    cout << "Count search: " << S / (n / 2) << endl;
    //освобождение памяти массива m[]
    delete[] m;
}

// Тест трудоёмкости операций вырожденного BST - дерева
void test_ord(int n) {
    BST<INT_64, int> tree;
    INT_64* m = new INT_64[n];
    for (int i = 0; i < n; i++) {
        m[i] = i * 10000;
        tree.put(m[i], 1);
    }
    cout << "items count: " << tree.getSize() << endl;
    double I = 0;
    double D = 0;
    double S = 0;
    sRand();
    tree.clearCount();
    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0) {
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2); 
            tree.clearCount();
            tree.remove(k);
            D += tree.countNodes();
            tree.clearCount();
            tree.put(m[rand() % n], 1);
            I += tree.countNodes();
            k = LineRand() % (10000 * n);
            k = k + !(k % 2); 
            try {
                tree.clearCount();
                tree.get(k);
                S += tree.countNodes();
            }
            catch (const exception e) {
                S += tree.countNodes();
            }
        }
        else //90% успешных операций
        {
            int ind = rand() % n;
            tree.clearCount();
            tree.remove(m[ind]);
            D += tree.countNodes();;
            int k = LineRand() % (10000 * n);
            k = k + k % 2; // случайный чётный ключ
            tree.clearCount();
            tree.put(k, 1);
            I += tree.countNodes();;
            m[ind] = k;
            try {
                tree.clearCount();
                tree.get(m[rand() % n]);
                S += tree.countNodes();;
            }
            catch (const exception e) {
                S += tree.countNodes(); 
            }
        }
    }
    //вывод результатов:
    //вывод размера дерева после теста
    cout << "items count: " << tree.getSize() << endl;
    //теоретической оценки трудоёмкости операций BST
    cout << "n/2 = " << n / 2 << endl;
    //экспериментальной оценки трудоёмкости вставки
    cout << "Count insert: " << I / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления
    cout << "Count delete: " << D / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости поиска
    cout << "Count search: " << S / (n / 2) << endl;
    //освобождение памяти массива m[]
    delete[] m;
}

int main() {
    setlocale(LC_ALL, "ru");
    int mode = -1, mode2 = -1, modePrint;
    BST<int, int> tree1;
    BST<int, int> tree2;
    BST<int, int>::Iterator iter(tree1);
    BST<int, int>::RevIterator riter(tree1);
    BST<int, int>::Iterator checkBegin;
    BST<int, int>::RevIterator checkRBegin;
    BST<int, int>::Iterator checkEnd;
    BST<int, int>::RevIterator checkREnd;
    string menu = "\n1 - Опрос размера дерева\n2 - Очистка дерева\n3 - Проверка дерева на пустоту\n4 - Доступ по чтению к данным по ключу\n5 - Доступ по записи к данным по ключу\n6 - Включение данных с заданным ключом\n7 - Удаление данных с заданным ключом\n8 - Вывод дерева на экран\n9 - Объединение двух BST-деревьев\n10 - Запрос прямого итератора\n11 - Запрос \"неустановленного\" прямого итератора\n12 - Операция доступа по чтению к текущему значению прямого итератора *\n13 - Операция доступа по записи к текущему значению прямого итератора *\n14 - Операция инкремента для перехода к следующему значению в списке для прямого итератора\n15 - Проверка равенства прямого итератора узлу с минимальным ключом\n16 - Проверка равенства прямого итератора \"неустановленному\" прямому итератору\n17 - Проверка неравенства прямого итератора узлу с минимальным ключом\n18 - Проверка неравенства прямого итератора \"неустановленному\" прямому итератору\n19 - Запрос обратного итератора\n20 - Запрос \"неустановленного\" обратного итератора\n21 - Операция доступа по чтению к текущему значению обратного итератора *\n22 - Операция доступа по записи к текущему значению обратного итератора *\n23 - Операция инкремента для перехода к предыдущему по ключу узлу в дереве для прямого итератора\n24 - Проверка равенства обратного итератора узлу с максимальным ключом\n25 - Проверка равенства обратного итератора \"неустановленному\" обратному итератору\n26 - Проверка неравенства обратного итератора узлу с максимальным ключом\n27 - Проверка неравенства обратного итератора \"неустановленному\" обратному итератору\n28 - Работа с деревом #2\n29 - Запустить тест трудоёмкости операций случайного BST-дерева\n30 - Запустить тест трудоёмкости операций вырожденного BST-дерева\n31 - Вывод меню\n32 - Вывод на экран последовательности ключей при обходе узлов дерева по схеме L -> R -> t\n0 - Завершение программы\n";
    string menuForSecondTree = "\n1 - Заполнение\n2 - Вывод на экран последовательности ключей при обходе узлов дерева по схеме L -> R -> t\n0 - Выход в главное меню\n";
    cout << "Доступные команды:" << menu << endl;
    int value, key, newValue, treeSize;
    int key2 = 0, value2;
    while (mode != 0) {
        cout << "> ";
        cin >> mode;
        switch (mode)
        {
        case 1:
            treeSize = tree1.getSize();
            cout << treeSize << endl;
            break;
        case 2:
            tree1.clear();
            cout << "Дерево очищено" << endl;
            break;
        case 3:
            cout << tree1.isEmpty() << endl;
            break;
        case 4:
            cin >> key;
            try
            {
                cout << tree1.get(key) << endl;
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
                tree1.get(key) = newValue;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 6:
            cin >> key >> value;
            cout << tree1.put(key, value) << endl;
            break;
        case 7:
            cin >> key;
            cout << tree1.remove(key) << endl;
            break;
        case 8:
            tree1.printVert();
            break;
        case 9:
            tree1.join(tree2);
            break;
        case 10:
            iter = tree1.begin();
            break;
        case 11:
            iter = tree1.end();
            break;
        case 12:
            try
            {
                cout << *iter << endl;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 13:
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
        case 14:
            try
            {
                ++iter;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 15:
            checkBegin = tree1.begin();
            cout << (iter == checkBegin) << endl;
            break;
        case 16:
            checkEnd = tree1.end();
            cout << (iter == checkEnd) << endl;
            break;
        case 17:
            checkBegin = tree1.begin();
            cout << (iter != checkBegin) << endl;
            break;
        case 18:
            checkEnd = tree1.end();
            cout << (iter != checkEnd) << endl;
            break;
        case 19:
            riter = tree1.rbegin();
            break;
        case 20:
            riter = tree1.rend();
            break;
        case 21:
            try
            {
                cout << *riter << endl;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 22:
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
        case 23:
            try
            {
                ++riter;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 24:
            checkRBegin = tree1.rbegin();
            cout << (riter == checkRBegin) << endl;
            break;
        case 25:
            checkREnd = tree1.rend();
            cout << (riter == checkREnd) << endl;
            break;
        case 26:
            checkRBegin = tree1.rbegin();
            cout << (riter != checkRBegin) << endl;
            break;
        case 27:
            checkREnd = tree1.rend();
            cout << (riter != checkREnd) << endl;
            break;
        case 28:
            mode2 = -1;
            cout << menuForSecondTree << endl;
            while (mode2 != 0) {
                cout << "> ";
                cin >> mode2;
                switch (mode2) {
                case 1:
                    tree2.clear();
                    while(true) {
                        cin >> key2;
                        if (key2 == -1) break;
                        cin >> value2;
                        tree2.put(key2, value2);
                    }
                    break;
                case 2:
                    tree2.printVert();
                    cout << endl;
                    break;
                default:
                    break;
                }
            }
            cout << "\nГлавное меню: " << endl;
            break;
        case 29:
            test_rand(5000);
            break;
        case 30:
            test_ord(5000);
            break;
        case 31:
            cout << "Доступные команды:" << menu << endl;
            break;
        case 32:
            tree1.printLRT();
            break;
        case 0:
            return -1;
        default:
            break;
        }
    }
    return 0;
}