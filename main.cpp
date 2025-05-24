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

bool lietotajsVaiRedaktors();
void redaktoraSkats();
void speletajaSkats();
void nospiedietEnter();

LietotajuParvaldnieks LP;
SpeluParvaldnieks SP;
SekmjuZurnals SZ;
Redaktors* redaktors = nullptr;
Speletajs* speletajs = nullptr;

int main() {
    while (lietotajsVaiRedaktors());
    LP.clearLietotaji();
    cout << "Programmas beigas!\n";
    return 0;
}

bool lietotajsVaiRedaktors(){
    system("cls");
    string izvele;

    while(true){
        izvele = stringIevade("Vai vēlaties PIESLĒGTIES(P), REĢISTRĒTIES(R) vai IZIET(X)?\n");
        uzUpperCase(izvele);

        if(izvele == "P" || izvele == "PIESLĒGTIES" || izvele == "PIESLEGTIES"){
            izvele = "P";
            break;
        }
        if(izvele == "R" || izvele == "REĢISTRĒTIES" || izvele == "REGISTRETIES"){
            izvele = "R";
            break;
        }
        if(izvele == "X" || izvele == "IZIET"){
            return false; // Aptur programmu
        }
        system("cls");
    }

    system("cls");

    if (izvele == "P") {
        Lietotajs* lietotajs = LP.pieslegties();
        if (lietotajs == nullptr) {
            cout << "Lietotājvārds vai parole nav pareiza!\nNospiediet ENTER\n";
            cin.get();
            return true;
        }

        if (lietotajs->getLoma() == "Redaktors") {
            redaktors = dynamic_cast<Redaktors*>(lietotajs);
            redaktoraSkats();
            redaktors = nullptr;
        } else {
            speletajs = dynamic_cast<Speletajs*>(lietotajs);
            speletajaSkats();
            speletajs = nullptr;
        }
    }
    else if(izvele == "R"){
        LP.izveidotProfilu();
        nospiedietEnter();
    }

    return true; // Turpina ciklu, lai atgrieztos login/reģistrācijas sākumekrānā
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
        cout << "9) Apskatīt rangu tabulu;\n";
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
            nospiedietEnter();
        }
        else if(ievade =="4"){
            redaktors->izveidotRangutabulu(SP, SZ);
        }
        else if(ievade == "5"){
            redaktors->redigetJautajumu();
        }
        else if(ievade == "6"){
            redaktors->dzestJautajumu();
            nospiedietEnter();
        }
        else if(ievade == "7"){
            redaktors->pievienotJautajumu();
        }
        else if(ievade == "8"){
            redaktors->dzestSpeli();
        }
        else if(ievade == "9"){
            redaktors->apskatitiesRanguTabulu(SP);
        }
        else if(ievade == "STOP" || ievade == "EXIT"){
            break;
        }
        nospiedietEnter();
    }
    redaktors = nullptr;
}

void speletajaSkats(){
    if(speletajs == nullptr) return;

    string ievade = "";
    while(true){
        system("cls");
        cout << "\tSPĒLĒTĀJA SKATS\n";
        cout << "1) Spēlēt spēli\n";
        cout << "2) Apskatīt sasniegumus\n";
        cout << "3) Apskatīt labākās spēles\n";
        cout << "4) Apskatīt protokolus\n";
        cout << "STOP vai EXIT - beigt darbu\n\n";
        ievade = stringIevade("Izvēle: ");
        uzUpperCase(ievade);

        system("cls");
        cout << "\tSPĒLĒTĀJA SKATS\n";
        if(ievade == "1"){
            speletajs->speletSpeli(SZ, SP, LP);
            nospiedietEnter();
        }
        else if(ievade == "2"){
            speletajs->apskatitSasniegumus();
        }
        else if(ievade == "3"){
            speletajs->paraditLabakasSpeles(SP);
        }
        else if(ievade == "4"){
            speletajs->apskatitProtokolus();
        }
        else if(ievade == "STOP" || ievade == "EXIT"){
            break;
        }
        nospiedietEnter();
    }
    speletajs = nullptr;
}

void nospiedietEnter() {
    cout << "Nospiediet ENTER, lai turpinātu...\n";
    cin.get();
}