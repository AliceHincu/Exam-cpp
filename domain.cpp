//
// Created by Sakura on 6/22/2021.
//


#include "domain.h"
#include <sstream>

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

    while(std::getline(attrib, coord, ';')) {
        b.locationCoord.push_back(coord);
        b.locationString+=coord+";";
    }

    return in;
}
