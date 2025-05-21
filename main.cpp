#include "PaligFunkcijas.h"
#include "LietotajuParvaldnieks.h"
#include "Lietotajs.h"
#include "Redaktors.h"
#include "Speletajs.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

void lietotajsVaiRedaktors();
void redaktoraSkats();

LietotajuParvaldnieks LP;
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
    while(ievade != "STOP" && ievade != "EXIT"){
        system("cls");
        cout << "\tREDAKTORA SKATS\n";
        //TODO:Pievienot vēl iespējas redaktoram
        cout << "1) Izveidot jaunu spēli - nav izveidota;\n";
        cout << "2) Apskatīt izveidotās spēles;\n";
        cout << "3) Rediģēt spēles jautājumus; \n";
        cout << "4) Dzēst spēles jautājumus; \n";
        cout << "STOP vai EXIT - beigt darbu;\n\n";
        ievade = stringIevade("Izvēle: ");
        uzUpperCase(ievade);

        system("cls");
        cout << "\tREDAKTORA SKATS\n";
        if(ievade == "1"){

        }
        else if (ievade == "2"){
            redaktors->apskatitIzveidotasSpeles();
        }
        else if(ievade == "3"){
            redaktors->redigetJautajumu();
        }
        else if(ievade == "4"){
            redaktors->dzestJautajumu();
        }
        cout << "Nospiediet - ENTER";
        cin.get();
    }
    delete redaktors;
    redaktors = nullptr;
}