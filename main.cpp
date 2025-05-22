#include "PaligFunkcijas.h"
#include "LietotajuParvaldnieks.h"
#include "SpeluParvaldnieks.h"
#include "SekmjuZurnals.h"
#include "Lietotajs.h"
#include "Redaktors.h"
#include "Speletajs.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

void lietotajsVaiRedaktors();
void redaktoraSkats();

LietotajuParvaldnieks LP;
SpeluParvaldnieks SP;
SekmjuZurnals SZ;
Redaktors* redaktors = nullptr;
Speletajs* speletajs = nullptr;

int main(){
    lietotajsVaiRedaktors();
    
    cout << "Programmas beigas!\n";
}

void lietotajsVaiRedaktors(){
    system("cls");
    string izvele;

    while(true){
        //Pārliecinās, ka izvele nav tukša
        izvele = stringIevade("Vai vēlaties PIESLĒGTIES(P) vai REĢISTRĒTIES(R)?\n");
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
    }
    system("cls");

    if(izvele == "P"){
        Lietotajs* lietotajs = LP.pieslegties();
        if(lietotajs == nullptr){
            //TODO:Izdomāt, ko darīt, ka tiek atriezts nullptr, pagaidām vēlreiz lietotajsVaiRedaktors();
            cout << "Litotājvārds vai parole nav pareiza!\nNospiediet ENTER\n";
            cin.get();
            lietotajsVaiRedaktors();
        }
        if(lietotajs->getLoma() == "Redaktors"){
            redaktors = new Redaktors(
                lietotajs->getId(),
                lietotajs->getLietotajvards(),
                lietotajs->getParole()
            );
            //Atīram atmiņu, lietotajs vairs nebūs vajadzīgs, jo pie tā varēs nokļūt caur Redaktors objektu
            delete lietotajs;
            redaktoraSkats();
        }
        else{
            //TODO:Iezveidot spēlētāja skata punktu
        }

    }
    else if(izvele == "R"){
        LP.izveidotProfilu();
        //Izmantojot rekursiju, lai vēlreiz tiktu pie izvēlēm pēc reģistrēšanās
        lietotajsVaiRedaktors();
    }
}

void redaktoraSkats(){
    if(redaktors == nullptr) return;

    string ievade = "";
    while(true){
        system("cls");
        cout << "\tREDAKTORA SKATS\n";
        cout << "1) Izveidot jaunu spēli;\n";
        cout << "2) Apskatīt izveidotās spēles;\n";
        cout << "3) Apskatīt sekmju žurnālu;\n";
        cout << "4) Izveidot rangu tabulu;\n";
        cout << "5) Rediģēt spēles jautājumus; \n";
        cout << "6) Dzēst spēles jautājumu; \n";
        cout << "7) Pievienot spēlei jautājumu;\n";
        cout << "8) Dzēst spēli;\n";
        cout << "STOP vai EXIT - beigt darbu;\n\n";
        ievade = stringIevade("Izvēle: ");
        uzUpperCase(ievade);

        system("cls");
        cout << "\tREDAKTORA SKATS\n";
        if(ievade == "1"){
            redaktors->izveidotSpeli(SP);
        }
        else if (ievade == "2"){
            redaktors->apskatitIzveidotasSpeles();
        }
        else if(ievade == "3"){
            redaktors->apskatitSekmjuZurnalu(SZ);
        }
        else if(ievade =="4"){
            redaktors->izveidotRangutabulu(SP, SZ);
        }
        else if(ievade == "5"){
            redaktors->redigetJautajumu();
        }
        else if(ievade == "6"){
            redaktors->dzestJautajumu();
        }
        else if(ievade == "7"){
            redaktors->pievienotJautajumu();
        }
        else if(ievade == "8"){
            redaktors->dzestSpeli();
        }
        else if(ievade == "STOP" || ievade == "EXIT"){
            break;
        }
        cout << "Nospiediet - ENTER";
        cin.get();
    }
    delete redaktors;
    redaktors = nullptr;
}