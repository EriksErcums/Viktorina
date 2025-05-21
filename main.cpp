#include "PaligFunkcijas.h"
#include "LietotajuParvaldnieks.h"
#include "Lietotajs.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

LietotajuParvaldnieks LP;

void lietotajsVaiRedaktors(){
    system("cls");
    cout << "Vai vēlaties PIESLĒGTIES(P) vai REĢISTRĒTIES(R)?\n";
    string izvele;

    while(true){
        //Pārliecinās, ka izvele nav tukša
        izvele = stringIevade(izvele);
        //Pārveidot izvele uz upper case
        uzUpperCase(izvele);


        if(izvele == "P" || izvele == "PIESLĒGTIES" || izvele == "PIESLEGTIES"){
            izvele = "P";
            break;
        }
        if(izvele == "R" || izvele == "REĢISTRĒTIES" || izvele == "REGISTRETIES"){
            izvele = "R";
            break;
        }

        system("cls");
        cout << "Vai vēlaties PIESLĒGTIES(P) vai REĢISTRĒTIES(R)?\n";
    }
    system("cls");

    if(izvele == "P"){
        Lietotajs* lietotajs = LP.pieslegties();
        if(lietotajs != nullptr){
            lietotajs->printInfo();
        }
        else{
            //TODO:Izdomāt, ko darīt, ka tiek atriezts nullptr, pagaidām vēlreiz lietotajsVaiRedaktors();
            cout << "Litotājvārds vai parole nav pareiza!\nNospiediet ENTER\n";
            cin.get();
            lietotajsVaiRedaktors();
        }
    }
    else if(izvele == "R"){
        LP.izveidotProfilu();
        //Izmantojot rekursiju, lai vēlreiz tiktu pie izvēlēm pēc reģistrēšanās
        lietotajsVaiRedaktors();
    }
}

int main(){
    lietotajsVaiRedaktors();
    
    cout << "Programmas beigas!\n";
}