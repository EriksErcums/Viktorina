#include "LietotajuParvaldnieks.h"
#include "Redaktors.h"
#include "Speletajs.h"
#include "sqlite3/sqlite3.h"
#include "bcrypt/bcrypt.h"

#include <iostream>
#include <string>

using namespace std;

void LietotajuParvaldnieks::izveidotProfilu() {
    string lv, p, l;
    do {
        cout << "Ievadi lietotājvārdu: ";
        cin >> lv;

        cout << "Ievadi paroli: ";
        cin >> p;

        cout << "Kāda būs lietotāja loma? (Spēlētājs | Redaktors): ";
        cin >> l;

        if (lv.length() < 3) cout << "Pārāk īss lietotājvārds!\n";
        if (lv.length() > 20) cout << "Pārāk garš lietotājvārds!\n";
        if (p.length() < 8) cout << "Pārāk īsa parole!\n";
        if (!saturCiparu(p)) cout << "Parolē ir jāiekļauj cipars!\n";
        if (!saturLieloBurtu(p)) cout << "Parolē ir jāiekļauj lielais burts!\n";
        if (l != "Spēlētājs" && l != "Redaktors") cout << "Lietotājam jābūt vai nu spēlētājam vai arī redaktoram!\n";

    } while (lv.length() < 3 || lv.length() > 20 || p.length() < 8 || (!saturCiparu(p) || !saturLieloBurtu(p)) || l != "Spēlētājs" && l != "Redaktors");
    pedejaisID++;

    if (l == "Spēlētājs") {
        lietotaji.push_back(new Speletajs(pedejaisID, lv, p));
        saglabatLietotajuDB(pedejaisID, lv, p, "Speletajs");
        cout << "Tika izveidots jauns spēlētāja profils\n";
    }
    if (l == "Redaktors") {
        cout << "Tika izveidots jauns Redaktora profils\n";
        lietotaji.push_back(new Redaktors(pedejaisID, lv, p));
        saglabatLietotajuDB(pedejaisID, lv, p, "Redaktors");
    }
}

bool LietotajuParvaldnieks::saturLieloBurtu(const string& parole) {
    for (int i = 0; i < parole.length(); i++) {
        if (isupper(parole[i])) return true;
    }
    return false;
}

bool LietotajuParvaldnieks::saturCiparu(const string& parole) {
    for (int i = 0; i < parole.length(); i++) {
        if (isdigit(parole[i])) return true;
    }
    return false;
}

void LietotajuParvaldnieks::dzestLietotaju() {
    int id;
    apskatitLietotajus();
    cout << "Ievadi lietotāja ID, kuru vēlies dzēst: ";
    cin >> id;

    bool izdzests = false;
    for (auto it = lietotaji.begin(); it != lietotaji.end();) {
        if ((*it)->getId() == id) {
            delete *it;
            it = lietotaji.erase(it);
            dzestLietotajuDB(id);
            izdzests = true;
            break;
        } else {
            ++it;
        }
    }

    if (izdzests) {
        cout << "Lietotājs ar ID " << id << " tika izdzēsts\n";
    } else {
        cout << "Lietotājs ar ID " << id << " netika atrasts\n";
    }
}

void LietotajuParvaldnieks::dzestLietotajuDB(int id) {

    sqlite3* db;
    char* errMsg;
    int rc;

    rc = sqlite3_open("lietotaji.db", &db);

    if (rc) {
        cerr << "Nevar atvērt datubāzi: " << sqlite3_errmsg(db) << endl;
        return;
    }

    string sql = "DELETE FROM lietotaji WHERE id = " + to_string(id) + ";";

    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Radās kļūda dzēšot lietotāju: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
}

void LietotajuParvaldnieks::saglabatLietotajuDB(const int id, const string& lv, const string& p, const string& l) {

    sqlite3* db;
    char* errMsg;
    int rc;

    rc = sqlite3_open("lietotaji.db", &db);

    if (rc) {
        cerr << "Neizdevās atvērt datubāzi: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // Izveido tabulu, ja neeksistē
    string izveidotTabulu =
        "CREATE TABLE IF NOT EXISTS lietotaji ("
        "id INTEGER PRIMARY KEY, "
        "lietotajvards TEXT NOT NULL, "
        "parole TEXT NOT NULL, "
        "loma TEXT NOT NULL);";

    rc = sqlite3_exec(db, izveidotTabulu.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Radās Kļūda veidojot tabulu: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return;
    }
    string hashedP = bcrypt::generateHash(p);
    string insertSQL = "INSERT INTO lietotaji (id, lietotajvards, parole, loma) VALUES (" +
                       to_string(id) + ", '" + lv + "', '" + hashedP + "', '" + l + "');";

    rc = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Radās kļūda saglabājot lietotāju datubāzē: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
}






