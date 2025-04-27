#include "Redaktors.h"

#include <algorithm>
#include <string>
using namespace std;


void Redaktors::izveidotSpeli() {
    string nosaukums, grutibaslimenis, jautajums, atbilde;
    int maxp, jautaumuSk, atbilzuSk, pareizaAtb, spelesId;
    vector<string> atbildes;
    vector<Jautajums> jautajumi;
    do
    {
        cout << "Ievadi spēles nosaukumu: ";
        getline(cin, nosaukums);

        cout << "Ievadi spēles maksimālo punktu skaitu: ";
        cin >> maxp;
        cin.ignore();

        cout << "Ievadi splēles grūtības līmeni: ";
        getline(cin, grutibaslimenis);

        cout << "Cik jautājumi būs spēlei?: ";
        cin >> jautaumuSk;
        cin.ignore();

        for (int i = 1; i <= jautaumuSk; i++)
        {
            cout << "Ievadi " << i << ". jautājumu: ";
            getline(cin, jautajums);

            cout << "Cik atbilžu varianti būs jautājumam?: ";
            cin >> atbilzuSk;
            cin.ignore();

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

                if (pareizaAtb < 1 || pareizaAtb > atbilzuSk) {
                    cout << "Nepareizs pareizās atbildes indekss! Mēģini vēlreiz.\n";
                }
            } while (pareizaAtb < 1 || pareizaAtb > atbilzuSk);

            jautajumi.push_back(Jautajums(jautajums, atbildes, pareizaAtb - 1));
            atbildes.clear();
        }

        if (nosaukums.empty()) cout << "Ievadi derīgu spēles nosaukumu!\n";
        if (maxp < 1) cout << "Punktu skaitam jābūt pozitīvam!\n";
        transform(grutibaslimenis.begin(), grutibaslimenis.end(), grutibaslimenis.begin(), ::tolower);
        if (grutibaslimenis != "viegls" && grutibaslimenis != "vidējs" && grutibaslimenis != "grūts")
            cout << "Spēles grūtības līmenim jābūt vienam no trim variantiem: \"viegls\", \"vidējs\", \"grūts\"\n";
        if (jautajumi.empty()) cout << "Spēlei ir jāsastāv no vismaz 1 jautājuma\n";
    } while (nosaukums.empty() || maxp < 1 || grutibaslimenis.empty() || jautajumi.empty());
    if (izveidotasSpeles.empty()) {
        spelesId = 1;
    }
    else {
        spelesId = izveidotasSpeles.back().getId() + 1;
    }
    izveidotasSpeles.push_back(Spele(spelesId, nosaukums, maxp, grutibaslimenis, jautajumi));

}

void Redaktors::pievienotJautajumu() {

}

void Redaktors::dzestJautajumu() {

}


