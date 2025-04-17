#include "SpelesProtokols.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

string SpelesProtokols::iegutLaiku(){
    auto laiks = chrono::system_clock::now();
    time_t laiksTagad = chrono::system_clock::to_time_t(laiks);

    ostringstream ls;
    ls << put_time(localtime(&laiksTagad), "%H:%M:%S");
    
    return  ls.str();
}