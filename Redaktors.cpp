#include "Redaktors.h"
#include <string>
using namespace std;


/*void Redaktors::izveidotSpeli() {
    string nosaukums, grutibaslimenis, jautajums, atbilde;
    int maxp, jautaumuSk, atbilzuSk, pareizaAtb;
    vector<string> atbildes;
    vector<Jautajums> jautajumi;
    jautajumi.clear();
    do
    {
        cout << "Ievadi spēles nosaukumu: ";
        cin >> nosaukums;

        cout << "Ievadi spēles maksimālo punktu skaitu: ";
        cin >> maxp;

        cout << "Ievadi splēles grūtības līmeni: ";
        cin >> grutibaslimenis;

        cout << "Cik jautājumi būs spēlei?: ";
        cin >> jautaumuSk;

        for (int i = 1; i <= jautaumuSk; i++)
        {
            cout << "Ievadi " << i << ". jautājumu: ";
            cin >> jautajums;

            cout << "Cik atbilžu varianti būs jautājumam?: ";
            cin >> atbilzuSk;

            for (int j = 1; j <= atbilzuSk; j++)
            {
                cout << "Ievadi " << j << ". atbildi: ";
                cin >> atbilde;
                atbildes.push_back(atbilde);
            }

            cout << "Ievadi pareizās atbildes indeksu: ";
            cin >> pareizaAtb;
            Jautajums j(jautajums, atbildes, pareizaAtb);
            jautajumi.push_back(j);
            atbildes.clear();
        }
    } while ();
    izveidotasSpeles.push_back(new Spele(0, nosaukums, maxp, grutibaslimenis, jautajumi));

}*/

void Redaktors::pievienotJautajumu() {

}

void Redaktors::dzestJautajumu() {

}


