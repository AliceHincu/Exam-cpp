//
// Created by Sakura on 6/22/2021.
//

#include <QSortFilterProxyModel>
#include <sstream>
#include <QMessageBox>
#include "GUI.h"

void TabsGUI::guiInit() {
    ///window
    this->setWindowTitle(QString::fromStdString(this->name));
    auto* mainLayout = new QHBoxLayout{ this }; //general layout
    std::vector<std::string> colors{"red", "yellow", "blue", "white"};
    int randomIndex = rand() % colors.size();
    this->setStyleSheet("background-color: "+QString::fromStdString(colors[randomIndex])+";");

    ///table with files
    this->buildingsList = new QTableView{};
    this->modelList = new TableModel{this->bs, this->thematicArea};
    auto* sortModel = new QSortFilterProxyModel{};
    sortModel->setSourceModel(this->modelList);
    this->buildingsList->setModel(sortModel);
    this->buildingsList->setSortingEnabled(true);
    this->buildingsList->sortByColumn(0, Qt::AscendingOrder);
    mainLayout->addWidget(this->buildingsList);
    //QObject::connect(this->fileList, &QTableView::clicked, this, &TabsGUI::changeStatus);

    ///add building
    auto* rightSide = new QVBoxLayout{};
    auto* lineeditlayout = new QGridLayout{};
    auto* idLabel = new QLabel{"Id:"};
    this->idLineEdit = new QLineEdit{};
    lineeditlayout->addWidget(idLabel,0,0,1,1);
    lineeditlayout->addWidget(this->idLineEdit,0,1,1,1);

    auto* descriptionLabel = new QLabel{"Description:"};
    this->descriptionLineEdit = new QLineEdit{};
    lineeditlayout->addWidget(descriptionLabel,1,0,1,1);
    lineeditlayout->addWidget(this->descriptionLineEdit,1,1,1,1);

    auto* locationLabel = new QLabel{"Location:"};
    this->locationLineEdit = new QLineEdit{};
    lineeditlayout->addWidget(locationLabel,2,0,1,1);
    lineeditlayout->addWidget(this->locationLineEdit,2,1,1,1);

    this->addButton = new QPushButton{"Add building"};
    lineeditlayout->addWidget(this->addButton, 3, 0, 1, 2);
    rightSide->addLayout(lineeditlayout);
    QObject::connect(this->addButton, &QPushButton::clicked, this, &TabsGUI::addHandler);

    ///update
    auto* idExistingLabel = new QLabel{"Existing id building:"};
    this->existingIdLineEdit = new QLineEdit{};
    lineeditlayout->addWidget(idExistingLabel,4,0,1,1);
    lineeditlayout->addWidget(this->existingIdLineEdit,4,1,1,1);


    auto* updateLocationLabel = new QLabel{"Update location:"};
    this->updateLocationLineEdit = new QLineEdit{};
    lineeditlayout->addWidget(updateLocationLabel,5,0,1,1);
    lineeditlayout->addWidget(this->updateLocationLineEdit,5,1,1,1);

    auto* updateDescriptionLabel = new QLabel{"Update description:"};
    this->updateDescriptionLineEdit = new QLineEdit{};
    lineeditlayout->addWidget(updateDescriptionLabel,6,0,1,1);
    lineeditlayout->addWidget(this->updateDescriptionLineEdit,6,1,1,1);

    this->updateButton = new QPushButton{"Update building"};
    lineeditlayout->addWidget(this->updateButton, 7, 0, 1, 2);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &TabsGUI::updateHandler);


    /*int identifier;
    std::string description;
    //std::string themArea;
    std::string locationString;
    std::vector<std::string> locationCoord;
    this->addButton = new QPushButton{"Add file"};
    this->addLineEdit = new QLineEdit{};
    rightSide->addWidget(this->addButton);
    rightSide->addWidget(this->addLineEdit);*/
    //

    mainLayout->addLayout(rightSide);
}


void TabsGUI::addHandler(){
    int id = stoi(this->idLineEdit->text().toStdString());
    std::string descr = this->descriptionLineEdit->text().toStdString();
    std::string location = this->locationLineEdit->text().toStdString();
    std::string parsed;
    std::string area = this->thematicArea;
    std::vector<std::string> locationCoord;
    //std::stringstream input_stringstream(location);



    size_t pos = 0;
    std::string token;
    while ((pos = location.find(';')) != std::string::npos) {
        token = location.substr(0, pos);
        location.erase(0, pos + 1);
        locationCoord.push_back(token);
        std::cout << token << " ";
    }
    locationCoord.push_back(location);

    if (descr.empty()) {
        QMessageBox::warning(this->buildingsList, "Error", "Empty string!");
        return;
    }
    for (const auto& building : this->bs.getElems())
        if (building.getIdentifier() == id) {
            QMessageBox::warning(this->buildingsList, "Error", "Id already exists!");
            return;
        }
    for (auto building : this->bs.getElems())
        for(const auto& tok : locationCoord) {
            for(const auto& check : building.getCoord())
                if (check == tok) {
                    QMessageBox::warning(this->buildingsList, "Error", "Buildings overlap!");
                    return;
            }
        }
    auto building = Building(id, descr, area, locationCoord);
    this->bs.add(building);
}

void TabsGUI::updateHandler() {
    int id = stoi(this->existingIdLineEdit->text().toStdString());
    std::string descr = this->updateDescriptionLineEdit->text().toStdString();
    std::string location = this->updateLocationLineEdit->text().toStdString();
    std::vector <std::string> locationCoord;

    size_t pos = 0;
    std::string token;
    while ((pos = location.find(';')) != std::string::npos) {
        token = location.substr(0, pos);
        location.erase(0, pos + 1);
        locationCoord.push_back(token);
        std::cout << token << " ";
    }
    locationCoord.push_back(location);

    if (descr.empty()) {
        QMessageBox::warning(this->buildingsList, "Error", "Empty string!");
        return;
    }

    for (auto building : this->bs.getElems())
        for(const auto& tok : locationCoord) {
            for(const auto& check : building.getCoord())
                if (check == tok) {
                    QMessageBox::warning(this->buildingsList, "Error", "Buildings overlap!");
                    return;
                }
        }

    int ok=0;
    for (auto building : this->bs.getElems())
        if (building.getIdentifier() == id) {
            building.setCoord(locationCoord);
            building.setLocationString(location);
            building.setDescription(descr);
            this->bs.notify();
            ok=1;
        }
    if(ok == 0){
        QMessageBox::warning(this->buildingsList, "Error", "Building does not exist!");
        return;
    }

}

void GUI::create_tabs() {
    for (const auto& et : this->es.getElems()) {
        std::cout << et.getName();

        auto* g = new TabsGUI(et.getName(), et.getThematicArea(),
                              this->es, this->bs);
        g->show();
    }
}
