#ifndef JAUTAJUMS_H
#define JAUTAJUMS_H

#include <iostream>
#include <string>
#include <vector>

class Jautajums{

private:
    std::string teksts;
    std::vector<std::string> atbildes;
    int pareizaAtbilde; //Atbildes ir jāsakrīt ar atbildes vectora indeksiem, proti sākot no 0 un līdz pēdējam indeksam atbildes vectorā, t.i. atbildes.size() - 1

public:
    Jautajums(std::string teksts, std::vector<std::string> atbildes, int pareizaAtb)
     : teksts(teksts), atbildes(atbildes), pareizaAtbilde(pareizaAtb) {};
    
    void paradiJautajumu();
    bool parbaudaJautajumu(int lietotajaAtbilde);
    std::string getTeksts() {return teksts;}
    void setTeksts(const std::string &teksts) {this->teksts = teksts;}
    void setAtbildes(const std::vector<std::string> &atbildes) {this->atbildes = atbildes;}

    void getAtbildes() {
        for (int i = 1; i <= atbildes.size(); i++) {
            std::cout << i << ". atbilde: " <<  atbildes[i - 1] << "\n";
        }
    }
    void mainitJautajumu(const std::string &jaunsJaut, const std::vector<std::string>& jaunasAtbildes, int pareizaAtb) {
        teksts = jaunsJaut;
        atbildes = jaunasAtbildes;
        pareizaAtbilde = pareizaAtb;
    }
};

#endif