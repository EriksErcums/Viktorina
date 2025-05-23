#ifndef SPELUPARVALDNIEKS_H
#define SPELUPARVALDNIEKS_H
#include <vector>

#include "RanguTabula.h"
#include "Spele.h"
class Speletajs;
#include <string>
#include <sstream>

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
    }

    void pievienotSpeli(const Spele& spele) {visasPieejamasSpeles.push_back(spele);}
    std::vector<Spele>& getPieejamasSpeles() {return visasPieejamasSpeles;}

    void parbauditSasniegumus(Speletajs& speletajs, SpelesProtokols& protokols);

    int konverteUzSekundem(const std::string& laiks) {
        int stundas = 0, minutes = 0, sekundes = 0;
        char atdalitajs;

        std::istringstream timeStream(laiks);
        timeStream >> stundas >> atdalitajs >> minutes >> atdalitajs >> sekundes;

        return (stundas * 3600) + (minutes * 60) + sekundes;
    }

    bool vaiSaturSasniegumu(const std::vector<std::string>& sasniegumi, const std::string& sasniegums);
    void saglabatRanguTabuluDB(const std::vector<Ieraksts>& ieraksti);
    void izveidotDBprieksRanguTab();
    void apskatitiesRanguTab();
};



#endif
