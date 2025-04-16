#ifndef SPELE_H
#define SPELE_H

#include <string>
#include <vector>
#include "Jautajums.h"

using namespace std;

class Spele {
private:
    int spelesID;
    string nosaukums;
    int maxPunkti;
    int rezultats;
    string grutibasLimenis;
    vector<Jautajums> jautajumi;

public:
    Spele(int id, string nosaukums, int maxPunkti, string limenis);

    void saktSpeli();
    void pievienotJautajumu(Jautajums jautajums);
    int getRezultats();
    string getNosaukums();
    int getMaxPunkti();
    string getGrutibasLimenis();
    int getJautajumuSkaits();
};

#endif
