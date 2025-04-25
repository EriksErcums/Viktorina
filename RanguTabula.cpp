#include "RanguTabula.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

void RanguTabula::pievienotIerakstu(int id, std::string vards, int punkti, int laiks)
{
    rezultati.push_back(Ieraksts{(id, vards, punkti, laiks)});
}

int RanguTabula::parveidotLaikuUzSekundem(std::string laiks)
{
    int h = 0, m = 0, s = 0;
    char delim;

    std::istringstream iss(laiks);
    iss >> h >> delim >> m >> delim >> s;

    return h * 3600 + m * 60 + s;
}

void RanguTabula::izveidotRanguTabulu(SekmjuZurnals zurnals)
{
    vector<SpelesProtokols> protokoli = zurnals.iegutVisusProtokolus();
    for(SpelesProtokols p : protokoli){
        int l = parveidotLaikuUzSekundem(p.getBeigas()) - parveidotLaikuUzSekundem(p.getSakums());
        pievienotIerakstu(p.getSpeletajaID(), p.getLietotajvardu(), p.getPunkti(), l);
    }

    sort(rezultati.begin(), rezultati.end(), [](const Ieraksts& a, const Ieraksts& b) {
        if (a.punkti == b.punkti)
            return a.laiks < b.laiks;
        return a.punkti > b.punkti;
    });
    
}

void RanguTabula::apskatitRanguTabulu()
{
    cout << "Rangu tabula\n";
    for(Ieraksts i : rezultati){
        cout << i.lietotajvards << " | Punkti: " << i.punkti << " | Laiks: " << i.laiks << "\n";
    }
}