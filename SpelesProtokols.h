#ifndef SPELESPROTOKOLS_H
#define SPELESPROTOKOLS_H

#include "Spele.h"

#include <string>
#include <vector>

class SpelesProtokols{

private:
    int speletajaID;
    Spele* spele = nullptr;
    std::string sakums;
    std::string beigas;
    int iegutiePunkti;
    std::vector<std::string> veiktasDarbibas;

    std::string iegutLaiku();
public:
    SpelesProtokols(Spele* spele, int id = -1) : speletajaID(id), spele(spele), sakums(iegutLaiku()) {}

    void setIegutiePunkti(int punkti) { iegutiePunkti = punkti; };
    void pievienotDarbibu(std::string darbiba) { veiktasDarbibas.push_back(darbiba);};
    void spelesBeigas() { beigas = iegutLaiku(); };

};

#endif