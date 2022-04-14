#include <iostream>
#include <string>
#include "BST.cpp"
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    int mode = -1, mode2 = -1;
    BST<int, int> tree1;
    BST<int, int> tree2;
    BST<int, int>::Iterator iter(tree1);
    BST<int, int>::RevIterator riter(tree1);
    BST<int, int>::Iterator checkBegin;
    BST<int, int>::RevIterator checkRBegin;
    BST<int, int>::Iterator checkEnd;
    BST<int, int>::RevIterator checkREnd;
    string menu = "\n1 - Опрос размера дерева\n2 - Очистка дерева\n3 - Проверка дерева на пустоту\n4 - Доступ по чтению к данным по ключу\n5 - Доступ по записи к данным по ключу\n6 - Включение данных с заданным ключом\n7 - Удаление данных с заданным ключом\n8 - Вывод на экран последовательности ключей при обходе узлов дерева по схеме L -> R -> t\n9 - Объединение двух BST-деревьев\n10 - Запрос прямого итератора\n11 - Запрос \"неустановленного\" прямого итератора\n12 - Операция доступа по чтению к текущему значению прямого итератора *\n13 - Операция доступа по записи к текущему значению прямого итератора *\n14 - Операция инкремента для перехода к следующему значению в списке для прямого итератора\n15 - Проверка равенства прямого итератора узлу с минимальным ключом\n16 - Проверка равенства прямого итератора \"неустановленному\" прямому итератору\n17 - Проверка неравенства прямого итератора узлу с минимальным ключом\n18 - Проверка неравенства прямого итератора \"неустановленному\" прямому итератору\n19 - Запрос обратного итератора\n20 - Запрос \"неустановленного\" обратного итератора\n21 - Операция доступа по чтению к текущему значению обратного итератора *\n22 - Операция доступа по записи к текущему значению обратного итератора *\n23 - Операция инкремента для перехода к предыдущему по ключу узлу в дереве для прямого итератора\n24 - Проверка равенства обратного итератора узлу с максимальным ключом\n25 - Проверка равенства обратного итератора \"неустановленному\" обратному итератору\n26 - Проверка неравенства обратного итератора узлу с максимальным ключом\n27 - Проверка неравенства обратного итератора \"неустановленному\" обратному итератору\n28 - Работа с деревом #2\n29 - Вывод меню\n0 - Завершение программы\n";
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
            tree1.print();
            cout << endl;
            break;
        case 9:
            //TODO
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
                    while(true) {
                        cin >> key2;
                        if (key2 == -1337) break;
                        cin >> value2;
                        tree2.put(key2, value2);
                    }
                    break;
                case 2:
                    tree2.print();
                    cout << endl;
                    break;
                default:
                    break;
                }
            }
            cout << "\nГлавное меню: " << endl;
            break;
        case 29:
            cout << "Доступные команды:" << menu << endl;
            break;
        case 0:
            return -1;
        default:
            break;
        }

    }
    return 0;
}