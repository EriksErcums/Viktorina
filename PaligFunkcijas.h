#ifndef PALIGFUNKCIJAS_H
#define PALIGFUNKCIJAS_H

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "Spele.h"

// Helper metodes, kuras var izmantot jebkura klase:

int dabutSpelesId(std::vector<Spele>& speles, const std::string& teksts);
int skaitluIevade(const std::string& teksts, int minVertiba);
std::string stringIevade(const std::string& teksts);

#endif