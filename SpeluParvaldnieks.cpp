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

void SpeluParvaldnieks::saglabatRanguTabuluDB(const vector<Ieraksts>& ieraksti) {
    izveidotDBprieksRanguTab();

    sqlite3* db;
    char* errMsg;
    int rc;

    rc = sqlite3_open("RanguTabula.db", &db);

    if (rc) {
        cerr << "Neizdevās atvērt datubāzi: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // dzēš vecos ierakstus pirms pa jaunu ievieto
    string clearSQL = "DELETE FROM RanguTabula;";
    char* errmsg = nullptr;
    rc = sqlite3_exec(db, clearSQL.c_str(), nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK) {
        cerr << "Kļūda dzēšot vecos ierakstus: " << errmsg << endl;
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return;
    }

    for (const Ieraksts& ieraksts : ieraksti) {

        string insertSQL = "INSERT INTO RanguTabula (id, lietotajvards, punkti, laiks_sekundes) VALUES (" +
    to_string(ieraksts.speletajsID) + ", '" +
    ieraksts.lietotajvards + "', " +
    to_string(ieraksts.punkti) + ", " +
    to_string(ieraksts.laiks) + ");";

        rc = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            cerr << "Radās kļūda saglabājot rangu tabulu datubāzē: " << errMsg << endl;
            sqlite3_free(errMsg);
        }
    }
    sqlite3_close(db);
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
        "laiks_sekundes INTEGER);";

    rc = sqlite3_exec(db, izveidotTabulu.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Kļūda veidojot tabulu: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
}

void SpeluParvaldnieks::apskatitiesRanguTab() {
    sqlite3* db;
    sqlite3_stmt* stmt;

    int rc = sqlite3_open("RanguTabula.db", &db);
    if (rc) {
        cerr << "Neizdevās atvērt datubāzi: " << sqlite3_errmsg(db) << endl;
        return;
    }

    string sql = "SELECT id, lietotajvards, punkti, laiks_sekundes FROM RanguTabula ORDER BY punkti DESC, laiks_sekundes ASC;";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Radās kļūda nolasot rangu tabulu no datubāzes: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string lietotajvards = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int punkti = sqlite3_column_int(stmt, 2);
        int laiks = sqlite3_column_int(stmt, 3);

        cout << "ID: " << id << " | lietotājvārds: " << lietotajvards << " | Punkti: " << punkti << " | Laiks: " << laiks << " sekundes\n";
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}