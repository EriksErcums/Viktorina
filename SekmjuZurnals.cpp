#include "SekmjuZurnals.h"
#include <set>
#include <string>
#include <iostream>

#include "PaligFunkcijas.h"
using namespace std;

void SekmjuZurnals::apskatitKonkretusProt() {
    set<string> lietotaji;
    for (SpelesProtokols& protokols : visiProtokoli) {
        lietotaji.insert(protokols.getLietotajvardu());
    }
    vector<string> lietotajivector(lietotaji.begin(), lietotaji.end()); //konvertē set uz vector, lai var pieklut pec indeksa

    cout << "Pieejamie lietotāji: \n";
    for (int i = 0; i < lietotajivector.size(); i++) {
        cout << i + 1 << ". " << lietotajivector[i] << "\n";
    }
    int speletajs = skaitluIevade("Par kuru spēlētāju vēlies apskatīties protokolus? (Ievadi kārtas numuru): ", 1) - 1;
    while (speletajs >= lietotajivector.size()) {
        cout << "Kļūda: Ievadīts nederīgs kārtas numurs. Lūdzu, mēģini vēlreiz.\n";
        speletajs = skaitluIevade("Par kuru spēlētāju vēlies apskatīties protokolus? (Ievadi kārtas numuru): ", 1) - 1;
    }

    const string& izveletaisLietotajs = lietotajivector[speletajs];
    for (SpelesProtokols& protokols : visiProtokoli) {
        if (protokols.getLietotajvardu() == izveletaisLietotajs) {
            protokols.printProtokoluInfo();
        }
    }
}

