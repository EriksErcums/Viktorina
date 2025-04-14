#ifndef LIETOTAJUPARVALDNIEKS_H
#define LIETOTAJUPARVALDNIEKS_H
#include <vector>

#include "Lietotajs.h"

class LietotajuParvaldnieks {

private:
    std::vector<Lietotajs*> lietotaji;
    int pedejaisID = 0;

public:
    void izveidotProfilu();
    bool saturLieloBurtu(const std::string& parole);
    bool saturCiparu(const std::string& parole);
    //TODO: void dzestLietotaju();
    //TODO: void saglabatLietotajuDB(int id, std::string lietotajvards, std::string parole, std::string loma);
    //TODO: void apskatitLietotajus() {}
};

#endif
