#include "Redaktors.h"
#include <algorithm>
#include <string>
#include <limits>
using namespace std;

// Helper metodes:

int Redaktors::dabutSpelesId(const string& teksts) {
    int spelesID;

    while (true) {
        cout << teksts;
        cin >> spelesID;

        if (cin.fail()) {
            cin.clear();  // Notīra error flagus
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Atmet visu pārējo ievades rindu, lai netruacē turpmākām ievadēm.
            cout << "Ievadi veselu skaitli!\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (Spele& s : izveidotasSpeles) {
            if (s.getId() == spelesID) {
                return spelesID;
            }
        }

        cout << "Ievadi derīgu spēles ID!\n";
    }
}

int Redaktors::skaitluIevade(const string& teksts, int minVertiba) {
    int vertiba;
    do {
        cout << teksts;
        cin >> vertiba;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (vertiba < minVertiba) {
            cout << "Skaitlim jābūt vismaz " << minVertiba << "!\n";
        }
    } while (vertiba < minVertiba);
    return vertiba;
}

string Redaktors::stringIevade(const string& teksts) {
    string ievade;
    do {
        cout << teksts;
        getline(cin, ievade);
        if (ievade.empty()) {
            cout << "Lauks nevar būt tukšs!\n";
        }
    } while (ievade.empty());
    return ievade;
}

void Redaktors::izveidotSpeli() {
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
    izveidotasSpeles.push_back(Spele(spelesId, nosaukums, maxp, grutibaslimenis, jautajumi));
}

void Redaktors::pievienotJautajumu() {
    if (izveidotasSpeles.empty()) {
        cout << "Nav izveidota neviena spēle!\n";
        return;
    }

    apskatitIzveidotasSpeles();
    int spelesID = dabutSpelesId("Kurai spēlei vēlies pievienot jautājumu? (Ievadi spēles ID): ");
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
    int id = dabutSpelesId("Ievadi spēles ID, kuru vēlies dzēst: ");

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
    int spelesId = dabutSpelesId("Kuras spēles jautājumu/s vēlies rediģēt? (Ievadi spēles ID): ");

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
    int spelesId = dabutSpelesId("Kuras spēles jautājumu/s vēlies dzēst? (Ievadi spēles ID): ");

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
