#include "SpeluParvaldnieks.h"
#include <string>
#include <algorithm>
#include "Speletajs.h"
using namespace std;


void SpeluParvaldnieks::parbauditSasniegumus(Speletajs& speletajs, SpelesProtokols& protokols) {

    int pavaditaisLaiks = konverteUzSekundem(protokols.getBeigas()) - konverteUzSekundem(protokols.getSakums());
    vector<string> sasniegumi = speletajs.getSasniegumi();

    if (pavaditaisLaiks < 60) {
        if (!vaiSaturSasniegumu(sasniegumi, "Ātrs finišētājs: pabeigta spēle mazāk nekā 1 minūtes laikā")) {
            speletajs.pievienotSasniegumu("Ātrs finišētājs: pabeigta spēle mazāk nekā 1 minūtes laikā");
        }
    }
    if (pavaditaisLaiks < 30) {
        if (!vaiSaturSasniegumu(sasniegumi, "Ātruma dēmons: pabeigta spēle mazāk nekā 30 sekunžu laikā")) {
            speletajs.pievienotSasniegumu("Ātruma dēmons: pabeigta spēle mazāk nekā 30 sekunžu laikā");
        }
    }
    if (speletajs.getSpeletasSpeles() == 5) {
        if (!vaiSaturSasniegumu(sasniegumi, "Amatieris: nospēlētas 5 spēles")) {
            speletajs.pievienotSasniegumu("Amatieris: nospēlētas 5 spēles");
        }
    }
    if (speletajs.getSpeletasSpeles() == 10) {
        if (!vaiSaturSasniegumu(sasniegumi, "Veterāns: nospēlētas 10 spēles")) {
            speletajs.pievienotSasniegumu("Veterāns: nospēlētas 10 spēles");
        }
    }
    if (speletajs.getSpeletasSpeles() == 20) {
        if (!vaiSaturSasniegumu(sasniegumi, "Maratonists: nospēlētas 20 spēles")) {
            speletajs.pievienotSasniegumu("Maratonists: nospēlētas 20 spēles");
        }
    }
    if (protokols.getPunkti() == protokols.getSpele().getMaxPunkti()) {
        if (!vaiSaturSasniegumu(sasniegumi, "Perfekcionists: sasniegts perfekts rezultāts spēlē (100%)")) {
            speletajs.pievienotSasniegumu("Perfekcionists: sasniegts perfekts rezultāts spēlē (100%)");
        }
    }
}

bool SpeluParvaldnieks::vaiSaturSasniegumu(const vector<string>& sasniegumi, const std::string& sasniegums) {
    if (find(sasniegumi.begin(), sasniegumi.end(), sasniegums) != sasniegumi.end()) return true;
    return false;
}

