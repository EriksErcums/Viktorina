#ifndef REDAKTORS_H
#define REDAKTORS_H

#include <iostream>
#include <string>
#include <vector>
#include "Lietotajs.h"
#include "Spele.h"
#include "SpeluParvaldnieks.h"

class Redaktors : public Lietotajs{

private:
    std::vector<Spele> izveidotasSpeles;

public:
    Redaktors(int Id = -1, std::string lv = "NA", std::string p = "NA") : Lietotajs(Id, lv, p) {loma = "Redaktors";}

    ~Redaktors() override = default;

    std::string getLoma() override {return loma;}

    void izveidotSpeli(SpeluParvaldnieks& parvaldnieks);
    void apskatitIzveidotasSpeles() {
        if (!izveidotasSpeles.empty()) {
            for (Spele s : izveidotasSpeles) {
                std::cout << "ID: " <<  s.getId() << "\n";
                std::cout << "Nosaukums: " << s.getNosaukums() << "\n";
                std::cout << "Jautājumu skaits: " << s.getJautajumuSkaits() << "\n";
                std::cout << "Maksimālais punktu skaits: " << s.getMaxPunkti() << "\n";
                std::cout << "Grūtības līmenis: " << s.getGrutibasLimenis() << "\n";
            }
        }
        else std::cout << "Tu neesi izveidojis nevienu spēli.\n";
    }
    
    void pievienotJautajumu();
    Jautajums pievienot_jautajums_helper(int i);
    void dzestJautajumu();
    void dzestSpeli();
    void redigetJautajumu();
};

#endif
