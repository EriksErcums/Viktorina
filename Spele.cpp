#include "Spele.h"
#include <iostream>

using namespace std;

Spele::Spele(int id, string nosaukums, int maxPunkti, string limenis){
    this->spelesID = id;
    this->nosaukums = nosaukums;
    this->maxPunkti = maxPunkti;
    this->rezultats = 0;
    this->grutibasLimenis = limenis;
}

void Spele::pievienotJautajumu(Jautajums jautajums){
    jautajumi.push_back(jautajums);
}

void Spele::saktSpeli(){
    rezultats = 0;
    cout << "Sākam spēli: " << nosaukums << endl << endl;

    for(int i = 0; i < jautajumi.size(); i++){
        jautajumi[i].paradiJautajumu();

        int atbilde;
        cout << "Tava atbilde (ievadi skaitli): ";
        cin >> atbilde;

        if(jautajumi[i].parbaudaJautajumu(atbilde)){
            cout << "Pareizi!" << endl;
            rezultats++;
        } else {
            cout << "Nepareizi!" << endl;
        }

    }

    cout << "Spēle pabeigta! Tu ieguvi " << rezultats << " punktus no " << maxPunkti << "." << endl;
}

int Spele::getRezultats(){
    return rezultats;
}

string Spele::getNosaukums(){
    return nosaukums;
}

int Spele::getMaxPunkti(){
    return maxPunkti;
}

string Spele::getGrutibasLimenis(){
    return grutibasLimenis;
}

int Spele::getJautajumuSkaits(){
    return jautajumi.size();
}
