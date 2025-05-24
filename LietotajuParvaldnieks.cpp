#include "LietotajuParvaldnieks.h"
#include "Redaktors.h"
#include "Speletajs.h"
#include "sqlite3/sqlite3.h"
#include "bcrypt/bcrypt.h"
#include <filesystem>
#include <fstream>

#include <iostream>
#include <string>

#include "PaligFunkcijas.h"

using namespace std;

void LietotajuParvaldnieks::izveidotProfilu() {
    string lv, p, l;
    do {
        lv = stringIevade("Ievadi lietotājvārdu: ");
        p = stringIevade("Ievadi paroli: ");
        l = stringIevade("Kāda būs lietotāja loma? (Spēlētājs | Redaktors): ");

        if (lv.length() < 3) cout << "Pārāk īss lietotājvārds!\n";
        if (lv.length() > 20) cout << "Pārāk garš lietotājvārds!\n";
        if (p.length() < 8) cout << "Pārāk īsa parole!\n";
        if (!saturCiparu(p)) cout << "Parolē ir jāiekļauj cipars!\n";
        if (!saturLieloBurtu(p)) cout << "Parolē ir jāiekļauj lielais burts!\n";
        if (l != "Spēlētājs" && l != "Redaktors") cout << "Lietotājam jābūt vai nu spēlētājam vai arī redaktoram!\n";

    } while (lv.length() < 3 || lv.length() > 20 || p.length() < 8 || (!saturCiparu(p) || !saturLieloBurtu(p)) || l != "Spēlētājs" && l != "Redaktors");
    pedejaisID = dabutPedejoId() + 1;

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

Lietotajs* LietotajuParvaldnieks::pieslegties() {
    string lietotajvards = stringIevade("ievadi lietotājvārdu: ");
    string parole = stringIevade("Ievadi paroli: ");

    sqlite3* db;
    sqlite3_stmt* stmt;

    int rc = sqlite3_open("lietotaji.db", &db);
    if (rc) {
        cerr << "Neizdevās atvērt datubāzi: " << sqlite3_errmsg(db) << endl;
        return nullptr;
    }

    string sql = "SELECT parole FROM lietotaji WHERE lietotajvards = ?;";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, lietotajvards.c_str(), -1, SQLITE_TRANSIENT);

    if (rc != SQLITE_OK) {
        cerr << "Radās kļūda nolasot paroli, lomu no datubāzes: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return nullptr;
    }

    Lietotajs* atrastsLietotajs = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        string Iegutaparole = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        if (bcrypt::validatePassword(parole, Iegutaparole)) {
            for (Lietotajs* lietotajs : lietotaji) {
                if (lietotajs->getLietotajvards() == lietotajvards) {
                    atrastsLietotajs = lietotajs;
                    break;
                }
            }
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return atrastsLietotajs;
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
        sqlite3_close(db);
        return;
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

    string hashedP = bcrypt::generateHash(p);  // sašifrē(hash) paroli
    string insertSQL = "INSERT INTO lietotaji (id, lietotajvards, parole, loma) VALUES (" +
                       to_string(id) + ", '" + lv + "', '" + hashedP + "', '" + l + "');";

    rc = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Radās kļūda saglabājot lietotāju datubāzē: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return;
    }

    sqlite3_close(db);
}

int LietotajuParvaldnieks::dabutPedejoId() {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;
    int maxID = 0;

    rc = sqlite3_open("lietotaji.db", &db);

    if (rc) {
        cerr << "Neizdevās atvērt datubāzi: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    string sql = "SELECT MAX(id) FROM lietotaji;";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            maxID = sqlite3_column_int(stmt, 0);
        }
    } else {
        cerr << "Radās kļūda vaicājumā: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return maxID;
}

void LietotajuParvaldnieks::izveidotDB() {
    sqlite3* db;
    char* errMsg;
    int rc = sqlite3_open("lietotaji.db", &db);
    if (rc) {
        cerr << "Nevar atvērt datubāzi: " << sqlite3_errmsg(db) << endl;
        return;
    }

    string izveidotTabulu =
        "CREATE TABLE IF NOT EXISTS lietotaji ("
        "id INTEGER PRIMARY KEY, "
        "lietotajvards TEXT NOT NULL, "
        "parole TEXT NOT NULL, "
        "loma TEXT NOT NULL);";

    rc = sqlite3_exec(db, izveidotTabulu.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Kļūda veidojot tabulu: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return;
    }

    sqlite3_close(db);
}

void LietotajuParvaldnieks::ieladetLietotajusNoDB() {
    sqlite3* db;
    sqlite3_stmt* stmt;

    int rc = sqlite3_open("lietotaji.db", &db);
    if (rc) {
        cerr << "Neizdevās atvērt datubāzi: " << sqlite3_errmsg(db) << endl;
        return;
    }

    string sql = "SELECT id, lietotajvards, parole, loma FROM lietotaji;";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Radās kļūda nolasot lietotājus no datubāzes: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    lietotaji.clear();

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string lietotajvards = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string parole = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string loma = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        if (loma == "Speletajs") {
            lietotaji.push_back(new Speletajs(id, lietotajvards, parole));
        } else if (loma == "Redaktors") {
            lietotaji.push_back(new Redaktors(id, lietotajvards, parole));
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void LietotajuParvaldnieks::protokoluUzFailu(Speletajs& s, SpelesProtokols &protokols) {

    if (!filesystem::exists("lietotajuProtokoli")) {
        if (filesystem::create_directory("lietotajuProtokoli")) {
            protokolsUzFailuHelper(s.getLietotajvards(), protokols);
        } else {
            cout << "Neizdevās izveidot mapi \"lietotajuProtokoli\".\n";
        }
    } else {
        protokolsUzFailuHelper(s.getLietotajvards(), protokols);
    }
}

void LietotajuParvaldnieks::protokolsUzFailuHelper(const string& nosaukums, SpelesProtokols& protokols) {
    string failaNosaukums = "lietotajuProtokoli/" + nosaukums + ".txt";

    bool eksiste = filesystem::exists(failaNosaukums);

    ofstream fails(failaNosaukums, ios::app);

    if (!fails) {
        cerr << "Neizdevās atvērt failu " << failaNosaukums << "\n";
        return;
    }

    if (!eksiste) fails << "Spēles protokoli par lietotāju " << nosaukums << ":\n\n";

        fails << "Spēlētāja ID: " << protokols.getSpeletajaID() << "\n";
        fails << "Spēlētāja lietotājvārds: " << protokols.getLietotajvardu() << "\n";
        fails << "Spēlētā spēle: " << protokols.getSpele().getNosaukums() << "\n";
        fails << "Spēles sākuma laiks: " << protokols.getSakums() << "\n";
        fails << "Spēles beigu laiks: " << protokols.getBeigas() << "\n";
        fails << "Iegūtie punkti par spēli: " << protokols.getPunkti() << " no " << protokols.getSpele().getMaxPunkti() << "\n";
        protokols.kopsavilkumsParDarbibam(fails);
        fails << "\n";
    fails.close();
    }