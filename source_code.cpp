#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class Passenger {
public:
    string nm;
    int ag;
    float fr;

    Passenger(string n, int a, float f) {
        nm = n;
        ag = a;
        fr = f;
    }

    void show() {
        cout << left << setw(20) << nm
             << setw(10) << ag
             << "Rs. " << fr << endl;
    }
};

class FareSys {
    vector<Passenger> list;
    float total = 0;

public:
    void add() {
        string n;
        int a;
        float f;

        cout << "Enter name: ";
        cin.ignore();
        getline(cin, n);
        cout << "Enter age: ";
        cin >> a;
        cout << "Enter fare: Rs. ";
        cin >> f;

        list.push_back(Passenger(n, a, f));
        total += f;

        cout << "Passenger added!\n";
    }

    void showAll() {
        cout << "\n--- Passenger List ---\n";
        cout << left << setw(20) << "Name" 
             << setw(10) << "Age"
             << "Fare\n";
        cout << "------------------------------------\n";
        for (auto &p : list) {
            p.show();
        }
    }

    void showTotal() {
        cout << "\nTotal Fare: Rs. " << total << endl;
    }

    void search() {
        string n;
        cout << "Enter name to search: ";
        cin.ignore();
        getline(cin, n);

        bool found = false;
        for (auto &p : list) {
            if (p.nm == n) {
                cout << "\nFound:\n";
                p.show();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Not found!\n";
        }
    }

    void save() {
        ofstream file("passengers.txt");
        if (!file) {
            cout << "Error saving!\n";
            return;
        }
        for (auto &p : list) {
            file << p.nm << "," << p.ag << "," << p.fr << "\n";
        }
        file.close();
        cout << "Data saved.\n";
    }

    void load() {
        ifstream file("passengers.txt");
        if (!file) return;

        list.clear();
        total = 0;

        string n;
        int a;
        float f;
        while (file >> ws && getline(file, n, ',')) {
            file >> a;
            file.ignore();
            file >> f;
            list.push_back(Passenger(n, a, f));
            total += f;
        }
        file.close();
        cout << "Data loaded.\n";
    }
};

int main() {
    FareSys sys;
    sys.load();

    int ch;
    do {
        cout << "\n--- Fare Collection ---\n";
        cout << "1. Add Passenger\n";
        cout << "2. Show All\n";
        cout << "3. Show Total Fare\n";
        cout << "4. Search Passenger\n";
        cout << "5. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch) {
        case 1: sys.add(); break;
        case 2: sys.showAll(); break;
        case 3: sys.showTotal(); break;
        case 4: sys.search(); break;
        case 5: sys.save(); cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (ch != 5);

    return 0;
}
