//
// Created by Sakura on 6/22/2021.
//

#ifndef E2_913ALICEHINCU_REPOSITORY_H
#define E2_913ALICEHINCU_REPOSITORY_H

#include "domain.h"

class EthnologistRepo {
private:
    std::vector<Ethnologist> ethnologists;
    std::string file;
public:
    explicit EthnologistRepo(std::string  file) :file(std::move(file)) { load(); };
    ~EthnologistRepo() = default;
    std::vector<Ethnologist>& getElems() { return this->ethnologists; }
    void load();
};


class BuildingRepo {
private:
    std::vector<Building> buildings;
    std::string file;
public:
    explicit BuildingRepo(std::string  file): file(std::move(file)){ load(); }
    ~BuildingRepo() = default;
    std::vector<Building>& getElems() { return this->buildings; }
    void add(const Building& b) {
        this->buildings.push_back(b);
    }
    /*
    bool isNotExisting(const SourceFile& source) {
        for (const auto& f : this->files)
            if (f.getName() == source.getName())
                return false;
        return true;
    }

    void sort(bool (*compare)(SourceFile, SourceFile)) { std::sort(this->files.begin(), this->files.end(), compare); }
    */
     void load();
};


#endif //E2_913ALICEHINCU_REPOSITORY_H
