#include "RanguTabula.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

void RanguTabula::pievienotIerakstu(int id, string vards, int punkti, int laiks)
{
    rezultati.push_back(Ieraksts{id, vards, punkti, laiks});
}

int RanguTabula::parveidotLaikuUzSekundem(const string& laiks)
{
    int h = 0, m = 0, s = 0;
    char delim;

    istringstream iss(laiks);
    iss >> h >> delim >> m >> delim >> s;

    return h * 3600 + m * 60 + s;
}

void RanguTabula::izveidotRanguTabulu(SekmjuZurnals& zurnals)
{
    vector<SpelesProtokols> protokoli = zurnals.iegutVisusProtokolus();
    map<int, SpelesProtokols> ieraksti; // nodrošinās, ka rangu tabula nesatur vairākus ierakstus par vienu un to pašu personu, bet tikai labāko ierakstu(rezultātu).

    for(SpelesProtokols p : protokoli){

        int l = parveidotLaikuUzSekundem(p.getBeigas()) - parveidotLaikuUzSekundem(p.getSakums());

        if (ieraksti.count(p.getSpeletajaID())) {
            SpelesProtokols ierakstaVertiba = ieraksti.at(p.getSpeletajaID());
            int ierakstaLaiks = parveidotLaikuUzSekundem(ierakstaVertiba.getBeigas()) - parveidotLaikuUzSekundem(ierakstaVertiba.getSakums());

            if (ierakstaVertiba.getPunkti() < p.getPunkti()) {
                ieraksti[p.getSpeletajaID()] = p;
            }
            else if (ierakstaVertiba.getPunkti() == p.getPunkti()) {
                if (ierakstaLaiks > l) {
                    ieraksti[p.getSpeletajaID()] = p;
                }
            }
        }
        else ieraksti[p.getSpeletajaID()] = p;
    }

    for (auto pair : ieraksti) {  // kad duplikāti ir izslēgti, pievieno rezultātu vektoram
        int laiks = parveidotLaikuUzSekundem(pair.second.getBeigas()) - parveidotLaikuUzSekundem(pair.second.getSakums());
        pievienotIerakstu(pair.second.getSpeletajaID(), pair.second.getLietotajvardu(), pair.second.getPunkti(), laiks);
    }

    sort(rezultati.begin(), rezultati.end(), [](const Ieraksts& a, const Ieraksts& b) {
        if (a.punkti == b.punkti)
            return a.laiks < b.laiks;
        return a.punkti > b.punkti;
    });

    // saglabā tikai top 5 rezultātus:
    if (rezultati.size() > 5) rezultati.erase(rezultati.begin() + 5, rezultati.end());

}

void RanguTabula::apskatitRanguTabulu()
{
    cout << "Rangu tabula\n";
    for(const Ieraksts& i : rezultati){
        cout << "ID: " << i.speletajsID << " | lietotājvārds: " << i.lietotajvards << " | Punkti: " << i.punkti << " | Laiks: " << i.laiks << "\n";
    }
}