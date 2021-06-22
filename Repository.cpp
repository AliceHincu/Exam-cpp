//
// Created by Sakura on 6/22/2021.
//

//
// Created by Sakura on 6/21/2021.
//
//
// Created by Sakura on 6/21/2021.
//
#include "Repository.h"
#include <sstream>
#include <fstream>

void EthnologistRepo::load()
{
    std::ifstream fin;
    fin.open(this->file);
    if (!fin.is_open())
        return;
    Ethnologist el;
    while (!fin.eof()) {
        fin >> el;
        this->ethnologists.push_back(el);
    }
    fin.close();
}

void BuildingRepo::load()
{
    std::ifstream fin;
    fin.open(this->file);
    if (!fin.is_open())
        return;
    Building el;
    while (!fin.eof()) {
        fin >> el;
        this->buildings.push_back(el);
    }
    fin.close();
}
