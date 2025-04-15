#ifndef LIETOTAJS_H
#define LIETOTAJS_H

#include <iostream>
#include <string>

class Lietotajs {

protected:
    int id = -1;
    std::string lietotajvards = "NA", parole = "NA", loma;

public:
    Lietotajs(int Id = -1, std::string lv = "NA", std::string p = "NA") : id(Id), lietotajvards(lv), parole(p) {}

    virtual ~Lietotajs() = default;

    virtual std::string getLoma() = 0;
    int getId() const {return id;}
    std::string getLietotajvards() {return lietotajvards;}
    std::string getParole() {return parole;}

    void setId(const int Id) {id = Id;}
    void setLietotajvards(const std::string &lv) {lietotajvards = lv;}
    void setParole(const std::string &p) {parole = p;}

    void printInfo() {std::cout << "ID: " << id << ", Lietotājvārds: " << lietotajvards << ", Loma: " << getLoma() << "\n";}
};

#endif
