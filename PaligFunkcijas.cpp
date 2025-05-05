#include "PaligFunkcijas.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "Spele.h"

using namespace std;

int dabutSpelesId(vector<Spele>& speles, const string& teksts) {
    int spelesID;

    while (true) {
        cout << teksts;
        cin >> spelesID;

        if (cin.fail()) {
            cin.clear();  // Notīra error flagus
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Atmet visu pārējo ievades rindu, lai netraucē turpmākām ievadēm.
            cout << "Ievadi veselu skaitli!\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (Spele& s : speles) {
            if (s.getId() == spelesID) {
                return spelesID;
            }
        }

        cout << "Ievadi derīgu spēles ID!\n";
    }
}

int skaitluIevade(const string& teksts, int minVertiba) {
    int vertiba;
    do {
        cout << teksts;
        cin >> vertiba;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (vertiba < minVertiba) {
            cout << "Skaitlim jābūt vismaz " << minVertiba << "!\n";
        }
    } while (vertiba < minVertiba);
    return vertiba;
}

string stringIevade(const string& teksts) {
    string ievade;
    do {
        cout << teksts;
        getline(cin, ievade);
        if (ievade.empty()) {
            cout << "Lauks nevar būt tukšs!\n";
        }
    } while (ievade.empty());
    return ievade;
}