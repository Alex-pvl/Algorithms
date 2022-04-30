#pragma once
#include <iostream>
#include <string>
#include "BST.cpp"
#include "RandTree.cpp"
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
    BST<INT_64, int> tree1;
    RandTree<INT_64, int> tree2;
    INT_64* m = new INT_64[n];
    INT_64 key;
    int ind;
    sRand();
    for (int i = 0; i < n; i++) {
        m[i] = LineRand();
        tree1.put(m[i], 1);
        tree2.put(m[i], 1);
    }
    cout << "items count BST: " << tree1.getSize() << endl;
    cout << "items count RND: " << tree2.getSize() << endl;
    double I1 = 0, I2 = 0;
    double D1 = 0, D2 = 0;
    double S1 = 0, S2 = 0;
    tree1.clearCount();
    tree2.clearCount();
    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0) {
            key = LineRand();

            tree1.clearCount();
            tree1.remove(key);
            D1+=tree1.countNodes();

            tree2.clearCount();
            tree2.remove(key);
            D2+=tree2.countNodes();

            ind = rand() % n;

            tree1.clearCount();
            tree1.put(m[ind], 1);
            I1+=tree1.countNodes();

            tree2.clearCount();
            tree2.put(m[ind], 1);
            I2 += tree2.countNodes();

            key = LineRand();

            try {
                tree1.clearCount();
                tree1.get(LineRand());
                S1+=tree1.countNodes(); 
            }
            catch (const exception e) {
                S1+=tree1.countNodes(); 
            }
            try {
                tree2.clearCount();
                tree2.get(LineRand());
                S2 += tree2.countNodes();
            }
            catch (const exception e) {
                S2 += tree2.countNodes();
            }
        }
        else { // 90%
            ind = rand() % n;

            tree1.clearCount();
            tree1.remove(m[ind]);
            D1+=tree1.countNodes();

            tree2.clearCount();
            tree2.remove(m[ind]);
            D2 += tree2.countNodes();

            key = LineRand();

            tree1.clearCount();
            tree1.put(key, 1);
            I1+=tree1.countNodes();

            tree2.clearCount();
            tree2.put(key, 1);
            I2 += tree2.countNodes();

            m[ind] = key;
            ind = rand() % n;
            try {
                tree1.clearCount();
                tree1.get(m[ind]);
                S1+=tree1.countNodes();
            }
            catch (const exception e) {
                S1+=tree1.countNodes(); 
            }

            try {
                tree2.clearCount();
                tree2.get(m[ind]);
                S2 += tree2.countNodes();
            }
            catch (const exception e) {
                S2 += tree2.countNodes();
            }
        }
    }
    //вывод результатов:
    //вывод размера BST дерева после теста
    cout << "items count BST: " << tree1.getSize() << endl;
    //вывод размера Сбалансированного дерева после теста
    cout << "items count RND: " << tree2.getSize() << endl;
    //теоретической оценки трудоёмкости операций BST
    cout << "1.39*log2(n)= " << 1.39 * (log((double)n) / log(2.0)) << endl;
    //экспериментальной оценки трудоёмкости вставки BST-дерева
    cout << "Count insert BST: " << I1 / (n / 2) << endl; 
    //экспериментальной оценки трудоёмкости вставки Сбалансированного дерева
    cout << "Count insert RND: " << I2 / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления BST-дерева
    cout << "Count delete BST: " << D1 / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления Сбалансированного дерева
    cout << "Count delete RND: " << D2 / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости поиска BST-дерева
    cout << "Count search BST: " << S1 / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости поиска Сбалансированного дерева
    cout << "Count search RND: " << S2 / (n / 2) << endl;

    //освобождение памяти массива m[]
    delete[] m;
}

// Тест трудоёмкости операций вырожденного BST - дерева
void test_ord(int n) {
    BST<INT_64, int> tree;
    RandTree<INT_64, int> tree2;
    INT_64* m = new INT_64[n];
    for (int i = 0; i < n; i++) {
        m[i] = i * 10000;
        tree.put(m[i], 1);
        tree2.put(m[i], 1);
    }
    cout << "items count BST: " << tree.getSize() << endl;
    cout << "items count RND: " << tree2.getSize() << endl;
    double I = 0, I2 = 0;
    double D = 0, D2 = 0;
    double S = 0, S2 = 0;
    sRand();
    tree.clearCount();
    tree2.clearCount();
    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0) {
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2);

            tree.clearCount();
            tree.remove(k);
            D += tree.countNodes();
            tree2.clearCount();
            tree2.remove(k);
            D2 += tree2.countNodes();

            int ind = rand() % n;

            tree.clearCount();
            tree.put(m[ind], 1);
            I += tree.countNodes();
            tree2.clearCount();
            tree2.put(m[ind], 1);
            I2 += tree2.countNodes();

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

            try {
                tree2.clearCount();
                tree2.get(k);
                S2 += tree2.countNodes();
            }
            catch (const exception e) {
                S2 += tree2.countNodes();
            }
        }
        else //90% успешных операций
        {
            int ind = rand() % n;
            tree.clearCount();
            tree.remove(m[ind]);
            D += tree.countNodes();
            tree2.clearCount();
            tree2.remove(m[ind]);
            D2 += tree2.countNodes();
            int k = LineRand() % (10000 * n);
            k = k + k % 2; // случайный чётный ключ
            tree.clearCount();
            tree.put(k, 1);
            I += tree.countNodes();
            tree2.clearCount();
            tree2.put(k, 1);
            I2 += tree2.countNodes();;
            m[ind] = k;
            ind = rand() % n;
            try {
                tree.clearCount();
                tree.get(m[ind]);
                S += tree.countNodes();;
            }
            catch (const exception e) {
                S += tree.countNodes();
            }
            try {
                tree2.clearCount();
                tree2.get(m[ind]);
                S2 += tree2.countNodes();;
            }
            catch (const exception e) {
                S2 += tree2.countNodes();
            }
        }
    }
    //вывод результатов:
    //вывод размера дерева после теста
    cout << "items count: " << tree.getSize() << endl;
    //теоретической оценки трудоёмкости операций BST
    cout << "n/2 = " << n / 2 << endl;
    //экспериментальной оценки трудоёмкости вставки BST-дерева
    cout << "Count insert BST: " << I / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости вставки Сбалансированного дерева
    cout << "Count insert RND: " << I2 / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления BST-дерева
    cout << "Count delete BST: " << D / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления Сбалансированного дерева
    cout << "Count delete RND: " << D2 / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости поиска BST-дерева
    cout << "Count search BST: " << S / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости поиска Сбалансированного дерева
    cout << "Count search RND: " << S2 / (n / 2) << endl;
    //освобождение памяти массива m[]
    delete[] m;
}

int main() {
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
            /*for (int i = 200; i <= 2000; i += 200) {
                test_rand(i);
            }*/
            break;
        case 28:
            cin >> n;
            test_ord(n);
            /*for (int i = 200; i <= 2000; i += 200) {
                test_ord(i);
            }*/
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
}