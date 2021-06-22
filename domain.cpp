//
// Created by Sakura on 6/22/2021.
//


#include "domain.h"
#include <sstream>
#include <iostream>

std::istream& operator>>(std::istream& in, Ethnologist& e)
{
    in.clear(); in.sync();

    std::string name, area, line;
    //int x;

    std::getline(in, line);
    std::stringstream attrib(line);

    std::getline(attrib, name, ';');
    e.name = name;

    std::getline(attrib, area, ';');
    e.thematicArea = area;

    return in;
}

std::istream& operator>>(std::istream& in, Building& b)
{
    in.clear(); in.sync();

    int identifier;
    std::string line, id;
    std::string description;
    std::string thematicArea, coord;
    std::vector<std::string> locationCoord;

    std::getline(in, line);
    std::stringstream attrib(line);

    std::getline(attrib, id, ';');
    std::stringstream aux(id);
    aux >> identifier;
    b.identifier = identifier;

    std::getline(attrib, description, ';');
    b.description = description;

    std::getline(attrib, thematicArea, ';');
    b.thematicArea = thematicArea;

    std::getline(attrib, coord, '\n');
    b.locationString = coord;
    size_t pos = 0;
    std::string token;
    while ((pos = coord.find(';')) != std::string::npos) {
        token = coord.substr(0, pos);
        coord.erase(0, pos + 1);
        b.locationCoord.push_back(token);
    }
    b.locationCoord.push_back(coord);
    return in;
}
