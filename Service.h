//
// Created by Sakura on 6/22/2021.
//

#ifndef E2_913ALICEHINCU_SERVICE_H
#define E2_913ALICEHINCU_SERVICE_H


#include <iostream>
#include "Observer.h"
#include "Repository.h"

class EthnologistService: public Observable{
private:
    EthnologistRepo* repo;
public:
    explicit EthnologistService(EthnologistRepo* r): repo(r){}
    ~EthnologistService() = default;
    std::vector<Ethnologist> &getElems() { return this->repo->getElems(); }
    /*
    void increaseRevisedFiles(const std::string& name) {
        for (auto &programmer: this->getElems()) {
            if (programmer.getName() == name) {
                programmer.increaseRevisedFiles();
            }
        }
        this->notify();
    }*/
    /*
    void setFile(int idx) {
        this->repo->getElems()[idx].setRevised();
        this->repo->getElems()[idx].setTotal();
        this->notify();
    }*/
};

class BuildingService: public Observable {
private:
    BuildingRepo* repo;
public:
    explicit BuildingService(BuildingRepo* r): repo(r){}
    ~BuildingService() = default;
    std::vector<Building>& getElems() { return this->repo->getElems(); }

    void add(const Building& b) {
        this->repo->add(b);
        this->notify();
    }
    void modify(int id, std::string descr, std::string loc, std::vector<std::string> vecLoc) {
        this->repo->modify(id, descr, loc, vecLoc);
        this->notify();
    }
/*
    void setFile(int idx, const std::string& name) {
        this->repo->getElems()[idx].setReviewer(name);
        this->repo->getElems()[idx].setStatus("revised");
        this->notify();
    }
    */

};

#endif //E2_913ALICEHINCU_SERVICE_H
