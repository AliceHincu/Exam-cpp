//
// Created by Sakura on 6/22/2021.
//

#ifndef E2_913ALICEHINCU_DOMAIN_H
#define E2_913ALICEHINCU_DOMAIN_H

#include <string>
#include <utility>
#include <vector>

class Ethnologist{
private:
    std::string name;
    std::string thematicArea;
public:
    Ethnologist(std::string aName, std::string aThematicArea): name(std::move(aName)), thematicArea(std::move(aThematicArea))  {};
    Ethnologist(): name(""), thematicArea("") {};
    Ethnologist(const Ethnologist& other){
        this->name = other.name;
        this->thematicArea = other.thematicArea;
    }
    ~Ethnologist() = default;
    std::string getName() const { return this->name; }
    std::string getThematicArea() const{ return this->thematicArea; }
    //int getTotalFiles() const{ return this->nrTotalFiles; }
    //void increaseRevisedFiles() {this->nrRevisedFiles++;}
    friend std::istream& operator>>(std::istream& in, Ethnologist& e);
};

class Building{
private:
    int identifier;
    std::string description;
    std::string thematicArea;
    std::string locationString;
    std::vector<std::string> locationCoord;
public:
    Building(int i, std::string d, std::string  t, std::vector<std::string> l): identifier(std::move(i)), description(std::move(d)), thematicArea(std::move(t)), locationCoord(std::move(l)){};
    Building(): identifier(0), description(""), thematicArea(""), locationCoord(std::vector<std::string>()) {};
    ~Building() = default;
    int getIdentifier() const { return this->identifier; }
    std::string getDescription() const { return this->description; }
    std::string getThematicArea() const { return this->thematicArea; }
    std::string getLocationString() const { return this->locationString; }
    std::vector<std::string>& getCoord() { return this->locationCoord; }
    //void setStatus(const std::string& s) { this->status = s; }
    //void setReviewer(const std::string& r) { this->reviewer = r; }
    friend std::istream& operator>>(std::istream& in, Building& b);

};


#endif //E2_913ALICEHINCU_DOMAIN_H
