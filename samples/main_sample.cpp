#include "../include/ttablemanager.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
    TTableManager mgr;

    cout << "1 - insert polynomial" << endl;
    cout << "2 - find polynomial" << endl;
    cout << "3 - remove polynomial" << endl;
    cout << "4 - calc (p1 op p2)" << endl;
    cout << "5 - store result" << endl;
    cout << "0 - exit" << endl;
    cout << endl;

    int cmd;
    while (true)
    {
        cout << "> ";
        cin >> cmd;

        if (cmd == 0)
        {
            break;
        }
        else if (cmd == 1)
        {
            string name;
            int count;
            cout << "Name: ";
            cin >> name;
            cout << "Count of monoms: ";
            cin >> count;

            TPolinom p;
            for (int i = 0; i < count; i++)
            {
                double c;
                int ind;
                cout << "  coeff ind: ";
                cin >> c >> ind;
                TMonom m = { c, ind };
                p.AddMonom(m);
            }

            try
            {
                mgr.insert(name, p);
                cout << "Inserted: " << name << " = " << p << endl;
            }
            catch (const runtime_error& e)
            {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (cmd == 2)
        {
            string name;
            cout << "Name: ";
            cin >> name;

            TPolinom* p = mgr.find(name);
            if (p == nullptr)
                cout << "Not found: " << name << endl;
            else
                cout << name << " = " << *p << endl;
        }
        else if (cmd == 3)
        {
            string name;
            cout << "Name: ";
            cin >> name;

            try
            {
                mgr.remove(name);
                cout << "Removed: " << name << endl;
            }
            catch (const runtime_error& e)
            {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (cmd == 4)
        {
            string left, op, right;
            cout << "Enter: name1 op name2 (e.g. p1 + p2): ";
            cin >> left >> op >> right;

            TPolinom* pl = mgr.find(left);
            TPolinom* pr = mgr.find(right);

            if (pl == nullptr) { cout << "Not found: " << left << endl; continue; }
            if (pr == nullptr) { cout << "Not found: " << right << endl; continue; }

            try
            {
                TPolinom res;
                if (op == "+") res = *pl + *pr;
                else if (op == "-") res = *pl - *pr;
                else if (op == "*") res = *pl * *pr;
                else { cout << "Unknown operator" << endl; continue; }
                cout << "Result: " << res << endl;
            }
            catch (const runtime_error& e)
            {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (cmd == 5)
        {
            string name, left, op, right;
            cout << "Result name: ";
            cin >> name;
            cout << "Enter: name1 op name2 (e.g. p1 + p2): ";
            cin >> left >> op >> right;

            TPolinom* pl = mgr.find(left);
            TPolinom* pr = mgr.find(right);

            if (pl == nullptr) { cout << "Not found: " << left << endl; continue; }
            if (pr == nullptr) { cout << "Not found: " << right << endl; continue; }

            try
            {
                TPolinom res;
                if (op == "+") res = *pl + *pr;
                else if (op == "-") res = *pl - *pr;
                else if (op == "*") res = *pl * *pr;
                else { cout << "Unknown operator" << endl; continue; }

                mgr.insert(name, res);
                cout << "Stored: " << name << " = " << res << endl;
            }
            catch (const runtime_error& e)
            {
                cout << "Error: " << e.what() << endl;
            }
        }
        else
        {
            cout << "Unknown command" << endl;
        }
    }

    return 0;
}
