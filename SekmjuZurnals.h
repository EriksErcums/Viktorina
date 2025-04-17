#ifndef SEKMjUZURNALS_H
#define SEKMJUZURNALS_H

#include "SpelesProtokols.h"

#include <vector>

class SekmjuZurnals{

private:
    std::vector<SpelesProtokols> visiProtokoli;
public:
    std::vector<SpelesProtokols> iegutVisusProtokolus() { return visiProtokoli; };
    void pievienotProtokolu(SpelesProtokols protokols) { visiProtokoli.push_back(protokols); }; 
};

#endif