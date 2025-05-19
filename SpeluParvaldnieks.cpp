#include "SpeluParvaldnieks.h"
#include <string>
#include <algorithm>
#include "Speletajs.h"
#include "sqlite3/sqlite3.h"
using namespace std;

void SpeluParvaldnieks::parbauditSasniegumus(Speletajs& speletajs, SpelesProtokols& protokols) {

    int pavaditaisLaiks = konverteUzSekundem(protokols.getBeigas()) - konverteUzSekundem(protokols.getSakums());
    vector<string> sasniegumi = speletajs.getSasniegumi();

    if (pavaditaisLaiks < 60) {
        string sasniegums = "Ātrs finišētājs: pabeigta spēle mazāk nekā 1 minūtes laikā\n";
        if (!vaiSaturSasniegumu(sasniegumi, sasniegums)) {
            speletajs.pievienotSasniegumu(sasniegums);
            cout << "Tu ieguvi sasniegumu!: " << sasniegums;
        }
    }
    if (pavaditaisLaiks < 30) {
        string sasniegums = "Ātruma dēmons: pabeigta spēle mazāk nekā 30 sekunžu laikā\n";
        if (!vaiSaturSasniegumu(sasniegumi, sasniegums)) {
            speletajs.pievienotSasniegumu(sasniegums);
            cout << "Tu ieguvi sasniegumu!: " << sasniegums;
        }
    }
    if (speletajs.getSpeletasSpeles() == 5) {
        string sasniegums = "Amatieris: nospēlētas 5 spēles\n";
        if (!vaiSaturSasniegumu(sasniegumi, sasniegums)) {
            speletajs.pievienotSasniegumu(sasniegums);
            cout << "Tu ieguvi sasniegumu!: " << sasniegums;
        }
    }
    if (speletajs.getSpeletasSpeles() == 10) {
        string sasniegums = "Veterāns: nospēlētas 10 spēles\n";
        if (!vaiSaturSasniegumu(sasniegumi, sasniegums)) {
            speletajs.pievienotSasniegumu(sasniegums);
            cout << "Tu ieguvi sasniegumu!: " << sasniegums;
        }
    }
    if (speletajs.getSpeletasSpeles() == 20) {
        string sasniegums = "Maratonists: nospēlētas 20 spēles\n";
        if (!vaiSaturSasniegumu(sasniegumi, sasniegums)) {
            speletajs.pievienotSasniegumu(sasniegums);
            cout << "Tu ieguvi sasniegumu!: " << sasniegums;
        }
    }
    if (protokols.getPunkti() == protokols.getSpele().getMaxPunkti()) {
        string sasniegums = "Perfekcionists: sasniegts perfekts rezultāts spēlē (100%)\n";
        if (!vaiSaturSasniegumu(sasniegumi, sasniegums)) {
            speletajs.pievienotSasniegumu(sasniegums);
            cout << "Tu ieguvi sasniegumu!: " << sasniegums;
        }
    }
}

bool SpeluParvaldnieks::vaiSaturSasniegumu(const vector<string>& sasniegumi, const std::string& sasniegums) {
    if (find(sasniegumi.begin(), sasniegumi.end(), sasniegums) != sasniegumi.end()) return true;
    return false;
}

void SpeluParvaldnieks::saglabatRanguTabuluDB(const vector<Ieraksts>& ieraksts) {
    izveidotDBprieksRanguTab();
    // TODO: ievietot ierakstus db, ja izveidotDBprieksRanguTab() veiksmigi izpildas
    // TODO:: izdomat ka noverst ierakstos duplikatus (viens un pats lietotajs, bet paturet tikai ar lielako p skaitu
}

void SpeluParvaldnieks::izveidotDBprieksRanguTab() {
    sqlite3* db;
    char* errMsg;
    int rc = sqlite3_open("RanguTabula.db", &db);
    if (rc) {
        cerr << "Nevar atvērt datubāzi: " << sqlite3_errmsg(db) << endl;
        return;
    }

    string izveidotTabulu =
        "CREATE TABLE IF NOT EXISTS RanguTabula ("
        "id INTEGER PRIMARY KEY, "
        "lietotajvards TEXT NOT NULL, "
        "punkti INTEGER, "
        "laiks INTEGER);";

    rc = sqlite3_exec(db, izveidotTabulu.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Kļūda veidojot tabulu: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
}



