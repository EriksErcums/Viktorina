#ifndef SPELE_H
#define SPELE_H

#include <iostream>
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
    Spele(int id, const std::string &Nosaukums, const int maxP, const std::string &limenis, const std::vector<Jautajums>& jautajumi)
    : spelesID(id), nosaukums(Nosaukums), maxPunkti(maxP), grutibasLimenis(limenis), jautajumi(jautajumi) {}

    void saktSpeli();
    void pievienotJaut(std::vector<Jautajums> jaut) {jautajumi.insert(jautajumi.end(), jaut.begin(), jaut.end());}

    int getRezultats() {return rezultats;}
    std::string getNosaukums() {return nosaukums;}
    int getMaxPunkti() {return maxPunkti;}
    std::string getGrutibasLimenis() {return grutibasLimenis;}
    int getJautajumuSkaits() {return jautajumi.size();}
    int getId() {return spelesID;}
    void getJautajumi() {
        for (int i = 1; i <= jautajumi.size(); i++) {
            std::cout << i << ". " << jautajumi[i].getTeksts() << "\n";
        }
    }
};

#endif
