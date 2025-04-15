#ifndef JAUTAJUMS_H
#define JAUTAJUMS_H

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
};

#endif