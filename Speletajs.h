#ifndef SPELETAJS_H
#define SPELETAJS_H

#include "Lietotajs.h"
#include <string>
#include <vector>
#include <iostream>

#include "SpelesProtokols.h"
class SpeluParvaldnieks;

class Speletajs : public Lietotajs{

private:
    std::vector<std::string> sasniegumi;
    std::vector<SpelesProtokols> spelesProtokoli;
    int speletasSpeles = 0;

public:
    Speletajs(int Id = -1, std::string lv = "NA", std::string p = "NA") : Lietotajs(Id, lv, p) {loma = "Speletajs";}

    ~Speletajs() override = default;

    std::string getLoma() override {return loma;}

    void apskatitSasniegumus() {
        for (const std::string& s : sasniegumi) {std::cout << s << "\n";}
    }

    int getSpeletasSpeles() {return  speletasSpeles;}
    std::vector<std::string> getSasniegumi() {return sasniegumi;}

    void speletSpeli(SpeluParvaldnieks& parvaldnieks);
    void paraditLabakasSpeles();
    void pievienotSasniegumu(const std::string& sasniegums) {sasniegumi.push_back(sasniegums);}
    void pievienotProtokolu(const SpelesProtokols& protokols) {spelesProtokoli.push_back(protokols);}
    void apskatitProtokolus()
    {
        for (SpelesProtokols protokols : spelesProtokoli) protokols.printProtokoluInfo();
    }
};

#endif
