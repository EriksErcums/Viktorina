#include "Redaktors.h"
#include <algorithm>
#include <string>
#include <limits>

#include "PaligFunkcijas.h"
#include "SpeluParvaldnieks.h"
using namespace std;

void Redaktors::izveidotSpeli(SpeluParvaldnieks& parvaldnieks) {
    string nosaukums = stringIevade("Ievadi spēles nosaukumu: ");
    int maxp = skaitluIevade("Ievadi spēles maksimālo punktu skaitu: ", 1);

    string grutibaslimenis;
    do {
        cout << "Ievadi spēles grūtības līmeni: ";
        getline(cin, grutibaslimenis);
        transform(grutibaslimenis.begin(), grutibaslimenis.end(), grutibaslimenis.begin(), ::tolower);
        if (grutibaslimenis != "viegls" && grutibaslimenis != "vidējs" && grutibaslimenis != "grūts") {
            cout << "Spēles grūtības līmenim jābūt vienam no trim variantiem: \"viegls\", \"vidējs\", \"grūts\"!\n";
        }
    } while (grutibaslimenis != "viegls" && grutibaslimenis != "vidējs" && grutibaslimenis != "grūts");

    int jautSk = skaitluIevade("Cik jautājumi būs spēlei?: ", 1);
    vector<Jautajums> jautajumi;
    for (int i = 1; i <= jautSk; i++) {
        jautajumi.push_back(pievienot_jautajums_helper(i));
    }

    int spelesId = izveidotasSpeles.empty() ? 1 : izveidotasSpeles.back().getId() + 1;
    Spele spele(spelesId, nosaukums, maxp, grutibaslimenis, jautajumi);
    izveidotasSpeles.push_back(spele);
    parvaldnieks.pievienotSpeli(spele);
}

void Redaktors::pievienotJautajumu() {
    if (izveidotasSpeles.empty()) {
        cout << "Nav izveidota neviena spēle!\n";
        return;
    }

    apskatitIzveidotasSpeles();
    int spelesID = dabutSpelesId(izveidotasSpeles, "Kurai spēlei vēlies pievienot jautājumu? (Ievadi spēles ID): ");
    int jautajumuSk = skaitluIevade("Cik jautājumus pievienosi?: ", 1);

    vector<Jautajums> jautajumi;
    for (int i = 1; i <= jautajumuSk; i++) {
        jautajumi.push_back(pievienot_jautajums_helper(i));
    }

    for (Spele& s : izveidotasSpeles) {
        if (s.getId() == spelesID) {
            s.pievienotJaut(jautajumi);
            break;
        }
    }
}

Jautajums Redaktors::pievienot_jautajums_helper(const int i) {
    string jautajums = stringIevade("Ievadi " + to_string(i) + ". jautājumu: ");
    int atbilzuSk = skaitluIevade("Cik atbilžu varianti būs jautājumam?: ", 1);

    vector<string> atbildes;
    for (int j = 1; j <= atbilzuSk; j++) {
        atbildes.push_back(stringIevade("Ievadi " + to_string(j) + ". atbildi: "));
    }

    int pareizaAtb = skaitluIevade("Ievadi pareizās atbildes indeksu (1 līdz " + to_string(atbilzuSk) + "): ", 1);
    while (pareizaAtb > atbilzuSk) {
        cout << "Nepareizs pareizās atbildes indekss! Mēģini vēlreiz.\n";
        pareizaAtb = skaitluIevade("Ievadi pareizās atbildes indeksu (1 līdz " + to_string(atbilzuSk) + "): ", 1);
    }

    return Jautajums(jautajums, atbildes, pareizaAtb - 1);
}

void Redaktors::dzestSpeli() {
    if (izveidotasSpeles.empty()) {
        cout << "Nav izveidota neviena spēle!\n";
        return;
    }

    apskatitIzveidotasSpeles();
    int id = dabutSpelesId(izveidotasSpeles, "Ievadi spēles ID, kuru vēlies dzēst: ");

    for (auto it = izveidotasSpeles.begin(); it != izveidotasSpeles.end(); ++it) {
        if (it->getId() == id) {
            izveidotasSpeles.erase(it);
            cout << "Spēle tika veiksmīgi izdzēsta\n";
            return;
        }
    }

    cout << "Netika atrasta spēle ar šādu ID!\n";
}

