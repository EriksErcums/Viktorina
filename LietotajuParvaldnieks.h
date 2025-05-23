#ifndef LIETOTAJUPARVALDNIEKS_H
#define LIETOTAJUPARVALDNIEKS_H
#include <vector>

#include "Lietotajs.h"
#include "Speletajs.h"

class SpelesProtokols;

class LietotajuParvaldnieks {

private:
    std::vector<Lietotajs*> lietotaji;
    int pedejaisID;

public:
    LietotajuParvaldnieks() {izveidotDB(); ieladetLietotajusNoDB();}
    void izveidotProfilu();
    bool saturLieloBurtu(const std::string& parole);
    bool saturCiparu(const std::string& parole);
    void dzestLietotaju();
    void dzestLietotajuDB(int id);
    void saglabatLietotajuDB(int id, const std::string& lv, const std::string& p, const std::string& l);
    void apskatitLietotajus() {
        if (lietotaji.empty()) {
            std::cout << "Nav izveidots neviens lietotājs!\n";
            return;
        }
        std::cout << "Izveidotie lietotāji:\n";
        for (Lietotajs* lietotajs : lietotaji) lietotajs->printInfo();
    }
    int dabutPedejoId();
    void izveidotDB();
    void ieladetLietotajusNoDB();
    Lietotajs* pieslegties();
    void protokoluUzFailu(Speletajs& s, SpelesProtokols& protokols);
    void protokolsUzFailuHelper(const std::string& nosaukums, SpelesProtokols& protokols);
    void clearLietotaji() {
        for (Lietotajs* lietotajs : lietotaji) {
            delete lietotajs;
        }
        lietotaji.clear();
    }
};

#endif
