#ifndef RANGUTABULA_H
#define RANGUTABULA_H

#include <string>
#include <vector>

#include "SekmjuZurnals.h"

struct Ieraksts{
    int speletajsID;
    std::string lietotajvards;
    int punkti;
    int laiks;
};

class RanguTabula{

private:
    std::vector<Ieraksts> rezultati;
public:
    void izveidotRanguTabulu(SekmjuZurnals zurnals);
    void apkskatitRanguTabulu();
    std::vector<Ieraksts> iegutRanguTabulu() { return rezultati; };
    void pievienotIerakstu(int id, std::string vards, int punkti, int laiks);
};

#endif