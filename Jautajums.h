#ifndef JAUTAJUMS_H
#define JAUTAJUMS_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Juatajums{

private:
    string teksts;
    vector<string> atbildes;
    int pareizaAtbilde; //Atbildes ir jāsakrīt ar atbildes vectora indeksiem, proti sākot no 0 un līdz pēdējam indeksam atbildes vectorā, t.i. atbildes.size() - 1

public:
    void paradiJautajumu(){
        cout << "Izvēlies vienu no dotajām atbildēm!\n";
        cout << teksts << "\n";
        for(int i = 0; i < atbildes.size(); i++){
            cout << i + 1 << ") " << atbildes[i] << "\n";
        }
    }

    bool parbaudaJautajumu(int lietotajaAtbilde){
        if(lietotajaAtbilde < 1 || lietotajaAtbilde > atbildes.size()) return false;
        return (lietotajaAtbilde - 1 == pareizaAtbilde);
    }
};

#endif