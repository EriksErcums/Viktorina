#ifndef SPELE_H
#define SPELE_H

#include <string>
#include <vector>
#include "Jautajums.h"

class Spele {

private:
    int spelesID;
    std::string nosaukums;
    int maxPunkti;
    int rezultats = 0;
    std::string grutibasLimenis;
    std::vector<Jautajums> jautajumi;

public:
    Spele(int id, const std::string &Nosaukums, const int maxP, const std::string &limenis)
    : spelesID(id), nosaukums(Nosaukums), maxPunkti(maxP), grutibasLimenis(limenis) {}

    void saktSpeli();
    void pievienotJautajumu(const Jautajums& jautajums){
        jautajumi.push_back(jautajums);
    }

    int getRezultats() {return rezultats;}
    std::string getNosaukums() {return nosaukums;}
    int getMaxPunkti() {return maxPunkti;}
    std::string getGrutibasLimenis() {return grutibasLimenis;}
    int getJautajumuSkaits() {return jautajumi.size();}
    int getId() {return spelesID;}
};

#endif
