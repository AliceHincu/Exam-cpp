//
// Created by Sakura on 6/22/2021.
//

#include <QSortFilterProxyModel>
#include <sstream>
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
    std::stringstream input_stringstream(location);

    if (getline(input_stringstream,parsed,';'))
    {
        locationCoord.push_back(parsed);
    }
    auto building = Building(id, descr, area, locationCoord);
    this->bs.add(building);
}

void GUI::create_tabs() {
    for (const auto& et : this->es.getElems()) {
        std::cout << et.getName();

        auto* g = new TabsGUI(et.getName(), et.getThematicArea(),
                              this->es, this->bs);
        g->show();
    }
}
