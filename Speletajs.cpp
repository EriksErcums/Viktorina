#include "Speletajs.h"
#include <iomanip>
#include <algorithm>
#include <iostream>
#include "LietotajuParvaldnieks.h"
#include "SpeluParvaldnieks.h"
#include "PaligFunkcijas.h"
using namespace std;

void Speletajs::speletSpeli(SekmjuZurnals& zurnals, SpeluParvaldnieks& spelu_parvaldnieks, LietotajuParvaldnieks& lietotaju_parvaldnieks) {

    if (spelu_parvaldnieks.getPieejamasSpeles().empty()) {
        cout << "Redaktors nav izveidojis nevienu spēli!\n";
        return;
    }

    int spelesId;
    cout << "Pieejamās spēles: \n";
    spelu_parvaldnieks.iegutPieejamasSpeles();

    spelesId = dabutSpelesId(spelu_parvaldnieks.getPieejamasSpeles(), "Kuru spēli spēlēsi? (Ievadi spēles ID): ");
    for (Spele& s : spelu_parvaldnieks.getPieejamasSpeles() ) {
        if (s.getId() == spelesId) {
            SpelesProtokols protokls(&s, getId(), getLietotajvards());
            s.saktSpeli(protokls);
            pievienotProtokolu(protokls);
            zurnals.pievienotProtokolu(protokls);
            speletasSpeles++;
            spelu_parvaldnieks.parbauditSasniegumus(*this, protokls);
            lietotaju_parvaldnieks.protokoluUzFailu(*this, protokls);
            break;
        }
    }
}

// sakārto protokolus balstoties uz punktu skaitu un pavadīto laiku:
void Speletajs::paraditLabakasSpeles(SpeluParvaldnieks& parvaldnieks) {
    if (spelesProtokoli.empty()) {
        cout << "Tu neesi spēlējis nevienu spēli!\n";
        return;
    }
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


