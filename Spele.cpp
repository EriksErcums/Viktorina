#include "Spele.h"
#include "SpelesProtokols.h"
#include <iostream>

using namespace std;

void Spele::saktSpeli(){
    rezultats = 0;
    SpelesProtokols protokols(this);
    int x = 1; //Jautajuma skaititajs
    string protokulaTeksts = "";

    cout << "Sākam spēli: " << nosaukums << endl << endl;

    for(auto & i : jautajumi){
        i.paradiJautajumu();

        int atbilde;
        cout << "Tava atbilde (ievadi skaitli): ";
        cin >> atbilde;

        protokulaTeksts += to_string(x) + ".jaut. Spēlētāja atbilde: " + to_string(atbilde);

        if(i.parbaudaJautajumu(atbilde)){
            cout << "Pareizi!" << endl;
            protokulaTeksts += " . ir pareiza";
            rezultats++;
        } else{
            cout << "Nepareizi!" << endl;
            protokulaTeksts += " . ir nepareiza";
        }
        protokols.pievienotDarbibu(protokulaTeksts);
        protokulaTeksts = "";
        x++;
    }
    protokols.spelesBeigas();
    //TODO: Vaig kaut ka to protokolu kaut kur pievienot

    cout << "Spēle pabeigta! Tu ieguvi " << rezultats << " punktus no " << maxPunkti << "." << endl;
}