void Redaktors::redigetJautajumu() {
    if (izveidotasSpeles.empty()) {
        cout << "Nav izveidota neviena spēle!\n";
        return;
    }

    apskatitIzveidotasSpeles();
    int spelesId = dabutSpelesId(izveidotasSpeles, "Kuras spēles jautājumu/s vēlies rediģēt? (Ievadi spēles ID): ");

    for (Spele& s : izveidotasSpeles) {
        if (s.getId() == spelesId) {
            cout << "Spēles nosaukums: " << s.getNosaukums() << "\n";
            cout << "Spēles jautājumi: \n";
            s.getJautajumi();

            int indekss = skaitluIevade("Kuru jautājumu vēlies rediģēt? (Ievadi jautājuma numuru): ", 1);
            while (indekss > s.getJautajumuSkaits()) {
                cout << "Izvēlies derīgu jautājumu numuru!\n";
                indekss = skaitluIevade("Kuru jautājumu vēlies rediģēt? (Ievadi jautājuma numuru): ", 1);
            }
            cout << "Vecais jautājums: " << s.getJaut(indekss).getTeksts() << "\n";
            cout << "Jautājuma atbildes: \n";
            s.getJaut(indekss).getAtbildes();

            string jaunaisJaut = stringIevade("Ievadi jauno jautājumu: ");
            int atbilzuSk = skaitluIevade("Cik atbilžu varianti būs jaunajam jautājumam?: ", 1);

            vector<string> atbildes;
            for (int j = 1; j <= atbilzuSk; j++) {
                atbildes.push_back(stringIevade("Ievadi " + to_string(j) + ". atbildi: "));
            }

            int jaunaPareizaAtb = skaitluIevade("Ievadi pareizās atbildes indeksu (1 līdz " + to_string(atbilzuSk) + "): ", 1);
            while (jaunaPareizaAtb > atbilzuSk) {
                cout << "Nepareizs pareizās atbildes indekss! Mēģini vēlreiz.\n";
                jaunaPareizaAtb = skaitluIevade("Ievadi pareizās atbildes indeksu (1 līdz " + to_string(atbilzuSk) + "): ", 1);
            }

            s.redigetJaut(indekss, jaunaisJaut, atbildes, jaunaPareizaAtb - 1);
            break;
        }
    }
}

void Redaktors::dzestJautajumu() {
    if (izveidotasSpeles.empty()) {
        cout << "Nav izveidota neviena spēle!\n";
        return;
    }

    apskatitIzveidotasSpeles();
    int spelesId = dabutSpelesId(izveidotasSpeles, "Kuras spēles jautājumu/s vēlies dzēst? (Ievadi spēles ID): ");

    for (Spele& s : izveidotasSpeles) {
        if (s.getId() == spelesId) {
            cout << "Spēles nosaukums: " << s.getNosaukums() << "\n";
            cout << "Spēles jautājumi: \n";
            s.getJautajumi();
            int indekss = skaitluIevade("Kuru jautājumu vēlies dzēst? (Ievadi jautājuma numuru): ", 1);
            while (indekss > s.getJautajumuSkaits()) {
                cout << "Izvēlies derīgu jautājumu numuru!\n";
                indekss = skaitluIevade("Kuru jautājumu vēlies dzēst? (Ievadi jautājuma numuru): ", 1);
            }
            s.dzestJaut(indekss);
            cout << "Jautājums veiksmīgi izdzēsts no spēles.\n";
            break;
        }
    }
}

void Redaktors::apskatitSekmjuZurnalu(SekmjuZurnals &zurnals) {
    if (zurnals.iegutVisusProtokolus().empty()) {
        cout << "Sekmju žurnāls ir tukšs!\n";
        return;
    }
    int izvele;
    do {
        cout << "1. Apskatīt visus sekmju žurnāla ierakstus\n2. Apskatīt sekmju žurnāla ierakstus par konkrētu spēlētaju\n";
        cout << "Tava izvēle (ievadi skaitli): ";
        cin >> izvele;
    } while (izvele < 1 || izvele > 2);

    if (izvele == 1) {
        cout << "Visi sekmju žurnāla ieraksti: \n";
        for (SpelesProtokols& protokols : zurnals.iegutVisusProtokolus()) {
            protokols.printProtokoluInfo();
        }
    }
    else if (izvele == 2) zurnals.apskatitKonkretusProt();
}


