#include "LietotajuParvaldnieks.h"
#include "Redaktors.h"
#include "Speletajs.h"

#include <iostream>
#include <string>

using namespace std;

void LietotajuParvaldnieks::izveidotProfilu() {
    string lv, p, l;
    do {
        cout << "Ievadi lietotājvārdu: ";
        cin >> lv;

        cout << "Ievadi paroli: ";
        cin >> p;

        cout << "Kāda būs lietotāja loma? (Spēlētājs | Redaktors): ";
        cin >> l;

        if (lv.length() < 3) cout << "Pārāk īss lietotājvārds!\n";
        if (lv.length() > 20) cout << "Pārāk garš lietotājvārds!\n";
        if (p.length() < 8) cout << "Pārāk īsa parole!\n";
        if (!saturCiparu(p)) cout << "Parolē ir jāiekļauj cipars!\n";
        if (!saturLieloBurtu(p)) cout << "Parolē ir jāiekļauj lielais burts!\n";
        if (l != "Spēlētājs" && l != "Redaktors") cout << "Lietotājam jābūt vai nu spēlētājam vai arī redaktoram!\n";

    } while (lv.length() < 3 || lv.length() > 20 || p.length() < 8 || (!saturCiparu(p) || !saturLieloBurtu(p)) || l != "Spēlētājs" && l != "Redaktors");
    pedejaisID++;

    if (l == "Spēlētājs") {
        lietotaji.push_back(new Speletajs(pedejaisID, lv, p));
        // TODO: saglabatLietotajuDB(pedejaisID, lv, p, "Speletajs");
        cout << "Tika izveidots jauns spēlētāja profils\n";
    }
    if (l == "Redaktors") {
        cout << "Tika izveidots jauns Redaktora profils\n";
        lietotaji.push_back(new Redaktors(pedejaisID, lv, p));
        // TODO: saglabatLietotajuDB(pedejaisID, lv, p, "Redaktors");
    }
}

bool LietotajuParvaldnieks::saturLieloBurtu(const string& parole) {
    for (int i = 0; i < parole.length(); i++) {
        if (isupper(parole[i])) return true;
    }
    return false;
}

bool LietotajuParvaldnieks::saturCiparu(const string& parole) {
    for (int i = 0; i < parole.length(); i++) {
        if (isdigit(parole[i])) return true;
    }
    return false;
}



