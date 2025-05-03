#include "Redaktors.h"

#include <algorithm>
#include <string>
using namespace std;

void Redaktors::izveidotSpeli() {
    string nosaukums, grutibaslimenis, jautajums, atbilde;
    int maxp, jautSk, spelesId;
    vector<string> atbildes;
    vector<Jautajums> jautajumi;

    do {
        cout << "Ievadi spēles nosaukumu: ";
        getline(cin, nosaukums);
        if (nosaukums.empty()) cout << "Ievadi derīgu spēles nosaukumu!\n";
    } while (nosaukums.empty());

    do {
        cout << "Ievadi spēles maksimālo punktu skaitu: ";
        cin >> maxp;
        cin.ignore();
        if (maxp < 1) cout << "Punktu skaitam jābūt pozitīvam!\n";
    } while (maxp < 1);

    do {
        cout << "Ievadi spēles grūtības līmeni: ";
        getline(cin, grutibaslimenis);
        transform(grutibaslimenis.begin(), grutibaslimenis.end(), grutibaslimenis.begin(), ::tolower);
        if (grutibaslimenis != "viegls" && grutibaslimenis != "vidējs" && grutibaslimenis != "grūts") {
            cout << "Spēles grūtības līmenim jābūt vienam no trim variantiem: \"viegls\", \"vidējs\", \"grūts\"!\n";
        }
    } while (grutibaslimenis != "viegls" && grutibaslimenis != "vidējs" && grutibaslimenis != "grūts");

    do {
        cout << "Cik jautājumi būs spēlei?: ";
        cin >> jautSk;
        cin.ignore();
        if (jautSk < 1) cout << "Spēlei ir jāsastāv no vismaz 1 jautājuma\n";
    } while (jautSk < 1);

    for (int i = 1; i <= jautSk; i++) {
        jautajumi.push_back(pievienot_jautajums_helper(i));
    }

    if (izveidotasSpeles.empty()) {
        spelesId = 1;
    }
    else {
        spelesId = izveidotasSpeles.back().getId() + 1;
    }

    izveidotasSpeles.push_back(Spele(spelesId, nosaukums, maxp, grutibaslimenis, jautajumi));
}


