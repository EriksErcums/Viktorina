#include "Redaktors.h"

#include <algorithm>
#include <string>
using namespace std;

void Redaktors::izveidotSpeli() {
    string nosaukums, grutibaslimenis, jautajums, atbilde;
    int maxp, jautaumuSk, spelesId;
    vector<string> atbildes;
    vector<Jautajums> jautajumi;

    do {
        cout << "Ievadi spēles nosaukumu: ";
        getline(cin, nosaukums);
        if (nosaukums.empty()) {
            cout << "Ievadi derīgu spēles nosaukumu!\n";
        }
    } while (nosaukums.empty());

    do {
        cout << "Ievadi spēles maksimālo punktu skaitu: ";
        cin >> maxp;
        cin.ignore();
        if (maxp < 1) {
            cout << "Punktu skaitam jābūt pozitīvam!\n";
        }
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
        cin >> jautaumuSk;
        cin.ignore();
        if (jautaumuSk < 1) {
            cout << "Spēlei ir jāsastāv no vismaz 1 jautājuma\n";
        }
    } while (jautaumuSk < 1);

    for (int i = 1; i <= jautaumuSk; i++) {
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
    do {
        cout << "Kurai spēlei vēlies pievienot jautājumu? (Ievadi spēles ID): ";
        cin >> spelesID;
        for (Spele& s : izveidotasSpeles) {
            if (s.getId() == spelesID) {
                cout << "Cik jautājums pievienosi?: ";
                cin >> jautajumuSk;
                cin.ignore();

                for (int i = 1; i <= jautajumuSk; i++)
                {
                    jautajumi.push_back(pievienot_jautajums_helper(i));
                }
                if (!jautajumi.empty()) s.pievienotJaut(jautajumi);
                break;
            }
        }

        if (jautajumi.empty()) cout << "Spēlei ir jāsastāv no vismaz 1 jautājuma\n";
        if (spelesID < 1 || spelesID > izveidotasSpeles.size()) cout << "Ievadi derīgu spēles ID!\n";


        } while (spelesID < 1 || spelesID > izveidotasSpeles.size() || jautajumi.empty());
    }
    else cout << "Nav izveidota neviena spēle!\n";
}


void Redaktors::dzestJautajumu() {

}

Jautajums Redaktors::pievienot_jautajums_helper(const int i) {
    string jautajums, atbilde;
    int atbilzuSk, pareizaAtb;
    vector<string> atbildes;
    cout << "Ievadi " << i << ". jautājumu: ";
    getline(cin, jautajums);

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


