#ifndef SPELESPROTOKOLS_H
#define SPELESPROTOKOLS_H

#include <string>
#include <vector>

class Spele;

class SpelesProtokols {
private:
    int speletajaID;
    std::string lietotajvards;
    Spele* spele = nullptr;
    std::string sakums;
    std::string beigas;
    int iegutiePunkti;
    std::vector<std::string> veiktasDarbibas;

    std::string iegutLaiku();

public:
    SpelesProtokols(Spele* spele, int id = -1, std::string vards = "NA")
        : speletajaID(id), lietotajvards(vards), spele(spele), sakums(iegutLaiku()) {}

    SpelesProtokols() : speletajaID(-1), lietotajvards("NA"), spele(nullptr), sakums(""), beigas(""), iegutiePunkti(0) {}

    void setIegutiePunkti(int punkti) { iegutiePunkti = punkti; }
    void pievienotDarbibu(std::string darbiba) { veiktasDarbibas.push_back(darbiba); }
    void spelesBeigas() { beigas = iegutLaiku(); }

    int getSpeletajaID() { return speletajaID; }
    Spele& getSpele();
    std::string getLietotajvardu() { return lietotajvards; }
    std::string getSakums() { return sakums; }
    std::string getBeigas() { return beigas; }
    int getPunkti() { return iegutiePunkti; }

    void printProtokoluInfo();
    void kopsavilkumsParDarbibam(std::ostream& os);
};

#endif