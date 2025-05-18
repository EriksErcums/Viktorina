#include "SpeluParvaldnieks.h"
#include <string>
#include <algorithm>
#include "Speletajs.h"
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

