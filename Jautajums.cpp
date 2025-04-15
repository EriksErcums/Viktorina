#include "Jautajums.h"

#include <iostream>

using namespace std;

void Jautajums::paradiJautajumu(){
    cout << "Izvēlies vienu no dotajām atbildēm!\n";
    cout << teksts << "\n";
    for(int i = 0; i < atbildes.size(); i++){
        cout << i + 1 << ") " << atbildes[i] << "\n";
    }
}

bool Jautajums::parbaudaJautajumu(int lietotajaAtbilde){
    if(lietotajaAtbilde < 1 || lietotajaAtbilde > atbildes.size()) return false;
    return (lietotajaAtbilde - 1 == pareizaAtbilde);
}