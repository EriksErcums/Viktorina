#ifndef SPELUPARVALDNIEKS_H
#define SPELUPARVALDNIEKS_H
#include <vector>
#include "Spele.h"


class SpeluParvaldnieks {

private:
    int id = - 1;
    std::vector<Spele> visasPieejamasSpeles;
public:
    SpeluParvaldnieks(int ID  = -1) : id(ID) {}

    void iegutPieejamasSpeles() {
        if (!visasPieejamasSpeles.empty()) {
            for (Spele s : visasPieejamasSpeles) {
                std::cout << "ID: " <<  s.getId() << "\n";
                std::cout << "Nosaukums: " << s.getNosaukums() << "\n";
                std::cout << "Jautājumu skaits: " << s.getJautajumuSkaits() << "\n";
                std::cout << "Maksimālais punktu skaits: " << s.getMaxPunkti() << "\n";
                std::cout << "Grūtības līmenis: " << s.getGrutibasLimenis() << "\n";
            }
        }
        else std::cout << "Redaktors nav izveidojis nevienu spēli!.\n";
    }

    void pievienotSpeli(const Spele& spele) {visasPieejamasSpeles.push_back(spele);}
    std::vector<Spele>& getPieejamasSpeles() {return visasPieejamasSpeles;}

};



#endif
