#ifndef SPELETAJS_H
#define SPELETAJS_H

#include "Lietotajs.h"
#include <string>
#include <vector>
#include <iostream>

class Speletajs : public Lietotajs{

private:
    std::vector<std::string> sasniegumi;

public:
    Speletajs(int Id = -1, std::string lv = "NA", std::string p = "NA") : Lietotajs(Id, lv, p) {loma = "Speletajs";}

    ~Speletajs() override = default;

    std::string getLoma() override {return loma;}

    void apskatitSasniegumus() {
        for (const std::string& s : sasniegumi) {std::cout << s << "\n";}
    }

    void speletSpeli();
    void paraditLabakasSpeles();
    void pievienotSasniegumu(const std::string& sasniegums) {sasniegumi.push_back(sasniegums);}
};

#endif
