//
// Created by Sakura on 6/22/2021.
//

#include <iostream>
#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    auto* er = new EthnologistRepo{"ethnologists.txt"};
    auto* br = new BuildingRepo{"buildings.txt"};
    EthnologistService es{ er };
    BuildingService bs{ br };
    GUI g(es, bs);
    g.show();
    return a.exec();

}