#include "Spele.h"
#include <iostream>

using namespace std;

void Spele::saktSpeli(){
    rezultats = 0;
    cout << "Sākam spēli: " << nosaukums << endl << endl;

    for(auto & i : jautajumi){
        i.paradiJautajumu();

        int atbilde;
        cout << "Tava atbilde (ievadi skaitli): ";
        cin >> atbilde;

        if(i.parbaudaJautajumu(atbilde)){
            cout << "Pareizi!" << endl;
            rezultats++;
        } else cout << "Nepareizi!" << endl;
    }

    cout << "Spēle pabeigta! Tu ieguvi " << rezultats << " punktus no " << maxPunkti << "." << endl;
}

