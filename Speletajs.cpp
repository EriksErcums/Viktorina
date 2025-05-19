#include "Speletajs.h"
#include <iomanip>
#include <algorithm>
#include <iostream>
#include "SpeluParvaldnieks.h"
#include "PaligFunkcijas.h"
using namespace std;

void Speletajs::speletSpeli(SekmjuZurnals& zurnals, SpeluParvaldnieks& parvaldnieks) {
    int spelesId;
    cout << "Pieejamās spēles: \n";
    parvaldnieks.iegutPieejamasSpeles();
    spelesId = dabutSpelesId(parvaldnieks.getPieejamasSpeles(), "Kuru spēli spēlēsi? (Ievadi spēles ID): ");
    for (Spele& s : parvaldnieks.getPieejamasSpeles() ) {
        if (s.getId() == spelesId) {
            SpelesProtokols protokls(&s, getId(), getLietotajvards());
            s.saktSpeli(protokls);
            pievienotProtokolu(protokls);
            zurnals.pievienotProtokolu(protokls);
            speletasSpeles++;
            parvaldnieks.parbauditSasniegumus(*this, protokls);
            break;
        }
    }
}

// sakārto protokolus balstoties uz punktu skaitu un pavadīto laiku:
void Speletajs::paraditLabakasSpeles(SpeluParvaldnieks& parvaldnieks) {
    sort(spelesProtokoli.begin(), spelesProtokoli.end(), [&parvaldnieks](SpelesProtokols& a, SpelesProtokols& b) {
        int laiksA = parvaldnieks.konverteUzSekundem(a.getBeigas()) - parvaldnieks.konverteUzSekundem(a.getSakums());
        int laiksB = parvaldnieks.konverteUzSekundem(b.getBeigas()) - parvaldnieks.konverteUzSekundem(b.getSakums());

        int rezultatsA = a.getPunkti() - 10 * laiksA;
        int rezultatsB = b.getPunkti() - 10 * laiksB;

        return rezultatsA > rezultatsB;
    });

    cout << "Tavas labākās spēles: \n";

        for (int i = 0; i < 3 && i < spelesProtokoli.size(); i++) {
            SpelesProtokols& protokols = spelesProtokoli[i];
            int laiks = parvaldnieks.konverteUzSekundem(protokols.getBeigas()) - parvaldnieks.konverteUzSekundem(protokols.getSakums());
            int min = laiks / 60;
            int sek = laiks % 60;
            Spele spele = protokols.getSpele();
            cout << "Spēles ID: " << spele.getId()
            << ", nosaukums: " << spele.getNosaukums()
            << ", rezultāts: " << protokols.getPunkti()
            << ", laiks: " << min << ":" << setw(2) << setfill('0') << sek << "\n";
        }
}


