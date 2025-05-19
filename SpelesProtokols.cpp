#include "SpelesProtokols.h"
#include "Spele.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

string SpelesProtokols::iegutLaiku() {
    auto laiks = chrono::system_clock::now();
    time_t laiksTagad = chrono::system_clock::to_time_t(laiks);

    ostringstream ls;
    ls << put_time(localtime(&laiksTagad), "%H:%M:%S");

    return ls.str();
}

Spele& SpelesProtokols::getSpele() {
    return *spele;
}

void SpelesProtokols::printProtokoluInfo() {
    cout << "Spēlētāja ID: " << getSpeletajaID() << "\n";
    cout << "Spēlētāja lietotājvārds: " << getLietotajvardu() << "\n";
    cout << "Spēlētā spēle: " << getSpele().getNosaukums() << "\n";
    cout << "Spēles sākuma laiks: " << getSakums() << "\n";
    cout << "Spēles beigu laiks: " << getBeigas() << "\n";
    cout << "Iegūtie punkti par spēli: " << getPunkti() << " no " << getSpele().getMaxPunkti() << "\n";
    kopsavilkumsParDarbibam(cout);
    cout << "\n";
}

void SpelesProtokols::kopsavilkumsParDarbibam(ostream& os) {
    int pareizoAtbSk = 0, nepareizoAtbSk = 0;
    for (const string& s : veiktasDarbibas) {
        size_t atrasts = s.find_last_of(' ');
        string rez = s.substr(atrasts + 1);
        if (rez == "pareiza") pareizoAtbSk++;
        else if (rez == "nepareiza") nepareizoAtbSk++;
    }
    os << "Spēlētājs atbildēja uz " << veiktasDarbibas.size() << " jautājumiem.\n";
    os << "Spēlētājs atbildēja pareizi uz " << pareizoAtbSk << " jautājumiem.\n";
    os << "Spēlētājs atbildēja nepareizi uz " << nepareizoAtbSk << " jautājumiem.\n";
}
