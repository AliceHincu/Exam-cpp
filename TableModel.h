//
// Created by Sakura on 6/22/2021.
//

#ifndef E2_913ALICEHINCU_TABLEMODEL_H
#define E2_913ALICEHINCU_TABLEMODEL_H


#pragma once
#include "Service.h"
#include <QtCore/qabstractitemmodel.h>

#include <utility>

class TableModel : public QAbstractTableModel
{
private:
    BuildingService& serv;
    std::string ethnologistThematicArea;

public:
    TableModel(BuildingService& r, std::string name, QObject* parent = nullptr) : QAbstractTableModel{ parent }, serv{ r }, ethnologistThematicArea(std::move(name)) {};

    // number of rows
    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

    // number of columns
    int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

    // Value at a given position
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // add header data
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void updateModel() { beginResetModel(); endResetModel(); }

    // used to set certain properties of a cell
    Qt::ItemFlags flags(const QModelIndex& index) const override;
};;


#endif //E2_913ALICEHINCU_TABLEMODEL_H
