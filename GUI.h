//
// Created by Sakura on 6/22/2021.
//

#ifndef E2_913ALICEHINCU_GUI_H
#define E2_913ALICEHINCU_GUI_H

#include <qwidget.h>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QApplication>
#include "Observer.h"
#include "Service.h"
#include <string>
#include <qlineedit.h>
#include <QTableView>
#include <utility>
#include "TableModel.h"

class GUI: public QWidget, public Observer {
private:
    EthnologistService& es;
    BuildingService& bs;
public:
    GUI(EthnologistService& e, BuildingService& b): es(e), bs(b) {
        //this->bs.addObserver(this);
        create_tabs();
    }
    ~GUI() {
        //this->ps.removeObserver(this);
    }
    void update() override {};
    void create_tabs();
};

class TabsGUI: public QWidget, public Observer {
private:
    std::string name;
    std::string thematicArea;
    //int lastSelected;

    EthnologistService& es;
    BuildingService& bs;
    QTableView* buildingsList{};
    TableModel* modelList{};
    QPushButton* addButton{};
    QLineEdit* idLineEdit{};
    QLineEdit* descriptionLineEdit{};
    QLineEdit* locationLineEdit{};

/*
    QLabel* revisedFiles{};
    QLabel* notRevisedYetFiles{};



    QPushButton* reviseButton;*/
public:
    TabsGUI( std::string name,  std::string thematicArea, EthnologistService& es, BuildingService &bs) : name(std::move(name)), thematicArea(std::move(thematicArea)), es(es), bs(bs) {
        this->bs.addObserver(this);
        guiInit();
        update();
    }
    ~TabsGUI() {
        this->bs.removeObserver(this);
    }
    void update() override {this->modelList->updateModel();};
    void guiInit();
    //void addHandler();
    //void reviseHandler();

    //void changeStatus(const QModelIndex &index);
    void addHandler();
};
#endif //E2_913ALICEHINCU_GUI_H
