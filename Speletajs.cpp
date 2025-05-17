#include "Speletajs.h"
#include <iostream>
#include "SpeluParvaldnieks.h"
#include "PaligFunkcijas.h"
using namespace std;

void Speletajs::speletSpeli(SpeluParvaldnieks& parvaldnieks) {
    int spelesId;
    cout << "Kuru spēli spēlēsi? (Ievadi spēles ID): ";
    parvaldnieks.iegutPieejamasSpeles();
    spelesId = dabutSpelesId(parvaldnieks.getPieejamasSpeles(), "Kuru spēli spēlēsi? (Ievadi spēles ID): ");
    for (Spele& s : parvaldnieks.getPieejamasSpeles() ) {
        if (s.getId() == spelesId) {
            SpelesProtokols protokls(&s, getId(), getLietotajvards());
            s.saktSpeli(protokls);
            pievienotProtokolu(protokls);
            speletasSpeles++;
            break;
        }
    }
}