void Redaktors::pievienotJautajumu() {

    if (!izveidotasSpeles.empty()) {
        apskatitIzveidotasSpeles();

        int spelesID, jautajumuSk;
        vector<Jautajums> jautajumi;

        bool derigsID = false;
        do {
            cout << "Kurai spēlei vēlies pievienot jautājumu? (Ievadi spēles ID): ";
            cin >> spelesID;
            cin.ignore();

            for (Spele& s : izveidotasSpeles) {
                if (s.getId() == spelesID) {
                    derigsID = true;
                    break;
                }
            }

            if (!derigsID) {
                cout << "Ievadi derīgu spēles ID!\n";
            }

        } while (!derigsID);

        do {
            cout << "Cik jautājumu pievienosi?: ";
            cin >> jautajumuSk;
            cin.ignore();
            if (jautajumuSk < 1) cout << "Tu nevari pievienot mazāk kā 1 jautājumu!\n";
        } while (jautajumuSk < 1);

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
    else cout << "Nav izveidota neviena spēle!\n";
}

Jautajums Redaktors::pievienot_jautajums_helper(const int i) {
    string jautajums, atbilde;
    int atbilzuSk, pareizaAtb;
    vector<string> atbildes;
    do {
        cout << "Ievadi " << i << ". jautājumu: ";
        getline(cin, jautajums);
        if (jautajums.empty()) cout << "Jautājums nevar būt tukšs!\n";
    } while (jautajums.empty());

    do {
        cout << "Cik atbilžu varianti būs jautājumam?: ";
        cin >> atbilzuSk;
        cin.ignore();
        if (atbilzuSk < 1) cout << "Atbilžu skaitam jābūt vismaz 1!\n";

    } while (atbilzuSk < 1);

    for (int j = 1; j <= atbilzuSk; j++)
    {
        cout << "Ievadi " << j << ". atbildi: ";
        getline(cin, atbilde);
        atbildes.push_back(atbilde);
    }

    do {
        cout << "Ievadi pareizās atbildes indeksu (1 līdz " << atbilzuSk << "): ";
        cin >> pareizaAtb;
        cin.ignore();

        if (pareizaAtb < 1 || pareizaAtb > atbilzuSk) cout << "Nepareizs pareizās atbildes indekss! Mēģini vēlreiz.\n";
    } while (pareizaAtb < 1 || pareizaAtb > atbilzuSk);
    return Jautajums(jautajums, atbildes, pareizaAtb - 1);
}

void Redaktors::dzestSpeli() {
    if (!izveidotasSpeles.empty()) {
        int id;
        apskatitIzveidotasSpeles();

        bool atrasts = false;
        do {
        cout << "Ievadi spēles ID, kuru vēlies dzēst: ";
            cin >> id;
            if (id < 1 || id > izveidotasSpeles.size()) cout << "Ievadi derīgu spēles ID!\n";
        } while (id < 1 || id > izveidotasSpeles.size());

        for (auto it = izveidotasSpeles.begin(); it != izveidotasSpeles.end(); ++it) {
            if (it->getId() == id) {
                izveidotasSpeles.erase(it);
                cout << "Spēle tika veiksmīgi izdzēsta\n";
                atrasts = true;
                break;
            }
        }
        if (!atrasts) cout << "Netika atrasta spēle ar šādu ID!\n";
    }
    else cout << "Nav izveidota neviena spēle!\n";
}

void Redaktors::redigetJautajumu() {

    if (!izveidotasSpeles.empty()) {
        apskatitIzveidotasSpeles();
        bool derigsID = false;
        int spelesId, indekss, atbilzuSk, jaunaPareizaAtb;
        string jaunaisJaut, atbilde;
        vector<string> atbildes;

        do {
            cout << "Kuras spēles jautājumu/s vēlies rediģēt? (Ievadi spēles ID): ";
            cin >> spelesId;
            cin.ignore();

            for (Spele& s : izveidotasSpeles) {
                if (s.getId() == spelesId) {
                    derigsID = true;
                    cout << "Spēles nosaukums: " << s.getNosaukums() << "\n";
                    cout << "Spēles jautājumi: \n";
                    s.getJautajumi();
                    do {
                    cout << "Kuru jautājumu vēlies rediģēt? (Ievadi jautājuma numuru): ";
                    cin >> indekss;
                        cin.ignore();
                        if (indekss < 1 || indekss > s.getJautajumuSkaits()) cout << "Izvēlies derīgu jautājumu!\n";
                    } while (indekss < 1 || indekss > s.getJautajumuSkaits());
                    cout << "Jautājuma atbildes: \n";
                    s.getJaut(indekss).getAtbildes();

                    do {
                        cout << "Ievadi jauno jautājumu: ";
                        getline(cin, jaunaisJaut);
                        if (jaunaisJaut.empty()) cout << "Ievadi derīgu jautājumu!\n";
                    } while (jaunaisJaut.empty());

                    do {
                        cout << "Cik atbilžu varianti būs jaunajam jautājumam?: ";
                        cin >> atbilzuSk;
                        cin.ignore();
                        if (atbilzuSk < 1) cout << "Atbilžu skaitam jābūt vismaz 1!\n";

                    } while (atbilzuSk < 1);

                    for (int j = 1; j <= atbilzuSk; j++)
                    {
                        cout << "Ievadi " << j << ". atbildi: ";
                        getline(cin, atbilde);
                        atbildes.push_back(atbilde);
                    }

                    do {
                        cout << "Ievadi pareizās atbildes indeksu (1 līdz " << atbilzuSk << "): ";
                        cin >> jaunaPareizaAtb;
                        cin.ignore();

                        if (jaunaPareizaAtb < 1 || jaunaPareizaAtb > atbilzuSk) cout << "Nepareizs pareizās atbildes indekss! Mēģini vēlreiz.\n";
                    } while (jaunaPareizaAtb < 1 || jaunaPareizaAtb > atbilzuSk);

                    s.redigetJaut(indekss, jaunaisJaut, atbildes, jaunaPareizaAtb - 1);
                    break;
                }
            }

            if (!derigsID) {
                cout << "Ievadi derīgu spēles ID!\n";
            }

        } while (!derigsID);
    }
    else cout << "Nav izveidota neviena spēle!\n";
}

void Redaktors::dzestJautajumu() {

}




