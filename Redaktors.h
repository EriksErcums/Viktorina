#ifndef REDAKTORS_H
#define REDAKTORS_H

#include <iostream>
#include <string>
#include <vector>
#include "Lietotajs.h"
#include "Spele.h"

class Redaktors : public Lietotajs{

private:
    std::vector<Spele*> izveidotasSpeles;

public:
    Redaktors(int Id = -1, std::string lv = "NA", std::string p = "NA") : Lietotajs(Id, lv, p) {loma = "Redaktors";}

    ~Redaktors() override = default;

    std::string getLoma() override {return loma;}

    void izveidotSpeli();
    void apskatitIzveidotasSpeles() {
        if (!izveidotasSpeles.empty()) {
            for (Spele s : izveidotasSpeles) {
                std::cout << s.getNosaukums() << "\n";
            }
        }
        else std::cout << "Tu neesi izveidojis nevienu spēli.\n";
    }
    void pievienotJautajumu();
    void dzestJautajumu();
};

#endif
